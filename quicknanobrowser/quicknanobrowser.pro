requires(contains(QT_CONFIG, accessibility))

TEMPLATE = app
TARGET = quicknanobrowser

#QT       += core
#QT       += network
#CONFIG   += debug
#CONFIG   += console

#HEADERS = utils.h
SOURCES = main.cpp

#OTHER_FILES += ApplicationRoot.qml \
#               BrowserDialog.qml \
#               BrowserWindow.qml \
#               DownloadView.qml \
#               FullScreenNotification.qml
#
#RESOURCES += resources.qrc
#
QT += webenginewidgets

qtHaveModule(widgets) {
    QT += widgets # QApplication is required to get native styling with QtQuickControls
}

target.path = $$[QT_INSTALL_EXAMPLES]/webengine/quicknanobrowser
INSTALLS += target
