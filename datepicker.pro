TEMPLATE = subdirs

SUBDIRS = library \
          test

library.subdir = datepicker_library
test.subdir = datepicker_test

test.depends = library