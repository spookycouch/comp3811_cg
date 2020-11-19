#include "MainWindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
        : QWidget(parent) {
    
    // setup the menu bar
    menu_bar_ = new QMenuBar(this);
    file_menu_ = menu_bar_->addMenu("&File");
    action_quit_ = new QAction("&Quit", this);
    file_menu_->addAction(action_quit_);

    // create the window layout
    window_layout_ = new QBoxLayout(QBoxLayout::TopToBottom, this);

    // create the main widget
    scene_widget_ = new SceneWidget(this);
    window_layout_->addWidget(scene_widget_);

    // framerate targetting 10hz
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene_widget_, SLOT(update()));
    timer->start(10);
}

MainWindow::~MainWindow(){}