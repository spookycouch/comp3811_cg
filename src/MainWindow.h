#ifndef __GL_POLYGON_WINDOW_H__
#define __GL_POLYGON_WINDOW_H__ 1

#include <QGLWidget>
#include <QMenuBar>
#include <QBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QTimer>
#include "SceneWidget.h"

class MainWindow: public QWidget {
    public:
    MainWindow(QWidget *parent);
    ~MainWindow();

    QMenuBar *menu_bar_;
    QMenu *file_menu_;
    QAction *action_quit_;

    QHBoxLayout *window_layout_;
    SceneWidget *scene_widget_;

    QVBoxLayout *user_layout_;
    QLabel *light_bulb_amp_label;
    QSlider *light_bulb_amp_slider;
    QLabel *light_bulb_period_label;
    QSlider *light_bulb_period_slider;

    QTimer* timer;
};

#endif