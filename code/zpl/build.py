# Copyright 2017-2018 Dominik Madarász <zaklaus@outlook.com>

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""
This small script builds `zpl.h` from separate parts into a single header-only library.
"""

import re
import os

wd = os.path.dirname(os.path.abspath(__file__))

TPL_PATH   = wd + "/zpl_template.c"
BUILD_PATH = wd + "/../zpl.h"

with open(TPL_PATH, 'r') as loader:
    tpl = loader.read()

    print("Generating zpl.h header-only single file...")

    incl = re.compile(r"(//<<([\w._]+)>>)", flags=re.MULTILINE | re.IGNORECASE)

    l = incl.findall(tpl)

    if l == None:
        print("This template contained no includes!")
        exit()

    head = ""
    source = ""

    for m in l:
        og = m[0]
        fn = m[1]
        repl = ""

        with open(wd + "/" + fn, 'r') as fi:
            c = fi.read()

            p = c.split("//!!")
            head += p[0]
            source += p[1]


    tpl = tpl.replace("//<#head>", head)
    tpl = tpl.replace("//<#source>", source)
    
    with open(BUILD_PATH, "w+") as output:
        output.write(tpl)

