// Comprueba filtros del catalogo sin dependencias de navegador.
const assert = require("node:assert/strict");
const fs = require("node:fs");
const path = require("node:path");
const vm = require("node:vm");
const root = path.resolve(__dirname, "..");
const html = fs.readFileSync(path.join(root, "catalogo/index.html"), "utf8");
const decode = s => s.replace(/&quot;/g, '"').replace(/&#x27;/g, "'").replace(/&amp;/g, "&").replace(/&lt;/g, "<").replace(/&gt;/g, ">");
const rows = [...html.matchAll(/<tr data-topics="([^"]*)" data-kind="([^"]*)" data-term="([^"]*)">([\s\S]*?)<\/tr>/g)].map(match => ({
  dataset: {topics: decode(match[1]), kind: decode(match[2]), term: decode(match[3])},
  textContent: decode(match[4].replace(/<[^>]*>/g, " ")),
  hidden: false,
}));
const elements = Object.fromEntries(["search", "topic", "kind", "term", "count", "empty"].map(id => [id, {
  value: "", hidden: false, textContent: "", addEventListener() {},
}]));
const context = vm.createContext({
  document: {
    getElementById: id => elements[id],
    querySelectorAll: selector => { assert.equal(selector, "tbody tr"); return rows; },
  },
});
vm.runInContext(html.match(/<script>([\s\S]*?)<\/script>/)[1], context);
function check(values, expected) {
  for (const id of ["search", "topic", "kind", "term"]) elements[id].value = values[id] || "";
  vm.runInContext("filter()", context);
  const count = rows.filter(row => !row.hidden).length;
  assert.equal(count, expected, JSON.stringify(values));
  assert.equal(elements.empty.hidden, count !== 0);
  assert.equal(elements.count.textContent, count + " de " + rows.length + " documentos");
}
check({}, 35);
check({search: "Nautilus"}, 1);
check({search: "tortuninjas"}, 1);
check({search: "barajado"}, 1);
check({search: "sin-coincidencias-xyz"}, 0);
check({kind: "Laboratorio"}, 19);
check({kind: "Examen", term: "2024-1"}, 2);
check({topic: "Backtracking"}, 3);
check({search: "recursion", kind: "Examen"}, 2);
console.log("OK: filtros de busqueda, tema, tipo, ciclo y estado vacio");
