const assert = require('node:assert/strict');
const fs = require('node:fs');
const path = require('node:path');
const vm = require('node:vm');

const root = path.resolve(__dirname, '..');
const html = fs.readFileSync(path.join(root, 'index.html'), 'utf8');
const script = html.match(/<script>([\s\S]*?)<\/script>/)[1];
const context = vm.createContext({});
vm.runInContext(script + '\nglobalThis.robot = { construirRecorrido, parsearMatriz, CPP_BASE64 };', context);
const { construirRecorrido, parsearMatriz, CPP_BASE64 } = context.robot;
assert.deepEqual(Buffer.from(CPP_BASE64, 'base64'), fs.readFileSync(path.join(root, '../soluciones/2025_2_ex01_p04_robotjardin.cpp')));
assert.equal(JSON.stringify(parsearMatriz(' 1 0\r\n0 1\n')), '[[1,0],[0,1]]');
for (const invalid of ['', '1 2', '1 0\n1', '1\n\n0', '1.0', '<script>', Array(21).fill('1').join(' '), Array(21).fill('1').join('\n')]) {
    assert.throws(() => parsearMatriz(invalid));
}

const matrices = JSON.parse(fs.readFileSync(0, 'utf8'));
const results = [];
for (const matrix of matrices) {
    const before = JSON.stringify(matrix);
    matrix.forEach(Object.freeze);
    Object.freeze(matrix);
    const states = construirRecorrido(matrix);
    let previousArea = 0;
    for (const state of states) {
        assert.ok(state.mejor.area >= previousArea, 'El máximo no puede disminuir.');
        previousArea = state.mejor.area;
        for (const rectangle of [state.mejor, state.candidato]) {
            if (!rectangle || rectangle.area === 0) continue;
            assert.ok(rectangle.filaInicio >= 0 && rectangle.filaFin < matrix.length);
            assert.ok(rectangle.columnaInicio >= 0 && rectangle.columnaFin < matrix[0].length);
            assert.equal(rectangle.area, (rectangle.filaFin - rectangle.filaInicio + 1) * (rectangle.columnaFin - rectangle.columnaInicio + 1));
            for (let row = rectangle.filaInicio; row <= rectangle.filaFin; row++) {
                for (let col = rectangle.columnaInicio; col <= rectangle.columnaFin; col++) {
                    assert.equal(matrix[row][col], 1, 'La vista no debe marcar ceros dentro de un rectángulo.');
                }
            }
        }
        for (let i = 1; i < state.pila.length; i++) {
            assert.ok(state.pila[i - 1] < state.pila[i]);
            assert.ok(state.alturas[state.pila[i - 1]] <= state.alturas[state.pila[i]]);
        }
        if (state.tipo === 'fin-fila') assert.equal(state.pila.length, 0);
    }
    assert.equal(JSON.stringify(matrix), before);
    results.push(states[states.length - 1].mejor);
}
process.stdout.write(JSON.stringify(results));
