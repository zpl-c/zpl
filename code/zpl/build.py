
# This Software is dual licensed under the following licenses:

# Unlicense
# This is free and unencumbered software released into the public domain.

# Anyone is free to copy, modify, publish, use, compile, sell, or
# distribute this software, either in source code form or as a compiled
# binary, for any purpose, commercial or non-commercial, and by any
# means.

# In jurisdictions that recognize copyright laws, the author or authors
# of this software dedicate any and all copyright interest in the
# software to the public domain. We make this dedication for the benefit
# of the public at large and to the detriment of our heirs and
# successors. We intend this dedication to be an overt act of
# relinquishment in perpetuity of all present and future rights to this
# software under copyright law.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
# OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.

# For more information, please refer to < http: // unlicense.org/>

# Apache 2.0
# Copyright 2017-2019 Dominik Madarász < zaklaus@outlook.com >
# Licensed under the Apache License, Version 2.0 (the "License")
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http: // www.apache.org/licenses/LICENSE-2.0

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

TPL_PATH   = wd + "/__main__.c"
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

            p = c.split("//$$")
            head += p[0]
            source += p[1]


    tpl = tpl.replace("//<#head>", head)
    tpl = tpl.replace("//<#source>", source)
    
    with open(BUILD_PATH, "w+") as output:
        output.write(tpl)

