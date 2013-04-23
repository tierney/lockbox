AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src
AM_CPPFLAGS += -DUSE_OPENSSL
AM_CXXFLAGS = -Wall -Wextra

TEST_DIR_LOC = $(top_srcdir)/src/testing/gtest

TESTS =

EXTRA_DIST = crypto_export.h

noinst_LTLIBRARIES =
check_PROGRAMS =
bin_PROGRAMS =

noinst_LTLIBRARIES += libencryptor.la
libencryptor_la_SOURCES = encryptor.h
libencryptor_la_SOURCES += encryptor.cc
libencryptor_la_SOURCES += encryptor_openssl.cc
libencryptor_la_LIBADD = libopenssl_util.la

noinst_LTLIBRARIES += librandom.la
librandom_la_SOURCES = random.h
librandom_la_SOURCES += random.cc
librandom_la_LIBADD = $(top_srcdir)/src/base/librand_util.la

noinst_LTLIBRARIES += libopenssl_util.la
libopenssl_util_la_SOURCES = openssl_util.h
libopenssl_util_la_SOURCES += openssl_util.cc

TESTS += random_unittest
bin_PROGRAMS += random_unittest
random_unittest_SOURCES = random_unittest.cc
random_unittest_LDADD = $(top_srcdir)/src/testing/gtest/lib/libgtest.la
random_unittest_LDADD += $(top_srcdir)/src/testing/gtest/lib/libgtest_main.la
random_unittest_LDADD += librandom.la
random_unittest_LDADD += $(top_srcdir)/src/liblogging.la

TESTS += encryptor_unittest
bin_PROGRAMS += encryptor_unittest
encryptor_unittest_SOURCES = encryptor_unittest.cc
encryptor_unittest_LDADD = $(top_srcdir)/src/testing/gtest/lib/libgtest.la
encryptor_unittest_LDADD += $(top_srcdir)/src/testing/gtest/lib/libgtest_main.la
encryptor_unittest_LDADD += $(top_srcdir)/src/liblogging.la
encryptor_unittest_LDADD += libencryptor.la
encryptor_unittest_LDADD += libsymmetric_key.la

noinst_LTLIBRARIES += libsymmetric_key.la
libsymmetric_key_la_SOURCES = symmetric_key.h
libsymmetric_key_la_SOURCES += symmetric_key_openssl.cc

TESTS += symmetric_key_unittest
bin_PROGRAMS += symmetric_key_unittest
symmetric_key_unittest_SOURCES = symmetric_key_unittest.cc
symmetric_key_unittest_LDADD = $(top_srcdir)/src/testing/gtest/lib/libgtest.la
symmetric_key_unittest_LDADD += $(top_srcdir)/src/testing/gtest/lib/libgtest_main.la
symmetric_key_unittest_LDADD += $(top_srcdir)/src/liblogging.la
symmetric_key_unittest_LDADD += libsymmetric_key.la
symmetric_key_unittest_LDADD += libencryptor.la

noinst_LTLIBRARIES += libopenpgp_symmetric_encryption.la
libopenpgp_symmetric_encryption_la_SOURCES = openpgp_symmetric_encryption.h
libopenpgp_symmetric_encryption_la_SOURCES += openpgp_symmetric_encryption.cc
libopenpgp_symmetric_encryption_la_CXXFLAGS = $(NSS_CFLAGS)
libopenpgp_symmetric_encryption_la_LIBADD = $(NSS_LIBS)
libopenpgp_symmetric_encryption_la_LIBADD += libnss_util.la
libopenpgp_symmetric_encryption_la_LIBADD += librandom.la
libopenpgp_symmetric_encryption_la_LIBADD += $(top_srcdir)/src/liblogging.la

TESTS += openpgp_symmetric_encryption_unittest
bin_PROGRAMS += openpgp_symmetric_encryption_unittest
openpgp_symmetric_encryption_unittest_SOURCES = openpgp_symmetric_encryption_unittest.cc
openpgp_symmetric_encryption_unittest_LDADD = $(top_srcdir)/src/testing/gtest/lib/libgtest.la
openpgp_symmetric_encryption_unittest_LDADD += $(top_srcdir)/src/testing/gtest/lib/libgtest_main.la
openpgp_symmetric_encryption_unittest_LDADD += $(top_srcdir)/src/liblogging.la
openpgp_symmetric_encryption_unittest_LDADD += libopenpgp_symmetric_encryption.la

noinst_LTLIBRARIES += libnss_util.la
libnss_util_la_SOURCES = nss_util.h
libnss_util_la_SOURCES += nss_util.cc
libnss_util_la_CXXFLAGS = $(NSS_CFLAGS)
libnss_util_la_LIBADD = $(NSS_LIBS)
libnss_util_la_LIBADD += $(top_srcdir)/src/base/metrics/libhistogram.la
libnss_util_la_LIBADD += $(top_srcdir)/src/libenvironment.la

noinst_LTLIBRARIES += librsa_private_key.la
librsa_private_key_la_SOURCES = rsa_private_key.h
librsa_private_key_la_SOURCES += rsa_private_key.cc
librsa_private_key_la_SOURCES += rsa_private_key_openssl.cc
librsa_private_key_la_LIBADD = $(top_srcdir)/src/liblogging.la
librsa_private_key_la_LIBADD += $(top_srcdir)/src/liblocation.la
librsa_private_key_la_LIBADD += libopenssl_util.la

TESTS += rsa_private_key_unittest
bin_PROGRAMS += rsa_private_key_unittest
rsa_private_key_unittest_SOURCES = rsa_private_key_unittest.cc
rsa_private_key_unittest_LDADD = $(top_srcdir)/src/testing/gtest/lib/libgtest.la
rsa_private_key_unittest_LDADD += $(top_srcdir)/src/testing/gtest/lib/libgtest_main.la
rsa_private_key_unittest_LDADD += librsa_private_key.la
