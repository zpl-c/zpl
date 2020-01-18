const fs = require('fs')
const path = require('path')
const {Plugin} = require('release-it')

const basefile = path.join(__dirname, '..', 'code', 'zpl.h')
const workdir = path.join(__dirname, 'deploy')

const versionGet = () => {
    const data = fs.readFileSync(basefile, 'utf8')

    const major = data.match(/ZPL_VERSION_MAJOR\s+([0-9]+)\n/)[1]
    const minor = data.match(/ZPL_VERSION_MINOR\s+([0-9]+)\n/)[1]
    const patch = data.match(/ZPL_VERSION_PATCH\s+([0-9]+)\n/)[1]

    return `${major}.${minor}.${patch}`
}

const versionSet = (major, minor, patch) => {
    let data = fs.readFileSync(basefile, 'utf8')

    data = data.replace(/ZPL_VERSION_MAJOR\s+([0-9]+)\n/, `ZPL_VERSION_MAJOR ${major}\n`)
    data = data.replace(/ZPL_VERSION_MINOR\s+([0-9]+)\n/, `ZPL_VERSION_MINOR ${minor}\n`)
    data = data.replace(/ZPL_VERSION_PATCH\s+([0-9]+)\n/, `ZPL_VERSION_PATCH ${patch}\n`)

    fs.writeFileSync(basefile, data)
}

const embedIncludes = () => {
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

        const content = fs
            .readFileSync(path.join(__dirname, '..', 'code', filename), 'utf8')
            .split('\n')
            .map(l => spaces + l)
            .map(l => l === spaces ? '' : l)
            .join('\n')
            .replace(/\s+$/g, '')

        return content
    })

    fs.writeFileSync(path.join(workdir, 'zpl.h'), lines.join('\n'))
}

class Bumper extends Plugin {
    getLatestVersion() {
        return versionGet()
    }

    bump(version) {
        this.version = version;

        const [major, minor, patch] = version
            .split('.')
            .map(a => parseInt(a))

        versionSet(major, minor, patch)
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
