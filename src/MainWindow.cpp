#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QWidget(parent) {
    
    // setup the menu bar
    menu_bar_ = new QMenuBar(this);
    file_menu_ = menu_bar_->addMenu("&File");
    action_quit_ = new QAction("&Quit", this);
    file_menu_->addAction(action_quit_);

    // create the window layout
    window_layout_ = new QHBoxLayout(this);

    // create scene widget
    scene_widget_ = new SceneWidget(this);
    scene_widget_->setMinimumSize(400,400);
    scene_widget_->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
    window_layout_->addWidget(scene_widget_);

    // create user interactivity items
    QVBoxLayout * user_layout_ = new QVBoxLayout();
    light_bulb_amp_label = new QLabel("Light bulb amplitude:");
    light_bulb_amp_slider = new QSlider(Qt::Horizontal);
    light_bulb_period_label = new QLabel("Light bulb period:");
    light_bulb_period_slider = new QSlider(Qt::Horizontal);

    // build user menu
    user_layout_->addWidget(light_bulb_amp_label);
    user_layout_->addWidget(light_bulb_amp_slider);
    user_layout_->addWidget(light_bulb_period_label);
    user_layout_->addWidget(light_bulb_period_slider);
    user_layout_->addStretch(1);
    window_layout_->addLayout(user_layout_);

    // timer for frame update
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene_widget_, SLOT(update()));
    timer->start(10);
}

MainWindow::~MainWindow(){}