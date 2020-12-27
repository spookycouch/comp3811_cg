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


    /** Create user interactivity items
     *
     */
    QVBoxLayout * user_layout_ = new QVBoxLayout();

    // light bulb amplitude
    light_bulb_amp_label = new QLabel("Light bulb amplitude:");
    light_bulb_amp_slider = new QSlider(Qt::Horizontal);
    light_bulb_amp_slider->setValue(60);
    light_bulb_amp_slider->setRange(0,85);
    // connect(light_bulb_amp_slider, SIGNAL(sliderMoved(int)), scene_widget_, SLOT(set_light_bulb_amplitude(int)));
    connect(light_bulb_amp_slider, &QSlider::sliderMoved, scene_widget_, &SceneWidget::set_light_bulb_amplitude);

    // light bulb period
    light_bulb_period_label = new QLabel("Light bulb period:");
    light_bulb_period_slider = new QSlider(Qt::Horizontal);
    light_bulb_period_slider->setRange(10,30);
    light_bulb_period_slider->setValue(20);
    // connect(light_bulb_period_slider, SIGNAL(sliderMoved(int)), scene_widget_, SLOT(set_light_bulb_period(int)));
    connect(light_bulb_period_slider, &QSlider::sliderMoved, scene_widget_, &SceneWidget::set_light_bulb_period);

    // background_texture
    background_tex_label = new QLabel("Background texture:");
    background_tex_combobox = new QComboBox();
    background_tex_combobox->addItem("Marc de Kamps");
    background_tex_combobox->addItem("Mercator");
    connect(background_tex_combobox, QOverload<int>::of(&QComboBox::currentIndexChanged), scene_widget_, &SceneWidget::set_background_index);

    // background speed
    background_speed_label = new QLabel("Background speed:");
    background_speed_slider = new QSlider(Qt::Horizontal);
    background_speed_slider->setRange(-6,6);
    background_speed_slider->setValue(2);
    connect(background_speed_slider, &QSlider::sliderMoved, scene_widget_, &SceneWidget::set_background_speed);

    // build user menu
    user_layout_->addWidget(light_bulb_amp_label);
    user_layout_->addWidget(light_bulb_amp_slider);
    user_layout_->addWidget(light_bulb_period_label);
    user_layout_->addWidget(light_bulb_period_slider);
    user_layout_->addWidget(background_tex_label);
    user_layout_->addWidget(background_tex_combobox);
    user_layout_->addWidget(background_speed_label);
    user_layout_->addWidget(background_speed_slider);
    user_layout_->addStretch(1);
    window_layout_->addLayout(user_layout_);

    // timer for frame update
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene_widget_, SLOT(update()));
    timer->start(10); // aim for 100fps haha
}

MainWindow::~MainWindow(){}