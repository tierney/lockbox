#!/usr/bin/env python

# Very simple regex parser for generating the automake thrift libraries.
#
# Filename becomes <fname>_{constants,types}.{h,cpp}
# Services become <service>.{h,cpp}

import re
import sys

kThriftFilename = re.compile("(.*).thrift")
kServiceLine = re.compile("service (.*) {")

kLTLIBRARIESName = 'lib%(fname)s_thrift.la'
kSOURCESName = 'lib%(fname)s_thrift_la_SOURCES'

def main(argv):
  if len(argv) < 2:
    print 'Check the code.'
    return 1

  to_clean = []
  for fname in argv[1:]:
    to_clean.append(GenerateLibraryDefinitions(fname))

  print '''clean-local: clean-local-check
.PHONY: clean-local-check
clean-local-check:
	-rm -rf \\'''

  for source in to_clean:
    print '\t\t$(%s) \\' % source
  print '\t\t*.skeleton.cpp'

def GenerateLibraryDefinitions(file_to_parse):

  # Get the name of the file.
  fname = re.match(kThriftFilename, file_to_parse).group(1)

  print 'noinst_LTLIBRARIES += ' + kLTLIBRARIESName % locals()

  sources = [
    "%(fname)s_constants.h" % locals(),
    "%(fname)s_constants.cpp" % locals(),
    "%(fname)s_types.h" % locals(),
    "%(fname)s_types.cpp" % locals(),
  ]

  # Find the services in the file.
  services = []
  with open(file_to_parse) as fh:
    for line in fh:
      m = re.match(kServiceLine, line)
      if not m:
        continue

      service = m.group(1)
      services.append(service)
      sources.append('%(service)s.h' % locals())
      sources.append('%(service)s.cpp' % locals())

  print kSOURCESName % locals() + ' ='
  print '\n'.join([kSOURCESName % locals() + ' += ' +
                   source % locals() for source in sources])

  build_line = \
      "$(" + kSOURCESName % locals() + "): $(srcdir)/%(fname)s.thrift" % locals()
  build_line += '\n\t$(THRIFT_BUILD)'
  print build_line

  return kSOURCESName % locals()

if __name__=='__main__':
  main(sys.argv)
