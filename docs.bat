@echo off

if exist README.md del README.md

type docs\HEADER.md > README.md
type docs\INDEX.md >> README.md

pushd docs

call make html

popd