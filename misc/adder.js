// temp script created just to add filenames on top of the files

const fs = require('fs')
const path = require('path')
const {Plugin} = require('release-it')

const basefile = path.join(__dirname, '..', 'code', 'zpl.h')
const workdir = path.join(__dirname, 'deploy')

const addstuff = () => {
    if (!fs.existsSync(workdir)) fs.mkdirSync(workdir)

    let data = fs.readFileSync(basefile, 'utf8')
    let lines = data.split('\n')

    const hedley = lines.find(a => a.indexOf('zpl_hedley.h') !== -1)
    const hedleyIndex = lines.indexOf(hedley)

    lines = lines.map((line, i) => {
        if (i < hedleyIndex) return line
        if (line.indexOf('#include') === -1) return line
        if (line.indexOf('<') !== -1) return line

        const parts = line.split('#include')
        const spaces = parts[0]
        const filename = parts[1].trim().replace(/"/g, '')
        const fullpath = path.join(__dirname, '..', 'code', filename)
        const content = fs.readFileSync(fullpath, 'utf8')

        fs.writeFileSync(fullpath, `// file: ${filename}\n\n${content}`)
        console.log(filename)
    })
}

addstuff()
