if USE_WEBKITGTK
HTML_CFLAGS=`pkg-config --cflags webkit-1.0`
HTML_LIBS=`pkg-config --libs webkit-1.0`
endif

if USE_GTKHTML
HTML_CFLAGS=`pkg-config --cflags libgtkhtml-3.14`
HTML_LIBS=`pkg-config --libs libgtkhtml-3.14`
endif

sylpf_srcdir = $(top_srcdir)/../sylplugin_factory/src

lib_LTLIBRARIES = commit_reader.la

commit_reader_la_SOURCES = commit_reader.c \
        $(sylplugin_factory_source_dir)/src/sylplugin_factory.c \
        $(sylplugin_factory_source_dir)/src/sylplugin_factory.h

commit_reader_la_LDFLAGS = -module -no-undefined -avoid-version $(HTML_LIBS)

INCLUDES = \
	$(GTK_CFLAGS) \
	$(HTML_CFLAGS) \
	-I$(includedir) \
	-I$(sylpheed_build_dir) \
	-I$(sylpheed_build_dir)/libsylph \
	-I$(sylpheed_build_dir)/src \
	-I$(sylplugin_factory_source_dir)/src

commit_reader_la_LIBADD = \
	$(GTK_LIBS) \
	$(sylpheed_build_dir)/src/libsylpheed-plugin-0.la \
	$(sylpheed_build_dir)/libsylph/libsylph-0.la

install:
install-plugin: install-am
