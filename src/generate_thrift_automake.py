#!/usr/bin/env python

# Very simple regex parser for generating the automake thrift libraries.
#
# Filename becomes <fname>_{constants,types}.{h,cpp}
# Services become <service>.{h,cpp}
import re
import sys

def main(argv):
  if len(argv) != 2:
    print 'Check the code.'
    return 1

  file_to_parse = argv[1]

if __name__=='__main__':
  main(sys.argv)
