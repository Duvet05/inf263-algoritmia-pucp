"""Verifica enlaces e integridad de los enunciados del índice de laboratorios."""

from hashlib import sha256
from pathlib import Path
import re


ROOT = Path(__file__).resolve().parents[1]
INDEX = ROOT / "laboratorios/README.md"
CHECKSUMS = ROOT / "laboratorios/checksums.sha256"


def ruta_local(destino):
    path = (INDEX.parent / destino.split("#", 1)[0]).resolve()
    if not path.is_relative_to(ROOT):
        raise AssertionError(f"Enlace fuera del repositorio: {destino}")
    if not path.exists():
        raise AssertionError(f"Enlace roto: {destino}")
    return path


def main():
    content = INDEX.read_text(encoding="utf-8")
    for destino in re.findall(r"\]\(([^)]+)\)", content):
        if destino.startswith(("http://", "https://", "#")):
            continue
        ruta_local(destino)

    pdfs = {
        ruta_local(destino).relative_to(ROOT)
        for destino in re.findall(r"\[PDF\]\(([^)]+)\)", content)
    }
    if len(pdfs) < 19:
        raise AssertionError(f"Se esperaban al menos 19 laboratorios; hay {len(pdfs)}")

    manifest = {}
    for line in CHECKSUMS.read_text(encoding="utf-8").splitlines():
        digest, filename = line.split(maxsplit=1)
        path = Path(filename)
        if path in manifest:
            raise AssertionError(f"PDF repetido en checksums: {path}")
        manifest[path] = digest
    if set(manifest) != pdfs:
        raise AssertionError("El índice y checksums.sha256 enumeran PDF diferentes")

    for relative, expected in manifest.items():
        path = ROOT / relative
        if not path.is_file() or path.open("rb").read(5) != b"%PDF-":
            raise AssertionError(f"PDF inválido: {relative}")
        if sha256(path.read_bytes()).hexdigest() != expected:
            raise AssertionError(f"PDF alterado: {relative}")

    for destino in re.findall(r"\[(?:Fuentes[^]]*|Fuente)\]\(([^)]+)\)", content):
        folder = ruta_local(destino)
        if not folder.is_dir() or not any(folder.rglob("*.cpp")):
            raise AssertionError(f"Falta código de origen en {destino}")

    print(f"OK: {len(pdfs)} enunciados PDF, enlaces y material de origen")


if __name__ == "__main__":
    main()
