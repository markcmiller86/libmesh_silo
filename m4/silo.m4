dnl -------------------------------------------------------------
dnl Silo file I/O API for reading Silo files, by Mark C. Miller
dnl -------------------------------------------------------------
AC_DEFUN([CONFIGURE_SILO],
[
  AC_ARG_ENABLE(silo,
                AC_HELP_STRING([--enable-silo],
                               [build with Silo file I/O support]),
		[case "${enableval}" in
		  yes)  enablesilo=yes ;;
		   no)  enablesilo=no ;;
 		    *)  AC_MSG_ERROR(bad value ${enableval} for --enable-silo) ;;
		 esac],
		 [enablesilo=$enableoptional])



  dnl The Silo API is distributed with libmesh, so we don't have to guess
  dnl where it might be installed...
  if (test x$enablesilo = xyes); then
     SILO_INCLUDE="-I\$(top_srcdir)/contrib/silo"
     SILO_LIBRARY="\$(EXTERNAL_LIBDIR)/libsilo\$(libext)"
     AC_DEFINE(HAVE_SILO, 1, [Flag indicating whether the library will be compiled with Silo support])
     AC_MSG_RESULT(<<< Configuring library with Silo support >>>)
  else
     SILO_INCLUDE=""
     SILO_LIBRARY=""
     enablesilo=no
  fi

  AC_SUBST(SILO_INCLUDE)
  AC_SUBST(SILO_LIBRARY)
])
