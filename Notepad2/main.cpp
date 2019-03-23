#include "notepad.h"
#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>
#include <QThread>
#include <QDateTime>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Notepad window;

    //window.resize(600, 500);
    //window.move(250, 150);
    window.setWindowTitle("Notepad Exmaple");
    window.show();

    return app.exec();
}
