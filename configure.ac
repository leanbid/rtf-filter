#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])
AC_INIT([rtf-filter], [2.10], [simon@pscomputer.co.uk])
AC_CONFIG_SRCDIR([src/rtf.cpp])
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_REQUIRE_CPP
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LN_S

# Checks for libraries.

# Checks for header files.
AC_LANG_PUSH([C++])
AC_CHECK_HEADERS( [boost/program_options.hpp], echo "Boost program_options library headers found.", echo "Boost program_options library headers not found. As root use: aptitude install libboost-program-options-dev."; exit  )
AC_CHECK_HEADERS(  [boost/filesystem/operations.hpp] [boost/filesystem/fstream.hpp] [boost/filesystem/exception.hpp] [boost/filesystem/convenience.hpp], echo "Boost Filesystem headers found.", echo "Boost Filesystem library headers not found. As root use: aptitude install libboost-filesystem-dev."; exit  )
AC_LANG_POP([C++])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

# Checks for library functions.

AC_CONFIG_FILES([Makefile] [src/Makefile])
AC_OUTPUT


