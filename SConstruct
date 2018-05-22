import os
import glob
import time
import sys

env = Environment(CCFLAGS=['-O3', '--std=c++11'],
                  CPPPATH=['./googlebenchmark/'],
                  LIBPATH=['./googlebenchmark/'],
                  LIBS=['benchmark', 'pthread'])

for sourceFile in glob.glob("*.cc"):
  # print (sourceFile)
  [name,suffix] = sourceFile.split(".")
  env.Program(target="build/%s" % name, source=sourceFile)

