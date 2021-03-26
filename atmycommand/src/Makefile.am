## Process this file with automake to produce Makefile.in

## Created by Anjuta - will be overwritten
## If you don't want it to overwrite it,
## 	Please disable it in the Anjuta project configuration

atdir = at
logdir = log
uidir = ui
topdir = .

INCLUDES = \
	$(PACKAGE_CFLAGS) $(topdir)

AM_CFLAGS = \
	 -Wall\
	 -g\
	 -I$(topdir)

bin_PROGRAMS = atmycommand

atmycommand_SOURCES = \
	main.c \
	at/atcmd.c \
	at/linked-list.c \
	at/pin.c \
	log/log.c \
	ui/callbacks.c \
	ui/interface.c \
	ui/support.c

atmycommand_LDFLAGS = `${OMDIR}/build/tmp/staging/i686-linux/bin/pkg-config --cflags --libs libmokoui2 libgsmd`
# atmycommand_LDFLAGS = -L$(OM)/build/tmp/staging/arm-angstrom-linux-gnueabi/lib -Wl,-rpath-link,$(OM)/build/tmp/staging/arm-angstrom-linux-gnueabi/lib -Wl,-O1 -g -o

atmycommand_LDADD = \
	$(PACKAGE_LIBS)

