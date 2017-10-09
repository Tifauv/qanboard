TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = core \
          test \
          app
test.depends = core
app.depends  = core

OTHER_FILES += sample.xml
