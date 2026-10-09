"""Verifica el catalogo, sus enlaces y el seguimiento de TortuNinjas."""
from pathlib import Path
from hashlib import sha256
from html.parser import HTMLParser
from urllib.parse import unquote, urlsplit
import csv
import json
import re
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]

def local_link(source, target):
    target = target.strip("<>")
    parts = urlsplit(target)
    if parts.scheme or target.startswith("#") or not parts.path: return
    path = (source.parent / unquote(parts.path)).resolve()
    assert path.is_relative_to(ROOT), f"Enlace fuera del repositorio: {source}: {target}"
    assert path.exists(), f"Enlace roto: {source.relative_to(ROOT)} -> {target}"

class Links(HTMLParser):
    def __init__(self, source):
        super().__init__()
        self.source = source
    def handle_starttag(self, tag, attrs):
        for name, target in attrs:
            if name in {"href","src"} and target: local_link(self.source,target)

def verify_trace():
    root = ROOT / "clases/tortuninjas"
    with (root / "seguimiento-ejemplo.csv").open(encoding="utf-8",newline="") as file:
        reader = csv.DictReader(file,delimiter=";")
        headers = reader.fieldnames
        rows = list(reader)
    capacities = {"Leonardo":34,"Rafael":24,"Donatello":12,"Miguel Angel":30}
    weights = {1:17,2:24,3:9,4:25,5:14}
    loads = dict.fromkeys(capacities,0)
    owners = {}
    for step, row in enumerate(rows,1):
        ninja = row["Ninja"]
        truck = int(row["Camion"])
        weight = weights[truck]
        count = sum(owner == ninja for owner in owners.values())
        assert int(row["Paso"]) == step
        assert int(row["Peso"]) == weight
        assert int(row["Capacidad"]) == capacities[ninja]
        assert int(row["Carga antes"]) == loads[ninja]
        assert int(row["Camiones antes"]) == count
        action = row["Accion"]
        if action == "Asignar":
            assert truck not in owners and count < 2
            assert loads[ninja] + weight <= capacities[ninja]
            owners[truck] = ninja
            loads[ninja] += weight
        elif action == "Deshacer":
            assert owners.pop(truck) == ninja
            loads[ninja] -= weight
        else:
            assert action == "Rechazar"
            assert count == 2 or loads[ninja] + weight > capacities[ninja]
        assert int(row["Carga despues"]) == loads[ninja]
    assert owners == {1:"Leonardo",2:"Rafael",3:"Donatello",4:"Miguel Angel",5:"Leonardo"}
    with (root / "seguimiento-plantilla.csv").open(encoding="utf-8",newline="") as file:
        template = csv.DictReader(file,delimiter=";")
        assert template.fieldnames == headers
        assert all(not value for row in template for key,value in row.items() if key != "Paso")
    print(f"OK: seguimiento de {len(rows)} pasos y plantilla Excel")

def main():
    docs = json.loads((ROOT / "catalogo/documentos.json").read_text(encoding="utf-8"))
    paths = set()
    digests = set()
    for doc in docs:
        if not doc["ruta"]:
            assert doc["tipo"] == "Archivo vacío"
            continue
        path = ROOT / doc["ruta"]
        assert path.is_file() and path.read_bytes().startswith(b"%PDF-"), doc["ruta"]
        assert doc["ruta"] not in paths and doc["sha256"] not in digests, "PDF duplicado en el catalogo"
        assert sha256(path.read_bytes()).hexdigest() == doc["sha256"], doc["ruta"]
        paths.add(doc["ruta"])
        digests.add(doc["sha256"])
        for material in doc.get("material", []): assert (ROOT / material).is_dir(), material
        for solution in doc.get("soluciones", []): assert (ROOT / solution["ruta"]).is_file(), solution
    manifest = {}
    for line in (ROOT / "catalogo/checksums.sha256").read_text().splitlines():
        digest, path = line.split(maxsplit=1)
        assert path not in manifest
        manifest[path] = digest
    assert manifest == {d["ruta"]:d["sha256"] for d in docs if d["ruta"]}
    for source in ROOT.rglob("*.md"):
        if ".git" in source.parts: continue
        for target in re.findall(r"\]\(([^)]+)\)",source.read_text(encoding="utf-8")):
            local_link(source,target)
    for source in [ROOT / "catalogo/index.html", ROOT / "soluciones-actuales/04_listas_pilas_colas/robotjardin_2025_2/index.html"]:
        Links(source).feed(source.read_text(encoding="utf-8"))
    result = subprocess.run([sys.executable,str(ROOT/"scripts/generar_catalogo.py"),"--check"],capture_output=True,text=True,timeout=30)
    assert result.returncode == 0, result.stdout + result.stderr
    print(result.stdout,end="")
    verify_trace()
    subprocess.run(["node",str(ROOT / "scripts/verificar_catalogo_visual.cjs")],check=True,timeout=30)
    print(f"OK: {len(paths)} PDF unicos, SHA-256 y enlaces internos")

if __name__ == "__main__":
    main()
