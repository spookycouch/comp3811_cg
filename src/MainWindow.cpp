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
    scene_widget_ = new SceneWidget();
    scene_widget_->setMinimumSize(400,400);
    scene_widget_->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
    window_layout_->addWidget(scene_widget_, 2);


    /** Create user interactivity items
     *
     */
    QVBoxLayout * user_layout_ = new QVBoxLayout();

    // light bulb amplitude
    light_bulb_amp_label = new QLabel("Light bulb amplitude:");
    light_bulb_amp_slider = new QSlider(Qt::Horizontal);
    light_bulb_amp_slider->setRange(0,85);
    // connect(light_bulb_amp_slider, SIGNAL(sliderMoved(int)), scene_widget_, SLOT(set_light_bulb_amplitude(int)));
    connect(light_bulb_amp_slider, &QSlider::valueChanged, scene_widget_, &SceneWidget::set_light_bulb_amplitude);

    // light bulb period
    light_bulb_period_label = new QLabel("Light bulb period:");
    light_bulb_period_slider = new QSlider(Qt::Horizontal);
    light_bulb_period_slider->setRange(10,30);
    // connect(light_bulb_period_slider, SIGNAL(sliderMoved(int)), scene_widget_, SLOT(set_light_bulb_period(int)));
    connect(light_bulb_period_slider, &QSlider::valueChanged, scene_widget_, &SceneWidget::set_light_bulb_period);

    // background_texture
    background_tex_label = new QLabel("Background texture:");
    background_tex_combobox = new QComboBox();
    background_tex_combobox->addItem("Dark woods");
    background_tex_combobox->addItem("Marc de Kamps");
    background_tex_combobox->addItem("Mercator projection");
    connect(background_tex_combobox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), scene_widget_, &SceneWidget::set_background_index);

    // background speed
    background_speed_label = new QLabel("Background speed:");
    background_speed_slider = new QSlider(Qt::Horizontal);
    background_speed_slider->setRange(-6,6);
    connect(background_speed_slider, &QSlider::valueChanged, scene_widget_, &SceneWidget::set_background_speed);

    // rocking chair period
    rocking_chair_speed_label = new QLabel("Rocking chair speed:");
    rocking_chair_speed_slider = new QSlider(Qt::Horizontal);
    rocking_chair_speed_slider->setRange(0,30);
    connect(rocking_chair_speed_slider, &QSlider::valueChanged, scene_widget_, &SceneWidget::set_rocking_chair_speed);

    // head vibrate speed
    head_vibrate_speed_label = new QLabel("Head vibrate speed:");
    head_vibrate_speed_slider = new QSlider(Qt::Horizontal);
    head_vibrate_speed_slider->setRange(0,10);
    connect(head_vibrate_speed_slider, &QSlider::valueChanged, scene_widget_, &SceneWidget::set_head_vibrate_speed);

    // proof of orbit
    proof_of_orbit_checkbox = new QCheckBox("Proof of orbit");
    connect(proof_of_orbit_checkbox, &QCheckBox::stateChanged, scene_widget_, &SceneWidget::set_proof_of_orbit);

    // reset button
    reset_button = new QPushButton("Reset");
    connect(this, &MainWindow::reset_geometry, scene_widget_, &SceneWidget::reset_geometry);
    connect(reset_button, &QPushButton::released, this, &MainWindow::reset);

    // build user menu
    user_layout_->addWidget(light_bulb_amp_label);
    user_layout_->addWidget(light_bulb_amp_slider);
    user_layout_->addWidget(light_bulb_period_label);
    user_layout_->addWidget(light_bulb_period_slider);
    user_layout_->addWidget(background_tex_label);
    user_layout_->addWidget(background_tex_combobox);
    user_layout_->addWidget(background_speed_label);
    user_layout_->addWidget(background_speed_slider);
    user_layout_->addWidget(rocking_chair_speed_label);
    user_layout_->addWidget(rocking_chair_speed_slider);
    user_layout_->addWidget(head_vibrate_speed_label);
    user_layout_->addWidget(head_vibrate_speed_slider);
    user_layout_->addWidget(proof_of_orbit_checkbox);
    user_layout_->addWidget(reset_button);
    user_layout_->addStretch(1);
    window_layout_->addLayout(user_layout_, 1);

    // reset widgets and scene to default state
    reset();

    // timer for frame update
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene_widget_, SLOT(update()));
    timer->start(10); // aim for 100fps haha
}

MainWindow::~MainWindow(){}

void MainWindow::reset() {
    light_bulb_amp_slider->setValue(60);
    light_bulb_period_slider->setValue(20);
    background_tex_combobox->setCurrentIndex(0);
    background_speed_slider->setValue(2);
    rocking_chair_speed_slider->setValue(15);
    head_vibrate_speed_slider->setValue(6);
    proof_of_orbit_checkbox->setChecked(0);
    reset_geometry();
}