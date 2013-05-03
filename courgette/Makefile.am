AM_CPPFLAGS = -I$(top_srcdir)/testing/gtest/include -DCOURGETTE_USE_CRC_LIB
AM_CPPFLAGS += -I$(top_srcdir) -I$(top_builddir)

noinst_LTLIBRARIES =
bin_PROGRAMS =
TESTS =

EXTRA_DIST =
EXTRA_DIST += types_elf.h
EXTRA_DIST += types_win_pe.h
EXTRA_DIST += patcher_x86_32.h
EXTRA_DIST += patch_generator_x86_32.h
EXTRA_DIST += third_party/paged_array.h

noinst_LTLIBRARIES += libsimple_delta.la
libsimple_delta_la_SOURCES = simple_delta.h
libsimple_delta_la_SOURCES += simple_delta.cc
libsimple_delta_la_SOURCES += courgette.h
libsimple_delta_la_LIBADD = $(top_builddir)/base/liblogging.la
libsimple_delta_la_LIBADD += third_party/libbsdiff.la

bin_PROGRAMS += courgette_tool
courgette_tool_SOURCES = courgette_tool.cc
courgette_tool_LDADD = $(top_builddir)/base/files/libfile_path.la
courgette_tool_LDADD += $(top_builddir)/base/libfile_util.la
courgette_tool_LDADD += libdisassembler.la
courgette_tool_LDADD += libstreams.la
courgette_tool_LDADD += third_party/libbsdiff.la
courgette_tool_LDADD += libadjustment_method.la
courgette_tool_LDADD += libensemble.la

noinst_LTLIBRARIES += libstreams.la
libstreams_la_SOURCES = streams.h
libstreams_la_SOURCES += streams.cc
libstreams_la_SOURCES += region.h
libstreams_la_LIBADD = libmemory_allocator.la
libstreams_la_LIBADD += $(top_builddir)/base/memory/libsingleton.la

TESTS += streams_unittest
bin_PROGRAMS += streams_unittest
streams_unittest_SOURCES = streams_unittest.cc
streams_unittest_LDADD = libsimple_delta.la
streams_unittest_LDADD += libstreams.la
streams_unittest_LDADD += $(top_builddir)/testing/gtest/lib/libgtest.la
streams_unittest_LDADD += $(top_builddir)/testing/gtest/lib/libgtest_main.la
streams_unittest_LDADD += $(top_builddir)/base/liblogging.la

noinst_LTLIBRARIES += third_party/libbsdiff.la
third_party_libbsdiff_la_SOURCES = third_party/bsdiff.h
third_party_libbsdiff_la_SOURCES += third_party/bsdiff_apply.cc
third_party_libbsdiff_la_SOURCES += third_party/bsdiff_create.cc
third_party_libbsdiff_la_LIBADD = libcrc.la $(ZLIB_LIBS)
third_party_libbsdiff_la_LIBADD += $(top_builddir)/base/libtime.la

noinst_LTLIBRARIES += libdisassembler.la
libdisassembler_la_SOURCES = disassembler.h
libdisassembler_la_SOURCES += disassembler.cc
libdisassembler_la_LIBADD = libassembly_program.la
libdisassembler_la_LIBADD += libdisassembler_win32_x86.la
libdisassembler_la_LIBADD += libdisassembler_elf_32_x86.la

noinst_LTLIBRARIES += libdisassembler_win32_x86.la
libdisassembler_win32_x86_la_SOURCES = disassembler_win32_x86.h
libdisassembler_win32_x86_la_SOURCES += disassembler_win32_x86.cc
libdisassembler_win32_x86_la_LIBADD = $(top_builddir)/base/liblogging.la

noinst_LTLIBRARIES += libdisassembler_elf_32_x86.la
libdisassembler_elf_32_x86_la_SOURCES = disassembler_elf_32_x86.h
libdisassembler_elf_32_x86_la_SOURCES += disassembler_elf_32_x86.cc
libdisassembler_elf_32_x86_la_LIBADD = $(top_builddir)/base/liblogging.la


noinst_LTLIBRARIES += libassembly_program.la
libassembly_program_la_SOURCES = assembly_program.h
libassembly_program_la_SOURCES += assembly_program.cc
libassembly_program_la_LIBADD = libencoded_program.la

noinst_LTLIBRARIES += libencoded_program.la
libencoded_program_la_SOURCES = encoded_program.h
libencoded_program_la_SOURCES += encoded_program.cc
libencoded_program_la_LIBADD = $(top_builddir)/base/libenvironment.la

noinst_LTLIBRARIES += libadjustment_method.la
libadjustment_method_la_SOURCES = adjustment_method.h
libadjustment_method_la_SOURCES += adjustment_method.cc
libadjustment_method_la_SOURCES += adjustment_method_2.cc

noinst_LTLIBRARIES += libensemble.la
libensemble_la_SOURCES = ensemble.h
libensemble_la_SOURCES += ensemble.cc
libensemble_la_SOURCES += ensemble_create.cc
libensemble_la_SOURCES += ensemble_apply.cc
libensemble_la_LIBADD = libdifference_estimator.la
libensemble_la_LIBADD += libsimple_delta.la
libensemble_la_LIBADD += $(top_builddir)/base/files/libmemory_mapped_file.la

noinst_LTLIBRARIES += libdifference_estimator.la
libdifference_estimator_la_SOURCES = difference_estimator.h
libdifference_estimator_la_SOURCES += difference_estimator.cc

noinst_LTLIBRARIES += libcrc.la
libcrc_la_SOURCES = crc.h
libcrc_la_SOURCES += crc.cc

noinst_LTLIBRARIES += libmemory_allocator.la
libmemory_allocator_la_SOURCES = memory_allocator.h
libmemory_allocator_la_SOURCES += memory_allocator.cc
libmemory_allocator_la_LIBADD = $(top_builddir)/base/files/libfile_path.la
libmemory_allocator_la_LIBADD += $(top_builddir)/base/libplatform_file.la
