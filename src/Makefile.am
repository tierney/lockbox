AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src \
	-I$(top_srcdir)/src/testing/gtest/include
AM_CPPFLAGS += -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -DCOURGETTE_USE_CRC_LIB \
	$(DEPS_CFLAGS) $(GTK_CFLAGS)
AM_CXXFLAGS = -Wall -Wextra

TESTS =
bin_PROGRAMS =
noinst_PROGRAMS =
noinst_LTLIBRARIES =

SUBDIRS = file_watcher base

EXTRA_DIST =
EXTRA_DIST += base/base_export.h
EXTRA_DIST += base/basictypes.h
EXTRA_DIST += base/port.h
EXTRA_DIST += build/build_config.h
EXTRA_DIST += base/compiler_specific.h
EXTRA_DIST += base/memory/scoped_ptr.h
EXTRA_DIST += base/move.h
EXTRA_DIST += base/template_util.h
EXTRA_DIST += base/file_descriptor_posix.h

# bin_PROGRAMS += qfilesystemwatcher_main
# qfilesystemwatcher_main_SOURCES = qfilesystemwatcher_main.cc
# qfilesystemwatcher_main_CXXFLAGS = $(QTCORE_CFLAGS) -fPIC
# qfilesystemwatcher_main_LDADD = $(QTCORE_LIB) $(QTBOOTSTRAP_LIB)

# noinst_LTLIBRARIES += base/librand_util.la
# base_librand_util_la_SOURCES =
# base_librand_util_la_SOURCES += base/rand_util.h
# base_librand_util_la_SOURCES += base/rand_util.cc
# base_librand_util_la_SOURCES += base/rand_util_posix.cc

# noinst_LTLIBRARIES += testing/gtest/src/libgtest.la
# testing_gtest_src_libgtest_la_CPPFLAGS = -Itesting/gtest
# testing_gtest_src_libgtest_la_SOURCES = testing/gtest/src/gtest.cc
# testing_gtest_src_libgtest_la_SOURCES += testing/gtest/src/gtest-port.cc

noinst_LTLIBRARIES += libclient_initialization.la
libclient_initialization_la_SOURCES = client_initialization.h
libclient_initialization_la_SOURCES += client_initialization.cc

noinst_LTLIBRARIES += base/librand_util.la
base_librand_util_la_SOURCES =
base_librand_util_la_SOURCES += base/rand_util.h
base_librand_util_la_SOURCES += base/rand_util.cc
base_librand_util_la_SOURCES += base/rand_util_posix.cc
noinst_LTLIBRARIES += base/metrics/libbucket_ranges.la
base_metrics_libbucket_ranges_la_SOURCES = base/metrics/bucket_ranges.h
base_metrics_libbucket_ranges_la_SOURCES += base/metrics/bucket_ranges.cc

noinst_LTLIBRARIES += base/metrics/libsample_vector.la
base_metrics_libsample_vector_la_SOURCES = base/metrics/sample_vector.h
base_metrics_libsample_vector_la_SOURCES += base/metrics/sample_vector.cc
base_metrics_libsample_vector_la_LIBADD = base/metrics/libhistogram_samples.la

noinst_LTLIBRARIES += base/memory/libweak_ptr.la
base_memory_libweak_ptr_la_SOURCES = base/memory/weak_ptr.h
base_memory_libweak_ptr_la_SOURCES += base/memory/weak_ptr.cc

noinst_LTLIBRARIES += base/synchronization/libcancellation_flag.la
base_synchronization_libcancellation_flag_la_SOURCES = base/synchronization/cancellation_flag.h
base_synchronization_libcancellation_flag_la_SOURCES += base/synchronization/cancellation_flag.cc

noinst_LTLIBRARIES += base/synchronization/libwaitable_event.la
base_synchronization_libwaitable_event_la_SOURCES = base/synchronization/waitable_event.h
base_synchronization_libwaitable_event_la_SOURCES += base/synchronization/waitable_event_posix.cc
base_synchronization_libwaitable_event_la_LIBADD = base/synchronization/libcondition_variable_posix.la

noinst_LTLIBRARIES += base/synchronization/libcondition_variable_posix.la
base_synchronization_libcondition_variable_posix_la_SOURCES = base/synchronization/condition_variable.h
base_synchronization_libcondition_variable_posix_la_SOURCES += base/synchronization/condition_variable_posix.cc

noinst_LTLIBRARIES += base/libthread_task_runner_handle.la
base_libthread_task_runner_handle_la_SOURCES = base/thread_task_runner_handle.h
base_libthread_task_runner_handle_la_SOURCES += base/thread_task_runner_handle.cc


noinst_LTLIBRARIES += base/metrics/libsample_map.la
base_metrics_libsample_map_la_SOURCES = base/metrics/sample_map.h
base_metrics_libsample_map_la_SOURCES += base/metrics/sample_map.cc

noinst_LTLIBRARIES += base/metrics/libhistogram_samples.la
base_metrics_libhistogram_samples_la_SOURCES = base/metrics/histogram_samples.h
base_metrics_libhistogram_samples_la_SOURCES += base/metrics/histogram_samples.cc

noinst_LTLIBRARIES += base/threading/libthread_checker_impl.la
base_threading_libthread_checker_impl_la_SOURCES = base/threading/thread_checker_impl.h
base_threading_libthread_checker_impl_la_SOURCES += base/threading/thread_checker_impl.cc


noinst_LTLIBRARIES += base/libvalues.la
base_libvalues_la_SOURCES = base/values.h
base_libvalues_la_SOURCES += base/values.cc

noinst_LTLIBRARIES += base/metrics/libstatistics_recorder.la
base_metrics_libstatistics_recorder_la_SOURCES = base/metrics/statistics_recorder.h
base_metrics_libstatistics_recorder_la_SOURCES += base/metrics/statistics_recorder.cc


noinst_LTLIBRARIES += base/debug/libtrace_event.la
base_debug_libtrace_event_la_SOURCES = base/debug/trace_event.h
base_debug_libtrace_event_la_SOURCES += base/debug/trace_event_impl.cc
base_debug_libtrace_event_la_SOURCES += base/debug/trace_event_impl.h
base_debug_libtrace_event_la_SOURCES += base/hash_tables.h
base_debug_libtrace_event_la_SOURCES += base/memory/scoped_vector.h
base_debug_libtrace_event_la_SOURCES += base/observer_list.h
base_debug_libtrace_event_la_SOURCES += base/observer_list_threadsafe.h

base_debug_libtrace_event_la_LIBADD = base/memory/libref_counted_memory.la
base_debug_libtrace_event_la_LIBADD += base/libstring_util.la
base_debug_libtrace_event_la_LIBADD += base/libcallback.la
base_debug_libtrace_event_la_LIBADD += base/synchronization/libcondition_variable_posix.la
# base_debug_libtrace_event_la_LIBADD += base/threading/libthread.la
base_debug_libtrace_event_la_LIBADD += base/libtimer.la
base_debug_libtrace_event_la_LIBADD += base/threading/libplatform_thread.la
base_debug_libtrace_event_la_LIBADD += base/synchronization/libcancellation_flag.la
base_debug_libtrace_event_la_LIBADD += base/memory/libsingleton.la
base_debug_libtrace_event_la_LIBADD += base/strings/libstring_piece.la

noinst_LTLIBRARIES += base/libpending_task.la
base_libpending_task_la_SOURCES = base/pending_task.h
base_libpending_task_la_SOURCES += base/pending_task.cc

noinst_LTLIBRARIES += base/librun_loop.la
base_librun_loop_la_SOURCES = base/run_loop.h
base_librun_loop_la_SOURCES += base/run_loop.cc
base_librun_loop_la_LIBADD = base/memory/libweak_ptr.la

noinst_LTLIBRARIES += base/memory/libref_counted_memory.la
base_memory_libref_counted_memory_la_SOURCES = base/memory/ref_counted_memory.h
base_memory_libref_counted_memory_la_SOURCES += base/memory/ref_counted_memory.cc

noinst_LTLIBRARIES += base/libtracking_info.la
base_libtracking_info_la_SOURCES = base/tracking_info.h
base_libtracking_info_la_SOURCES += base/tracking_info.cc

noinst_LTLIBRARIES += base/libmessage_pump_default.la
base_libmessage_pump_default_la_SOURCES = base/message_pump_default.cc
base_libmessage_pump_default_la_SOURCES += base/message_pump_default.h
base_libmessage_pump_default_la_LIBADD = base/synchronization/libwaitable_event.la

noinst_LTLIBRARIES += base/libmessage_pump_glib.la
base_libmessage_pump_glib_la_SOURCES = base/message_pump_glib.cc
base_libmessage_pump_glib_la_SOURCES += base/message_pump_glib.h
base_libmessage_pump_glib_la_LIBADD = base/memory/libweak_ptr.la

noinst_LTLIBRARIES += base/libmessage_pump_gtk.la
base_libmessage_pump_gtk_la_SOURCES = base/message_pump_gtk.cc
base_libmessage_pump_gtk_la_SOURCES += base/message_pump_gtk.h
base_libmessage_pump_gtk_la_LIBADD = $(GTK_LIBS)
base_libmessage_pump_gtk_la_LIBADD += base/memory/libweak_ptr.la

noinst_LTLIBRARIES += base/libmessage_pump_libevent.la
base_libmessage_pump_libevent_la_SOURCES = base/message_pump_libevent.cc
base_libmessage_pump_libevent_la_SOURCES += base/message_pump_libevent.h
base_libmessage_pump_libevent_la_LIBADD = $(LIBEVENT_LIBS)
base_libmessage_pump_libevent_la_LIBADD += base/memory/libweak_ptr.la
base_libmessage_pump_libevent_la_LIBADD += base/threading/libthread_checker_impl.la

noinst_LTLIBRARIES += base/libmessage_pump.la
base_libmessage_pump_la_SOURCES = base/message_pump.cc
base_libmessage_pump_la_SOURCES += base/message_pump.h
base_libmessage_pump_la_LIBADD = base/libmessage_pump_default.la
base_libmessage_pump_la_LIBADD += base/libmessage_pump_libevent.la
base_libmessage_pump_la_LIBADD += base/libmessage_pump_gtk.la
base_libmessage_pump_la_LIBADD += base/libmessage_pump_glib.la

noinst_LTLIBRARIES += base/metrics/libsparse_histogram.la
base_metrics_libsparse_histogram_la_SOURCES = base/metrics/sparse_histogram.cc
base_metrics_libsparse_histogram_la_SOURCES += base/metrics/sparse_histogram.h
base_metrics_libsparse_histogram_la_LIBADD = base/metrics/libsample_map.la
base_metrics_libsparse_histogram_la_LIBADD += base/metrics/libhistogram_samples.la
# base_metrics_libsparse_histogram_la_LIBADD += base/metrics/libhistogram_base.la
base_metrics_libsparse_histogram_la_LIBADD += base/synchronization/liblock.la


noinst_LTLIBRARIES += base/json/libjson_string_value_serializer.la
base_json_libjson_string_value_serializer_la_SOURCES = base/json/json_string_value_serializer.h
base_json_libjson_string_value_serializer_la_SOURCES += base/json/json_string_value_serializer.cc
base_json_libjson_string_value_serializer_la_LIBADD = base/json/libjson_reader.la
base_json_libjson_string_value_serializer_la_LIBADD += base/json/libjson_writer.la

noinst_LTLIBRARIES += base/json/libstring_escape.la
base_json_libstring_escape_la_SOURCES = base/json/string_escape.h
base_json_libstring_escape_la_SOURCES += base/json/string_escape.cc

noinst_LTLIBRARIES += base/json/libjson_writer.la
base_json_libjson_writer_la_SOURCES = base/json/json_writer.h
base_json_libjson_writer_la_SOURCES += base/json/json_writer.cc
base_json_libjson_writer_la_LIBADD = base/json/libstring_escape.la

noinst_LTLIBRARIES += base/json/libjson_parser.la
base_json_libjson_parser_la_SOURCES = base/json/json_parser.h
base_json_libjson_parser_la_SOURCES += base/json/json_parser.cc

noinst_LTLIBRARIES += base/json/libjson_reader.la
base_json_libjson_reader_la_SOURCES = base/json/json_reader.h
base_json_libjson_reader_la_SOURCES += base/json/json_reader.cc
base_json_libjson_reader_la_LIBADD = base/strings/libstring_piece.la
base_json_libjson_reader_la_LIBADD += base/json/libjson_parser.la

noinst_LTLIBRARIES += base/threading/libpost_task_and_reply_impl.la
base_threading_libpost_task_and_reply_impl_la_SOURCES = base/threading/post_task_and_reply_impl.cc
base_threading_libpost_task_and_reply_impl_la_LIBADD = base/message_loop/libmessage_loop_proxy.la

noinst_LTLIBRARIES += base/metrics/libhistogram.la
base_metrics_libhistogram_la_SOURCES = base/metrics/histogram.cc
base_metrics_libhistogram_la_SOURCES += base/metrics/histogram.h
base_metrics_libhistogram_la_LIBADD = base/metrics/libhistogram_base.la
base_metrics_libhistogram_la_LIBADD += base/metrics/libhistogram_samples.la
# base_metrics_libhistogram_la_LIBADD += base/json/libjson_reader.la
# base_metrics_libhistogram_la_LIBADD += base/json/libjson_writer.la
# base_metrics_libhistogram_la_LIBADD += base/json/libjson_string_value_serializer.la
# base_metrics_libhistogram_la_LIBADD += base/metrics/libsparse_histogram.la
base_metrics_libhistogram_la_LIBADD += base/libvalues.la
base_metrics_libhistogram_la_LIBADD += base/metrics/libbucket_ranges.la
base_metrics_libhistogram_la_LIBADD += base/metrics/libsample_vector.la
base_metrics_libhistogram_la_LIBADD += base/libatomicops.la
base_metrics_libhistogram_la_LIBADD += base/libtime.la

base_metrics_libhistogram_la_LIBADD += base/metrics/libstatistics_recorder.la



noinst_LTLIBRARIES += base/metrics/libhistogram_base.la
base_metrics_libhistogram_base_la_SOURCES = base/metrics/histogram_base.h
base_metrics_libhistogram_base_la_SOURCES += base/metrics/histogram_base.cc
base_metrics_libhistogram_base_la_LIBADD = base/libtime.la
base_metrics_libhistogram_base_la_LIBADD += base/json/libjson_string_value_serializer.la
base_metrics_libhistogram_base_la_LIBADD += base/metrics/libsparse_histogram.la


noinst_LTLIBRARIES += base/libsys_info.la
base_libsys_info_la_SOURCES = base/sys_info.h
base_libsys_info_la_SOURCES += base/sys_info_posix.cc

noinst_LTLIBRARIES += base/posix/libfile_descriptor_shuffle.la
base_posix_libfile_descriptor_shuffle_la_SOURCES = base/posix/file_descriptor_shuffle.h
base_posix_libfile_descriptor_shuffle_la_SOURCES += base/posix/file_descriptor_shuffle.cc

noinst_LTLIBRARIES += base/allocator/libtype_profiler_control.la
base_allocator_libtype_profiler_control_la_SOURCES = base/allocator/type_profiler_control.h
base_allocator_libtype_profiler_control_la_SOURCES += base/allocator/type_profiler_control.cc

noinst_LTLIBRARIES += base/libprocess.la
base_libprocess_la_SOURCES = base/process.h
base_libprocess_la_SOURCES += base/process_posix.cc
base_libprocess_la_SOURCES += base/process_linux.cc

noinst_LTLIBRARIES += base/third_party/dynamic_annotations/libdynamic_annotations.la
base_third_party_dynamic_annotations_libdynamic_annotations_la_SOURCES = base/third_party/dynamic_annotations/dynamic_annotations.h
base_third_party_dynamic_annotations_libdynamic_annotations_la_SOURCES += base/third_party/dynamic_annotations/dynamic_annotations.c

noinst_LTLIBRARIES += base/libprocess_util.la
base_libprocess_util_la_SOURCES = base/process_util.h
base_libprocess_util_la_SOURCES += base/process_util.cc
base_libprocess_util_la_SOURCES += base/process_util_posix.cc
base_libprocess_util_la_SOURCES += base/process_util_linux.cc
base_libprocess_util_la_LIBADD = base/libcommand_line.la
base_libprocess_util_la_LIBADD += base/threading/libthread_restrictions.la
base_libprocess_util_la_LIBADD += base/files/libfile_path.la
base_libprocess_util_la_LIBADD += base/threading/libthread_local.la
base_libprocess_util_la_LIBADD += base/strings/libsys_string_conversions.la
base_libprocess_util_la_LIBADD += base/libpickle.la
base_libprocess_util_la_LIBADD += base/libtime.la
base_libprocess_util_la_LIBADD += base/libsys_info.la
base_libprocess_util_la_LIBADD += base/third_party/dynamic_annotations/libdynamic_annotations.la
base_libprocess_util_la_LIBADD += base/libprocess.la
base_libprocess_util_la_LIBADD += base/allocator/libtype_profiler_control.la
base_libprocess_util_la_LIBADD += base/posix/libfile_descriptor_shuffle.la
base_libprocess_util_la_LIBADD += base/libfile_util.la

noinst_LTLIBRARIES += base/libtimer.la
base_libtimer_la_SOURCES = base/timer.h
base_libtimer_la_SOURCES += base/timer.cc

noinst_LTLIBRARIES += base/profiler/libalternate_timer.la
base_profiler_libalternate_timer_la_SOURCES = base/profiler/alternate_timer.h
base_profiler_libalternate_timer_la_SOURCES += base/profiler/alternate_timer.cc

noinst_LTLIBRARIES += base/threading/libthread_local_storage.la
base_threading_libthread_local_storage_la_SOURCES = base/threading/thread_local_storage_posix.cc
base_threading_libthread_local_storage_la_SOURCES += base/threading/thread_local_storage.h

noinst_LTLIBRARIES += base/profiler/libtracked_time.la
base_profiler_libtracked_time_la_SOURCES = base/profiler/tracked_time.h
base_profiler_libtracked_time_la_SOURCES += base/profiler/tracked_time.cc

noinst_LTLIBRARIES += base/threading/libthread_collision_warner.la
base_threading_libthread_collision_warner_la_SOURCES = base/threading/thread_collision_warner.h
base_threading_libthread_collision_warner_la_SOURCES += base/threading/thread_collision_warner.cc

noinst_LTLIBRARIES += base/strings/libutf_string_conversion_utils.la
base_strings_libutf_string_conversion_utils_la_SOURCES = base/strings/utf_string_conversion_utils.h
base_strings_libutf_string_conversion_utils_la_SOURCES += base/strings/utf_string_conversion_utils.cc

noinst_LTLIBRARIES += base/threading/libthread_id_name_manager.la
base_threading_libthread_id_name_manager_la_SOURCES = base/threading/thread_id_name_manager.h
base_threading_libthread_id_name_manager_la_SOURCES += base/threading/thread_id_name_manager.cc
base_threading_libthread_id_name_manager_la_LIBADD = base/synchronization/liblock.la
base_threading_libthread_id_name_manager_la_LIBADD += base/libatomicops.la

noinst_LTLIBRARIES += base/memory/libsingleton.la
base_memory_libsingleton_la_SOURCES = base/memory/singleton.h
base_memory_libsingleton_la_SOURCES += base/memory/singleton.cc
base_memory_libsingleton_la_LIBADD = base/threading/libplatform_thread.la
base_memory_libsingleton_la_LIBADD += base/libat_exit.la

noinst_LTLIBRARIES += base/libatomicops.la
base_libatomicops_la_SOURCES = base/atomicops_internals_x86_gcc.cc
base_libatomicops_la_SOURCES += base/atomicops_internals_x86_gcc.h
base_libatomicops_la_SOURCES += base/atomicops.h

noinst_LTLIBRARIES += base/third_party/icu/libicu_utf.la
base_third_party_icu_libicu_utf_la_SOURCES = base/third_party/icu/icu_utf.h
base_third_party_icu_libicu_utf_la_SOURCES += base/third_party/icu/icu_utf.cc

noinst_LTLIBRARIES += base/threading/libthread_local.la
base_threading_libthread_local_la_SOURCES = base/threading/thread_local.h
base_threading_libthread_local_la_SOURCES += base/threading/thread_local_posix.cc

noinst_LTLIBRARIES += base/third_party/nspr/libprtime.la
base_third_party_nspr_libprtime_la_SOURCES = base/third_party/nspr/prtime.h
base_third_party_nspr_libprtime_la_SOURCES += base/third_party/nspr/prtime.cc

noinst_LTLIBRARIES += base/libpickle.la
base_libpickle_la_SOURCES = base/pickle.h
base_libpickle_la_SOURCES += base/pickle.cc

noinst_LTLIBRARIES += base/strings/libsys_string_conversions.la
base_strings_libsys_string_conversions_la_SOURCES = base/strings/sys_string_conversions.h
base_strings_libsys_string_conversions_la_SOURCES += base/strings/sys_string_conversions_posix.cc

noinst_LTLIBRARIES += base/libstring16.la
base_libstring16_la_SOURCES = base/string16.h
base_libstring16_la_SOURCES += base/string16.cc

noinst_LTLIBRARIES += base/third_party/dmg_fp/libdmg_fp.la
base_third_party_dmg_fp_libdmg_fp_la_SOURCES = base/third_party/dmg_fp/g_fmt.cc
base_third_party_dmg_fp_libdmg_fp_la_SOURCES += base/third_party/dmg_fp/dtoa.cc


noinst_LTLIBRARIES += base/strings/libstring_split.la
base_strings_libstring_split_la_SOURCES = base/strings/string_split.h
base_strings_libstring_split_la_SOURCES += base/strings/string_split.cc


noinst_LTLIBRARIES += base/debug/libstack_trace.la
base_debug_libstack_trace_la_SOURCES = base/debug/stack_trace.h
base_debug_libstack_trace_la_SOURCES += base/debug/stack_trace_posix.cc
base_debug_libstack_trace_la_SOURCES += base/debug/stack_trace.cc
base_debug_libstack_trace_la_LIBADD = base/debug/libdebugger.la

noinst_LTLIBRARIES += base/debug/libalias.la
base_debug_libalias_la_SOURCES = base/debug/alias.cc
base_debug_libalias_la_SOURCES += base/debug/alias.h



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

noinst_LTLIBRARIES += base/files/libscoped_temp_dir.la
base_files_libscoped_temp_dir_la_SOURCES = base/files/scoped_temp_dir.h
base_files_libscoped_temp_dir_la_SOURCES += base/files/scoped_temp_dir.cc

noinst_LTLIBRARIES += base/libsequenced_task_runner.la
base_libsequenced_task_runner_la_SOURCES = base/sequenced_task_runner.h
base_libsequenced_task_runner_la_SOURCES += base/sequenced_task_runner.cc

noinst_LTLIBRARIES += base/files/libfile_path_watcher.la
base_files_libfile_path_watcher_la_CPPFLAGS = -I$(top_srcdir)/src $(DEPS_CFLAGS)
base_files_libfile_path_watcher_la_LIBS = $(DEPS_LIBS)
base_files_libfile_path_watcher_la_SOURCES = base/files/file_path_watcher.h
base_files_libfile_path_watcher_la_SOURCES += base/files/file_path_watcher.cc
base_files_libfile_path_watcher_la_SOURCES += base/files/file_path_watcher_@FILE_PATH_WATCHER_SUFFIX@.cc
base_files_libfile_path_watcher_la_LIBADD = base/message_loop/libmessage_loop_proxy.la
base_files_libfile_path_watcher_la_LIBADD += base/libcallback.la
base_files_libfile_path_watcher_la_LIBADD += base/libtask_runner.la
base_files_libfile_path_watcher_la_LIBADD += base/libmessage_loop.la
base_files_libfile_path_watcher_la_LIBADD += base/files/libfile_path.la
base_files_libfile_path_watcher_la_LIBADD += base/libfile_util.la
base_files_libfile_path_watcher_la_LIBADD += base/threading/libthread.la
base_files_libfile_path_watcher_la_LIBADD += base/strings/libstring_piece.la
base_files_libfile_path_watcher_la_LIBADD += base/liblogging.la

# TESTS += base/files/file_path_watcher_browsertest
# bin_PROGRAMS += base/files/file_path_watcher_browsertest
# base_files_file_path_watcher_browsertest_SOURCES = base/files/file_path_watcher_browsertest.cc
# base_files_file_path_watcher_browsertest_LDADD =
# base_files_file_path_watcher_browsertest_LDADD += base/files/libfile_path_watcher.la
# base_files_file_path_watcher_browsertest_LDADD += base/files/libscoped_temp_dir.la
# base_files_file_path_watcher_browsertest_LDADD += base/libsequenced_task_runner.la
# base_files_file_path_watcher_browsertest_LDADD += $(top_srcdir)/src/testing/gtest/lib/libgtest.la
# base_files_file_path_watcher_browsertest_LDADD += $(top_srcdir)/src/testing/gtest/lib/libgtest_main.la

noinst_LTLIBRARIES += base/threading/libthread.la
base_threading_libthread_la_SOURCES = base/threading/thread.h
base_threading_libthread_la_SOURCES += base/threading/thread.cc
base_threading_libthread_la_LIBADD = base/memory/libweak_ptr.la
base_threading_libthread_la_LIBADD += base/libmessage_loop.la
base_threading_libthread_la_LIBADD += base/synchronization/libwaitable_event.la

noinst_LTLIBRARIES += base/libfile_util.la
base_libfile_util_la_SOURCES = base/file_util.h
base_libfile_util_la_SOURCES += base/file_util.cc
base_libfile_util_la_SOURCES += base/file_util_linux.cc
base_libfile_util_la_SOURCES += base/file_util_posix.cc
base_libfile_util_la_LIBADD = base/libplatform_file.la

noinst_LTLIBRARIES += base/liblazy_instance.la
base_liblazy_instance_la_SOURCES = base/lazy_instance.h
base_liblazy_instance_la_SOURCES += base/lazy_instance.cc

noinst_LTLIBRARIES += base/files/libfile_path.la
base_files_libfile_path_la_SOURCES = base/files/file_path.h
base_files_libfile_path_la_SOURCES += base/files/file_path.cc
base_files_libfile_path_la_LIBADD = base/libpickle.la
base_files_libfile_path_la_LIBADD += base/strings/libsys_string_conversions.la

noinst_LTLIBRARIES += base/libmessage_loop.la
base_libmessage_loop_la_SOURCES = base/message_loop.h
base_libmessage_loop_la_SOURCES += base/message_loop.cc
base_libmessage_loop_la_LIBADD = base/libtracked_objects.la
base_libmessage_loop_la_LIBADD += base/libmessage_pump.la
base_libmessage_loop_la_LIBADD += base/libpending_task.la
base_libmessage_loop_la_LIBADD += base/libtracking_info.la
base_libmessage_loop_la_LIBADD += base/libthread_task_runner_handle.la
base_libmessage_loop_la_LIBADD += base/message_loop/libmessage_loop_proxy.la
base_libmessage_loop_la_LIBADD += base/message_loop/libmessage_loop_proxy_impl.la
base_libmessage_loop_la_LIBADD += base/libtime.la
base_libmessage_loop_la_LIBADD += base/librun_loop.la
base_libmessage_loop_la_LIBADD += base/metrics/libhistogram.la
base_libmessage_loop_la_LIBADD += base/metrics/libstatistics_recorder.la
base_libmessage_loop_la_LIBADD += base/debug/libalias.la
base_libmessage_loop_la_LIBADD += base/debug/libtrace_event.la

noinst_LTLIBRARIES += base/message_loop/libmessage_loop_proxy.la
base_message_loop_libmessage_loop_proxy_la_SOURCES = base/message_loop/message_loop_proxy.h
base_message_loop_libmessage_loop_proxy_la_SOURCES += base/message_loop/message_loop_proxy.cc

noinst_LTLIBRARIES += base/message_loop/libmessage_loop_proxy_impl.la
base_message_loop_libmessage_loop_proxy_impl_la_SOURCES = base/message_loop/message_loop_proxy_impl.h
base_message_loop_libmessage_loop_proxy_impl_la_SOURCES += base/message_loop/message_loop_proxy_impl.cc

noinst_LTLIBRARIES += base/libtracked_objects.la
base_libtracked_objects_la_SOURCES = base/tracked_objects.h
base_libtracked_objects_la_SOURCES += base/tracked_objects.cc
base_libtracked_objects_la_LIBADD = base/liblazy_instance.la
base_libtracked_objects_la_LIBADD += base/synchronization/liblock.la
base_libtracked_objects_la_LIBADD += base/liblocation.la
base_libtracked_objects_la_LIBADD += base/profiler/libtracked_time.la
base_libtracked_objects_la_LIBADD += base/threading/libthread_local_storage.la
base_libtracked_objects_la_LIBADD += base/profiler/libalternate_timer.la
base_libtracked_objects_la_LIBADD += base/libprocess_util.la


noinst_LTLIBRARIES += base/memory/libref_counted.la
base_memory_libref_counted_la_SOURCES = base/memory/ref_counted.h
base_memory_libref_counted_la_SOURCES += base/memory/ref_counted.cc
base_memory_libref_counted_la_LIBADD = base/threading/libthread_collision_warner.la
base_memory_libref_counted_la_LIBADD += base/libatomicops.la
base_memory_libref_counted_la_LIBADD += base/libtask_runner.la


noinst_LTLIBRARIES += base/libcallback.la
base_libcallback_la_SOURCES = base/callback.h
base_libcallback_la_SOURCES += base/callback_forward.h
base_libcallback_la_SOURCES += base/cancelable_callback.h
base_libcallback_la_SOURCES += base/callback_internal.cc
base_libcallback_la_SOURCES += base/callback_helpers.h
base_libcallback_la_LIBADD = base/memory/libref_counted.la

noinst_LTLIBRARIES += base/liblocation.la
base_liblocation_la_SOURCES = base/location.h base/location.cc

noinst_LTLIBRARIES += base/libtask_runner.la
base_libtask_runner_la_SOURCES = base/task_runner.h
base_libtask_runner_la_SOURCES += base/task_runner.cc
base_libtask_runner_la_SOURCES += base/task_runner_util.h
base_libtask_runner_la_LIBADD = base/threading/libpost_task_and_reply_impl.la

noinst_LTLIBRARIES += base/synchronization/liblock.la
base_synchronization_liblock_la_SOURCES = base/synchronization/lock_impl.h
base_synchronization_liblock_la_SOURCES += base/synchronization/lock_impl_posix.cc
base_synchronization_liblock_la_SOURCES += base/synchronization/lock.h
base_synchronization_liblock_la_SOURCES += base/synchronization/lock.cc

noinst_LTLIBRARIES += courgette/libsimple_delta.la
courgette_libsimple_delta_la_SOURCES = courgette/simple_delta.h
courgette_libsimple_delta_la_SOURCES += courgette/simple_delta.cc
courgette_libsimple_delta_la_SOURCES += courgette/courgette.h
courgette_libsimple_delta_la_LIBADD = base/liblogging.la
courgette_libsimple_delta_la_LIBADD += courgette/third_party/libbsdiff.la

noinst_LTLIBRARIES += base/liblogging.la
base_liblogging_la_SOURCES = base/logging.h
base_liblogging_la_SOURCES += base/logging.cc
base_liblogging_la_LIBADD =
base_liblogging_la_LIBADD += base/debug/libdebugger.la
base_liblogging_la_LIBADD += base/debug/libstack_trace.la
base_liblogging_la_LIBADD += base/libutf_string_conversions.la
base_liblogging_la_LIBADD += base/libsafe_strerror_posix.la
base_liblogging_la_LIBADD += base/libvlog.la
base_liblogging_la_LIBADD += base/libbase_switches.la
base_liblogging_la_LIBADD += base/debug/libalias.la
base_liblogging_la_LIBADD += base/strings/libstring_piece.la
base_liblogging_la_LIBADD += base/threading/libplatform_thread.la

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

noinst_LTLIBRARIES += base/libcommand_line.la
base_libcommand_line_la_SOURCES = base/command_line.h
base_libcommand_line_la_SOURCES += base/command_line.cc
base_libcommand_line_la_LIBADD = base/strings/libstring_split.la

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

noinst_LTLIBRARIES += base/strings/libstring_number_conversions.la
base_strings_libstring_number_conversions_la_SOURCES =
base_strings_libstring_number_conversions_la_SOURCES += base/strings/string_number_conversions.h
base_strings_libstring_number_conversions_la_SOURCES += base/strings/string_number_conversions.cc
base_strings_libstring_number_conversions_la_LIBADD = base/third_party/dmg_fp/libdmg_fp.la

noinst_LTLIBRARIES += courgette/libencoded_program.la
courgette_libencoded_program_la_SOURCES = courgette/encoded_program.h
courgette_libencoded_program_la_SOURCES += courgette/encoded_program.cc
courgette_libencoded_program_la_LIBADD = base/libenvironment.la

noinst_LTLIBRARIES += courgette/libadjustment_method.la
courgette_libadjustment_method_la_SOURCES = courgette/adjustment_method.h
courgette_libadjustment_method_la_SOURCES += courgette/adjustment_method.cc
courgette_libadjustment_method_la_SOURCES += courgette/adjustment_method_2.cc

noinst_LTLIBRARIES += base/libat_exit.la
base_libat_exit_la_SOURCES = base/at_exit.cc
base_libat_exit_la_SOURCES += base/at_exit.h
base_libat_exit_la_LIBADD = base/synchronization/liblock.la
base_libat_exit_la_LIBADD += base/libcallback.la

noinst_LTLIBRARIES += base/libtime.la
base_libtime_la_SOURCES = base/time.h
base_libtime_la_SOURCES += base/time.cc
base_libtime_la_SOURCES += base/time_posix.cc
base_libtime_la_LIBADD = base/third_party/nspr/libprtime.la

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

noinst_LTLIBRARIES += base/files/libmemory_mapped_file.la
base_files_libmemory_mapped_file_la_SOURCES =
base_files_libmemory_mapped_file_la_SOURCES += base/files/memory_mapped_file.h
base_files_libmemory_mapped_file_la_SOURCES += base/files/memory_mapped_file.cc
base_files_libmemory_mapped_file_la_SOURCES += base/files/memory_mapped_file_posix.cc

noinst_LTLIBRARIES += base/libplatform_file.la
base_libplatform_file_la_SOURCES = base/platform_file.cc
base_libplatform_file_la_SOURCES += base/platform_file.h
base_libplatform_file_la_SOURCES += base/platform_file_posix.cc
base_libplatform_file_la_LIBADD = base/threading/libthread_local.la

noinst_LTLIBRARIES += base/libstringprintf.la
base_libstringprintf_la_SOURCES = base/stringprintf.h
base_libstringprintf_la_SOURCES += base/stringprintf.cc
base_libstringprintf_la_LIBADD = base/libstring_util.la

noinst_LTLIBRARIES += base/threading/libthread_restrictions.la
base_threading_libthread_restrictions_la_SOURCES = base/threading/thread_restrictions.h
base_threading_libthread_restrictions_la_SOURCES += base/threading/thread_restrictions.cc
base_threading_libthread_restrictions_la_LIBADD = base/liblazy_instance.la

noinst_LTLIBRARIES += base/libstring_util.la
base_libstring_util_la_SOURCES = base/string_util.cc
base_libstring_util_la_SOURCES += base/string_util.h
base_libstring_util_la_SOURCES += base/string_util_posix.h
base_libstring_util_la_LIBADD = base/third_party/icu/libicu_utf.la
base_libstring_util_la_LIBADD += base/threading/libthread_restrictions.la
base_libstring_util_la_LIBADD += base/libatomicops.la
base_libstring_util_la_LIBADD += base/libstring16.la
base_libstring_util_la_LIBADD += base/memory/libsingleton.la

noinst_LTLIBRARIES += base/strings/libstring_piece.la
base_strings_libstring_piece_la_SOURCES = base/strings/string_piece.cc
base_strings_libstring_piece_la_SOURCES += base/strings/string_piece.h

noinst_LTLIBRARIES += base/threading/libplatform_thread.la
base_threading_libplatform_thread_la_SOURCES =
base_threading_libplatform_thread_la_SOURCES += base/threading/platform_thread.h
base_threading_libplatform_thread_la_SOURCES += base/threading/platform_thread_posix.cc
base_threading_libplatform_thread_la_LIBADD =
base_threading_libplatform_thread_la_LIBADD += base/libtracked_objects.la
base_threading_libplatform_thread_la_LIBADD += base/threading/libthread_id_name_manager.la

noinst_LTLIBRARIES += base/libutf_string_conversions.la
base_libutf_string_conversions_la_SOURCES = base/utf_string_conversions.cc
base_libutf_string_conversions_la_SOURCES += base/utf_string_conversions.h
base_libutf_string_conversions_la_LIBADD = base/strings/libutf_string_conversion_utils.la
base_libutf_string_conversions_la_LIBADD += base/strings/libstring_piece.la
base_libutf_string_conversions_la_LIBADD += base/libstring16.la

noinst_LTLIBRARIES += base/debug/libdebugger.la
base_debug_libdebugger_la_SOURCES = base/debug/debugger.cc
base_debug_libdebugger_la_SOURCES += base/debug/debugger.h
base_debug_libdebugger_la_SOURCES += base/debug/debugger_posix.cc
base_debug_libdebugger_la_LIBADD = base/libstringprintf.la

noinst_LTLIBRARIES += base/libsafe_strerror_posix.la
base_libsafe_strerror_posix_la_SOURCES = base/safe_strerror_posix.h
base_libsafe_strerror_posix_la_SOURCES += base/safe_strerror_posix.cc

noinst_LTLIBRARIES += base/libvlog.la
base_libvlog_la_SOURCES = base/vlog.h
base_libvlog_la_SOURCES += base/vlog.cc
base_libvlog_la_LIBADD = base/strings/libstring_number_conversions.la

noinst_LTLIBRARIES += base/libbase_switches.la
base_libbase_switches_la_SOURCES = base/base_switches.h
base_libbase_switches_la_SOURCES += base/base_switches.cc

noinst_LTLIBRARIES += base/libenvironment.la
base_libenvironment_la_SOURCES = base/environment.h
base_libenvironment_la_SOURCES += base/environment.cc


bin_PROGRAMS += delta_encoding_main
delta_encoding_main_SOURCES = delta_encoding_main.cc
delta_encoding_main_LDADD =
delta_encoding_main_LDADD += courgette/libsimple_delta.la
delta_encoding_main_LDADD += courgette/libstreams.la
