#include <QApplication>
#include <QIcon>
#include <QLoggingCategory>
#include <cstdlib>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    // Suppress GStreamer device enumeration spam
    setenv("GST_DEBUG", "0", 0);
    setenv("PIPEWIRE_LOG_LEVEL", "0", 0);

    QLoggingCategory::setFilterRules(
        "qt.multimedia.*=false\n"
        "qt.core.qfuture.*=false\n");

    QApplication app(argc, argv);
    app.setApplicationName("TRYX Panorama Manager");
    app.setOrganizationName("DXVSI");
    app.setWindowIcon(QIcon(":/tryx-panorama.png"));
    app.setDesktopFileName("tryx-panorama-manager");

    MainWindow window;
    window.show();

    return app.exec();
}
