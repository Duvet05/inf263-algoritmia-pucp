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
        stack = "biblioteca/pilas/FuncionesPila.cpp"
        sources = {
            "biblioteca": ["tests/test_funciones_lista.cpp", library],
            "cuadrigas_casos": ["tests/test_cuadrigas.cpp"],
            "barajado_casos": ["tests/test_barajado.cpp"],
            "ejemplo": ["ejemplos/uso_lista.cpp", library],
            "pila": ["tests/test_funciones_pila.cpp", stack, library],
            "hanoi": ["ejemplos/torres_de_hanoi.cpp", stack, library],
            "bad_sunny_casos": ["tests/test_bad_sunny.cpp", stack, library],
            "bad_sunny": ["soluciones/2022_2_ex01_p02_bad_sunny.cpp", stack, library],
            "nautilus_casos": ["tests/test_nautilus.cpp"],
            "nautilus": ["soluciones/2024_1_ex01_p02_nautilus.cpp"],
            "tortuninjas_casos": ["tests/test_tortuninjas.cpp"],
            "tortuninjas": ["soluciones/2023_2_ex01_p01_tortuninjas.cpp"],
            "incidentes_casos": ["tests/test_incidentes.cpp"],
            "incidentes": ["soluciones/2023_2_ex01_p02_incidentes.cpp"],
            "cuadrigas": ["soluciones/2025_1_lab02_p01_cuadrigas.cpp"],
            "barajado": ["soluciones/2026_1_lab02_p01_barajado.cpp"],
        }
        cls.binaries = {}
        for name, files in sources.items():
            binary = Path(cls.temp.name) / name
            subprocess.run(flags + [str(ROOT / file) for file in files] + ["-o", str(binary)],
                           check=True, timeout=60)
            cls.binaries[name] = binary

    def ejecutar(self, name, *args, entrada=None):
        result = subprocess.run([str(self.binaries[name]), *args], input=entrada, capture_output=True,
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

    def test_pila_lifo_y_traslado_de_nodos(self):
        self.ejecutar("pila")

    def test_hanoi_recursivo_e_iterativo(self):
        output = self.ejecutar("hanoi")
        self.assertEqual(output.count("Total: 7 movimientos"), 2)
        self.assertEqual(re.findall(r"^\d+\. Mover disco (\d) de ([ABC]) a ([ABC])$", output, re.M)[:7],
                         [("1", "A", "C"), ("2", "A", "B"), ("1", "C", "B"), ("3", "A", "C"),
                          ("1", "B", "A"), ("2", "B", "C"), ("1", "A", "C")])
        self.assertIn("ambos metodos correctos", output)
        self.assertIn("Total: 1048575 movimientos", self.ejecutar("hanoi", "20"))

    def test_bad_sunny_contra_fuerza_bruta(self):
        self.ejecutar("bad_sunny_casos")

    def test_ejemplo_bad_sunny(self):
        output = self.ejecutar("bad_sunny")
        self.assertIn("Frecuencia maxima = 4 Duracion = 5 (tiempos 4 a 8)", output)
        self.assertIn("Frecuencia maxima = 3 Duracion = 6 (tiempos 1 a 6)", output)
        corregidas = re.findall(r"^\s+\d+\s+\d+\s+(\d+)$", output.split("\n\n")[0], re.M)
        self.assertEqual(corregidas, ["1", "2", "1", "4", "4", "4", "4", "4", "2", "2", "1"])

    def test_nautilus_ejemplos_del_enunciado(self):
        self.assertEqual(self.ejecutar("nautilus"), (
            "1 2 3 5 4 6\n"
            "3 2 1 4\n"
            "1 3 2 6 5 4 7 8\n"
        ))

    def test_nautilus_ordenes_y_limites(self):
        self.ejecutar("nautilus_casos")

    def test_tortuninjas_ejemplo_del_enunciado(self):
        entrada = (ROOT / "tests/datos/tortuninjas-ejemplo.txt").read_text()
        output = self.ejecutar("tortuninjas", entrada=entrada)
        self.assertIn("Las TortuNinjas completaron su mision.", output)
        self.assertIn("Leonardo: 8 6 9 5 3\n", output)
        self.assertIn("Rafael: 15 9\n", output)
        self.assertIn("Donatello: 3 6\n", output)
        self.assertIn("Miguel Angel: 1 6 8 4 6\n", output)

    def test_tortuninjas_sin_solucion(self):
        entrada = "5\n1 1 1 1\n2 0\n2 0\n2 0\n2 0\n2 0\n"
        output = self.ejecutar("tortuninjas", entrada=entrada)
        self.assertIn("no pueden completar la mision", output)

    def test_tortuninjas_ingreso_variable_y_limites(self):
        for cantidad in range(5, 9):
            entrada = f"{cantidad}\n2 2 2 2\n" + "1 0\n" * cantidad
            self.assertIn("completaron su mision", self.ejecutar("tortuninjas", entrada=entrada))
        for entrada in ("4\n", "5\n1 1 1 1\n1 0\n-1\n"):
            result = subprocess.run([str(self.binaries["tortuninjas"])], input=entrada,
                                    capture_output=True, text=True, timeout=10)
            self.assertEqual(result.returncode, 1)
            self.assertTrue(result.stderr)

    def test_tortuninjas_reparto_y_conservacion_de_nodos(self):
        self.ejecutar("tortuninjas_casos")

    def test_incidentes_ejemplo_del_enunciado(self):
        self.assertEqual(self.ejecutar("incidentes"), (
            "INICIAL:\n"
            "Cola: 206 107 208 109 210 211 112 113\n"
            "Pila 1: 105 102 101\n"
            "Pila 2: 204 203\n\n"
            "REINICIA COLA:\n"
            "Cola: 101 102 203 204 105 206 107 208\n"
            "Pila 1: vacia\n"
            "Pila 2: 113 112 211 210 109\n\n"
            "RECLASIFICA PILAS:\n"
            "Cola: 101 102 203 204 105 206 107 208\n"
            "Pila 1: 210 211\n"
            "Pila 2: 109 112 113\n\n"
        ))

    def test_incidentes_capacidad_orden_y_conservacion_de_nodos(self):
        self.ejecutar("incidentes_casos")

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
