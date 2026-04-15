#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

env.Append(CPPPATH=["src/"])

sources = Glob("src/*.cpp")
lib_filename = "{}fiveletters{}{}".format(
    env.subst('$SHLIBPREFIX'),
    env["suffix"],
    env.subst('$SHLIBSUFFIX')
)

library = env.SharedLibrary(
    "project/bin/{}".format(lib_filename),
    source=sources,
)

Default(library)
