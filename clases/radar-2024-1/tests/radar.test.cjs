// Run with: node laboratorios/01_recursion/radar_2024_1/tests/radar.test.cjs
// No packages are required. Read the actual recursive function from the HTML.
const assert = require('node:assert/strict');
const fs = require('node:fs');
const path = require('node:path');
const vm = require('node:vm');

const html = fs.readFileSync(path.join(__dirname, '..', 'index.html'), 'utf8');
const script = html.match(/<script>([\s\S]*?)<\/script>/)[1];
const context = vm.createContext({});
vm.runInContext(script.slice(0, script.indexOf('    let state =')), context);
const traceFor = (matrix, x, y) => context.buildTrace(matrix, x, y);
const resultFor = (matrix, x, y) => traceFor(matrix, x, y).at(-1).result;
const first = [
  [0, 0, 0, 1, 0, 1],
  [0, 0, 1, 0, 0, 0],
  [0, 1, 0, 0, 0, 1],
  [1, 0, 0, 0, 0, 0],
  [0, 1, 0, 0, 0, 0],
  [0, 0, 0, 0, 1, 0]
];

assert.equal(resultFor(first, 3, 2), 5, 'First example from the PDF');
const second = first.map(row => [...row]);
second[4][4] = 1;
assert.equal(resultFor(second, 4, 4), 2, 'Second example includes the center unit');
assert.equal(resultFor(first, 0, 3), 1, 'A radar on an edge counts only its center');
assert.equal(resultFor([[1]], 0, 0), 1, 'Smallest occupied matrix');
assert.equal(resultFor([[0]], 0, 0), 0, 'Smallest empty matrix');

// Reject an incomplete ring even if its in-bounds cells all contain units.
assert.equal(resultFor(Array.from({ length: 3 }, () => [1, 1, 1, 1, 1]), 1, 1), 9);
assert.equal(resultFor([[1, 1, 1, 1]], 0, 2), 1);
assert.equal(traceFor([[1], [1], [1], [1]], 2, 0).at(-1).kind, 'invalid');

// Independent oracle: sum the maximal centered square, without walking rings.
let scenarios = 0;
for (let n = 1; n <= 12; n++) {
  for (let m = 1; m <= 12; m++) {
    const matrix = Array.from({ length: n }, (_, x) =>
      Array.from({ length: m }, (_, y) => ((x * 17 + y * 13 + n * 7 + m) % 5 < 2 ? 1 : 0)));
    const original = JSON.stringify(matrix);
    for (let x = 0; x < n; x++) {
      for (let y = 0; y < m; y++) {
        const radius = Math.min(x, n - 1 - x);
        if (y - radius < 0 || y + radius >= m) {
          const invalid = traceFor(matrix, x, y).at(-1);
          assert.equal(invalid.kind, 'invalid', 'Original ignores horizontal boundaries');
          assert.equal(invalid.result, undefined, 'No invented result for undefined C++ behavior');
          assert.equal(invalid.visited.length, 0);
          scenarios++;
          continue;
        }
        let expected = 0;
        for (let row = x - radius; row <= x + radius; row++) {
          for (let col = y - radius; col <= y + radius; col++) expected += matrix[row][col];
        }
        const trace = traceFor(matrix, x, y);
        const last = trace.at(-1);
        const label = `${n}x${m}, radar (${x},${y})`;
        assert.equal(last.result, expected, label);
        assert.equal(last.detected, expected, label);
        assert.equal(last.visited.length, (2 * radius + 1) ** 2, label);
        assert.equal(new Set(last.visited).size, last.visited.length, `No repeated corner: ${label}`);
        assert.equal(last.frames.length, 0, `Stack empties: ${label}`);
        assert.equal(last.completed.length, radius + 1, `Includes radius 0: ${label}`);
        const base = trace.find(event => event.kind === 'base');
        assert.equal(base.r, -1, `Stops when bounds cross: ${label}`);
        assert.equal(base.suma, expected, label);
        assert.equal(base.visited.length, last.visited.length, `Base counts no extra cells: ${label}`);
        const returns = trace.filter(event => event.kind === 'return');
        assert.equal(returns[0].r, 0, `Innermost call returns first: ${label}`);
        assert.equal(returns.at(-1).r, radius, `Outermost call returns last: ${label}`);
        assert.equal(returns.at(-1).suma, expected, label);
        assert.ok(returns.every(event => event.suma === expected), 'Returning never adds to suma');
        assert.equal(trace.find(event => event.kind === 'scan').r, radius);
        assert.equal(trace.filter(event => event.kind === 'scan').at(-1).r, 0);
        assert.equal(JSON.stringify(matrix), original, `Input is preserved: ${label}`);
        scenarios++;
      }
    }
  }
}
console.log(`OK: PDF examples, edge cases and ${scenarios} rectangular scenarios; counts, unique visits and stack returns verified.`);

const encoded = html.match(/const ORIGINAL_BASE64 = '([^']+)'/)[1];
assert.deepEqual(Buffer.from(encoded, 'base64'), fs.readFileSync(path.resolve(__dirname, '../../../laboratorios/laboratorio-01/2024-1/material_original/variantes/2025-0/Semana 2 - Recursión/SESIÓN 2/Copia de P2.cpp')));
console.log('OK: original C++ download is byte-identical; inward traversal and shared sum verified.');
