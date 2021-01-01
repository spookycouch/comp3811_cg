#ifndef __GL_POLYGON_WINDOW_H__
#define __GL_POLYGON_WINDOW_H__ 1

#include <QGLWidget>
#include <QMenuBar>
#include <QBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QComboBox>
#include <QCheckBox>
#include <QTimer>
#include "SceneWidget.h"

class MainWindow: public QWidget {
    public:
    MainWindow(QWidget *parent);
    ~MainWindow();

    QMenuBar* menu_bar_;
    QMenu* file_menu_;
    QAction* action_quit_;

    QHBoxLayout* window_layout_;
    SceneWidget* scene_widget_;

    QVBoxLayout* user_layout_;
    QLabel* light_bulb_amp_label;
    QSlider* light_bulb_amp_slider;
    QLabel* light_bulb_period_label;
    QSlider* light_bulb_period_slider;
    QLabel* background_speed_label;
    QSlider* background_speed_slider;
    QLabel* background_tex_label;
    QComboBox* background_tex_combobox;
    QLabel* rocking_chair_speed_label;
    QSlider* rocking_chair_speed_slider;
    QLabel* head_vibrate_speed_label;
    QSlider* head_vibrate_speed_slider;
    QCheckBox* proof_of_orbit_checkbox;

    QTimer* timer;
};

#endif