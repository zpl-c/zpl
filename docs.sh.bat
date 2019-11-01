#/bin/bash 2>nul || goto :windows
cat docs/HEADER.md > README.md
cat docs/INDEX.md >> README.md

cd docs

rm -rf export 2> /dev/null

python3 mcss/doxygen/dox2html5.py --debug Doxyfile-mcss

exit

:windows
@echo off

type docs\HEADER.md > README.md
type docs\INDEX.md >> README.md

pushd docs

if exist export rmdir /Q /S export

python3 mcss\doxygen\dox2html5.py --debug Doxyfile-mcss

popd
