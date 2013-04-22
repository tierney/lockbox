AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src
AM_CPPFLAGS += -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -DCOURGETTE_USE_CRC_LIB \
	$(DEPS_CFLAGS) $(GTK_CFLAGS)
AM_CXXFLAGS = -Wall -Wextra

SUBDIRS =
TESTS =
bin_PROGRAMS =
noinst_PROGRAMS =
noinst_LTLIBRARIES =


bin_PROGRAMS += lockbox_main
lockbox_main_LDADD = $(DEPS_LIBS) $(LIBEVENT_LIBS) $(GTK_LIBS)
lockbox_main_SOURCES = lockbox_main.cc
lockbox_main_SOURCES +=
lockbox_main_SOURCES += base/run_loop.h
lockbox_main_SOURCES += base/run_loop.cc
lockbox_main_SOURCES += base/pending_task.cc
lockbox_main_SOURCES += base/metrics/statistics_recorder.cc
lockbox_main_SOURCES += base/metrics/histogram.cc
lockbox_main_SOURCES += base/metrics/histogram_base.cc
lockbox_main_SOURCES += base/base_export.h
lockbox_main_SOURCES += base/values.cc
lockbox_main_SOURCES += base/metrics/bucket_ranges.cc
lockbox_main_SOURCES += base/metrics/sample_vector.cc
lockbox_main_SOURCES += \
	base/memory/weak_ptr.cc \
	base/debug/trace_event_impl.h \
	base/debug/trace_event_impl.cc
lockbox_main_SOURCES += base/synchronization/cancellation_flag.cc
lockbox_main_SOURCES += base/synchronization/waitable_event_posix.cc
lockbox_main_SOURCES += base/memory/ref_counted_memory.cc
lockbox_main_SOURCES += base/synchronization/condition_variable_posix.cc
lockbox_main_SOURCES += \
	base/tracking_info.cc
lockbox_main_SOURCES += base/thread_task_runner_handle.cc
lockbox_main_SOURCES += base/message_pump_default.cc
lockbox_main_SOURCES += base/message_pump_libevent.cc
lockbox_main_SOURCES += base/message_pump_gtk.cc
lockbox_main_SOURCES += base/message_pump_glib.cc
lockbox_main_SOURCES += base/metrics/sparse_histogram.cc
lockbox_main_SOURCES += base/metrics/sample_map.cc
lockbox_main_SOURCES += base/metrics/histogram_samples.cc
lockbox_main_SOURCES += base/json/json_string_value_serializer.cc
lockbox_main_SOURCES += base/json/json_writer.cc
lockbox_main_SOURCES += base/threading/thread_checker_impl.cc
lockbox_main_SOURCES += base/message_pump.cc
lockbox_main_SOURCES += base/json/json_reader.cc
lockbox_main_SOURCES += base/json/string_escape.cc
lockbox_main_SOURCES += base/json/json_parser.cc
lockbox_main_SOURCES += base/threading/post_task_and_reply_impl.cc


lockbox_main_LDADD += libfile_path_watcher.la
lockbox_main_LDADD += libfile_path.la
lockbox_main_LDADD += libmessage_loop.la
lockbox_main_LDADD += libmessage_loop_proxy.la
lockbox_main_LDADD += libtracked_objects.la
lockbox_main_LDADD += libref_counted.la
lockbox_main_LDADD += libcallback.la
lockbox_main_LDADD += liblocation.la
lockbox_main_LDADD += libtask_runner.la
lockbox_main_LDADD += liblock.la
lockbox_main_LDADD += libstring_number_conversions.la
lockbox_main_LDADD += libat_exit.la
lockbox_main_LDADD += libtime.la
lockbox_main_LDADD += libstringprintf.la
lockbox_main_LDADD += libthread_restrictions.la
lockbox_main_LDADD += libstring_util.la
lockbox_main_LDADD += libstring_piece.la
lockbox_main_LDADD += libplatform_thread.la
lockbox_main_LDADD += libutf_string_conversions.la
lockbox_main_LDADD += libalias.la
lockbox_main_LDADD += libstring_split.la
lockbox_main_LDADD += libdmg_fp.la
lockbox_main_LDADD += libstring16.la
lockbox_main_LDADD += libsys_string_conversions.la
lockbox_main_LDADD += libpickle.la
lockbox_main_LDADD += libprtime.la
lockbox_main_LDADD += libthread_local.la
lockbox_main_LDADD += liblazy_instance.la
lockbox_main_LDADD += libicu_utf.la
lockbox_main_LDADD += libatomic_internals_x86_gcc.la
lockbox_main_LDADD += libsingleton.la
lockbox_main_LDADD += libthread_id_name_manager.la
lockbox_main_LDADD += libutf_string_conversion_utils.la
lockbox_main_LDADD += libthread_collision_warner.la
lockbox_main_LDADD += libfile_util.la
lockbox_main_LDADD += libplatform_file.la
lockbox_main_LDADD += libtracked_time.la
lockbox_main_LDADD += libthread_local_storage.la
lockbox_main_LDADD += libalternate_timer.la
lockbox_main_LDADD += libprocess_util.la
lockbox_main_LDADD += libdynamic_annotations.la
lockbox_main_LDADD += libprocess.la
lockbox_main_LDADD += libtype_profiler_control.la
lockbox_main_LDADD += libfile_descriptor_shuffle.la
lockbox_main_LDADD += libsys_info.la
lockbox_main_LDADD += liblogging.la
lockbox_main_LDADD += libstack_trace.la
lockbox_main_LDADD += libdebugger.la
lockbox_main_LDADD += libsafe_strerror_posix.la
lockbox_main_LDADD += libvlog.la
lockbox_main_LDADD += libcommand_line.la
lockbox_main_LDADD += libbase_switches.la
lockbox_main_LDADD += libthread.la

noinst_LTLIBRARIES += libsys_info.la
libsys_info_la_SOURCES = base/sys_info.h
libsys_info_la_SOURCES += base/sys_info_posix.cc

noinst_LTLIBRARIES += libfile_descriptor_shuffle.la
libfile_descriptor_shuffle_la_SOURCES = base/posix/file_descriptor_shuffle.h
libfile_descriptor_shuffle_la_SOURCES += base/posix/file_descriptor_shuffle.cc

noinst_LTLIBRARIES += libtype_profiler_control.la
libtype_profiler_control_la_SOURCES = base/allocator/type_profiler_control.h
libtype_profiler_control_la_SOURCES += base/allocator/type_profiler_control.cc

noinst_LTLIBRARIES += libprocess.la
libprocess_la_SOURCES = base/process.h
libprocess_la_SOURCES += base/process_posix.cc
libprocess_la_SOURCES += base/process_linux.cc

noinst_LTLIBRARIES += libdynamic_annotations.la
libdynamic_annotations_la_SOURCES = base/third_party/dynamic_annotations/dynamic_annotations.h
libdynamic_annotations_la_SOURCES += base/third_party/dynamic_annotations/dynamic_annotations.c

noinst_LTLIBRARIES += libprocess_util.la
libprocess_util_la_SOURCES = base/process_util.h
libprocess_util_la_SOURCES += base/process_util.cc
libprocess_util_la_SOURCES += base/process_util_posix.cc
libprocess_util_la_SOURCES += base/process_util_linux.cc

noinst_LTLIBRARIES += libalternate_timer.la
libalternate_timer_la_SOURCES = base/profiler/alternate_timer.h
libalternate_timer_la_SOURCES += base/profiler/alternate_timer.cc

noinst_LTLIBRARIES += libthread_local_storage.la
libthread_local_storage_la_SOURCES = base/threading/thread_local_storage_posix.cc
libthread_local_storage_la_SOURCES += base/threading/thread_local_storage.h

noinst_LTLIBRARIES += libtracked_time.la
libtracked_time_la_SOURCES = base/profiler/tracked_time.h
libtracked_time_la_SOURCES += base/profiler/tracked_time.cc

noinst_LTLIBRARIES += libthread_collision_warner.la
libthread_collision_warner_la_SOURCES = base/threading/thread_collision_warner.h
libthread_collision_warner_la_SOURCES += base/threading/thread_collision_warner.cc

noinst_LTLIBRARIES += libutf_string_conversion_utils.la
libutf_string_conversion_utils_la_SOURCES = base/strings/utf_string_conversion_utils.h
libutf_string_conversion_utils_la_SOURCES += base/strings/utf_string_conversion_utils.cc

noinst_LTLIBRARIES += libthread_id_name_manager.la
libthread_id_name_manager_la_SOURCES = base/threading/thread_id_name_manager.h
libthread_id_name_manager_la_SOURCES += base/threading/thread_id_name_manager.cc

noinst_LTLIBRARIES += libsingleton.la
libsingleton_la_SOURCES = base/memory/singleton.h base/memory/singleton.cc

noinst_LTLIBRARIES += libatomic_internals_x86_gcc.la
libatomic_internals_x86_gcc_la_SOURCES = base/atomicops_internals_x86_gcc.cc
libatomic_internals_x86_gcc_la_SOURCES += base/atomicops_internals_x86_gcc.h

noinst_LTLIBRARIES += libicu_utf.la
libicu_utf_la_SOURCES = base/third_party/icu/icu_utf.h
libicu_utf_la_SOURCES += base/third_party/icu/icu_utf.cc

noinst_LTLIBRARIES += libthread_local.la
libthread_local_la_SOURCES = base/threading/thread_local.h
libthread_local_la_SOURCES += base/threading/thread_local_posix.cc

noinst_LTLIBRARIES += libprtime.la
libprtime_la_SOURCES = base/third_party/nspr/prtime.h
libprtime_la_SOURCES += base/third_party/nspr/prtime.cc

noinst_LTLIBRARIES += libpickle.la
libpickle_la_SOURCES = base/pickle.h
libpickle_la_SOURCES += base/pickle.cc

noinst_LTLIBRARIES += libsys_string_conversions.la
libsys_string_conversions_la_SOURCES = base/strings/sys_string_conversions.h
libsys_string_conversions_la_SOURCES += base/strings/sys_string_conversions_posix.cc

noinst_LTLIBRARIES += libstring16.la
libstring16_la_SOURCES = base/string16.h
libstring16_la_SOURCES += base/string16.cc

noinst_LTLIBRARIES += libdmg_fp.la
libdmg_fp_la_SOURCES = base/third_party/dmg_fp/g_fmt.cc
libdmg_fp_la_SOURCES += base/third_party/dmg_fp/dtoa.cc


noinst_LTLIBRARIES += libstring_split.la
libstring_split_la_SOURCES = base/strings/string_split.h
libstring_split_la_SOURCES += base/strings/string_split.cc


noinst_LTLIBRARIES += libstack_trace.la
libstack_trace_la_SOURCES = base/debug/stack_trace.h
libstack_trace_la_SOURCES += base/debug/stack_trace_posix.cc
libstack_trace_la_SOURCES += base/debug/stack_trace.cc

noinst_LTLIBRARIES += libalias.la
libalias_la_SOURCES = base/debug/alias.cc
libalias_la_SOURCES += base/debug/alias.h



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


noinst_LTLIBRARIES += libfile_path_watcher.la
libfile_path_watcher_la_CPPFLAGS = -I$(top_srcdir)/src $(DEPS_CFLAGS)
libfile_path_watcher_la_LIBS = $(DEPS_LIBS)
libfile_path_watcher_la_SOURCES = base/files/file_path_watcher.h
libfile_path_watcher_la_SOURCES += base/files/file_path_watcher.cc
libfile_path_watcher_la_SOURCES += base/files/file_path_watcher_@FILE_PATH_WATCHER_SUFFIX@.cc
libfile_path_watcher_la_SOURCES += \
 base/base_export.h base/basictypes.h base/port.h build/build_config.h \
 base/callback.h base/callback_forward.h base/callback_internal.h \
 base/memory/ref_counted.h base/atomic_ref_count.h base/atomicops.h \
 base/atomicops_internals_x86_gcc.h \
 base/third_party/dynamic_annotations/dynamic_annotations.h \
 base/compiler_specific.h base/threading/thread_collision_warner.h \
 base/memory/scoped_ptr.h base/move.h base/template_util.h \
 base/files/file_path.h base/hash_tables.h base/string16.h \
 base/strings/string_piece.h base/message_loop_proxy.h \
 base/message_loop/message_loop_proxy.h base/single_thread_task_runner.h \
 base/sequenced_task_runner.h base/sequenced_task_runner_helpers.h \
 base/task_runner.h base/time.h base/bind.h base/bind_internal.h \
 base/bind_helpers.h base/memory/weak_ptr.h base/logging.h \
 base/debug/debugger.h base/threading/thread_checker.h \
 base/threading/thread_checker_impl.h base/synchronization/lock.h \
 base/synchronization/lock_impl.h base/threading/platform_thread.h \
 base/memory/raw_scoped_refptr_mismatch_checker.h base/tuple.h \
 base/file_util.h base/platform_file.h base/file_descriptor_posix.h \
 base/posix/eintr_wrapper.h base/lazy_instance.h \
 base/memory/aligned_memory.h base/threading/thread_restrictions.h \
 base/location.h base/message_loop.h base/message_pump.h \
 base/observer_list.h base/pending_task.h base/tracking_info.h \
 base/message_pump_libevent.h base/message_pump_gtk.h \
 base/message_pump_glib.h base/threading/thread.h
libfile_path_watcher_la_SOURCES += base/message_loop/message_loop_proxy_impl.cc

noinst_LTLIBRARIES += libthread.la
libthread_la_SOURCES = base/threading/thread.h
libthread_la_SOURCES += base/threading/thread.cc

noinst_LTLIBRARIES += libfile_util.la
libfile_util_la_SOURCES = base/file_util.h
libfile_util_la_SOURCES += base/file_util.cc
libfile_util_la_SOURCES += base/file_util_linux.cc
libfile_util_la_SOURCES += base/file_util_posix.cc

noinst_LTLIBRARIES += liblazy_instance.la
liblazy_instance_la_SOURCES = base/lazy_instance.h
liblazy_instance_la_SOURCES += base/lazy_instance.cc

noinst_LTLIBRARIES += libfile_path.la
libfile_path_la_SOURCES = base/files/file_path.cc

noinst_LTLIBRARIES += libmessage_loop.la
libmessage_loop_la_SOURCES = base/message_loop.h
libmessage_loop_la_SOURCES += base/message_loop.cc

noinst_LTLIBRARIES += libmessage_loop_proxy.la
libmessage_loop_proxy_la_SOURCES = base/message_loop/message_loop_proxy.h
libmessage_loop_proxy_la_SOURCES += base/message_loop/message_loop_proxy.cc

noinst_LTLIBRARIES += libtracked_objects.la
libtracked_objects_la_SOURCES = base/tracked_objects.h
libtracked_objects_la_SOURCES += base/tracked_objects.cc

noinst_LTLIBRARIES += libref_counted.la
libref_counted_la_SOURCES = base/memory/ref_counted.h
libref_counted_la_SOURCES += base/memory/ref_counted.cc

noinst_LTLIBRARIES += libcallback.la
libcallback_la_SOURCES = base/callback.h
libcallback_la_SOURCES += base/callback_forward.h
libcallback_la_SOURCES += base/cancelable_callback.h
libcallback_la_SOURCES += base/callback_internal.cc
libcallback_la_SOURCES += base/callback_helpers.h

noinst_LTLIBRARIES += liblocation.la
liblocation_la_SOURCES = base/location.h base/location.cc

noinst_LTLIBRARIES += libtask_runner.la
libtask_runner_la_SOURCES = base/task_runner.h base/task_runner.cc base/task_runner_util.h

noinst_LTLIBRARIES += liblock.la
liblock_la_SOURCES = base/synchronization/lock_impl.h
liblock_la_SOURCES += base/synchronization/lock_impl_posix.cc
liblock_la_SOURCES += base/synchronization/lock.h
liblock_la_SOURCES += base/synchronization/lock.cc


noinst_LTLIBRARIES += libsimple_delta.la
libsimple_delta_la_SOURCES = courgette/simple_delta.h
libsimple_delta_la_SOURCES += courgette/simple_delta.cc

noinst_LTLIBRARIES += liblogging.la
liblogging_la_SOURCES = base/logging.h base/logging.cc

noinst_LTLIBRARIES += libcourgette_tool.la
libcourgette_tool_la_SOURCES = courgette/courgette_tool.cc

noinst_LTLIBRARIES += libstreams.la
libstreams_la_SOURCES = courgette/streams.h
libstreams_la_SOURCES += courgette/streams.cc


# TESTS += streams_unittest
# bin_PROGRAMS += streams_unittest
# streams_unittest_SOURCES = courgette/streams_unittest.cc
# streams_unittest_LDADD = libsimple_delta.la
# streams_unittest_LDADD += liblock.la

noinst_LTLIBRARIES += libbsdiff.la
libbsdiff_la_SOURCES = courgette/third_party/bsdiff.h
libbsdiff_la_SOURCES += courgette/third_party/bsdiff_apply.cc
libbsdiff_la_SOURCES += courgette/third_party/bsdiff_create.cc

noinst_LTLIBRARIES += libcommand_line.la
libcommand_line_la_SOURCES = base/command_line.h
libcommand_line_la_SOURCES += base/command_line.cc

noinst_LTLIBRARIES += libdisassembler.la
libdisassembler_la_SOURCES = courgette/disassembler.h
libdisassembler_la_SOURCES += courgette/disassembler.cc

noinst_LTLIBRARIES += libassembly_program.la
libassembly_program_la_SOURCES = courgette/assembly_program.h
libassembly_program_la_SOURCES += courgette/assembly_program.cc

noinst_LTLIBRARIES += libstring_number_conversions.la
libstring_number_conversions_la_SOURCES =
libstring_number_conversions_la_SOURCES += base/strings/string_number_conversions.h
libstring_number_conversions_la_SOURCES += base/strings/string_number_conversions.cc

noinst_LTLIBRARIES += libencoded_program.la
libencoded_program_la_SOURCES = courgette/encoded_program.h
libencoded_program_la_SOURCES += courgette/encoded_program.cc

noinst_LTLIBRARIES += libadjustment_method.la
libadjustment_method_la_SOURCES = courgette/adjustment_method.h
libadjustment_method_la_SOURCES += courgette/adjustment_method.cc
libadjustment_method_la_SOURCES += courgette/adjustment_method_2.cc

noinst_LTLIBRARIES += libat_exit.la
libat_exit_la_SOURCES = base/at_exit.cc
libat_exit_la_SOURCES += base/at_exit.h

noinst_LTLIBRARIES += libtime.la
libtime_la_SOURCES = base/time.h base/time.cc base/time_posix.cc

noinst_LTLIBRARIES += libensemble.la
libensemble_la_SOURCES = courgette/ensemble.h
libensemble_la_SOURCES += courgette/ensemble.cc
libensemble_la_SOURCES += courgette/ensemble_create.cc
libensemble_la_SOURCES += courgette/ensemble_apply.cc

noinst_LTLIBRARIES += libdifference_estimator.la
libdifference_estimator_la_SOURCES = courgette/difference_estimator.h
libdifference_estimator_la_SOURCES += courgette/difference_estimator.cc

noinst_LTLIBRARIES += libcrc.la
libcrc_la_SOURCES = courgette/crc.h
libcrc_la_SOURCES += courgette/crc.cc

noinst_LTLIBRARIES += libmemory_mapped_file.la
libmemory_mapped_file_la_SOURCES =
libmemory_mapped_file_la_SOURCES += base/files/memory_mapped_file.h
libmemory_mapped_file_la_SOURCES += base/files/memory_mapped_file.cc
libmemory_mapped_file_la_SOURCES += base/files/memory_mapped_file_posix.cc

noinst_LTLIBRARIES += libplatform_file.la
libplatform_file_la_SOURCES = base/platform_file.cc
libplatform_file_la_SOURCES += base/platform_file_posix.cc

noinst_LTLIBRARIES += libstringprintf.la
libstringprintf_la_SOURCES = base/stringprintf.h
libstringprintf_la_SOURCES += base/stringprintf.cc

noinst_LTLIBRARIES += libthread_restrictions.la
libthread_restrictions_la_SOURCES = base/threading/thread_restrictions.h
libthread_restrictions_la_SOURCES += base/threading/thread_restrictions.cc

noinst_LTLIBRARIES += libstring_util.la
libstring_util_la_SOURCES = base/string_util.cc
libstring_util_la_SOURCES += base/string_util.h

noinst_LTLIBRARIES += libstring_piece.la
libstring_piece_la_SOURCES = base/strings/string_piece.cc
libstring_piece_la_SOURCES += base/strings/string_piece.h

noinst_LTLIBRARIES += libplatform_thread.la
libplatform_thread_la_SOURCES =
libplatform_thread_la_SOURCES += base/threading/platform_thread.h
libplatform_thread_la_SOURCES += base/threading/platform_thread_posix.cc

noinst_LTLIBRARIES += libutf_string_conversions.la
libutf_string_conversions_la_SOURCES = base/utf_string_conversions.cc
libutf_string_conversions_la_SOURCES += base/utf_string_conversions.h

noinst_LTLIBRARIES += libdebugger.la
libdebugger_la_SOURCES = base/debug/debugger.cc
libdebugger_la_SOURCES += base/debug/debugger.h
libdebugger_la_SOURCES += base/debug/debugger_posix.cc

noinst_LTLIBRARIES += libsafe_strerror_posix.la
libsafe_strerror_posix_la_SOURCES = base/safe_strerror_posix.h
libsafe_strerror_posix_la_SOURCES += base/safe_strerror_posix.cc

noinst_LTLIBRARIES += libvlog.la
libvlog_la_SOURCES = base/vlog.h
libvlog_la_SOURCES += base/vlog.cc

noinst_LTLIBRARIES += libbase_switches.la
libbase_switches_la_SOURCES = base/base_switches.h
libbase_switches_la_SOURCES += base/base_switches.cc

noinst_LTLIBRARIES += libdisassembler_win32_x86.la
libdisassembler_win32_x86_la_SOURCES = courgette/disassembler_win32_x86.h
libdisassembler_win32_x86_la_SOURCES += courgette/disassembler_win32_x86.cc

noinst_LTLIBRARIES += libdisassembler_elf_32_x86.la
libdisassembler_elf_32_x86_la_SOURCES = courgette/disassembler_elf_32_x86.h
libdisassembler_elf_32_x86_la_SOURCES += courgette/disassembler_elf_32_x86.cc

noinst_LTLIBRARIES += libenvironment.la
libenvironment_la_SOURCES = base/environment.h
libenvironment_la_SOURCES += base/environment.cc



bin_PROGRAMS += delta_encoding_main
delta_encoding_main_SOURCES = delta_encoding_main.cc
delta_encoding_main_LDADD =

delta_encoding_main_LDADD += libcourgette_tool.la
delta_encoding_main_LDADD += libsimple_delta.la
delta_encoding_main_LDADD += liblogging.la
delta_encoding_main_LDADD += libbsdiff.la
delta_encoding_main_LDADD += libstreams.la
delta_encoding_main_LDADD += libcommand_line.la
delta_encoding_main_LDADD += libdisassembler.la
delta_encoding_main_LDADD += libassembly_program.la
delta_encoding_main_LDADD += libencoded_program.la
delta_encoding_main_LDADD += libadjustment_method.la
delta_encoding_main_LDADD += libvlog.la
delta_encoding_main_LDADD += libstring_number_conversions.la
delta_encoding_main_LDADD += libfile_path.la
delta_encoding_main_LDADD += libtime.la
delta_encoding_main_LDADD += libensemble.la
delta_encoding_main_LDADD += libdifference_estimator.la
delta_encoding_main_LDADD += libcrc.la $(ZLIB_LIBS)
delta_encoding_main_LDADD += libmemory_mapped_file.la
delta_encoding_main_LDADD += libstring_util.la
delta_encoding_main_LDADD += libthread_restrictions.la
delta_encoding_main_LDADD += libstring_piece.la
delta_encoding_main_LDADD += libutf_string_conversions.la
delta_encoding_main_LDADD += libstack_trace.la
delta_encoding_main_LDADD += libalias.la
delta_encoding_main_LDADD += libdebugger.la
delta_encoding_main_LDADD += libstringprintf.la
delta_encoding_main_LDADD += libsafe_strerror_posix.la
delta_encoding_main_LDADD += libbase_switches.la
delta_encoding_main_LDADD += libstring_split.la
delta_encoding_main_LDADD += libdisassembler_win32_x86.la
delta_encoding_main_LDADD += libdisassembler_elf_32_x86.la
delta_encoding_main_LDADD += libenvironment.la
delta_encoding_main_LDADD += libdmg_fp.la
delta_encoding_main_LDADD += libstring16.la
delta_encoding_main_LDADD += libsys_string_conversions.la
delta_encoding_main_LDADD += libpickle.la
delta_encoding_main_LDADD += libprtime.la
delta_encoding_main_LDADD += libthread_local.la
delta_encoding_main_LDADD += liblazy_instance.la
delta_encoding_main_LDADD += libicu_utf.la
delta_encoding_main_LDADD += libatomic_internals_x86_gcc.la
delta_encoding_main_LDADD += libsingleton.la
delta_encoding_main_LDADD += libat_exit.la
delta_encoding_main_LDADD += libutf_string_conversion_utils.la
delta_encoding_main_LDADD += liblock.la
delta_encoding_main_LDADD += libref_counted.la
delta_encoding_main_LDADD += libcallback.la
delta_encoding_main_LDADD += libthread_collision_warner.la
delta_encoding_main_LDADD += libplatform_thread.la
delta_encoding_main_LDADD += libthread_id_name_manager.la
delta_encoding_main_LDADD += libtracked_objects.la
delta_encoding_main_LDADD += liblocation.la
delta_encoding_main_LDADD += libtracked_time.la
delta_encoding_main_LDADD += libthread_local_storage.la
delta_encoding_main_LDADD += libalternate_timer.la
delta_encoding_main_LDADD += libprocess_util.la
delta_encoding_main_LDADD += libdynamic_annotations.la
delta_encoding_main_LDADD += libprocess.la
delta_encoding_main_LDADD += libtype_profiler_control.la
delta_encoding_main_LDADD += libfile_descriptor_shuffle.la
delta_encoding_main_LDADD += libfile_util.la
delta_encoding_main_LDADD += libsys_info.la
delta_encoding_main_LDADD += libplatform_file.la
