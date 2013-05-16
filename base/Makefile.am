SUBDIRS =
DEFAULT_INCLUDES =
AM_CPPFLAGS = -I$(top_srcdir) -I$(top_builddir)
AM_CFLAGS = -I$(top_srcdir)
AM_CXXFLAGS = -g -O0 -DOS_POSIX -arch x86_64 -DCOMPILER_GCC -DARCH_CPU_X86_FAMILY

if DARWIN
AM_LDFLAGS = -framework Foundation
AM_CXXFLAGS += -DOS_MACOSX --stdlib=libc++
endif

EXTRA_DIST =
EXTRA_DIST += auto_reset.h
EXTRA_DIST += base_export.h
EXTRA_DIST += basictypes.h
EXTRA_DIST += compiler_specific.h
EXTRA_DIST += file_descriptor_posix.h
EXTRA_DIST += format_macros.h
EXTRA_DIST += memory/scoped_ptr.h
EXTRA_DIST += move.h
EXTRA_DIST += native_library.h
EXTRA_DIST += port.h
EXTRA_DIST += stl_util.h
EXTRA_DIST += sys_byteorder.h
EXTRA_DIST += template_util.h
EXTRA_DIST += tuple.h

noinst_LTLIBRARIES =

noinst_LTLIBRARIES += libsha1.la
libsha1_la_SOURCES = sha1.h
libsha1_la_SOURCES += sha1_portable.cc

noinst_LTLIBRARIES += libbase64.la
libbase64_la_SOURCES = base64.h
libbase64_la_SOURCES += base64.cc
libbase64_la_LIBADD = strings/libstring_piece.la
libbase64_la_LIBADD += $(top_builddir)/third_party/modp_b64/libmodp_b64.la

noinst_LTLIBRARIES += libmd5.la
libmd5_la_SOURCES = md5.h
libmd5_la_SOURCES += md5.cc
libmd5_la_LIBADD = strings/libstring_piece.la

noinst_LTLIBRARIES += profiler/libscoped_profile.la
profiler_libscoped_profile_la_SOURCES = profiler/scoped_profile.h
profiler_libscoped_profile_la_SOURCES += profiler/scoped_profile.cc

noinst_LTLIBRARIES += libbind.la
libbind_la_SOURCES = bind.h
libbind_la_SOURCES += bind_internal.h
libbind_la_SOURCES += bind_helpers.h
libbind_la_SOURCES += bind_helpers.cc
libbind_la_SOURCES += memory/raw_scoped_refptr_mismatch_checker.h

noinst_LTLIBRARIES += libtime.la
libtime_la_SOURCES = time.h
libtime_la_SOURCES += time.cc
libtime_la_SOURCES += time_posix.cc
if DARWIN
libtime_la_SOURCES += time_mac.cc
endif
libtime_la_LIBADD = third_party/nspr/libprtime.la

noinst_LTLIBRARIES += third_party/nspr/libprtime.la
third_party_nspr_libprtime_la_SOURCES = third_party/nspr/prtime.h
third_party_nspr_libprtime_la_SOURCES += third_party/nspr/prtime.cc
third_party_nspr_libprtime_la_SOURCES += third_party/nspr/prtypes.h
third_party_nspr_libprtime_la_SOURCES += third_party/nspr/prcpucfg.h
third_party_nspr_libprtime_la_SOURCES += third_party/nspr/prcpucfg_linux.h

noinst_LTLIBRARIES += librand_util.la
librand_util_la_SOURCES =
librand_util_la_SOURCES += rand_util.h
librand_util_la_SOURCES += rand_util.cc
librand_util_la_SOURCES += rand_util_posix.cc

noinst_LTLIBRARIES += metrics/libbucket_ranges.la
metrics_libbucket_ranges_la_SOURCES = metrics/bucket_ranges.h
metrics_libbucket_ranges_la_SOURCES += metrics/bucket_ranges.cc

noinst_LTLIBRARIES += metrics/libsample_vector.la
metrics_libsample_vector_la_SOURCES = metrics/sample_vector.h
metrics_libsample_vector_la_SOURCES += metrics/sample_vector.cc
metrics_libsample_vector_la_LIBADD = metrics/libhistogram_samples.la

noinst_LTLIBRARIES += memory/libweak_ptr.la
memory_libweak_ptr_la_SOURCES = memory/weak_ptr.h
memory_libweak_ptr_la_SOURCES += memory/weak_ptr.cc

noinst_LTLIBRARIES += synchronization/libcancellation_flag.la
synchronization_libcancellation_flag_la_SOURCES = synchronization/cancellation_flag.h
synchronization_libcancellation_flag_la_SOURCES += synchronization/cancellation_flag.cc

noinst_LTLIBRARIES += synchronization/libwaitable_event.la
synchronization_libwaitable_event_la_SOURCES = synchronization/waitable_event.h
synchronization_libwaitable_event_la_SOURCES += synchronization/waitable_event_posix.cc
synchronization_libwaitable_event_la_LIBADD = synchronization/libcondition_variable_posix.la

noinst_LTLIBRARIES += synchronization/libcondition_variable_posix.la
synchronization_libcondition_variable_posix_la_SOURCES = synchronization/condition_variable.h
synchronization_libcondition_variable_posix_la_SOURCES += synchronization/condition_variable_posix.cc

noinst_LTLIBRARIES += libthread_task_runner_handle.la
libthread_task_runner_handle_la_SOURCES = thread_task_runner_handle.h
libthread_task_runner_handle_la_SOURCES += thread_task_runner_handle.cc
libthread_task_runner_handle_la_SOURCES += single_thread_task_runner.h

noinst_LTLIBRARIES += metrics/libsample_map.la
metrics_libsample_map_la_SOURCES = metrics/sample_map.h
metrics_libsample_map_la_SOURCES += metrics/sample_map.cc

noinst_LTLIBRARIES += metrics/libhistogram_samples.la
metrics_libhistogram_samples_la_SOURCES = metrics/histogram_samples.h
metrics_libhistogram_samples_la_SOURCES += metrics/histogram_samples.cc

noinst_LTLIBRARIES += threading/libthread_checker_impl.la
threading_libthread_checker_impl_la_SOURCES = threading/thread_checker.h
threading_libthread_checker_impl_la_SOURCES += threading/thread_checker_impl.h
threading_libthread_checker_impl_la_SOURCES += threading/thread_checker_impl.cc


noinst_LTLIBRARIES += libvalues.la
libvalues_la_SOURCES = values.h
libvalues_la_SOURCES += values.cc
libvalues_la_SOURCES += float_util.h

noinst_LTLIBRARIES += metrics/libstatistics_recorder.la
metrics_libstatistics_recorder_la_SOURCES = metrics/statistics_recorder.h
metrics_libstatistics_recorder_la_SOURCES += metrics/statistics_recorder.cc
metrics_libstatistics_recorder_la_SOURCES += gtest_prod_util.h
metrics_libstatistics_recorder_la_SOURCES += debug/leak_annotations.h

# noinst_LTLIBRARIES += debug/libtrace_event.la
# debug_libtrace_event_la_SOURCES = debug/trace_event.h
# debug_libtrace_event_la_SOURCES += debug/trace_event_impl.cc
# debug_libtrace_event_la_SOURCES += debug/trace_event_impl.h
# debug_libtrace_event_la_SOURCES += hash_tables.h
# debug_libtrace_event_la_SOURCES += memory/scoped_vector.h
# debug_libtrace_event_la_SOURCES += observer_list.h
# debug_libtrace_event_la_SOURCES += observer_list_threadsafe.h
# debug_libtrace_event_la_LIBADD = memory/libref_counted_memory.la
# debug_libtrace_event_la_LIBADD += libstring_util.la
# debug_libtrace_event_la_LIBADD += libcallback.la
# debug_libtrace_event_la_LIBADD += synchronization/libcondition_variable_posix.la
# # debug_libtrace_event_la_LIBADD += threading/libthread.la
# debug_libtrace_event_la_LIBADD += libtimer.la
# debug_libtrace_event_la_LIBADD += threading/libplatform_thread.la
# debug_libtrace_event_la_LIBADD += synchronization/libcancellation_flag.la
# debug_libtrace_event_la_LIBADD += memory/libsingleton.la
# debug_libtrace_event_la_LIBADD += strings/libstring_piece.la

noinst_LTLIBRARIES += libpending_task.la
libpending_task_la_SOURCES = pending_task.h
libpending_task_la_SOURCES += pending_task.cc

noinst_LTLIBRARIES += librun_loop.la
librun_loop_la_SOURCES = run_loop.h
librun_loop_la_SOURCES += run_loop.cc
librun_loop_la_LIBADD = memory/libweak_ptr.la

noinst_LTLIBRARIES += memory/libref_counted_memory.la
memory_libref_counted_memory_la_SOURCES = memory/ref_counted_memory.h
memory_libref_counted_memory_la_SOURCES += memory/ref_counted_memory.cc

noinst_LTLIBRARIES += libtracking_info.la
libtracking_info_la_SOURCES = tracking_info.h
libtracking_info_la_SOURCES += tracking_info.cc

# noinst_LTLIBRARIES += libmessage_pump_default.la
# libmessage_pump_default_la_SOURCES = message_pump_default.cc
# libmessage_pump_default_la_SOURCES += message_pump_default.h
# libmessage_pump_default_la_LIBADD = synchronization/libwaitable_event.la

# noinst_LTLIBRARIES += libmessage_pump_glib.la
# libmessage_pump_glib_la_SOURCES = message_pump_glib.cc
# libmessage_pump_glib_la_SOURCES += message_pump_glib.h
# libmessage_pump_glib_la_CXXFLAGS = $(GLIB_CFLAGS)
# libmessage_pump_glib_la_LIBADD = memory/libweak_ptr.la

# noinst_LTLIBRARIES += libmessage_pump_gtk.la
# libmessage_pump_gtk_la_SOURCES = message_pump_gtk.cc
# libmessage_pump_gtk_la_SOURCES += message_pump_gtk.h
# libmessage_pump_gtk_la_CXXFLAGS = $(GTK_CFLAGS)
# libmessage_pump_gtk_la_LIBADD = $(GTK_LIBS)
# libmessage_pump_gtk_la_LIBADD += memory/libweak_ptr.la

# noinst_LTLIBRARIES += libmessage_pump_libevent.la
# libmessage_pump_libevent_la_SOURCES = message_pump_libevent.cc
# libmessage_pump_libevent_la_SOURCES += message_pump_libevent.h
# libmessage_pump_libevent_la_LIBADD = $(LIBEVENT_LIBS)
# libmessage_pump_libevent_la_LIBADD += memory/libweak_ptr.la
# libmessage_pump_libevent_la_LIBADD += threading/libthread_checker_impl.la

# noinst_LTLIBRARIES += libmessage_pump.la
# libmessage_pump_la_SOURCES = message_pump.cc
# libmessage_pump_la_SOURCES += message_pump.h
# libmessage_pump_la_LIBADD = libmessage_pump_default.la
# libmessage_pump_la_LIBADD += libmessage_pump_libevent.la
# libmessage_pump_la_LIBADD += libmessage_pump_gtk.la
# libmessage_pump_la_LIBADD += libmessage_pump_glib.la

noinst_LTLIBRARIES += metrics/libsparse_histogram.la
metrics_libsparse_histogram_la_SOURCES = metrics/sparse_histogram.cc
metrics_libsparse_histogram_la_SOURCES += metrics/sparse_histogram.h
metrics_libsparse_histogram_la_LIBADD = metrics/libsample_map.la
metrics_libsparse_histogram_la_LIBADD += metrics/libhistogram_samples.la
# metrics_libsparse_histogram_la_LIBADD += metrics/libhistogram_base.la
metrics_libsparse_histogram_la_LIBADD += synchronization/liblock.la


noinst_LTLIBRARIES += json/libjson_string_value_serializer.la
json_libjson_string_value_serializer_la_SOURCES = json/json_string_value_serializer.h
json_libjson_string_value_serializer_la_SOURCES += json/json_string_value_serializer.cc
json_libjson_string_value_serializer_la_LIBADD = json/libjson_reader.la
json_libjson_string_value_serializer_la_LIBADD += json/libjson_writer.la

noinst_LTLIBRARIES += json/libstring_escape.la
json_libstring_escape_la_SOURCES = json/string_escape.h
json_libstring_escape_la_SOURCES += json/string_escape.cc

noinst_LTLIBRARIES += json/libjson_writer.la
json_libjson_writer_la_SOURCES = json/json_writer.h
json_libjson_writer_la_SOURCES += json/json_writer.cc
json_libjson_writer_la_LIBADD = json/libstring_escape.la

noinst_LTLIBRARIES += json/libjson_parser.la
json_libjson_parser_la_SOURCES = json/json_parser.h
json_libjson_parser_la_SOURCES += json/json_parser.cc

noinst_LTLIBRARIES += json/libjson_reader.la
json_libjson_reader_la_SOURCES = json/json_reader.h
json_libjson_reader_la_SOURCES += json/json_reader.cc
json_libjson_reader_la_LIBADD = strings/libstring_piece.la
json_libjson_reader_la_LIBADD += json/libjson_parser.la

noinst_LTLIBRARIES += threading/libpost_task_and_reply_impl.la
threading_libpost_task_and_reply_impl_la_SOURCES = threading/post_task_and_reply_impl.cc
threading_libpost_task_and_reply_impl_la_SOURCES += threading/post_task_and_reply_impl.h
threading_libpost_task_and_reply_impl_la_LIBADD = message_loop/libmessage_loop_proxy.la

noinst_LTLIBRARIES += metrics/libhistogram.la
metrics_libhistogram_la_SOURCES = metrics/histogram.cc
metrics_libhistogram_la_SOURCES += metrics/histogram.h
metrics_libhistogram_la_LIBADD = metrics/libhistogram_base.la
metrics_libhistogram_la_LIBADD += metrics/libhistogram_samples.la
# metrics_libhistogram_la_LIBADD += json/libjson_reader.la
# metrics_libhistogram_la_LIBADD += json/libjson_writer.la
# metrics_libhistogram_la_LIBADD += json/libjson_string_value_serializer.la
# metrics_libhistogram_la_LIBADD += metrics/libsparse_histogram.la
metrics_libhistogram_la_LIBADD += libvalues.la
metrics_libhistogram_la_LIBADD += metrics/libbucket_ranges.la
metrics_libhistogram_la_LIBADD += metrics/libsample_vector.la
# metrics_libhistogram_la_LIBADD += libatomicops.la
metrics_libhistogram_la_LIBADD += libtime.la

metrics_libhistogram_la_LIBADD += metrics/libstatistics_recorder.la



noinst_LTLIBRARIES += metrics/libhistogram_base.la
metrics_libhistogram_base_la_SOURCES = metrics/histogram_base.h
metrics_libhistogram_base_la_SOURCES += metrics/histogram_base.cc
metrics_libhistogram_base_la_LIBADD = libtime.la
metrics_libhistogram_base_la_LIBADD += json/libjson_string_value_serializer.la
metrics_libhistogram_base_la_LIBADD += metrics/libsparse_histogram.la


noinst_LTLIBRARIES += libsys_info.la
libsys_info_la_SOURCES = sys_info.h
libsys_info_la_SOURCES += sys_info_posix.cc

noinst_LTLIBRARIES += posix/libfile_descriptor_shuffle.la
posix_libfile_descriptor_shuffle_la_SOURCES = posix/file_descriptor_shuffle.h
posix_libfile_descriptor_shuffle_la_SOURCES += posix/file_descriptor_shuffle.cc

noinst_LTLIBRARIES += allocator/libtype_profiler_control.la
allocator_libtype_profiler_control_la_SOURCES = allocator/type_profiler_control.h
allocator_libtype_profiler_control_la_SOURCES += allocator/type_profiler_control.cc

noinst_LTLIBRARIES += libprocess.la
libprocess_la_SOURCES = process.h
libprocess_la_SOURCES += process_posix.cc
# libprocess_la_SOURCES += process_linux.cc

noinst_LTLIBRARIES += third_party/dynamic_annotations/libdynamic_annotations.la
third_party_dynamic_annotations_libdynamic_annotations_la_SOURCES = third_party/dynamic_annotations/dynamic_annotations.h
third_party_dynamic_annotations_libdynamic_annotations_la_SOURCES += third_party/dynamic_annotations/dynamic_annotations.c

# Mac-specific libraries.
if DARWIN
noinst_LTLIBRARIES += mac/libmac_logging.la
mac_libmac_logging_la_SOURCES = \
  mac/mac_logging.h \
  mac/mac_logging.cc

noinst_LTLIBRARIES += mac/libscoped_mach_port.la
mac_libscoped_mach_port_la_SOURCES = \
  mac/scoped_mach_port.h \
  mac/scoped_mach_port.cc

noinst_LTLIBRARIES += mac/libmac_util.la
mac_libmac_util_la_SOURCES = \
  mac/mac_util.h \
  mac/mac_util.mm

noinst_LTLIBRARIES += mac/libbundle_locations.la
mac_libbundle_locations_la_SOURCES = \
  mac/bundle_locations.h \
  mac/bundle_locations.mm

noinst_LTLIBRARIES += mac/libfoundation_util.la
mac_libfoundation_util_la_SOURCES = \
  mac/foundation_util.h \
  mac/foundation_util.mm
mac_libfoundation_util_la_LIBADD = \
  mac/libbundle_locations.la \
  mac/libmac_logging.la

endif

noinst_LTLIBRARIES += libprocess_util.la
libprocess_util_la_SOURCES = process_util.h
libprocess_util_la_SOURCES += process_util.cc

if DARWIN
libprocess_util_la_SOURCES += process_util_mac.mm
endif

if LINUX
libprocess_util_la_SOURCES += process_util_linux.cc
endif

libprocess_util_la_SOURCES += files/dir_reader_posix.h
# libprocess_util_la_SOURCES += files/dir_reader_linux.h
libprocess_util_la_SOURCES += process_util_posix.cc
libprocess_util_la_SOURCES += strings/string_tokenizer.h
libprocess_util_la_LIBADD = libcommand_line.la
if DARWIN
libprocess_util_la_LIBADD += mac/libscoped_mach_port.la
libprocess_util_la_LIBADD += mac/libmac_util.la
libprocess_util_la_LIBADD += mac/libfoundation_util.la
endif
libprocess_util_la_LIBADD += threading/libthread_restrictions.la
libprocess_util_la_LIBADD += files/libfile_path.la
libprocess_util_la_LIBADD += threading/libthread_local.la
libprocess_util_la_LIBADD += strings/libsys_string_conversions.la
libprocess_util_la_LIBADD += libpickle.la
libprocess_util_la_LIBADD += libtime.la
libprocess_util_la_LIBADD += libsys_info.la
libprocess_util_la_LIBADD += third_party/dynamic_annotations/libdynamic_annotations.la
libprocess_util_la_LIBADD += libprocess.la
libprocess_util_la_LIBADD += allocator/libtype_profiler_control.la
libprocess_util_la_LIBADD += posix/libfile_descriptor_shuffle.la
libprocess_util_la_LIBADD += libfile_util.la


noinst_LTLIBRARIES += libtimer.la
libtimer_la_SOURCES = timer.h
libtimer_la_SOURCES += timer.cc

noinst_LTLIBRARIES += profiler/libalternate_timer.la
profiler_libalternate_timer_la_SOURCES = profiler/alternate_timer.h
profiler_libalternate_timer_la_SOURCES += profiler/alternate_timer.cc

noinst_LTLIBRARIES += threading/libthread_local_storage.la
threading_libthread_local_storage_la_SOURCES = threading/thread_local_storage_posix.cc
threading_libthread_local_storage_la_SOURCES += threading/thread_local_storage.h

noinst_LTLIBRARIES += profiler/libtracked_time.la
profiler_libtracked_time_la_SOURCES = profiler/tracked_time.h
profiler_libtracked_time_la_SOURCES += profiler/tracked_time.cc

noinst_LTLIBRARIES += threading/libthread_collision_warner.la
threading_libthread_collision_warner_la_SOURCES = threading/thread_collision_warner.h
threading_libthread_collision_warner_la_SOURCES += threading/thread_collision_warner.cc

noinst_LTLIBRARIES += strings/libutf_string_conversion_utils.la
strings_libutf_string_conversion_utils_la_SOURCES = strings/utf_string_conversion_utils.h
strings_libutf_string_conversion_utils_la_SOURCES += strings/utf_string_conversion_utils.cc

noinst_LTLIBRARIES += threading/libthread_id_name_manager.la
threading_libthread_id_name_manager_la_SOURCES = threading/thread_id_name_manager.h
threading_libthread_id_name_manager_la_SOURCES += threading/thread_id_name_manager.cc
threading_libthread_id_name_manager_la_LIBADD = synchronization/liblock.la
# threading_libthread_id_name_manager_la_LIBADD += libatomicops.la

noinst_LTLIBRARIES += memory/libsingleton.la
memory_libsingleton_la_SOURCES = memory/singleton.h
memory_libsingleton_la_SOURCES += memory/singleton.cc
memory_libsingleton_la_LIBADD = threading/libplatform_thread.la
memory_libsingleton_la_LIBADD += libat_exit.la

EXTRA_DIST = atomicops.h
if LINUX
noinst_LTLIBRARIES += libatomicops.la
libatomicops_la_SOURCES =
libatomicops_la_SOURCES += atomicops_internals_x86_gcc.h
libatomicops_la_SOURCES += atomicops_internals_x86_gcc.cc
endif
if DARWIN
EXTRA_DIST += atomicops_internals_mac.h
endif

noinst_LTLIBRARIES += third_party/icu/libicu_utf.la
third_party_icu_libicu_utf_la_SOURCES = third_party/icu/icu_utf.h
third_party_icu_libicu_utf_la_SOURCES += third_party/icu/icu_utf.cc

noinst_LTLIBRARIES += threading/libthread_local.la
threading_libthread_local_la_SOURCES = threading/thread_local.h
threading_libthread_local_la_SOURCES += threading/thread_local_posix.cc

noinst_LTLIBRARIES += libpickle.la
libpickle_la_SOURCES = pickle.h
libpickle_la_SOURCES += pickle.cc

noinst_LTLIBRARIES += strings/libsys_string_conversions.la
strings_libsys_string_conversions_la_SOURCES = strings/sys_string_conversions.h
strings_libsys_string_conversions_la_SOURCES += strings/sys_string_conversions_posix.cc
if DARWIN
strings_libsys_string_conversions_la_SOURCES += strings/sys_string_conversions_mac.mm
endif

noinst_LTLIBRARIES += libstring16.la
libstring16_la_SOURCES = string16.h
libstring16_la_SOURCES += string16.cc

noinst_LTLIBRARIES += third_party/dmg_fp/libdmg_fp.la
third_party_dmg_fp_libdmg_fp_la_SOURCES = third_party/dmg_fp/g_fmt.cc
third_party_dmg_fp_libdmg_fp_la_SOURCES += third_party/dmg_fp/dtoa.cc
third_party_dmg_fp_libdmg_fp_la_SOURCES += third_party/dmg_fp/dmg_fp.h

noinst_LTLIBRARIES += strings/libstring_split.la
strings_libstring_split_la_SOURCES = strings/string_split.h
strings_libstring_split_la_SOURCES += strings/string_split.cc


noinst_LTLIBRARIES += debug/libstack_trace.la
debug_libstack_trace_la_SOURCES = debug/stack_trace.h
debug_libstack_trace_la_SOURCES += debug/stack_trace_posix.cc
debug_libstack_trace_la_SOURCES += debug/stack_trace.cc
debug_libstack_trace_la_LIBADD = debug/libdebugger.la

noinst_LTLIBRARIES += debug/libalias.la
debug_libalias_la_SOURCES = debug/alias.cc
debug_libalias_la_SOURCES += debug/alias.h


noinst_LTLIBRARIES += files/libscoped_temp_dir.la
files_libscoped_temp_dir_la_SOURCES = files/scoped_temp_dir.h
files_libscoped_temp_dir_la_SOURCES += files/scoped_temp_dir.cc

# noinst_LTLIBRARIES += libsequenced_task_runner.la
# libsequenced_task_runner_la_SOURCES = sequenced_task_runner.h
# libsequenced_task_runner_la_SOURCES += sequenced_task_runner.cc
# libsequenced_task_runner_la_SOURCES += sequenced_task_runner_helpers.h

# noinst_LTLIBRARIES += files/libfile_path_watcher.la
# files_libfile_path_watcher_la_SOURCES = files/file_path_watcher.h
# files_libfile_path_watcher_la_SOURCES += files/file_path_watcher.cc
# files_libfile_path_watcher_la_SOURCES += files/file_path_watcher_@FILE_PATH_WATCHER_SUFFIX@.cc
# files_libfile_path_watcher_la_LIBADD = message_loop/libmessage_loop_proxy.la
# files_libfile_path_watcher_la_LIBADD += libcallback.la
# files_libfile_path_watcher_la_LIBADD += libtask_runner.la
# files_libfile_path_watcher_la_LIBADD += libmessage_loop.la
# files_libfile_path_watcher_la_LIBADD += files/libfile_path.la
# files_libfile_path_watcher_la_LIBADD += libfile_util.la
# files_libfile_path_watcher_la_LIBADD += threading/libthread.la
# files_libfile_path_watcher_la_LIBADD += strings/libstring_piece.la
# files_libfile_path_watcher_la_LIBADD += liblogging.la

# noinst_LTLIBRARIES += threading/libthread.la
# threading_libthread_la_SOURCES = threading/thread.h
# threading_libthread_la_SOURCES += threading/thread.cc
# threading_libthread_la_LIBADD = memory/libweak_ptr.la
# threading_libthread_la_LIBADD += libmessage_loop.la
# threading_libthread_la_LIBADD += synchronization/libwaitable_event.la

noinst_LTLIBRARIES += libfile_util.la
libfile_util_la_CXXFLAGS = $(GLIB_CFLAGS)
libfile_util_la_SOURCES = file_util.h
libfile_util_la_SOURCES += posix/eintr_wrapper.h
libfile_util_la_SOURCES += file_util.cc
if DARWIN
libfile_util_la_SOURCES += file_util_mac.mm
endif
if LINUX
libfile_util_la_SOURCES += file_util_linux.cc
endif
libfile_util_la_SOURCES += file_util_posix.cc
libfile_util_la_LIBADD = libplatform_file.la

noinst_LTLIBRARIES += nix/libxdg_util.la
nix_libxdg_util_la_SOURCES = nix/xdg_util.h
nix_libxdg_util_la_SOURCES += nix/xdg_util.cc

noinst_LTLIBRARIES += third_party/xdg_user_dirs/libxdg_user_dir_lookup.la
third_party_xdg_user_dirs_libxdg_user_dir_lookup_la_SOURCES = third_party/xdg_user_dirs/xdg_user_dir_lookup.h
third_party_xdg_user_dirs_libxdg_user_dir_lookup_la_SOURCES += third_party/xdg_user_dirs/xdg_user_dir_lookup.cc

noinst_LTLIBRARIES += third_party/xdg_mime/libxdgmimealias.la
third_party_xdg_mime_libxdgmimealias_la_SOURCES = third_party/xdg_mime/xdgmimealias.c
third_party_xdg_mime_libxdgmimealias_la_SOURCES += third_party/xdg_mime/xdgmimealias.h

noinst_LTLIBRARIES += third_party/xdg_mime/libxdgmime.la
third_party_xdg_mime_libxdgmime_la_SOURCES = third_party/xdg_mime/xdgmime.c
third_party_xdg_mime_libxdgmime_la_SOURCES += third_party/xdg_mime/xdgmime.h

noinst_LTLIBRARIES += third_party/xdg_mime/libxdgmimecache.la
third_party_xdg_mime_libxdgmimecache_la_SOURCES = third_party/xdg_mime/xdgmimecache.c
third_party_xdg_mime_libxdgmimecache_la_SOURCES += third_party/xdg_mime/xdgmimecache.h

noinst_LTLIBRARIES += third_party/xdg_mime/libxdgmimeglob.la
third_party_xdg_mime_libxdgmimeglob_la_SOURCES = third_party/xdg_mime/xdgmimeglob.c
third_party_xdg_mime_libxdgmimeglob_la_SOURCES += third_party/xdg_mime/xdgmimeglob.h

noinst_LTLIBRARIES += third_party/xdg_mime/libxdgmimeicon.la
third_party_xdg_mime_libxdgmimeicon_la_SOURCES = third_party/xdg_mime/xdgmimeicon.c
third_party_xdg_mime_libxdgmimeicon_la_SOURCES += third_party/xdg_mime/xdgmimeicon.h

noinst_LTLIBRARIES += third_party/xdg_mime/libxdgmimeint.la
third_party_xdg_mime_libxdgmimeint_la_SOURCES = third_party/xdg_mime/xdgmimeint.c
third_party_xdg_mime_libxdgmimeint_la_SOURCES += third_party/xdg_mime/xdgmimeint.h

noinst_LTLIBRARIES += third_party/xdg_mime/libxdgmimemagic.la
third_party_xdg_mime_libxdgmimemagic_la_SOURCES = third_party/xdg_mime/xdgmimemagic.c
third_party_xdg_mime_libxdgmimemagic_la_SOURCES += third_party/xdg_mime/xdgmimemagic.h

noinst_LTLIBRARIES += third_party/xdg_mime/libxdgmimeparent.la
third_party_xdg_mime_libxdgmimeparent_la_SOURCES = third_party/xdg_mime/xdgmimeparent.c
third_party_xdg_mime_libxdgmimeparent_la_SOURCES += third_party/xdg_mime/xdgmimeparent.h

noinst_LTLIBRARIES += nix/libmime_util_xdg.la
nix_libmime_util_xdg_la_SOURCES = nix/mime_util_xdg.h
nix_libmime_util_xdg_la_SOURCES += nix/mime_util_xdg.cc

noinst_LTLIBRARIES += libbase_paths.la
libbase_paths_la_SOURCES = base_paths.h
libbase_paths_la_SOURCES += base_paths.cc
libbase_paths_la_SOURCES += base_paths_posix.h
libbase_paths_la_SOURCES += base_paths_posix.cc

noinst_LTLIBRARIES += libpath_service.la
libpath_service_la_SOURCES = path_service.h
libpath_service_la_SOURCES += path_service.cc

noinst_LTLIBRARIES += liblazy_instance.la
liblazy_instance_la_SOURCES = lazy_instance.h
liblazy_instance_la_SOURCES += lazy_instance.cc
liblazy_instance_la_SOURCES += memory/aligned_memory.h

noinst_LTLIBRARIES += files/libfile_path.la
files_libfile_path_la_SOURCES = files/file_path.h
files_libfile_path_la_SOURCES += files/file_path.cc
files_libfile_path_la_LIBADD = libpickle.la \
	strings/libsys_string_conversions.la \
	libutf_string_conversions.la \
	libstring_util.la

# noinst_LTLIBRARIES += libmessage_loop.la
# libmessage_loop_la_SOURCES = message_loop.h
# libmessage_loop_la_SOURCES += message_loop.cc
# libmessage_loop_la_SOURCES += message_loop_proxy.h
# libmessage_loop_la_LIBADD = libtracked_objects.la
# libmessage_loop_la_LIBADD += libmessage_pump.la
# libmessage_loop_la_LIBADD += libpending_task.la
# libmessage_loop_la_LIBADD += libtracking_info.la
# libmessage_loop_la_LIBADD += libthread_task_runner_handle.la
# libmessage_loop_la_LIBADD += message_loop/libmessage_loop_proxy.la
# libmessage_loop_la_LIBADD += message_loop/libmessage_loop_proxy_impl.la
# libmessage_loop_la_LIBADD += libtime.la
# libmessage_loop_la_LIBADD += librun_loop.la
# libmessage_loop_la_LIBADD += metrics/libhistogram.la
# libmessage_loop_la_LIBADD += metrics/libstatistics_recorder.la
# libmessage_loop_la_LIBADD += debug/libalias.la
# libmessage_loop_la_LIBADD += debug/libtrace_event.la

noinst_LTLIBRARIES += message_loop/libmessage_loop_proxy.la
message_loop_libmessage_loop_proxy_la_SOURCES = message_loop/message_loop_proxy.h
message_loop_libmessage_loop_proxy_la_SOURCES += message_loop/message_loop_proxy.cc

# noinst_LTLIBRARIES += message_loop/libmessage_loop_proxy_impl.la
# message_loop_libmessage_loop_proxy_impl_la_SOURCES = message_loop/message_loop_proxy_impl.h
# message_loop_libmessage_loop_proxy_impl_la_SOURCES += message_loop/message_loop_proxy_impl.cc

noinst_LTLIBRARIES += libtracked_objects.la
libtracked_objects_la_SOURCES = tracked_objects.h
libtracked_objects_la_SOURCES += tracked_objects.cc
libtracked_objects_la_SOURCES += third_party/valgrind/memcheck.h
libtracked_objects_la_SOURCES += third_party/valgrind/valgrind.h
libtracked_objects_la_LIBADD = liblazy_instance.la
libtracked_objects_la_LIBADD += synchronization/liblock.la
libtracked_objects_la_LIBADD += liblocation.la
libtracked_objects_la_LIBADD += profiler/libtracked_time.la
libtracked_objects_la_LIBADD += threading/libthread_local_storage.la
libtracked_objects_la_LIBADD += profiler/libalternate_timer.la
# libtracked_objects_la_LIBADD += libprocess_util.la

noinst_LTLIBRARIES += memory/libref_counted.la
memory_libref_counted_la_SOURCES = memory/ref_counted.h
memory_libref_counted_la_SOURCES += memory/ref_counted.cc
memory_libref_counted_la_SOURCES += atomic_ref_count.h
memory_libref_counted_la_LIBADD = threading/libthread_collision_warner.la
# memory_libref_counted_la_LIBADD += libatomicops.la
memory_libref_counted_la_LIBADD += libtask_runner.la


noinst_LTLIBRARIES += libcallback.la
libcallback_la_SOURCES = callback.h
libcallback_la_SOURCES += callback_forward.h
libcallback_la_SOURCES += callback_internal.h
libcallback_la_SOURCES += callback_internal.cc
libcallback_la_SOURCES += callback_helpers.h
libcallback_la_SOURCES += cancelable_callback.h
libcallback_la_LIBADD = memory/libref_counted.la

noinst_LTLIBRARIES += liblocation.la
liblocation_la_SOURCES = location.h location.cc

noinst_LTLIBRARIES += libtask_runner.la
libtask_runner_la_SOURCES = task_runner.h
libtask_runner_la_SOURCES += task_runner.cc
libtask_runner_la_SOURCES += task_runner_util.h
libtask_runner_la_LIBADD = threading/libpost_task_and_reply_impl.la

noinst_LTLIBRARIES += synchronization/liblock.la
synchronization_liblock_la_SOURCES = synchronization/lock_impl.h
synchronization_liblock_la_SOURCES += synchronization/lock_impl_posix.cc
synchronization_liblock_la_SOURCES += synchronization/lock.h
synchronization_liblock_la_SOURCES += synchronization/lock.cc

noinst_LTLIBRARIES += liblogging.la
liblogging_la_SOURCES = logging.h
liblogging_la_SOURCES += logging.cc
liblogging_la_LIBADD =
liblogging_la_LIBADD += debug/libdebugger.la
liblogging_la_LIBADD += debug/libstack_trace.la
liblogging_la_LIBADD += libutf_string_conversions.la
liblogging_la_LIBADD += libsafe_strerror_posix.la
liblogging_la_LIBADD += libvlog.la
liblogging_la_LIBADD += libbase_switches.la
liblogging_la_LIBADD += debug/libalias.la
liblogging_la_LIBADD += strings/libstring_piece.la
liblogging_la_LIBADD += threading/libplatform_thread.la
liblogging_la_LIBADD += libcommand_line.la

noinst_LTLIBRARIES += libcommand_line.la
libcommand_line_la_SOURCES = command_line.h
libcommand_line_la_SOURCES += command_line.cc
libcommand_line_la_LIBADD = strings/libstring_split.la

noinst_LTLIBRARIES += strings/libstring_number_conversions.la
strings_libstring_number_conversions_la_SOURCES =
strings_libstring_number_conversions_la_SOURCES += string_number_conversions.h
strings_libstring_number_conversions_la_SOURCES += strings/string_number_conversions.h
strings_libstring_number_conversions_la_SOURCES += strings/string_number_conversions.cc
strings_libstring_number_conversions_la_LIBADD = third_party/dmg_fp/libdmg_fp.la

noinst_LTLIBRARIES += libat_exit.la
libat_exit_la_SOURCES = at_exit.cc
libat_exit_la_SOURCES += at_exit.h
libat_exit_la_LIBADD = synchronization/liblock.la
libat_exit_la_LIBADD += libcallback.la

noinst_LTLIBRARIES += files/libmemory_mapped_file.la
files_libmemory_mapped_file_la_SOURCES =
files_libmemory_mapped_file_la_SOURCES += files/memory_mapped_file.h
files_libmemory_mapped_file_la_SOURCES += files/memory_mapped_file.cc
files_libmemory_mapped_file_la_SOURCES += files/memory_mapped_file_posix.cc

noinst_LTLIBRARIES += libplatform_file.la
libplatform_file_la_SOURCES = platform_file.cc
libplatform_file_la_SOURCES += platform_file.h
libplatform_file_la_SOURCES += platform_file_posix.cc
libplatform_file_la_LIBADD = threading/libthread_local.la

noinst_LTLIBRARIES += libstringprintf.la
libstringprintf_la_SOURCES = stringprintf.h
libstringprintf_la_SOURCES += stringprintf.cc
libstringprintf_la_LIBADD = libstring_util.la

noinst_LTLIBRARIES += threading/libthread_restrictions.la
threading_libthread_restrictions_la_SOURCES = threading/thread_restrictions.h
threading_libthread_restrictions_la_SOURCES += threading/thread_restrictions.cc
threading_libthread_restrictions_la_LIBADD = liblazy_instance.la

noinst_LTLIBRARIES += libstring_util.la
libstring_util_la_SOURCES = string_util.cc
libstring_util_la_SOURCES += string_util.h
libstring_util_la_SOURCES += string_util_posix.h
libstring_util_la_LIBADD = third_party/icu/libicu_utf.la
libstring_util_la_LIBADD += threading/libthread_restrictions.la
# libstring_util_la_LIBADD += libatomicops.la
libstring_util_la_LIBADD += libstring16.la
libstring_util_la_LIBADD += memory/libsingleton.la

noinst_LTLIBRARIES += strings/libstring_piece.la
strings_libstring_piece_la_SOURCES = strings/string_piece.cc
strings_libstring_piece_la_SOURCES += strings/string_piece.h

noinst_LTLIBRARIES += threading/libplatform_thread.la
threading_libplatform_thread_la_SOURCES =
threading_libplatform_thread_la_SOURCES += threading/platform_thread.h
threading_libplatform_thread_la_SOURCES += threading/platform_thread_posix.cc
if DARWIN
threading_libplatform_thread_la_SOURCES += threading/platform_thread_mac.mm
endif
threading_libplatform_thread_la_LIBADD =
threading_libplatform_thread_la_LIBADD += libtracked_objects.la
threading_libplatform_thread_la_LIBADD += threading/libthread_id_name_manager.la

noinst_LTLIBRARIES += libutf_string_conversions.la
libutf_string_conversions_la_SOURCES = utf_string_conversions.cc
libutf_string_conversions_la_SOURCES += utf_string_conversions.h
libutf_string_conversions_la_LIBADD = strings/libutf_string_conversion_utils.la
libutf_string_conversions_la_LIBADD += strings/libstring_piece.la
libutf_string_conversions_la_LIBADD += libstring16.la

noinst_LTLIBRARIES += debug/libdebugger.la
debug_libdebugger_la_SOURCES = debug/debugger.cc
debug_libdebugger_la_SOURCES += debug/debugger.h
debug_libdebugger_la_SOURCES += debug/debugger_posix.cc
debug_libdebugger_la_LIBADD = libstringprintf.la

noinst_LTLIBRARIES += libsafe_strerror_posix.la
libsafe_strerror_posix_la_SOURCES = safe_strerror_posix.h
libsafe_strerror_posix_la_SOURCES += safe_strerror_posix.cc

noinst_LTLIBRARIES += libvlog.la
libvlog_la_SOURCES = vlog.h
libvlog_la_SOURCES += vlog.cc
libvlog_la_LIBADD = strings/libstring_number_conversions.la

noinst_LTLIBRARIES += libbase_switches.la
libbase_switches_la_SOURCES = base_switches.h
libbase_switches_la_SOURCES += base_switches.cc

noinst_LTLIBRARIES += libenvironment.la
libenvironment_la_SOURCES = environment.h
libenvironment_la_SOURCES += environment.cc
