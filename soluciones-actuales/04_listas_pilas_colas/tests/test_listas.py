"""Compila y verifica la biblioteca y las soluciones; no deja binarios en el proyecto."""
import os
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]


class ListasTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.temp = tempfile.TemporaryDirectory(prefix="pruebas-listas-")
        cls.addClassCleanup(cls.temp.cleanup)
        compiler = shutil.which("clang++") or shutil.which("g++")
        if not compiler:
            raise RuntimeError("Se necesita un compilador C++17 (clang++ o g++).")
        flags = [compiler, "-std=c++17", "-Wall", "-Wextra", "-Wpedantic", "-Werror"]
        if os.environ.get("LISTAS_SANITIZERS") == "1":
            flags += ["-g", "-fsanitize=address,undefined", "-fno-omit-frame-pointer"]
        library = "biblioteca/listas/FuncionesLista.cpp"
        sources = {
            "biblioteca": ["tests/test_funciones_lista.cpp", library],
            "cuadrigas_casos": ["tests/test_cuadrigas.cpp"],
            "barajado_casos": ["tests/test_barajado.cpp"],
            "ejemplo": ["ejemplos/uso_lista.cpp", library],
            "cuadrigas": ["soluciones/2025_1_lab02_p01_cuadrigas.cpp"],
            "barajado": ["soluciones/2026_1_lab02_p01_barajado.cpp"],
        }
        cls.binaries = {}
        for name, files in sources.items():
            binary = Path(cls.temp.name) / name
            subprocess.run(flags + [str(ROOT / file) for file in files] + ["-o", str(binary)],
                           check=True, timeout=60)
            cls.binaries[name] = binary

    def ejecutar(self, name):
        result = subprocess.run([str(self.binaries[name])], capture_output=True,
                                text=True, timeout=30)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        return result.stdout

    def test_biblioteca_limites_transferencia_y_5000_operaciones(self):
        self.ejecutar("biblioteca")

    def test_cuadrigas_orden_estable_y_mismos_nodos(self):
        self.ejecutar("cuadrigas_casos")

    def test_barajado_conserva_cartas_y_nodos(self):
        self.ejecutar("barajado_casos")

    def test_ejemplo_biblioteca(self):
        self.assertEqual(self.ejecutar("ejemplo"), (
            "Lista inicial: 10 -> 15 -> 20 -> nullptr\n"
            "Encontrado: 15\n"
            "Primero al final: 15 -> 20 -> 10 -> nullptr\n"
            "Tras eliminar 20 e invertir: 10 -> 15 -> nullptr\n"
            "Longitud final: 0\n"
        ))

    def test_ejemplo_cuadrigas(self):
        output = self.ejecutar("cuadrigas")
        self.assertEqual(re.findall(r"ID: (-?\d+)", output),
                         ["17", "4", "12", "7", "4", "12", "17", "7"])

    def test_ejemplo_barajado(self):
        output = self.ejecutar("barajado")
        original, shuffled = output.split("BARAJA BARAJADA")
        expected = {f"{number}{suit}" for suit in "CDTE" for number in range(1, 14)}
        for section in (original, shuffled):
            cards = re.findall(r"\b\d+[CDTE]\b", section)
            self.assertEqual(len(cards), 52)
            self.assertEqual(set(cards), expected)
        self.assertIn("Longitud final: 0", shuffled)


if __name__ == "__main__":
    unittest.main(verbosity=2)
