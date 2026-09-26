"""Compila y verifica las soluciones recientes sin generar artefactos en el repo."""

from pathlib import Path
import shutil
import subprocess
import sys
import tempfile


ROOT = Path(__file__).resolve().parents[1]
ACTUAL = ROOT / "soluciones-actuales"


def ejecutar(*args, cwd=ROOT):
    result = subprocess.run(args, cwd=cwd, capture_output=True,
                            text=True, timeout=120)
    if result.returncode != 0:
        raise RuntimeError(
            f"Falló {' '.join(map(str, args))}\n{result.stdout}{result.stderr}"
        )
    return result.stdout


def compilar(compiler, source, binary):
    ejecutar(compiler, "-std=c++17", "-Wall", "-Wextra", "-Wpedantic",
            "-Werror", str(source), "-o", str(binary))


def comprobar_salida(compiler, temp):
    samples = [
        (ACTUAL / "2026_1_lab01/2026_1_lab01_p01_arqueologo.cpp",
         "El robot encontro 4 artefactos"),
        (ACTUAL / "2026_1_lab01/2026_1_lab01_p02_citas.cpp",
         "La ganancia maxima es: 437"),
        (ACTUAL / "04_listas_pilas_colas/soluciones/2026_1_lab02_p02_canarios.cpp",
         "6"),
        (ACTUAL / "04_listas_pilas_colas/soluciones/2026_1_lab02_lista_enlazada.cpp",
         "10 -> 15 -> nullptr"),
    ]
    for i, (source, expected) in enumerate(samples):
        binary = temp / f"programa_{i}"
        compilar(compiler, source, binary)
        result = ejecutar(str(binary))
        if expected not in result:
            raise AssertionError(f"Salida inesperada en {source}: {result!r}")
        print(f"OK {source.relative_to(ROOT)}")


def main():
    compiler = shutil.which("clang++") or shutil.which("g++")
    if not compiler:
        raise RuntimeError("Se necesita clang++ o g++ con soporte C++17.")
    checks = [
        ACTUAL / "2024_1_lab01_po/test_p1.py",
        ACTUAL / "04_listas_pilas_colas/tests/test_listas.py",
        ACTUAL / "04_listas_pilas_colas/robotjardin_2025_2/tests/test_robotjardin.py",
    ]
    for test in checks:
        ejecutar(sys.executable, str(test))
        print(f"OK {test.relative_to(ROOT)}")
    with tempfile.TemporaryDirectory(prefix="inf263-actuales-") as folder:
        comprobar_salida(compiler, Path(folder))
    print("Todas las soluciones actuales verificadas.")


if __name__ == "__main__":
    main()
