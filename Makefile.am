AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = alarm
alarm_SOURCES = \
		src/main.c

PKG_CHECK_MODULES(SQLITE, sqlite3S)
alarm_CPPFLAGS = $(SQLITE_CFLAGS)
alarm_LDFLAGS = $(SQLITE_LIBS)