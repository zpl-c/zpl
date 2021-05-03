// temp script created to change preprocessor macro indentation to a new style

const fs = require('fs')
const path = require('path')
const { resolve } = require('path');
const { readdir } = require('fs').promises;

async function* getFiles(dir) {
  const dirents = await readdir(dir, { withFileTypes: true });
  for (const dirent of dirents) {
    const res = resolve(dir, dirent.name);
    if (dirent.isDirectory()) {
      yield* getFiles(res);
    } else {
      yield res;
    }
  }
}

const basedir = path.join(__dirname, '..', 'code')

const iterate_over_files = async () => {
    for await (const f of getFiles(path.join(basedir, '.'))) {
        console.log(`processing ${f}`)
        let data = fs.readFileSync(f, 'utf8')
        let lines = data.split('\n')
        lines = lines.map(line => {
            if (!line.trim().startsWith('#')) return line
            const indent = line.indexOf('#')
            return `#${' '.repeat(indent)}${line.substr(indent+1)}`
        })
        fs.writeFileSync(f, lines.join('\n'))
    }
}

iterate_over_files()
