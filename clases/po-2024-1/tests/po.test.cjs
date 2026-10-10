// Run: node laboratorios/03_fuerza_bruta/po_2024_1/tests/po.test.cjs
const assert = require('node:assert/strict');
const fs = require('node:fs');
const path = require('node:path');
const vm = require('node:vm');
const root = path.join(__dirname, '..');
const html = fs.readFileSync(path.join(root, 'index.html'), 'utf8');
const script = html.match(/<script>([\s\S]*?)<\/script>/)[1];
const context = vm.createContext({});
vm.runInContext(script.slice(0, script.indexOf('    const ORIGINAL_BASE64')), context);
const source = path.resolve(root, 'referencia');
const sourceBytes = fs.readFileSync(path.join(source, 'P1.cpp'));
const dataBytes = fs.readFileSync(path.resolve(root, '../../laboratorios/laboratorio-01/2024-1/material_original/variantes/2024-2/LAB1/Viernes 13／09/Copia de datos1.txt'));
assert.deepEqual(Buffer.from(html.match(/const ORIGINAL_BASE64 = '([^']+)'/)[1], 'base64'), sourceBytes);
assert.deepEqual(Buffer.from(html.match(/const DATA_BASE64 = '([^']+)'/)[1], 'base64'), dataBytes);
assert.deepEqual(Buffer.from(html.match(/const UPDATED_BASE64 = '([^']+)'/)[1], 'base64'), fs.readFileSync(path.resolve(root, '../../laboratorios/laboratorio-01/2024-1/material_original/variantes/2024-2/LAB1/Viernes 13／09/Copia de P1.cpp')));
const { warriors, weapons } = context.parseData(dataBytes.toString('utf8'));
assert.equal(warriors.length, 3);
assert.equal(weapons.length, 12);
const unused = Array(12).fill(0);
assert.equal(context.cargarCromosoma(12, 1).join(''), '000000000001', 'Least significant bit is L');
assert.equal(context.cargarCromosoma(12, 2048).join(''), '100000000000', 'Most significant bit is Z');
assert.equal(context.validateCandidate(0, unused, warriors[0], weapons).reason, 'power');
assert.equal(context.validateCandidate(1024, unused, warriors[1], weapons).reason, 'prereq');
assert.equal(context.validateCandidate(512, unused, warriors[1], weapons).reason, 'type');
const equality = context.validateCandidate(524, unused, { power:142, types:[2] }, weapons);
assert.equal(equality.valid, true, 'Original accepts equal power');
const taken = [...unused]; taken[2] = 1;
const conflict = context.validateCandidate(524, taken, warriors[0], weapons);
assert.equal(conflict.reason, 'used');
assert.equal(conflict.checks.slice(1).every(check => check === null), true, 'Stop at first failed check');

const trace = context.buildSearchTrace(warriors, weapons);
const last = trace.at(-1);
assert.equal(last.success, true);
assert.equal(last.frames.length, 0);
assert.equal(last.tested, 48690);
assert.equal(last.backtracks, 11);
assert.equal(trace.find(event => event.kind === 'candidate').mask, 524);
const bags = warriors.map((_, g) => weapons.filter((w, i) => last.used[i] === g + 1).map(w => w.id).join(' '));
assert.equal(JSON.stringify(bags), JSON.stringify(['R I J', 'Z P K', 'G L']), 'First solution of original C++');
assert.equal(last.used.filter(Boolean).length, 8);
let reconstructedAttempts = 0;
for (let i = 0; i < trace.length; i++) {
  const event = trace[i];
  if (event.kind === 'rejections') {
    assert.equal(event.batch.end - event.batch.start + 1, event.batch.count);
    assert.equal(Object.values(event.batch.reasons).reduce((a, b) => a + b, 0), event.batch.count);
    reconstructedAttempts += event.batch.count;
  }
  if (event.kind === 'candidate') {
    reconstructedAttempts++;
    assert.equal(context.validateCandidate(event.mask, event.used, warriors[event.index], weapons).valid, true);
  }
  if (event.kind === 'undo') {
    const previous = trace[i - 1];
    assert.equal(previous.kind, 'failure');
    const restored = previous.used.map(owner => owner === event.index + 1 ? 0 : owner);
    assert.equal(JSON.stringify(event.used), JSON.stringify(restored), 'Undo only this warrior’s reservations');
  }
}
assert.equal(reconstructedAttempts, last.tested, 'Grouped events account for every attempted combination');
const impossible = warriors.map(w => ({ ...w })); impossible[0].power = 999;
const noSolution = context.buildSearchTrace(impossible, weapons).at(-1);
assert.equal(noSolution.success, false);
assert.equal(noSolution.tested, 4096);
assert.equal(noSolution.used.every(owner => owner === 0), true);
console.log('OK: original source/data, binary order, short-circuit checks, equal power, 48,690 attempts, 11 backtracks, first solution and impossible case.');
