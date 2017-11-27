// Generate c source from js files

const fs = require('fs')
const path = require('path')
const childProcess = require('child_process')

var js_path = path.join(__dirname, '../src/js')
var files = fs.readdirSync(js_path)
var snapshots = []

files.forEach(file => {
  if (path.extname(file) === '.js') {
    const basename = path.basename(file, '.js')
    const src = path.join(js_path, file)
    const wrapped = path.join(js_path, basename + '.wrapped')
    const snapshot = path.join(js_path, basename + '.snapshot')
    generateWrapper(src, wrapped)
    generateSnapshot(wrapped, snapshot)
    snapshots.push(snapshot)
  }
})
generate();

function generateWrapper(src, dest) {
  const wrapper_header = '(function(exports, require, module) {\n'
  const wrapper_footer = '\n});\n'
  const data = fs.readFileSync(src, 'utf8')
  fs.writeFileSync(dest, wrapper_header + data + wrapper_footer, 'utf8')
}

function generateSnapshot(src, dest) {
  childProcess.spawnSync('deps/jerryscript/build/bin/jerry-snapshot', [ 'generate', src, '-o', dest ], { stdio: 'inherit' })
}

function generate() {
  snapshots.forEach(snapshot => {
    var buffer = fs.readFileSync(snapshot);
    var hex = buffer.toString('hex')
    console.log(snapshot)
    console.log(hex + '\n')
    console.log('length=' + hex.length + '\n')
    console.log('\n')
  })
}
