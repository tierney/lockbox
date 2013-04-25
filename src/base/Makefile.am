SUBDIRS =
AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src
noinst_LTLIBRARIES =

EXTRA_DIST = base/base_export.h
EXTRA_DIST += base/basictypes.h
EXTRA_DIST += base/port.h
EXTRA_DIST += base/compiler_specific.h
EXTRA_DIST += base/memory/scoped_ptr.h
EXTRA_DIST += base/move.h
EXTRA_DIST += base/template_util.h
EXTRA_DIST += base/file_descriptor_posix.h


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
base_libprocess_util_la_LIBADD += base/libthread_restrictions.la
base_libprocess_util_la_LIBADD += base/libfile_path.la
base_libprocess_util_la_LIBADD += base/libthread_local.la
base_libprocess_util_la_LIBADD += base/libsys_string_conversions.la
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
