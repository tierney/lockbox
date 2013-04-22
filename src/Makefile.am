AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src
AM_CPPFLAGS += -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -DCOURGETTE_USE_CRC_LIB \
	$(DEPS_CFLAGS) $(GTK_CFLAGS)
AM_CXXFLAGS = -Wall -Wextra

SUBDIRS =
TESTS =
bin_PROGRAMS =
noinst_PROGRAMS =
noinst_LTLIBRARIES =

EXTRA_DIST = base/base_export.h

bin_PROGRAMS += lockbox_main
lockbox_main_LDADD = $(DEPS_LIBS)
lockbox_main_SOURCES = lockbox_main.cc
lockbox_main_LDADD += libfile_path_watcher.la

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

noinst_LTLIBRARIES += base/synchronization/libwaitable_event_posix.la
base_synchronization_libwaitable_event_posix_la_SOURCES = base/synchronization/waitable_event_posix.h
base_synchronization_libwaitable_event_posix_la_SOURCES += base/synchronization/waitable_event_posix.cc
base_synchronization_libwaitable_event_posix_la_LIBADD = base/synchronization/libcondition_variable_posix.la

noinst_LTLIBRARIES += base/synchronization/libcondition_variable_posix.la
base_synchronization_libcondition_variable_posix_la_SOURCES = base/synchronization/condition_variable_posix.h
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

noinst_LTLIBRARIES += base/debug/libtrace_event_impl.la
base_debug_libtrace_event_impl_la_SOURCES =	base/debug/trace_event_impl.cc
base_debug_libtrace_event_impl_la_SOURCES += base/debug/trace_event_impl.h
base_debug_libtrace_event_impl_la_LIBADD = base/memory/libref_counted_memory.la
base_debug_libtrace_event_impl_la_LIBADD += base/memory/libweak_ptr.la
base_debug_libtrace_event_impl_la_LIBADD += base/synchronization/libcancellation_flag.la
base_debug_libtrace_event_impl_la_LIBADD += base/libstringprintf.la
base_debug_libtrace_event_impl_la_LIBADD += libatomic_internals_x86_gcc.la
base_debug_libtrace_event_impl_la_LIBADD += base/memory/libsingleton.la
base_debug_libtrace_event_impl_la_LIBADD += libat_exit.la
base_debug_libtrace_event_impl_la_LIBADD += libthread_id_name_manager.la
base_debug_libtrace_event_impl_la_LIBADD += base/libprocess_util.la

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
base_libmessage_pump_default_la_LIBADD = base/synchronization/libwaitable_event_posix.la

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
base_metrics_libsparse_histogram_la_LIBADD += base/metrics/libstatistics_recorder.la
base_metrics_libsparse_histogram_la_LIBADD += base/metrics/libhistogram_samples.la


noinst_LTLIBRARIES += base/json/libjson_string_value_serializer.la
base_json_libjson_string_value_serializer_la_SOURCES = base/json/json_string_value_serializer.h
base_json_libjson_string_value_serializer_la_SOURCES += base/json/json_string_value_serializer.cc

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
base_json_libjson_parser_la_LIBADD = base/json/libjson_string_value_serializer.la
base_json_libjson_parser_la_LIBADD += base/libvalues.la

noinst_LTLIBRARIES += base/json/libjson_reader.la
base_json_libjson_reader_la_SOURCES = base/json/json_reader.h
base_json_libjson_reader_la_SOURCES += base/json/json_reader.cc
base_json_libjson_reader_la_LIBADD = base/json/libjson_parser.la

noinst_LTLIBRARIES += base/threading/libpost_task_and_reply_impl.la
base_threading_libpost_task_and_reply_impl_la_SOURCES = base/threading/post_task_and_reply_impl.cc
base_threading_libpost_task_and_reply_impl_la_LIBADD = base/message_loop/libmessage_loop_proxy.la

noinst_LTLIBRARIES += base/metrics/libhistogram.la
base_metrics_libhistogram_la_SOURCES = base/metrics/histogram.cc
base_metrics_libhistogram_la_SOURCES += base/metrics/histogram.h
base_metrics_libhistogram_la_SOURCES += base/metrics/histogram_base.cc
base_metrics_libhistogram_la_LIBADD = base/json/libjson_reader.la
base_metrics_libhistogram_la_LIBADD += base/json/libjson_writer.la
base_metrics_libhistogram_la_LIBADD += base/json/libjson_string_value_serializer.la
base_metrics_libhistogram_la_LIBADD += base/metrics/libsparse_histogram.la
base_metrics_libhistogram_la_LIBADD += base/libvalues.la
base_metrics_libhistogram_la_LIBADD += base/metrics/libbucket_ranges.la
base_metrics_libhistogram_la_LIBADD += base/metrics/libsample_vector.la
base_metrics_libhistogram_la_LIBADD += base/metrics/libstatistics_recorder.la


noinst_LTLIBRARIES += libsys_info.la
libsys_info_la_SOURCES = base/sys_info.h
libsys_info_la_SOURCES += base/sys_info_posix.cc

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

noinst_LTLIBRARIES += libdynamic_annotations.la
libdynamic_annotations_la_SOURCES = base/third_party/dynamic_annotations/dynamic_annotations.h
libdynamic_annotations_la_SOURCES += base/third_party/dynamic_annotations/dynamic_annotations.c

noinst_LTLIBRARIES += base/libprocess_util.la
base_libprocess_util_la_SOURCES = base/process_util.h
base_libprocess_util_la_SOURCES += base/process_util.cc
base_libprocess_util_la_SOURCES += base/process_util_posix.cc
base_libprocess_util_la_SOURCES += base/process_util_linux.cc
base_libprocess_util_la_LIBADD = libcommand_line.la
base_libprocess_util_la_LIBADD += libthread_restrictions.la
base_libprocess_util_la_LIBADD += libfile_path.la
base_libprocess_util_la_LIBADD += libthread_local.la
base_libprocess_util_la_LIBADD += libsys_string_conversions.la
base_libprocess_util_la_LIBADD += libpickle.la
base_libprocess_util_la_LIBADD += base/libtime.la
base_libprocess_util_la_LIBADD += libsys_info.la
base_libprocess_util_la_LIBADD += libdynamic_annotations.la
base_libprocess_util_la_LIBADD += base/libprocess.la
base_libprocess_util_la_LIBADD += base/allocator/libtype_profiler_control.la
base_libprocess_util_la_LIBADD += base/posix/libfile_descriptor_shuffle.la
base_libprocess_util_la_LIBADD += libfile_util.la

noinst_LTLIBRARIES += base/profiler/libalternate_timer.la
base_profiler_libalternate_timer_la_SOURCES = base/profiler/alternate_timer.h
base_profiler_libalternate_timer_la_SOURCES += base/profiler/alternate_timer.cc

noinst_LTLIBRARIES += libthread_local_storage.la
libthread_local_storage_la_SOURCES = base/threading/thread_local_storage_posix.cc
libthread_local_storage_la_SOURCES += base/threading/thread_local_storage.h

noinst_LTLIBRARIES += libtracked_time.la
libtracked_time_la_SOURCES = base/profiler/tracked_time.h
libtracked_time_la_SOURCES += base/profiler/tracked_time.cc

noinst_LTLIBRARIES += libthread_collision_warner.la
libthread_collision_warner_la_SOURCES = base/threading/thread_collision_warner.h
libthread_collision_warner_la_SOURCES += base/threading/thread_collision_warner.cc
libthread_collision_warner_la_LIBADD = libatomic_internals_x86_gcc.la

noinst_LTLIBRARIES += libutf_string_conversion_utils.la
libutf_string_conversion_utils_la_SOURCES = base/strings/utf_string_conversion_utils.h
libutf_string_conversion_utils_la_SOURCES += base/strings/utf_string_conversion_utils.cc

noinst_LTLIBRARIES += libthread_id_name_manager.la
libthread_id_name_manager_la_SOURCES = base/threading/thread_id_name_manager.h
libthread_id_name_manager_la_SOURCES += base/threading/thread_id_name_manager.cc
libthread_id_name_manager_la_LIBADD = liblock.la
libthread_id_name_manager_la_LIBADD += libatomic_internals_x86_gcc.la

noinst_LTLIBRARIES += base/memory/libsingleton.la
base_memory_libsingleton_la_SOURCES = base/memory/singleton.h
base_memory_libsingleton_la_SOURCES += base/memory/singleton.cc
base_memory_libsingleton_la_LIBADD = libplatform_thread.la

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
libstring16_la_LIBADD = libutf_string_conversions.la

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
libstack_trace_la_LIBADD = base/debug/libdebugger.la

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
libfile_path_watcher_la_LIBADD = base/libthread.la
libfile_path_watcher_la_LIBADD += base/message_loop/libmessage_loop_proxy.la
libfile_path_watcher_la_LIBADD += liblogging.la
libfile_path_watcher_la_LIBADD += libcallback.la
libfile_path_watcher_la_LIBADD += libtask_runner.la
libfile_path_watcher_la_LIBADD += libmessage_loop.la
libfile_path_watcher_la_LIBADD += libfile_path.la
libfile_path_watcher_la_LIBADD += libfile_util.la

noinst_LTLIBRARIES += base/libthread.la
base_libthread_la_SOURCES = base/threading/thread.h
base_libthread_la_SOURCES += base/threading/thread.cc
base_libthread_la_LIBADD = base/memory/libweak_ptr.la
base_libthread_la_LIBADD += libmessage_loop.la
base_libthread_la_LIBADD += base/synchronization/libwaitable_event_posix.la

noinst_LTLIBRARIES += libfile_util.la
libfile_util_la_SOURCES = base/file_util.h
libfile_util_la_SOURCES += base/file_util.cc
libfile_util_la_SOURCES += base/file_util_linux.cc
libfile_util_la_SOURCES += base/file_util_posix.cc
libfile_util_la_LIBADD = libplatform_file.la

noinst_LTLIBRARIES += liblazy_instance.la
liblazy_instance_la_SOURCES = base/lazy_instance.h
liblazy_instance_la_SOURCES += base/lazy_instance.cc
liblazy_instance_la_LIBADD = libat_exit.la

noinst_LTLIBRARIES += libfile_path.la
libfile_path_la_SOURCES = base/files/file_path.cc
libfile_path_la_LIBADD = libpickle.la
libfile_path_la_LIBADD += libsys_string_conversions.la

noinst_LTLIBRARIES += libmessage_loop.la
libmessage_loop_la_SOURCES = base/message_loop.h
libmessage_loop_la_SOURCES += base/message_loop.cc
libmessage_loop_la_LIBADD = libtracked_objects.la
libmessage_loop_la_LIBADD += base/libmessage_pump.la
libmessage_loop_la_LIBADD += base/librun_loop.la
libmessage_loop_la_LIBADD += base/libpending_task.la
libmessage_loop_la_LIBADD += base/debug/libtrace_event_impl.la
libmessage_loop_la_LIBADD += base/libtracking_info.la
libmessage_loop_la_LIBADD += base/metrics/libstatistics_recorder.la
libmessage_loop_la_LIBADD += base/memory/libweak_ptr.la
libmessage_loop_la_LIBADD += base/libthread_task_runner_handle.la
libmessage_loop_la_LIBADD += base/metrics/libhistogram.la
libmessage_loop_la_LIBADD += base/message_loop/libmessage_loop_proxy.la
libmessage_loop_la_LIBADD += base/message_loop/libmessage_loop_proxy_impl.la
libmessage_loop_la_LIBADD += base/libtime.la

noinst_LTLIBRARIES += base/message_loop/libmessage_loop_proxy.la
base_message_loop_libmessage_loop_proxy_la_SOURCES = base/message_loop/message_loop_proxy.h
base_message_loop_libmessage_loop_proxy_la_SOURCES += base/message_loop/message_loop_proxy.cc

noinst_LTLIBRARIES += base/message_loop/libmessage_loop_proxy_impl.la
base_message_loop_libmessage_loop_proxy_impl_la_SOURCES = base/message_loop/message_loop_proxy_impl.h
base_message_loop_libmessage_loop_proxy_impl_la_SOURCES += base/message_loop/message_loop_proxy_impl.cc

noinst_LTLIBRARIES += libtracked_objects.la
libtracked_objects_la_SOURCES = base/tracked_objects.h
libtracked_objects_la_SOURCES += base/tracked_objects.cc
libtracked_objects_la_LIBADD = liblazy_instance.la
libtracked_objects_la_LIBADD += liblock.la
libtracked_objects_la_LIBADD += liblocation.la
libtracked_objects_la_LIBADD += libtracked_time.la
libtracked_objects_la_LIBADD += libthread_local_storage.la
libtracked_objects_la_LIBADD += base/profiler/libalternate_timer.la
libtracked_objects_la_LIBADD += base/libprocess_util.la

noinst_LTLIBRARIES += libref_counted.la
libref_counted_la_SOURCES = base/memory/ref_counted.h
libref_counted_la_SOURCES += base/memory/ref_counted.cc
libref_counted_la_LIBADD = libthread_collision_warner.la
libref_counted_la_LIBADD += libatomic_internals_x86_gcc.la

noinst_LTLIBRARIES += libcallback.la
libcallback_la_SOURCES = base/callback.h
libcallback_la_SOURCES += base/callback_forward.h
libcallback_la_SOURCES += base/cancelable_callback.h
libcallback_la_SOURCES += base/callback_internal.cc
libcallback_la_SOURCES += base/callback_helpers.h
libcallback_la_LIBADD = libref_counted.la

noinst_LTLIBRARIES += liblocation.la
liblocation_la_SOURCES = base/location.h base/location.cc

noinst_LTLIBRARIES += libtask_runner.la
libtask_runner_la_SOURCES = base/task_runner.h
libtask_runner_la_SOURCES += base/task_runner.cc
libtask_runner_la_SOURCES += base/task_runner_util.h
libtask_runner_la_LIBADD = base/threading/libpost_task_and_reply_impl.la

noinst_LTLIBRARIES += liblock.la
liblock_la_SOURCES = base/synchronization/lock_impl.h
liblock_la_SOURCES += base/synchronization/lock_impl_posix.cc
liblock_la_SOURCES += base/synchronization/lock.h
liblock_la_SOURCES += base/synchronization/lock.cc

noinst_LTLIBRARIES += libsimple_delta.la
libsimple_delta_la_SOURCES = courgette/simple_delta.h
libsimple_delta_la_SOURCES += courgette/simple_delta.cc
libsimple_delta_la_LIBADD = libcourgette_tool.la

noinst_LTLIBRARIES += liblogging.la
liblogging_la_SOURCES = base/logging.h base/logging.cc
liblogging_la_LIBADD = libcommand_line.la
liblogging_la_LIBADD += libvlog.la
liblogging_la_LIBADD += libstring_piece.la
liblogging_la_LIBADD += libstack_trace.la
liblogging_la_LIBADD += libalias.la
liblogging_la_LIBADD += libsafe_strerror_posix.la
liblogging_la_LIBADD += libbase_switches.la
liblogging_la_LIBADD += libstring16.la
liblogging_la_LIBADD += liblock.la
liblogging_la_LIBADD += libplatform_thread.la
liblogging_la_LIBADD += base/debug/libdebugger.la

noinst_LTLIBRARIES += libcourgette_tool.la
libcourgette_tool_la_SOURCES = courgette/courgette_tool.cc
libcourgette_tool_la_LIBADD = libbsdiff.la

noinst_LTLIBRARIES += libstreams.la
libstreams_la_SOURCES = courgette/streams.h
libstreams_la_SOURCES += courgette/streams.cc
libstreams_la_SOURCES += courgette/region.h
libstreams_la_LIBADD = libmemory_allocator.la
libstreams_la_LIBADD += libatomic_internals_x86_gcc.la
libstreams_la_LIBADD += base/memory/libsingleton.la
libstreams_la_LIBADD += libat_exit.la

# TESTS += streams_unittest
# bin_PROGRAMS += streams_unittest
# streams_unittest_SOURCES = courgette/streams_unittest.cc
# streams_unittest_LDADD = libsimple_delta.la
# streams_unittest_LDADD += liblock.la

noinst_LTLIBRARIES += libbsdiff.la
libbsdiff_la_SOURCES = courgette/third_party/bsdiff.h
libbsdiff_la_SOURCES += courgette/third_party/bsdiff_apply.cc
libbsdiff_la_SOURCES += courgette/third_party/bsdiff_create.cc
libbsdiff_la_LIBADD = libcrc.la $(ZLIB_LIBS)
libbsdiff_la_LIBADD += base/libtime.la

noinst_LTLIBRARIES += libcommand_line.la
libcommand_line_la_SOURCES = base/command_line.h
libcommand_line_la_SOURCES += base/command_line.cc
libcommand_line_la_LIBADD = libstring_split.la

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
libstring_number_conversions_la_LIBADD = libdmg_fp.la

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
libat_exit_la_LIBADD = liblock.la
libat_exit_la_LIBADD += libcallback.la

noinst_LTLIBRARIES += base/libtime.la
base_libtime_la_SOURCES = base/time.h
base_libtime_la_SOURCES += base/time.cc
base_libtime_la_SOURCES += base/time_posix.cc
base_libtime_la_LIBADD = libprtime.la

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

noinst_LTLIBRARIES += libmemory_allocator.la
libmemory_allocator_la_SOURCES = courgette/memory_allocator.h
libmemory_allocator_la_SOURCES += courgette/memory_allocator.cc
libmemory_allocator_la_LIBADD = libfile_path.la
libmemory_allocator_la_LIBADD += libplatform_file.la
libmemory_allocator_la_LIBADD += liblogging.la
libmemory_allocator_la_LIBADD += base/debug/libdebugger.la

noinst_LTLIBRARIES += libmemory_mapped_file.la
libmemory_mapped_file_la_SOURCES =
libmemory_mapped_file_la_SOURCES += base/files/memory_mapped_file.h
libmemory_mapped_file_la_SOURCES += base/files/memory_mapped_file.cc
libmemory_mapped_file_la_SOURCES += base/files/memory_mapped_file_posix.cc

noinst_LTLIBRARIES += libplatform_file.la
libplatform_file_la_SOURCES = base/platform_file.cc
libplatform_file_la_SOURCES += base/platform_file_posix.cc
libplatform_file_la_LIBADD = libthread_local.la

noinst_LTLIBRARIES += base/libstringprintf.la
base_libstringprintf_la_SOURCES = base/stringprintf.h
base_libstringprintf_la_SOURCES += base/stringprintf.cc

noinst_LTLIBRARIES += libthread_restrictions.la
libthread_restrictions_la_SOURCES = base/threading/thread_restrictions.h
libthread_restrictions_la_SOURCES += base/threading/thread_restrictions.cc
libthread_restrictions_la_LIBADD = liblazy_instance.la

noinst_LTLIBRARIES += libstring_util.la
libstring_util_la_SOURCES = base/string_util.cc
libstring_util_la_SOURCES += base/string_util.h
libstring_util_la_LIBADD = libicu_utf.la
libstring_util_la_LIBADD += libthread_restrictions.la
libstring_util_la_LIBADD += libat_exit.la
libstring_util_la_LIBADD += libatomic_internals_x86_gcc.la

noinst_LTLIBRARIES += libstring_piece.la
libstring_piece_la_SOURCES = base/strings/string_piece.cc
libstring_piece_la_SOURCES += base/strings/string_piece.h

noinst_LTLIBRARIES += libplatform_thread.la
libplatform_thread_la_SOURCES =
libplatform_thread_la_SOURCES += base/threading/platform_thread.h
libplatform_thread_la_SOURCES += base/threading/platform_thread_posix.cc
libplatform_thread_la_LIBADD =
libplatform_thread_la_LIBADD += libtracked_objects.la
libplatform_thread_la_LIBADD += libthread_id_name_manager.la

noinst_LTLIBRARIES += libutf_string_conversions.la
libutf_string_conversions_la_SOURCES = base/utf_string_conversions.cc
libutf_string_conversions_la_SOURCES += base/utf_string_conversions.h
libutf_string_conversions_la_LIBADD = libstring_util.la
libutf_string_conversions_la_LIBADD += libutf_string_conversion_utils.la

noinst_LTLIBRARIES += base/debug/libdebugger.la
base_debug_libdebugger_la_SOURCES = base/debug/debugger.cc
base_debug_libdebugger_la_SOURCES += base/debug/debugger.h
base_debug_libdebugger_la_SOURCES += base/debug/debugger_posix.cc
base_debug_libdebugger_la_LIBADD = base/libstringprintf.la

noinst_LTLIBRARIES += libsafe_strerror_posix.la
libsafe_strerror_posix_la_SOURCES = base/safe_strerror_posix.h
libsafe_strerror_posix_la_SOURCES += base/safe_strerror_posix.cc

noinst_LTLIBRARIES += libvlog.la
libvlog_la_SOURCES = base/vlog.h
libvlog_la_SOURCES += base/vlog.cc
libvlog_la_LIBADD = libstring_number_conversions.la

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
delta_encoding_main_LDADD += libsimple_delta.la
delta_encoding_main_LDADD += libstreams.la
