AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src
AM_CPPFLAGS += -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H
AM_CXXFLAGS = -Wall -Wextra

SUBDIRS =
TESTS =
bin_PROGRAMS =
noinst_PROGRAMS =
noinst_LIBRARIES =


bin_PROGRAMS += lockbox_main
lockbox_main_SOURCES = lockbox_main.cc
lockbox_main_SOURCES +=
lockbox_main_LDADD = libfile_path_watcher.a
lockbox_main_LDADD += libmessage_loop.a
lockbox_main_LDADD += libmessage_loop_proxy.a
lockbox_main_LDADD += libtracked_objects.a
lockbox_main_LDADD += libref_counted.a
lockbox_main_LDADD += libcallback.a
lockbox_main_LDADD += liblocation.a
lockbox_main_LDADD += libtask_runner.a
lockbox_main_LDADD += liblock.a

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


noinst_LIBRARIES += libuserthrift.a
libuserthrift_a_SOURCES =
libuserthrift_a_SOURCES += UserStorage.cpp
libuserthrift_a_SOURCES += UserStorage.h
libuserthrift_a_SOURCES += user_constants.cpp
libuserthrift_a_SOURCES += user_types.cpp
libuserthrift_a_SOURCES += user_constants.h
libuserthrift_a_SOURCES += user_types.h

$(libuserthrift_la_SOURCES): $(srcdir)/user.thrift
	$(THRIFT_BUILD)


noinst_LIBRARIES += libhash_chain_digestthrift.a
libhash_chain_digestthrift_a_SOURCES =
libhash_chain_digestthrift_a_SOURCES += VersionExchange.cpp
libhash_chain_digestthrift_a_SOURCES += VersionExchange.h
libhash_chain_digestthrift_a_SOURCES += hash_chain_digest_constants.cpp
libhash_chain_digestthrift_a_SOURCES += hash_chain_digest_constants.h
libhash_chain_digestthrift_a_SOURCES += hash_chain_digest_types.cpp
libhash_chain_digestthrift_a_SOURCES += hash_chain_digest_types.h

$(libhash_chain_digestthrift_la_SOURCES): $(srcdir)/hash_chain_digest.thrift
	$(THRIFT_BUILD)


clean-local: clean-local-check
.PHONY: clean-local-check
clean-local-check:
	-rm -rf \
		$(libuserthrift_la_SOURCES) \
		$(libhash_chain_digestthrift_la_SOURCES) \
		*.skeleton.cpp

noinst_LIBRARIES += libfile_path_watcher.a
libfile_path_watcher_a_CPPFLAGS = -I$(top_srcdir)/src
libfile_path_watcher_a_SOURCES = base/files/file_path_watcher.h
libfile_path_watcher_a_SOURCES += base/files/file_path_watcher.cc
libfile_path_watcher_a_SOURCES += base/files/file_path_watcher_@FILE_PATH_WATCHER_SUFFIX@.cc
libfile_path_watcher_a_SOURCES += \
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
libfile_path_watcher_a_SOURCES += base/threading/thread.cc
libfile_path_watcher_a_SOURCES += base/logging.cc
libfile_path_watcher_a_SOURCES += base/files/file_path.cc
libfile_path_watcher_a_SOURCES += base/lazy_instance.cc
libfile_path_watcher_a_SOURCES += base/file_util.cc
libfile_path_watcher_a_SOURCES += base/file_util_linux.cc
libfile_path_watcher_a_SOURCES += base/file_util_posix.cc



noinst_LIBRARIES += libmessage_loop.a
libmessage_loop_a_SOURCES = base/message_loop.h
libmessage_loop_a_SOURCES += base/message_loop.cc

noinst_LIBRARIES += libmessage_loop_proxy.a
libmessage_loop_proxy_a_SOURCES = base/message_loop/message_loop_proxy.h
libmessage_loop_proxy_a_SOURCES += base/message_loop/message_loop_proxy.cc

noinst_LIBRARIES += libtracked_objects.a
libtracked_objects_a_SOURCES = base/tracked_objects.h
libtracked_objects_a_SOURCES += base/tracked_objects.cc

noinst_LIBRARIES += libref_counted.a
libref_counted_a_SOURCES = base/memory/ref_counted.h
libref_counted_a_SOURCES += base/memory/ref_counted.cc

noinst_LIBRARIES += libcallback.a
libcallback_a_SOURCES = base/callback.h
libcallback_a_SOURCES += base/callback_forward.h
libcallback_a_SOURCES += base/cancelable_callback.h
libcallback_a_SOURCES += base/callback_internal.cc
libcallback_a_SOURCES += base/callback_helpers.h

noinst_LIBRARIES += liblocation.a
liblocation_a_SOURCES = base/location.h base/location.cc

noinst_LIBRARIES += libtask_runner.a
libtask_runner_a_SOURCES = base/task_runner.h base/task_runner.cc base/task_runner_util.h

noinst_LIBRARIES += liblock.a
liblock_a_SOURCES = base/synchronization/lock_impl.h
liblock_a_SOURCES += base/synchronization/lock_impl_posix.cc
liblock_a_SOURCES += base/synchronization/lock.h
liblock_a_SOURCES += base/synchronization/lock.cc
