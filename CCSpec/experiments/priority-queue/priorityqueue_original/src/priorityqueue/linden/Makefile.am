EXTRA_DIST =

noinst_LTLIBRARIES = liblpq.la

liblpq_la_SOURCES = gc/gc.c\
					gc/ptst.c\
					common.c\
					prioq.c


liblpq_la_CFLAGS = -O3 -DINTEL -std=c99 $(WARN_FLAGS) \
				   -DCACHE_LINE_SIZE=`getconf LEVEL1_DCACHE_LINESIZE`
					  -I$(top_builddir)/src/priorityqueue/linden -I$(top_srcdir)/src/priorityqueue/linden
