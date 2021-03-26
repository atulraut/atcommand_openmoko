TARGET = amc

OM=/home/atul/moko
TOP_DIR=src/.
AT_DIR=src/at
LOG_DIR=src/log
UI_DIR=src/ui
DATA_DIR=src/data

CC = $(OM)/build/tmp/cross/arm-angstrom-linux-gnueabi/bin/gcc
CFLAGS = -I$(TOP_DIR)
LDFLAGS = -L$(OM)/build/tmp/staging/arm-angstrom-linux-gnueabi/lib -Wl,-rpath-link,$(OM)/build/tmp/staging/arm-angstrom-linux-gnueabi/lib -Wl,-O1 -g -o

SRC =	src/main.c \
	$(AT_DIR)/pin.c \
	$(AT_DIR)/atcmd.c \
	$(UI_DIR)/interface.c \
	$(UI_DIR)/callbacks.c \
	$(UI_DIR)/support.c \
	$(LOG_DIR)/log.c \
	$(AT_DIR)/linked-list.c 	

PKG = `$(OM)/build/tmp/staging/i686-linux/bin/pkg-config --cflags --libs libmokoui2 libgsmd`

all:
	${CC} ${CFLAGS} ${LDFLAGS} $(TARGET) $(SRC) $(PKG)

send:
	scp $(TARGET) root@neo:/home/root

clean:
	rm -f *~ $(TOP_DIR)/*~ $(AT_DIR)/*~ $(UI_DIR)/*~ $(LOG_DIR)/*~ $(TARGET)
