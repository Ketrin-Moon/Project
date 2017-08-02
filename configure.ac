#                                       -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

#AC_PREREQ([2.69])
AC_INIT([src/client.c])

#AC_CONFIG_SRCDIR([src/client.c], [lib/hash.c])
#AC_CONFIG_HEADERS([header.h])

# Checks for programs.
AC_PROG_CC 

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netdb.h netinet/in.h stdlib.h string.h sys/ioctl.h sys/socket.h unistd.h])

# Checks for library functions.
#AC_FUNC_FORK
AC_CHECK_FUNCS([bzero memset socket])
#AC_CONFIG_FILES([Makefile])
AM_INIT_AUTOMAKE([Makefile], [0.1])

AC_OUTPUT([Makefile src/Makefile]) 
