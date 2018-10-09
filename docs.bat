@echo off

type docs\HEADER.md > README.md
type docs\INDEX.md >> README.md

pushd docs

python mcss\doxygen\dox2html5.py --debug Doxyfile-mcss

popd
