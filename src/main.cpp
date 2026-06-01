#include <QApplication>
#include <QDir>
#include <QIcon>
#include <QLocalServer>
#include <QLocalSocket>
#include <QLoggingCategory>
#include <QStandardPaths>
#include <cstdlib>
#include "mainwindow.h"

namespace {
// Anchor the single-instance socket in the per-user runtime dir
// (XDG_RUNTIME_DIR) so its location does not depend on $TMPDIR, which can
// differ between the systemd service and a launcher/terminal start.
QString instanceSocketPath() {
    QString base =
        QStandardPaths::writableLocation(QStandardPaths::RuntimeLocation);
    if (base.isEmpty())
        base = QDir::tempPath();
    return base + "/tryx-panorama-manager.instance";
}
}

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

    // Single-instance guard: if another instance is already running, ask it to
    // raise its window and exit instead of spawning a second tray icon.
    const QString instancePath = instanceSocketPath();
    {
        QLocalSocket probe;
        probe.connectToServer(instancePath);
        if (probe.waitForConnected(300)) {
            probe.write("show");
            probe.flush();
            probe.waitForBytesWritten(300);
            return 0;
        }
    }

    // We are the primary instance. Remove any stale socket left by a crash,
    // then listen for future launches.
    QLocalServer::removeServer(instancePath);
    QLocalServer instanceServer;
    instanceServer.listen(instancePath);

    MainWindow window;
    window.show();

    QObject::connect(&instanceServer, &QLocalServer::newConnection, &window, [&]() {
        QLocalSocket *conn = instanceServer.nextPendingConnection();
        if (conn)
            conn->deleteLater();
        window.show();
        window.setWindowState((window.windowState() & ~Qt::WindowMinimized) |
                              Qt::WindowActive);
        window.raise();
        window.activateWindow();
    });

    return app.exec();
}
