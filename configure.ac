dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(bijiben, 3.9.5)
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

dnl _FOR_DOC
AC_CONFIG_MACRO_DIR([m4])
dnl end of _FOR_DOC

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AC_CONFIG_HEADERS([config.h])
AM_MAINTAINER_MODE

AC_PROG_CC

GNOME_COMMON_INIT
GNOME_DOC_PREPARE


YELP_HELP_INIT


dnl ***************************************************************************
dnl Internatinalization
dnl ***************************************************************************
GETTEXT_PACKAGE=bijiben
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
AM_GLIB_GNU_GETTEXT
IT_PROG_INTLTOOL([0.35.0])

#
# Check if we should update the mime database
#

AC_PATH_PROG(UPDATE_MIME_DATABASE, update-mime-database, no)

AC_ARG_ENABLE(update-mimedb,
   AC_HELP_STRING([--disable-update-mimedb],
                   [disable the update-mime-database after install [default=no]]),,
    enable_update_mimedb=yes)
AM_CONDITIONAL(ENABLE_UPDATE_MIMEDB, (test x$enable_update_mimedb = xyes) && (test x$UPDATE_MIME_DATABASE != xno))



AM_PROG_LIBTOOL


GLIB_REQUIRED_VERSION=2.28
GTK_REQUIRED_VERSION=3.9.3


PKG_CHECK_MODULES(BIJIBEN,
                  [ clutter-gtk-1.0
                    gio-unix-2.0
                    glib-2.0 >= $GLIB_REQUIRED_VERSION
                    goa-1.0
                    gtk+-3.0 >= $GTK_REQUIRED_VERSION
                    libxml-2.0
                    tracker-sparql-0.16
                    uuid
                    webkitgtk-3.0
                    zeitgeist-2.0])



GLIB_GSETTINGS

LIBGD_INIT([
  view-common
  gtk-hacks
  main-view
  static
  tagged-entry
])

AC_CONFIG_FILES([
Makefile
libgd/Makefile
data/Makefile
data/bijiben.desktop.in
data/icons/Makefile
help/Makefile
po/Makefile.in
src/libbiji/Makefile
src/Makefile
])

AC_OUTPUT

echo "	Version:	$VERSION

	Run make to compile."


