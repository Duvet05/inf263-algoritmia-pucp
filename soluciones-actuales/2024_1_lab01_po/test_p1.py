import itertools
from pathlib import Path
import random
import re
import shutil
import subprocess
import tempfile
import unittest


PROJECT = Path(__file__).resolve().parent


def valid_assignment(assignment, warriors, weapons):
    """Check the statement by constructing each warrior's complete backpack."""
    for number, (required_power, allowed_types) in enumerate(warriors, 1):
        backpack = [weapon for owner, weapon in zip(assignment, weapons) if owner == number]
        ids = {weapon[0] for weapon in backpack}
        if sum(weapon[1] for weapon in backpack) <= required_power:
            return False
        if any(weapon[2] not in allowed_types for weapon in backpack):
            return False
        if any(not set(weapon[3]).issubset(ids) for weapon in backpack):
            return False
    return True


def encode(warriors, weapons):
    lines = [str(len(warriors))]
    for power, types in warriors:
        lines.append(' '.join(map(str, [power, len(types), *types])))
    lines.append(str(len(weapons)))
    for name, power, kind, requirements in weapons:
        lines.append(' '.join(map(str, [name, power, kind, len(requirements), *requirements])))
    return '\n'.join(lines) + '\n'


class FuerzaBrutaTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.temp = tempfile.TemporaryDirectory(prefix='po-p1-tests-')
        cls.addClassCleanup(cls.temp.cleanup)
        cls.binary = Path(cls.temp.name) / 'p1'
        compiler = shutil.which('clang++') or shutil.which('g++')
        if not compiler:
            raise RuntimeError('Se necesita un compilador C++17 (clang++ o g++).')
        subprocess.run([
            compiler, '-std=c++17', '-O2', '-Wall', '-Wextra', '-Wpedantic',
            '-Werror', str(PROJECT / '2024_1_lab01_p01_po.cpp'), '-o', str(cls.binary),
        ], check=True, capture_output=True, text=True)

    def run_case(self, warriors, weapons, expected=None):
        data = Path(self.temp.name) / 'case.txt'
        data.write_text(encode(warriors, weapons))
        result = subprocess.run([str(self.binary), str(data)], capture_output=True,
                                text=True, timeout=30, check=True)
        if expected is None:
            expected = any(valid_assignment(a, warriors, weapons) for a in
                           itertools.product(range(len(warriors) + 1), repeat=len(weapons)))
        if not expected:
            self.assertIn('No existe una solucion', result.stdout)
            return
        blocks = re.findall(
            r'Guerrero (\d+)\nPoder del guerrero: (\d+)\n'
            r'Armas en mochila para vencerlo:([^\n]*)\nPoder reunido: (\d+)',
            result.stdout,
        )
        self.assertEqual(len(blocks), len(warriors), result.stdout)
        assignment = [0] * len(weapons)
        indexes = {weapon[0]: i for i, weapon in enumerate(weapons)}
        seen = set()
        self.assertEqual({int(b[0]) for b in blocks}, set(range(1, len(warriors) + 1)))
        for owner, required, names, reported_power in blocks:
            power = 0
            self.assertEqual(int(required), warriors[int(owner) - 1][0])
            for name in names.split():
                self.assertIn(name, indexes)
                self.assertNotIn(name, seen, 'An arm cannot be reused')
                seen.add(name)
                assignment[indexes[name]] = int(owner)
                power += weapons[indexes[name]][1]
            self.assertEqual(power, int(reported_power))
        self.assertTrue(valid_assignment(assignment, warriors, weapons), result.stdout)

    def test_pdf_example_and_default_file(self):
        warriors = [(120, [2]), (160, [1, 3]), (80, [3])]
        weapons = [
            ('Z', 60, 3, []), ('P', 80, 1, ['Z']), ('R', 38, 2, []),
            ('D', 25, 2, ['R']), ('E', 49, 2, []), ('F', 57, 1, []),
            ('G', 68, 3, []), ('H', 35, 2, ['Z', 'E']), ('I', 62, 2, ['R']),
            ('J', 42, 2, []), ('K', 36, 1, ['Z']), ('L', 54, 3, []),
        ]
        self.assertEqual((PROJECT / 'datos1.txt').read_text().split(), encode(warriors, weapons).split())
        self.run_case(warriors, weapons, True)
        result = subprocess.run([str(self.binary)], cwd=PROJECT, capture_output=True,
                                text=True, timeout=30, check=True)
        self.assertIn('Guerrero 3', result.stdout)

    def test_constraints(self):
        cases = [
            ('strict power', [(10, [1])], [('A', 10, 1, [])], False),
            ('enough power', [(10, [1])], [('A', 11, 1, [])], True),
            ('wrong type', [(10, [1])], [('A', 20, 2, [])], False),
            ('missing prerequisite', [(8, [1])], [('A', 9, 1, ['Z'])], False),
            ('same backpack', [(5, [1]), (5, [2])],
             [('A', 10, 1, ['B']), ('B', 10, 2, [])], False),
            ('no reuse', [(5, [1]), (5, [1])], [('A', 6, 1, [])], False),
            ('base three', [(5, [1]), (6, [2])],
             [('A', 6, 1, []), ('B', 7, 2, [])], True),
            ('unused arm', [(10, [1])], [('A', 11, 1, []), ('B', 1, 2, [])], True),
            ('dependency chain', [(10, [1])],
             [('A', 5, 1, ['B']), ('B', 5, 1, ['C']), ('C', 1, 1, [])], True),
            ('no arms', [(0, [1])], [], False),
        ]
        for name, warriors, weapons, expected in cases:
            with self.subTest(name=name):
                self.run_case(warriors, weapons, expected)

    def test_small_instances_against_independent_enumeration(self):
        rng = random.Random(20241)
        for case in range(30):
            warriors = [(rng.randint(0, 12), rng.sample([1, 2, 3], rng.randint(1, 3)))
                        for _ in range(rng.randint(1, 3))]
            ids = list('ABCDEF'[:rng.randint(1, 6)])
            weapons = [(name, rng.randint(1, 15), rng.randint(1, 3),
                        rng.sample([other for other in ids if other != name],
                                   rng.randint(0, min(2, len(ids) - 1)))) for name in ids]
            with self.subTest(case=case):
                self.run_case(warriors, weapons)

    def test_maximum_size_with_no_solution(self):
        self.run_case([(100, [1])] * 3,
                      [(name, 1, 1, []) for name in 'ABCDEFGHIJKL'], False)

    def test_input_errors(self):
        for content in ['4\n', '1\n10 4\n', '1\n10 1 1\n13\n', '1\n10 1 1\n1\nA 20 1 4\n']:
            with self.subTest(content=content):
                path = Path(self.temp.name) / 'bad.txt'
                path.write_text(content)
                result = subprocess.run([str(self.binary), str(path)], capture_output=True,
                                        text=True, timeout=5)
                self.assertEqual(result.returncode, 1)
                self.assertIn('Datos invalidos', result.stderr)
        result = subprocess.run([str(self.binary), str(Path(self.temp.name) / 'missing.txt')],
                                capture_output=True, text=True, timeout=5)
        self.assertEqual(result.returncode, 1)
        self.assertIn('No se pudo abrir', result.stderr)


if __name__ == '__main__':
    unittest.main()
