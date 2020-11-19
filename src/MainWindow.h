#ifndef __GL_POLYGON_WINDOW_H__
#define __GL_POLYGON_WINDOW_H__ 1

#include <QGLWidget>
#include <QMenuBar>
#include <QBoxLayout>
#include "SceneWidget.h"

class MainWindow: public QWidget {
    public:
    MainWindow(QWidget *parent);
    ~MainWindow();

    // menu bar members
    QMenuBar *menu_bar_;
    QMenu *file_menu_;
    QAction *action_quit_;
    QBoxLayout *window_layout_;

    // the scene widget
    SceneWidget *scene_widget_;
};

#endif