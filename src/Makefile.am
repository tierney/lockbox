AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src
AM_CPPFLAGS += -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H $(DEPS_CFLAGS) $(GTK_CFLAGS)
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
lockbox_main_SOURCES += base/pickle.h base/base_export.h base/pickle.cc
lockbox_main_SOURCES += base/values.cc
lockbox_main_SOURCES += base/metrics/bucket_ranges.cc
lockbox_main_SOURCES += base/time_posix.cc
lockbox_main_SOURCES += base/metrics/sample_vector.cc
lockbox_main_SOURCES += base/time.cc
lockbox_main_SOURCES += base/stringprintf.cc
lockbox_main_SOURCES += base/threading/thread_restrictions.cc \
	base/debug/alias.cc \
	base/memory/weak_ptr.cc \
	base/debug/trace_event_impl.h \
	base/debug/trace_event_impl.cc
lockbox_main_SOURCES += base/threading/platform_thread_posix.cc
lockbox_main_SOURCES += base/synchronization/cancellation_flag.cc
lockbox_main_SOURCES += base/synchronization/waitable_event_posix.cc
lockbox_main_SOURCES += base/string_util.cc
lockbox_main_SOURCES += base/strings/string_split.h
lockbox_main_SOURCES += base/strings/string_split.cc
lockbox_main_SOURCES += base/memory/ref_counted_memory.cc
lockbox_main_SOURCES += base/threading/thread_id_name_manager.cc
lockbox_main_SOURCES += base/threading/thread_local_posix.cc
lockbox_main_SOURCES += base/atomicops_internals_x86_gcc.cc
lockbox_main_SOURCES += base/at_exit.cc
lockbox_main_SOURCES += base/memory/singleton.h base/memory/singleton.cc
lockbox_main_SOURCES += base/strings/string_piece.cc
lockbox_main_SOURCES += base/synchronization/condition_variable_posix.cc
lockbox_main_SOURCES += base/third_party/dynamic_annotations/dynamic_annotations.c
lockbox_main_SOURCES += base/process_util_@GENERIC_OS_SUFFIX@.@OS_LANG_EXT@
lockbox_main_SOURCES += base/process_posix.cc
lockbox_main_SOURCES += base/process_util_posix.cc \
	base/process_util.h \
	base/process_util.cc \
	base/allocator/type_profiler_control.cc \
	base/posix/file_descriptor_shuffle.cc \
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
lockbox_main_SOURCES += base/string16.cc
lockbox_main_SOURCES += base/utf_string_conversions.cc
lockbox_main_SOURCES += base/json/json_writer.cc
lockbox_main_SOURCES += base/third_party/nspr/prtime.cc
lockbox_main_SOURCES += base/threading/thread_checker_impl.cc
lockbox_main_SOURCES += base/third_party/icu/icu_utf.cc
lockbox_main_SOURCES += base/strings/string_number_conversions.cc
lockbox_main_SOURCES += base/sys_info_posix.cc
lockbox_main_SOURCES += base/message_pump.cc
lockbox_main_SOURCES += base/json/json_reader.cc
lockbox_main_SOURCES += base/strings/utf_string_conversion_utils.cc
lockbox_main_SOURCES += base/json/string_escape.cc
lockbox_main_SOURCES += base/third_party/dmg_fp/g_fmt.cc
lockbox_main_SOURCES += base/third_party/dmg_fp/dtoa.cc
lockbox_main_SOURCES += base/json/json_parser.cc
lockbox_main_SOURCES += base/debug/stack_trace_posix.cc
lockbox_main_SOURCES += base/debug/stack_trace.cc
lockbox_main_SOURCES += base/debug/debugger_posix.cc
lockbox_main_SOURCES += base/safe_strerror_posix.cc
lockbox_main_SOURCES += base/vlog.cc
lockbox_main_SOURCES += base/command_line.cc
lockbox_main_SOURCES += base/base_switches.cc
lockbox_main_SOURCES += base/strings/sys_string_conversions_posix.cc
lockbox_main_SOURCES += base/platform_file.cc
lockbox_main_SOURCES += base/platform_file_posix.cc
lockbox_main_SOURCES += base/profiler/tracked_time.cc
lockbox_main_SOURCES += base/threading/thread_local_storage_posix.cc
lockbox_main_SOURCES += base/profiler/alternate_timer.cc
lockbox_main_SOURCES += base/threading/thread_collision_warner.cc
lockbox_main_SOURCES += base/threading/post_task_and_reply_impl.cc

lockbox_main_LDADD += libfile_path_watcher.la
lockbox_main_LDADD += libmessage_loop.la
lockbox_main_LDADD += libmessage_loop_proxy.la
lockbox_main_LDADD += libtracked_objects.la
lockbox_main_LDADD += libref_counted.la
lockbox_main_LDADD += libcallback.la
lockbox_main_LDADD += liblocation.la
lockbox_main_LDADD += libtask_runner.la
lockbox_main_LDADD += liblock.la


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
libfile_path_watcher_la_SOURCES += base/threading/thread.cc
libfile_path_watcher_la_SOURCES += base/logging.cc
libfile_path_watcher_la_SOURCES += base/files/file_path.cc
libfile_path_watcher_la_SOURCES += base/lazy_instance.cc
libfile_path_watcher_la_SOURCES += base/file_util.cc
libfile_path_watcher_la_SOURCES += base/file_util_@GENERIC_OS_SUFFIX@.@OS_LANG_EXT@
# libfile_path_watcher_la_SOURCES += base/file_util_posix.cc
libfile_path_watcher_la_SOURCES += base/message_loop/message_loop_proxy_impl.cc



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
