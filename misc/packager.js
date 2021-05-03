const fs = require('fs')
const path = require('path')
const {Plugin} = require('release-it')

const basefile = path.join(__dirname, '..', 'code', 'zpl.h')
const changelogfile = path.join(__dirname, '..', 'CHANGELOG')
const licensefile = path.join(__dirname, '..', 'LICENSE')
const workdir = path.join(__dirname, 'deploy')

const versionGet = () => {
    const data = fs.readFileSync(basefile, 'utf8')

    const major = data.match(/ZPL_VERSION_MAJOR\s+([0-9]+)\n/)[1]
    const minor = data.match(/ZPL_VERSION_MINOR\s+([0-9]+)\n/)[1]
    const patch = data.match(/ZPL_VERSION_PATCH\s+([0-9]+)\n/)[1]
    const pre   = data.match(/ZPL_VERSION_PRE\s+\"([\.a-z0-9]+)\"\n/)

    return `${major}.${minor}.${patch}${pre ? '-' + pre[1] : ''}`
}

const versionSet = (version) => {
    let data = fs.readFileSync(basefile, 'utf8')

    let [base, pre] = version.split('-')
    let [major, minor, patch] = base.split('.').map(a => parseInt(a))

    if (!pre) pre = ''

    data = data.replace(/ZPL_VERSION_MAJOR\s+([0-9]+)\n/, `ZPL_VERSION_MAJOR ${major}\n`)
    data = data.replace(/ZPL_VERSION_MINOR\s+([0-9]+)\n/, `ZPL_VERSION_MINOR ${minor}\n`)
    data = data.replace(/ZPL_VERSION_PATCH\s+([0-9]+)\n/, `ZPL_VERSION_PATCH ${patch}\n`)
    data = data.replace(/ZPL_VERSION_PRE\s+\"([\.0-9a-z]+)\"\n/, `ZPL_VERSION_PRE "${pre}"\n`)

    fs.writeFileSync(basefile, data)
}

const embedIncludes = (print) => {
    if (!fs.existsSync(workdir)) fs.mkdirSync(workdir)

    let data = fs.readFileSync(basefile, 'utf8')
    let lines = data.split('\n')

    const embedFile = (filename, symbol, spaces='  ') => lines.map(line => {
        if (line.indexOf(`@{${symbol}}`) === -1) return line
        return fs
            .readFileSync(filename, 'utf8')
            .split('\n')
            .map(l => `${spaces}${l}`)
            .map(l => l === spaces ? '' : l)
            .join('\n')
    })

    lines = embedFile(changelogfile, 'CHANGELOG')
    lines = embedFile(licensefile, 'LICENSE')

    const hedley = lines.find(a => a.indexOf('zpl_hedley.h') !== -1)
    const hedleyIndex = lines.indexOf(hedley)

    lines = lines.map((line, i) => {
        if (i < hedleyIndex) return line
        if (line.indexOf('<') !== -1) return line
        if (line.startsWith('#') && line.indexOf('include') !== -1) {
            const includePos = line.indexOf('include')
            const parts = line.split('include')
            const spaces = ' '.repeat(includePos)
            const filename = parts[1].trim().replace(/"/g, '')

            const content = fs
                .readFileSync(path.join(__dirname, '..', 'code', filename), 'utf8')
                .split('\n')
                .map(l => spaces + l)
                .map(l => l === spaces ? '' : l)
                .join('\n')
                .replace(/\s+$/g, '')

            return content
        } else return line
    })

    const code = lines.join('\n')
    if (print) console.log(code)
    else       fs.writeFileSync(path.join(workdir, 'zpl.h'), code)
}

class Bumper extends Plugin {
    getLatestVersion() {
        return versionGet()
    }

    bump(version) {
        this.version = version;
        versionSet(version)
    }

    async beforeRelease() {
        embedIncludes()
        console.log('done')
    }

    afterRelease() {
        if (fs.existsSync(path.join(workdir, 'zpl.h'))) {
            fs.unlinkSync(path.join(workdir, 'zpl.h'))
        }
    }
}

module.exports = Bumper
module.exports.embedIncludes = embedIncludes
