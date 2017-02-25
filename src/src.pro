requires(contains(QT_CONFIG, accessibility))

TEMPLATE = app
TARGET = qurlew

HEADERS = Qurlew.hpp StandardInput.hpp
SOURCES = Qurlew.cpp StandardInput.cpp main.cpp

QT += webenginewidgets

target.path = $$[QT_INSTALL_BINS]
INSTALLS += target
