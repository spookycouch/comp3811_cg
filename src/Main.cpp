#include <QApplication>
#include <QVBoxLayout>
#include <GL/glut.h>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    // initialise glut
    glutInit(&argc, argv);

    // create the app and the master widget
    QApplication app(argc, argv);
    MainWindow *window = new MainWindow(NULL);
    
    // show the window and exec the QApplication
	window->resize(640, 480);
    window->show();
    app.exec();

    // delete and error code
    delete window;
    return 0;
}