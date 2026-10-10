"""Run: python3 tests/test_fuerza_bruta.py (requires clang++ or g++)."""
import itertools
from pathlib import Path
import random
import re
import shutil
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]
REPO = ROOT.parents[1]
SOURCE = REPO / 'laboratorios/laboratorio-01/2024-1/material_original/variantes/2024-2/LAB1/Viernes 13／09/Copia de P1.cpp'
DATA = REPO / 'laboratorios/laboratorio-01/2024-1/material_original/variantes/2024-2/LAB1/Viernes 13／09/Copia de datos1.txt'


def encode_data(warriors, weapons):
    lines = [str(len(warriors))]
    for power, types in warriors:
        lines.append(f"{power} {len(types)} " + " ".join(map(str, types)))
    lines.append(str(len(weapons)))
    for name, power, kind, dependencies in weapons:
        lines.append(f"{name} {power} {kind} {len(dependencies)} " + " ".join(dependencies))
    return "\n".join(lines) + "\n"


def oracle(warriors, weapons):
    """Independent Cartesian product: validate whole bags, not C++ loop order."""
    for tested, owners in enumerate(
        itertools.product(range(len(warriors) + 1), repeat=len(weapons)), 1
    ):
        valid = True
        for g, (power, types) in enumerate(warriors, 1):
            bag = [weapon for i, weapon in enumerate(weapons) if owners[i] == g]
            ids = {weapon[0] for weapon in bag}
            if sum(weapon[1] for weapon in bag) <= power:
                valid = False
            if any(weapon[2] not in types for weapon in bag):
                valid = False
            if any(not set(weapon[3]).issubset(ids) for weapon in bag):
                valid = False
        if valid:
            return owners, tested
    return None, (len(warriors) + 1) ** len(weapons)


class FuerzaBrutaTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        compiler = shutil.which("clang++") or shutil.which("g++")
        if not compiler:
            raise unittest.SkipTest("A C++ compiler is required")
        cls.temp = tempfile.TemporaryDirectory(prefix="po-fuerza-bruta-")
        cls.work = Path(cls.temp.name)
        cls.binary = cls.work / "po"
        subprocess.run(
            [compiler, "-std=c++17", "-O2", "-Wall", "-Wextra", "-Wpedantic",
             "-Werror", str(SOURCE), "-o", str(cls.binary)],
            check=True, capture_output=True, text=True,
        )

    @classmethod
    def tearDownClass(cls):
        cls.temp.cleanup()

    def run_data(self, data):
        file = self.work / "input.txt"
        file.write_text(data)
        return subprocess.run([str(self.binary), str(file)], cwd=self.work,
                              capture_output=True, text=True, timeout=15)

    def check_scenario(self, warriors, weapons):
        expected, tested = oracle(warriors, weapons)
        run = self.run_data(encode_data(warriors, weapons))
        self.assertEqual(run.returncode, 0, run.stderr + run.stdout)
        self.assertIn(f"Asignaciones probadas: {tested}\n", run.stdout)
        self.assertIn(f"Asignaciones posibles: {(len(warriors) + 1) ** len(weapons)}\n", run.stdout)
        if expected is None:
            self.assertIn("No existe una solucion", run.stdout)
        else:
            bags = re.findall(r"Armas en mochila para vencerlo: ([^\n]*)", run.stdout)
            self.assertEqual([bag.split() for bag in bags], [
                [weapon[0] for i, weapon in enumerate(weapons) if expected[i] == g]
                for g in range(1, len(warriors) + 1)
            ])

    def test_lab_example(self):
        run = self.run_data((DATA).read_text())
        self.assertEqual(run.returncode, 0, run.stderr)
        bags = re.findall(r"Armas en mochila para vencerlo: ([^\n]*)", run.stdout)
        self.assertEqual([bag.split() for bag in bags], [["R", "I", "J"], ["Z", "P", "K"], ["G", "L"]])
        self.assertIn("Poder de la mochila: 142", run.stdout)
        self.assertIn("Poder de la mochila: 176", run.stdout)
        self.assertIn("Poder de la mochila: 122", run.stdout)
        self.assertIn("Asignaciones probadas: 10751068\n", run.stdout)
        self.assertIn("Asignaciones posibles: 16777216\n", run.stdout)

    def test_strict_power_and_no_solution(self):
        self.check_scenario([(10, [1])], [("A", 10, 1, [])])
        self.check_scenario([(10, [1])], [("A", 11, 1, [])])
        self.check_scenario([(0, [1])], [])
        self.check_scenario([(100, [1])], [("A", 10, 1, []), ("B", 20, 1, [])])

    def test_prerequisites_types_and_exclusive_assignment(self):
        self.check_scenario([(9, [1]), (9, [1])], [("A", 20, 1, [])])
        self.check_scenario([(11, [1]), (9, [1])],
                            [("A", 7, 1, []), ("B", 7, 1, ["A"]), ("C", 10, 1, [])])
        self.check_scenario([(10, [2])], [("A", 100, 1, [])])
        self.check_scenario([(10, [1])], [("A", 10, 1, ["B"]), ("B", 1, 2, [])])

    def test_large_power_does_not_overflow(self):
        self.check_scenario([(2147483647, [1])],
                            [("A", 2147483647, 1, []), ("B", 1, 1, [])])

    def test_variable_cases_against_independent_oracle(self):
        rng = random.Random(2024)
        for case in range(45):
            count = 1 + case % 3
            warriors = [(rng.randrange(0, 30), sorted(rng.sample([1, 2, 3], rng.randrange(1, 4))))
                        for _ in range(count)]
            weapons = []
            for i in range(case % 6):
                dependencies = [chr(65 + rng.randrange(i))] if i and rng.random() < .3 else []
                weapons.append((chr(65 + i), rng.randrange(1, 20), rng.randrange(1, 4), dependencies))
            with self.subTest(case=case):
                self.check_scenario(warriors, weapons)

    def test_invalid_input_fails_cleanly(self):
        cases = ["", "4\n", "1\n10 4\n", "1\n10 1 1\n13\n",
                 "1\n10 1 1\n1\nA 20 1 4\n",
                 "1\n10 1 1\n1\nA 20 1 1 Z\n",
                 "1\n10 1 1\n2\nA 20 1 0\nA 20 1 0\n",
                 "1\n10 1 1\n1\nA -1 1 0\n"]
        for data in cases:
            with self.subTest(data=data):
                run = self.run_data(data)
                self.assertEqual(run.returncode, 1)
                self.assertNotIn("Asignaciones probadas", run.stdout)

    def test_existing_lab_filename_fallback(self):
        data = encode_data([(1, [1])], [("A", 2, 1, [])])
        (self.work / "Copia de datos1.txt").write_text(data)
        run = subprocess.run([str(self.binary)], cwd=self.work, capture_output=True, text=True)
        self.assertEqual(run.returncode, 0)
        self.assertIn("Armas en mochila para vencerlo: A", run.stdout)
        (self.work / "Copia de datos1.txt").unlink()

    def test_missing_file(self):
        run = subprocess.run([str(self.binary), "does-not-exist.txt"], cwd=self.work,
                             capture_output=True, text=True)
        self.assertEqual(run.returncode, 1)
        self.assertIn("No se puede abrir", run.stdout)

    def test_function_calls_have_no_recursion(self):
        source = re.sub(r"//[^\n]*|/\*.*?\*/", "", (SOURCE).read_text(), flags=re.S)
        bodies = {}
        for match in re.finditer(r"\b(?:int|void|bool)\s+(\w+)\s*\([^;{}]*\)\s*\{", source):
            start = position = match.end()
            depth = 1
            while depth:
                if source[position] == "{":
                    depth += 1
                elif source[position] == "}":
                    depth -= 1
                position += 1
            bodies[match.group(1)] = source[start:position - 1]
        self.assertIn("encontrarSolucionFuerzaBruta", bodies)
        graph = {name: {other for other in bodies if re.search(r"\b" + other + r"\s*\(", body)}
                 for name, body in bodies.items()}
        remaining = set(graph)
        while remaining:
            leaves = {name for name in remaining if not graph[name].intersection(remaining)}
            self.assertTrue(leaves, "Direct or indirect recursive call detected")
            remaining -= leaves


if __name__ == "__main__":
    unittest.main(verbosity=2)
