AM_CPPFLAGS = -I$(top_srcdir)/src/testing/gtest/include
AM_CPPFLAGS += -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -DCOURGETTE_USE_CRC_LIB 
AM_CXXFLAGS = -Wall -Wextra

TESTS =
bin_PROGRAMS =
noinst_PROGRAMS =
noinst_LTLIBRARIES =

SUBDIRS = file_watcher base

EXTRA_DIST =
EXTRA_DIST += build/build_config.h

noinst_LTLIBRARIES += libclient_initialization.la
libclient_initialization_la_SOURCES = client_initialization.h
libclient_initialization_la_SOURCES += client_initialization.cc



bin_PROGRAMS += server
server_SOURCES = UserStorage_server.cpp
server_LDADD =
server_LDADD += libuserthrift.la
server_LDADD += -lthrift -lthriftnb -levent -lpthread -lc
server_LDADD += $(BOOST_THREAD_LIBS)


bin_PROGRAMS += client
client_SOURCES = UserStorage_client.cpp
client_LDADD =
client_LDADD += libuserthrift.la
client_LDADD += -lthrift

# thrift compiler command. Note that the --out value for the output
# directory.
THRIFT_BUILD = $(THRIFT) --gen cpp --out . $<


noinst_LTLIBRARIES += libuserthrift.la
libuserthrift_la_SOURCES =
libuserthrift_la_SOURCES += UserStorage.cpp
libuserthrift_la_SOURCES += UserStorage.h
libuserthrift_la_SOURCES += user_constants.cpp
libuserthrift_la_SOURCES += user_types.cpp
libuserthrift_la_SOURCES += user_constants.h
libuserthrift_la_SOURCES += user_types.h

$(libuserthrift_la_SOURCES): $(srcdir)/user.thrift
	$(THRIFT_BUILD)


noinst_LTLIBRARIES += libhash_chain_digestthrift.la
libhash_chain_digestthrift_la_SOURCES =
libhash_chain_digestthrift_la_SOURCES += VersionExchange.cpp
libhash_chain_digestthrift_la_SOURCES += VersionExchange.h
libhash_chain_digestthrift_la_SOURCES += hash_chain_digest_constants.cpp
libhash_chain_digestthrift_la_SOURCES += hash_chain_digest_constants.h
libhash_chain_digestthrift_la_SOURCES += hash_chain_digest_types.cpp
libhash_chain_digestthrift_la_SOURCES += hash_chain_digest_types.h

$(libhash_chain_digestthrift_la_SOURCES): $(srcdir)/hash_chain_digest.thrift
	$(THRIFT_BUILD)


clean-local: clean-local-check
.PHONY: clean-local-check
clean-local-check:
	-rm -rf \
		$(libuserthrift_la_SOURCES) \
		$(libhash_chain_digestthrift_la_SOURCES) \
		*.skeleton.cpp

noinst_LTLIBRARIES += courgette/libsimple_delta.la
courgette_libsimple_delta_la_SOURCES = courgette/simple_delta.h
courgette_libsimple_delta_la_SOURCES += courgette/simple_delta.cc
courgette_libsimple_delta_la_SOURCES += courgette/courgette.h
courgette_libsimple_delta_la_LIBADD = base/liblogging.la
courgette_libsimple_delta_la_LIBADD += courgette/third_party/libbsdiff.la

bin_PROGRAMS += courgette/courgette_tool
courgette_courgette_tool_SOURCES = courgette/courgette_tool.cc
courgette_courgette_tool_LDADD = base/files/libfile_path.la
courgette_courgette_tool_LDADD += base/libfile_util.la
courgette_courgette_tool_LDADD += courgette/libdisassembler.la
courgette_courgette_tool_LDADD += courgette/libstreams.la
courgette_courgette_tool_LDADD += courgette/third_party/libbsdiff.la
courgette_courgette_tool_LDADD += courgette/libadjustment_method.la
courgette_courgette_tool_LDADD += courgette/libensemble.la

noinst_LTLIBRARIES += courgette/libstreams.la
courgette_libstreams_la_SOURCES = courgette/streams.h
courgette_libstreams_la_SOURCES += courgette/streams.cc
courgette_libstreams_la_SOURCES += courgette/region.h
courgette_libstreams_la_LIBADD = courgette/libmemory_allocator.la
courgette_libstreams_la_LIBADD += base/memory/libsingleton.la

TESTS += courgette/streams_unittest
bin_PROGRAMS += courgette/streams_unittest
courgette_streams_unittest_SOURCES = courgette/streams_unittest.cc
courgette_streams_unittest_LDADD = courgette/libsimple_delta.la
courgette_streams_unittest_LDADD += courgette/libstreams.la
courgette_streams_unittest_LDADD += testing/gtest/lib/libgtest.la
courgette_streams_unittest_LDADD += testing/gtest/lib/libgtest_main.la
courgette_streams_unittest_LDADD += base/liblogging.la

noinst_LTLIBRARIES += courgette/third_party/libbsdiff.la
courgette_third_party_libbsdiff_la_SOURCES = courgette/third_party/bsdiff.h
courgette_third_party_libbsdiff_la_SOURCES += courgette/third_party/bsdiff_apply.cc
courgette_third_party_libbsdiff_la_SOURCES += courgette/third_party/bsdiff_create.cc
courgette_third_party_libbsdiff_la_LIBADD = courgette/libcrc.la $(ZLIB_LIBS)
courgette_third_party_libbsdiff_la_LIBADD += base/libtime.la

noinst_LTLIBRARIES += courgette/libdisassembler.la
courgette_libdisassembler_la_SOURCES = courgette/disassembler.h
courgette_libdisassembler_la_SOURCES += courgette/disassembler.cc
courgette_libdisassembler_la_LIBADD = courgette/libassembly_program.la
courgette_libdisassembler_la_LIBADD += courgette/libdisassembler_win32_x86.la
courgette_libdisassembler_la_LIBADD += courgette/libdisassembler_elf_32_x86.la

noinst_LTLIBRARIES += courgette/libdisassembler_win32_x86.la
courgette_libdisassembler_win32_x86_la_SOURCES = courgette/disassembler_win32_x86.h
courgette_libdisassembler_win32_x86_la_SOURCES += courgette/disassembler_win32_x86.cc
courgette_libdisassembler_win32_x86_la_LIBADD = base/liblogging.la

noinst_LTLIBRARIES += courgette/libdisassembler_elf_32_x86.la
courgette_libdisassembler_elf_32_x86_la_SOURCES = courgette/disassembler_elf_32_x86.h
courgette_libdisassembler_elf_32_x86_la_SOURCES += courgette/disassembler_elf_32_x86.cc
courgette_libdisassembler_elf_32_x86_la_LIBADD = base/liblogging.la


noinst_LTLIBRARIES += courgette/libassembly_program.la
courgette_libassembly_program_la_SOURCES = courgette/assembly_program.h
courgette_libassembly_program_la_SOURCES += courgette/assembly_program.cc
courgette_libassembly_program_la_LIBADD = courgette/libencoded_program.la

noinst_LTLIBRARIES += courgette/libencoded_program.la
courgette_libencoded_program_la_SOURCES = courgette/encoded_program.h
courgette_libencoded_program_la_SOURCES += courgette/encoded_program.cc
courgette_libencoded_program_la_LIBADD = base/libenvironment.la

noinst_LTLIBRARIES += courgette/libadjustment_method.la
courgette_libadjustment_method_la_SOURCES = courgette/adjustment_method.h
courgette_libadjustment_method_la_SOURCES += courgette/adjustment_method.cc
courgette_libadjustment_method_la_SOURCES += courgette/adjustment_method_2.cc

noinst_LTLIBRARIES += courgette/libensemble.la
courgette_libensemble_la_SOURCES = courgette/ensemble.h
courgette_libensemble_la_SOURCES += courgette/ensemble.cc
courgette_libensemble_la_SOURCES += courgette/ensemble_create.cc
courgette_libensemble_la_SOURCES += courgette/ensemble_apply.cc
courgette_libensemble_la_LIBADD = courgette/libdifference_estimator.la
courgette_libensemble_la_LIBADD += courgette/libsimple_delta.la
courgette_libensemble_la_LIBADD += base/files/libmemory_mapped_file.la

noinst_LTLIBRARIES += courgette/libdifference_estimator.la
courgette_libdifference_estimator_la_SOURCES = courgette/difference_estimator.h
courgette_libdifference_estimator_la_SOURCES += courgette/difference_estimator.cc

noinst_LTLIBRARIES += courgette/libcrc.la
courgette_libcrc_la_SOURCES = courgette/crc.h
courgette_libcrc_la_SOURCES += courgette/crc.cc

noinst_LTLIBRARIES += courgette/libmemory_allocator.la
courgette_libmemory_allocator_la_SOURCES = courgette/memory_allocator.h
courgette_libmemory_allocator_la_SOURCES += courgette/memory_allocator.cc
courgette_libmemory_allocator_la_LIBADD = base/files/libfile_path.la
courgette_libmemory_allocator_la_LIBADD += base/libplatform_file.la


bin_PROGRAMS += delta_encoding_main
delta_encoding_main_SOURCES = delta_encoding_main.cc
delta_encoding_main_LDADD =
delta_encoding_main_LDADD += courgette/libsimple_delta.la
delta_encoding_main_LDADD += courgette/libstreams.la
