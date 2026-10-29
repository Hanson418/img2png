#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    /* QSettings is a silent no-op without an organisation name, which is
     * what used to make the language/theme choice forget itself. */
    app.setOrganizationName("Hanson418");
    app.setApplicationName("img2png");
    MainWindow win;
    win.show();
    return app.exec();
}
