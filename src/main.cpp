#include "mainwindow.h"

#include <QApplication>
#include <QSurfaceFormat>
#include <QScreen>

int main(int argc, char *argv[])
{
    // Setting up the application
    QApplication a(argc, argv);

    QCoreApplication::setApplicationName("Crystal Generation via L-Systems");
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    // Format for QSurface (a renderable surface in Qt)
    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
    fmt.setVersion(4, 1);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(fmt);

    // Create a main window. See mainwindow.h/cpp for details. Contains a GLWidget (see glwidget.h/cpp for details)
    MainWindow w;
    w.setupUI();
    w.resize(650, 400);
    w.setWindowTitle(QStringLiteral("W Systems: Crystal Generation via L-Systems"));
    int desktopArea = QGuiApplication::primaryScreen()->size().width() *
                      QGuiApplication::primaryScreen()->size().height();
    int widgetArea = w.width() * w.height();
    if (((float)widgetArea / (float)desktopArea) < 0.75f) {
        w.show();
    } else {
        w.showMaximized();
    }

    return a.exec();
}
