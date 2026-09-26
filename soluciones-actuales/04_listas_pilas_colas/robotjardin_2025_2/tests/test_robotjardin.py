"""Verifica C++, visualización y rectángulos contra enumeración exhaustiva."""
import itertools
import json
from pathlib import Path
import random
import re
import shutil
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]
EXAMPLES = [
    [[1, 1, 1, 0], [1, 1, 1, 0], [1, 0, 1, 1], [1, 1, 0, 0]],
    [[1, 1, 1, 0, 0], [1, 1, 1, 1, 1], [1, 1, 1, 1, 1], [1, 1, 0, 0, 0]],
]


def oracle(matrix):
    """Enumera todos los rectángulos usando sumas de la matriz, sin pilas."""
    n, m = len(matrix), len(matrix[0])
    prefix = [[0] * (m + 1) for _ in range(n + 1)]
    for row in range(n):
        for col in range(m):
            prefix[row + 1][col + 1] = (
                matrix[row][col] + prefix[row][col + 1]
                + prefix[row + 1][col] - prefix[row][col]
            )
    best = 0
    for top in range(n):
        for bottom in range(top + 1, n + 1):
            for left in range(m):
                for right in range(left + 1, m + 1):
                    area = (bottom - top) * (right - left)
                    ones = (prefix[bottom][right] - prefix[top][right]
                            - prefix[bottom][left] + prefix[top][left])
                    if ones == area:
                        best = max(best, area)
    return best


class RobotJardinTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.temp = tempfile.TemporaryDirectory(prefix="robotjardin-")
        cls.addClassCleanup(cls.temp.cleanup)
        folder = Path(cls.temp.name)
        compiler = shutil.which("clang++") or shutil.which("g++")
        if not compiler or not shutil.which("node"):
            raise RuntimeError("Se necesita un compilador C++ y Node.js.")
        flags = [compiler, "-std=c++17", "-O2", "-Wall", "-Wextra", "-Wpedantic", "-Werror"]
        cls.demo = folder / "robotjardin"
        subprocess.run(flags + [str(ROOT / "../soluciones/2025_2_ex01_p04_robotjardin.cpp"), "-o", str(cls.demo)], check=True, capture_output=True, text=True)
        harness = folder / "harness.cpp"
        harness.write_text('''#define main mainEjemplos
#include "../soluciones/2025_2_ex01_p04_robotjardin.cpp"
#undef main
int main() {
    int casos;
    if (!(std::cin >> casos)) return 1;
    while (casos--) {
        int n, m;
        if (!(std::cin >> n >> m) || n < 0 || n > 20 || m < 0 || m > MAX_COLUMNAS) return 2;
        int jardin[20][MAX_COLUMNAS]{};
        int original[20][MAX_COLUMNAS]{}; // Solo la prueba conserva una copia.
        for (int fila = 0; fila < n; fila++) {
            for (int col = 0; col < m; col++) {
                if (!(std::cin >> jardin[fila][col])) return 3;
                original[fila][col] = jardin[fila][col];
            }
        }
        Rectangulo r = calcularAreaMaxima(jardin, n, m);
        for (int fila = 0; fila < 20; fila++) {
            for (int col = 0; col < MAX_COLUMNAS; col++) {
                if (jardin[fila][col] != original[fila][col]) return 4;
            }
        }
        std::cout << r.area << ' ' << r.filaInicio << ' ' << r.filaFin << ' '
                  << r.columnaInicio << ' ' << r.columnaFin << '\\n';
    }
}
''')
        cls.binary = folder / "harness"
        subprocess.run(flags + ["-I", str(ROOT), str(harness), "-o", str(cls.binary)], check=True, capture_output=True, text=True)

    def solve_cpp(self, matrices):
        lines = [str(len(matrices))]
        for matrix in matrices:
            lines.append(f"{len(matrix)} {len(matrix[0]) if matrix else 0}")
            lines.extend(" ".join(map(str, row)) for row in matrix)
        result = subprocess.run([str(self.binary)], input="\n".join(lines), text=True,
                                capture_output=True, check=True, timeout=20)
        results = [tuple(map(int, line.split())) for line in result.stdout.splitlines()]
        self.assertEqual(len(results), len(matrices))
        return results

    def test_examples_and_executable(self):
        self.assertEqual(self.solve_cpp(EXAMPLES), [(6, 0, 1, 0, 2), (10, 1, 2, 0, 4)])
        output = subprocess.run([str(self.demo)], capture_output=True, text=True, check=True).stdout
        self.assertEqual(re.findall(r"Area maxima: (\d+)", output), ["6", "10"])

    def test_empty_dimensions(self):
        self.assertEqual(self.solve_cpp([[], [[]]]), [(0, -1, -1, -1, -1)] * 2)

    def test_cpp_and_visual_against_oracle(self):
        matrices = list(EXAMPLES)
        for n, m in itertools.chain(itertools.product(range(1, 4), repeat=2), [(3, 4)]):
            for bits in itertools.product((0, 1), repeat=n * m):
                matrices.append([list(bits[row * m:(row + 1) * m]) for row in range(n)])
        rng = random.Random(42)
        for _ in range(100):
            n, m = rng.randint(1, 8), rng.randint(1, 8)
            matrices.append([[rng.randrange(2) for _ in range(m)] for _ in range(n)])
        matrices.extend([
            [[0] * 20 for _ in range(20)],
            [[1] * 20 for _ in range(20)],
            [[1] * 100],
            [[1] for _ in range(20)],
            [[1, 0, 1, 1, 0, 1, 1, 1]],
        ])
        cpp = self.solve_cpp(matrices)
        visual = subprocess.run(
            ["node", str(ROOT / "tests" / "verificar_visual.cjs")],
            input=json.dumps(matrices), text=True, capture_output=True, check=True, timeout=30,
        )
        visual_results = json.loads(visual.stdout)
        self.assertEqual(len(visual_results), len(matrices))
        for matrix, result, shown in zip(matrices, cpp, visual_results):
            with self.subTest(matrix=matrix):
                self.assertEqual(result[0], oracle(matrix))
                self.assertEqual(result, (
                    shown["area"], shown["filaInicio"], shown["filaFin"],
                    shown["columnaInicio"], shown["columnaFin"],
                ))
        print(f"\n{len(matrices)} matrices: C++, HTML y búsqueda exhaustiva coinciden.")

    def test_no_recursive_function_calls(self):
        source = (ROOT / "../soluciones/2025_2_ex01_p04_robotjardin.cpp").read_text()
        source = re.sub(r"//[^\n]*|/\*[\s\S]*?\*/", "", source)
        bodies = {}
        for match in re.finditer(r"^(?:bool|int|void|Rectangulo)\s+(\w+)\([^)]*\)\s*\{", source, re.M):
            start, depth, end = match.end(), 1, match.end()
            while depth:
                depth += (source[end] == "{") - (source[end] == "}")
                end += 1
            bodies[match.group(1)] = source[start:end - 1]
        self.assertIn("calcularAreaMaxima", bodies)
        edges = {name: {other for other in bodies if re.search(r"\b" + other + r"\s*\(", body)}
                 for name, body in bodies.items()}
        while edges:
            leaves = {name for name, calls in edges.items() if not calls}
            self.assertTrue(leaves, f"Se encontró un ciclo de llamadas: {edges}")
            edges = {name: calls - leaves for name, calls in edges.items() if name not in leaves}


if __name__ == "__main__":
    unittest.main(verbosity=2)
