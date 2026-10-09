"""Genera los índices desde catalogo/documentos.json; --check no escribe."""
from pathlib import Path
from collections import Counter
import argparse
import html
import json
import os
from urllib.parse import quote

ROOT = Path(__file__).resolve().parents[1]
TOPICS = [
    ("01_recursion", "Recursión"), ("02_divide_y_venceras", "Divide y vencerás"),
    ("03_fuerza_bruta", "Fuerza bruta"), ("04_listas_pilas_colas", "Listas, pilas y colas"),
    ("05_arboles", "Árboles"), ("06_backtracking", "Backtracking"),
    ("07_programacion_dinamica", "Programación dinámica"), ("08_grafos", "Grafos"),
    ("09_material_de_apoyo", "Material de apoyo"),
]

def relative(path, parent):
    return quote(os.path.relpath(ROOT / path, ROOT / parent), safe="/._-")

def link(label, path, parent):
    return f"[{label}]({relative(path, parent)})"

def table(docs, parent):
    rows = ["| Ciclo | Material | Temas | Soluciones verificadas |",
            "| --- | --- | --- | --- |"]
    for doc in docs:
        title = link(doc["titulo"], doc["ruta"], parent) if doc["ruta"] else doc["titulo"] + " (vacío en origen)"
        solutions = " · ".join(link(s["nombre"], s["ruta"], parent) for s in doc.get("soluciones", [])) or "Pendiente"
        rows.append(f'| {doc["ciclo"]} | {title} | {"; ".join(doc["temas"])} | {solutions} |')
    return "\n".join(rows) + "\n"

def render(docs):
    docs = sorted(docs, key=lambda d: (d["ciclo"], d["tipo"], d["titulo"]))
    counts = Counter(d["tipo"] for d in docs if d["ruta"])
    intro = (f'{counts["Laboratorio"]} laboratorios, {counts["Examen"]} exámenes y '
             f'{counts["Teoría"] + counts["Ejercicios"]} documentos de teoría y ejercicios. '
             'El PDF vacío de origen se registra como incidencia. Cada enunciado tiene una sola ruta canónica.\n\n')
    outputs = {}
    outputs["catalogo/README.md"] = (
        "# Catálogo del curso\n\n[Inicio](../README.md) · [Catálogo con filtros](index.html) · "
        "[Por temas](../temas/README.md) · [Exámenes](../examenes/README.md) · "
        "[Laboratorios](../laboratorios/README.md) · [Videos](../material-de-apoyo/VIDEOS.md)\n\n"
        + intro + table(docs, "catalogo") +
        "\nLos enlaces de soluciones indican código con pruebas reproducibles. Los fuentes recibidos se conservan en "
        "\x60material_original/\x60 de su evaluación y se consultan desde el detalle de cada documento. "
        "La clasificación procede del enunciado, no del nombre de la carpeta donde se recibió.\n\n"
        "Fuente editable: [documentos.json](documentos.json). "
        "Regenera los índices con \x60python3 scripts/generar_catalogo.py\x60.\n")
    topics = ["# Estudiar por temas\n\n[Inicio](../README.md) · [Catálogo completo](../catalogo/README.md)\n\n",
              "| Tema | Documentos |\n| --- | --- |\n"]
    for slug, name in TOPICS:
        selected = [d for d in docs if name in d["temas"]]
        topics.append(f"| [{name}]({slug}/README.md) | {len(selected)} |\n")
        parent = f"temas/{slug}"
        outputs[parent + "/README.md"] = f"# {name}\n\n[Todos los temas](../README.md) · [Catálogo](../../catalogo/README.md)\n\n" + table(selected, parent)
        for d in selected:
            outputs[parent + "/README.md"] += f'\n### {d["ciclo"]}: {d["titulo"]}\n\n{d["preguntas"]}\n'
            if d.get("restricciones"):
                outputs[parent + "/README.md"] += f'\nRestricciones del enunciado: {d["restricciones"]}\n'
    outputs["temas/README.md"] = "".join(topics)
    exams = [d for d in docs if d["tipo"] == "Examen"]
    outputs["examenes/README.md"] = (
        "# Exámenes por ciclo\n\n[Inicio](../README.md) · [Soluciones](../soluciones-actuales/CATALOGO.md) · "
        "[Por temas](../temas/README.md)\n\n"
        "Examen 1 corresponde a parcial y examen 2 a final. Cada ciclo reúne su enunciado, "
        "material de origen y enlaces a las resoluciones verificadas.\n\n" + table(exams, "examenes"))
    for section in ["parcial", "final"]:
        selected = [d for d in exams if d["ruta"].startswith(f"examenes/{section}/")]
        outputs[f"examenes/{section}/README.md"] = (
            f"# {'Exámenes parciales' if section == 'parcial' else 'Exámenes finales'}\n\n"
            "[Todos los exámenes](../README.md)\n\n" + table(selected, f"examenes/{section}"))
    support = [d for d in docs if d["tipo"] in {"Teoría", "Ejercicios", "Archivo vacío"}]
    outputs["material-de-apoyo/README.md"] = (
        "# Material de apoyo\n\n[Inicio](../README.md) · [Videos y grabaciones](VIDEOS.md) · [Fuentes adicionales](fuentes-adicionales/README.md) · [Catálogo](../catalogo/README.md)\n\n"
        + table(support, "material-de-apoyo") +
        "\nEl documento vacío no se publica como PDF utilizable; su enlace de origen y estado se conservan en el catálogo.\n")
    for d in docs:
        if not d.get("detalle"): continue
        path = Path(d["detalle"])
        parent = str(path.parent)
        text = f'# {d["titulo"]} — {d["ciclo"]}\n\n'
        text += link("Catálogo", "catalogo/README.md", parent)
        if d["ruta"]: text += " · " + link("Enunciado PDF", d["ruta"], parent)
        text += f'\n\n{d["preguntas"]}\n\nTemas: {"; ".join(d["temas"])}.\n'
        if d.get("restricciones"): text += "\nRestricciones: " + d["restricciones"] + "\n"
        if d.get("material"):
            text += "\n## Material de origen\n\nEstos fuentes conservan sus variantes y no se presentan como soluciones verificadas.\n\n"
            for material in d["material"]: text += "- " + link("Fuentes y datos", material, parent) + "\n"
        if d.get("soluciones"):
            text += "\n## Soluciones verificadas\n\n"
            for s in d["soluciones"]: text += "- " + link(s["nombre"], s["ruta"], parent) + "\n"
        if d.get("fuente"):
            text += f'\nProcedencia: [material compartido]({d["fuente"]}).\n'
        outputs[str(path)] = text
    body = []
    for d in docs:
        esc = html.escape
        pdf = f'<a href="{relative(d["ruta"], "catalogo")}">PDF</a>' if d["ruta"] else "Vacío en origen"
        detail = f' · <a href="{relative(d["detalle"], "catalogo")}">Fuentes y detalle</a>' if d.get("detalle") else ""
        sols = " · ".join(f'<a href="{relative(s["ruta"], "catalogo")}">{esc(s["nombre"])}</a>' for s in d.get("soluciones", [])) or "Pendiente"
        body.append(f'<tr data-topics="{esc("|".join(d["temas"]), quote=True)}" data-kind="{esc(d["tipo"], quote=True)}" data-term="{esc(d["ciclo"], quote=True)}"><td>{esc(d["ciclo"])}</td><td><strong>{esc(d["titulo"])}</strong><p>{esc(d["preguntas"])}</p></td><td>{esc("; ".join(d["temas"]))}</td><td>{pdf}{detail}</td><td>{sols}</td></tr>')
    def options(values):
        return "".join(f'<option>{html.escape(v)}</option>' for v in sorted(set(values)))
    outputs["catalogo/index.html"] = """<!doctype html>
<html lang="es"><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>Catálogo de Algoritmia INF263</title>
<style>body{font:16px system-ui,sans-serif;margin:2rem auto;padding:0 1rem;max-width:1400px;color:#17202a}a{color:#1557a0}nav,form{display:flex;gap:1rem;flex-wrap:wrap;margin:1rem 0}label{display:grid;gap:.3rem}input,select{font:inherit;padding:.5rem;border:1px solid #8c99a8;border-radius:.3rem}table{border-collapse:collapse;width:100%}th,td{text-align:left;vertical-align:top;padding:.7rem;border-bottom:1px solid #cbd5df}th{background:#edf2f7}td p{font-size:.9rem;line-height:1.5}caption{text-align:left;margin:1rem 0}.scroll{overflow-x:auto}[hidden]{display:none!important}</style>
<body><h1>Algoritmia INF263</h1><nav><a href="../README.md">Inicio</a><a href="../temas/README.md">Temas</a><a href="../examenes/README.md">Exámenes</a><a href="../laboratorios/README.md">Laboratorios</a><a href="../soluciones-actuales/CATALOGO.md">Soluciones</a></nav>
<p>Enunciados, fuentes de origen, soluciones verificadas y material de clase. Abre este archivo directamente en el navegador.</p>
<form onsubmit="return false"><label>Buscar<input id="search" type="search" placeholder="Nautilus, pilas, robot…"></label>
<label>Tema<select id="topic"><option value="">Todos</option>""" + options(t for d in docs for t in d["temas"]) + """</select></label>
<label>Tipo<select id="kind"><option value="">Todos</option>""" + options(d["tipo"] for d in docs) + """</select></label>
<label>Ciclo<select id="term"><option value="">Todos</option>""" + options(d["ciclo"] for d in docs) + """</select></label></form>
<p id="count" role="status" aria-live="polite">""" + str(len(docs)) + """ documentos catalogados</p>
<div class="scroll"><table><caption>Una sola copia por enunciado; los fuentes de origen tienen su estado indicado.</caption><thead><tr><th>Ciclo</th><th>Documento y preguntas</th><th>Temas</th><th>Material</th><th>Soluciones verificadas</th></tr></thead><tbody>""" + "\n".join(body) + """</tbody></table></div><p id="empty" hidden>No hay coincidencias.</p>
<script>
const inputs=['search','topic','kind','term'].map(id=>document.getElementById(id));
const rows=[...document.querySelectorAll('tbody tr')];
const norm=s=>s.normalize('NFD').replace(/[\\u0300-\\u036f]/g,'').toLowerCase();
const corpus=rows.map(row=>norm(row.textContent));
function filter(){const [search,topic,kind,term]=inputs.map(x=>x.value);const words=norm(search).trim().split(/\\s+/).filter(Boolean);let count=0;rows.forEach((row,i)=>{const visible=words.every(word=>corpus[i].includes(word))&&(!topic||row.dataset.topics.split('|').includes(topic))&&(!kind||row.dataset.kind===kind)&&(!term||row.dataset.term===term);row.hidden=!visible;if(visible)count++});document.getElementById('count').textContent=count+' de '+rows.length+' documentos';document.getElementById('empty').hidden=count!==0;}
inputs.forEach(input=>input.addEventListener('input',filter));
</script></body></html>
"""
    return outputs

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true", help="comprobar sin modificar archivos")
    args = parser.parse_args()
    docs = json.loads((ROOT / "catalogo/documentos.json").read_text(encoding="utf-8"))
    outputs = render(docs)
    stale = []
    for name, content in outputs.items():
        path = ROOT / name
        if args.check:
            if not path.exists() or path.read_text(encoding="utf-8") != content: stale.append(name)
        else:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(content, encoding="utf-8")
    if stale:
        raise SystemExit("Regenerar catálogo: " + ", ".join(stale))
    print(f"OK: {len(docs)} documentos, {len(outputs)} índices {'comprobados' if args.check else 'generados'}")

if __name__ == "__main__":
    main()
