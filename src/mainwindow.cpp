#include "mainwindow.h"
#include "Settings.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <iostream>

void MainWindow::setupUI() {
  // Create glWidget for OpenGL stuff
  glWidget = new GLWidget;
  glWidget->initializeShapesAndParameters();
  glWidget->setEnabled(
      true); // specifically allow handling of keyboard and mouse events

  /* Set up the layouts (parent-child diagram):
   *
   *                 hLayout
   *                 /     \
   *           vLayout      glWidget (canvas)
   *          |      \
   * labels,buttons   \
   *                   \
   *             p1Layout,p2Layout (sliders/spinboxes)
   *
   */
  QHBoxLayout *hLayout = new QHBoxLayout(); // horizontal alignment
  QVBoxLayout *vLayout = new QVBoxLayout(); // vertical alignment
  vLayout->setAlignment(Qt::AlignTop);
  hLayout->addLayout(vLayout);
  hLayout->addWidget(glWidget, 1);
  this->setLayout(hLayout);

  // Create labels in sidebox
  QFont font;
  font.setPointSize(16);
  font.setBold(true);
  QLabel *trimesh_label = new QLabel(); // Trimeshes label
  trimesh_label->setText("Crystal Generation via L-Systems");
  trimesh_label->setFont(font);
  QLabel *params_label = new QLabel(); // Parameters label
  params_label->setText("Parameters");
  params_label->setFont(font);
  QLabel *param1_label = new QLabel(); // Parameter 1 label
  param1_label->setText("Parameter 1:");
  QLabel *param2_label = new QLabel(); // Parameter 2 label
  param2_label->setText("Parameter 2:");
  QLabel *param3_label = new QLabel(); // Parameter 1 label
  param3_label->setText("Parameter 3:");
  QLabel *param4_label = new QLabel(); // Parameter 2 label
  param4_label->setText("Parameter 4:");
  QLabel *width_spacer =
      new QLabel(); // cheat-y way of adding more width to the QVBoxLayout
  width_spacer->setText("                                               ");
  width_spacer->setFont(font);

  exportObj = new QPushButton();
  exportObj->setText(QStringLiteral("Export to Obj"));

  // Create button controls to toggle 3D shapes
  pointCB = new QRadioButton(); // Point button
  pointCB->setText(QStringLiteral("Point"));
  pointCB->setChecked(false); // Default Point toggled

  bool1CB = new QRadioButton(); // Bool 1 button
  bool1CB->setText(QStringLiteral("Bool 1"));
  bool1CB->setChecked(false); // Default Bool 1 toggled

  bool2CB = new QRadioButton(); // Bool 2 button
  bool2CB->setText(QStringLiteral("Bool 2"));
  bool2CB->setChecked(false); // Default Bool 2 toggled

  // Create toggle for showing wireframe / normals
  showWireframeNormals = new QCheckBox();
  showWireframeNormals->setText(QStringLiteral("Show Wireframe and Normals"));
  showWireframeNormals->setChecked(true);

  // Creates the boxes containing the parameter sliders and number boxes
  QGroupBox *p1Layout = new QGroupBox(); // horizonal slider 1 alignment
  QHBoxLayout *l1 = new QHBoxLayout();
  QGroupBox *p2Layout = new QGroupBox(); // horizonal slider 2 alignment
  QHBoxLayout *l2 = new QHBoxLayout();
  QGroupBox *p3Layout = new QGroupBox(); // horizonal slider 2 alignment
  QHBoxLayout *l3 = new QHBoxLayout();
  QGroupBox *p4Layout = new QGroupBox(); // horizonal slider 2 alignment
  QHBoxLayout *l4 = new QHBoxLayout();

  // Create slider controls to control parameters
  p1Slider = new QSlider(Qt::Orientation::Horizontal); // Parameter 1 slider
  p1Slider->setTickInterval(1);
  p1Slider->setMinimum(1);
  p1Slider->setMaximum(50);
  p1Slider->setValue(1);

  p1Box = new QSpinBox();
  p1Box->setMinimum(1);
  p1Box->setMaximum(50);
  p1Box->setSingleStep(1);
  p1Box->setValue(1);
  p1Box->setFocusPolicy(Qt::NoFocus);

  p2Slider = new QSlider(Qt::Orientation::Horizontal); // Parameter 2 slider
  p2Slider->setTickInterval(1);
  p2Slider->setMinimum(1);
  p2Slider->setMaximum(50);
  p2Slider->setValue(1);

  p2Box = new QSpinBox();
  p2Box->setMinimum(1);
  p2Box->setMaximum(50);
  p2Box->setSingleStep(1);
  p2Box->setValue(1);
  p2Box->setFocusPolicy(Qt::NoFocus);

  p3Slider = new QSlider(Qt::Orientation::Horizontal); // Parameter 3 slider
  p3Slider->setTickInterval(1);
  p3Slider->setMinimum(1);
  p3Slider->setMaximum(50);
  p3Slider->setValue(1);

  p3Box = new QSpinBox();
  p3Box->setMinimum(1);
  p3Box->setMaximum(50);
  p3Box->setSingleStep(1);
  p3Box->setValue(1);
  p3Box->setFocusPolicy(Qt::NoFocus);

  p4Slider = new QSlider(Qt::Orientation::Horizontal); // Parameter 2 slider
  p4Slider->setTickInterval(1);
  p4Slider->setMinimum(1);
  p4Slider->setMaximum(50);
  p4Slider->setValue(1);

  p4Box = new QSpinBox();
  p4Box->setMinimum(1);
  p4Box->setMaximum(50);
  p4Box->setSingleStep(1);
  p4Box->setValue(1);
  p4Box->setFocusPolicy(Qt::NoFocus);

  // Adds the slider and number box to the parameter layouts
  l1->addWidget(p1Slider);
  l1->addWidget(p1Box);
  p1Layout->setLayout(l1);

  l2->addWidget(p2Slider);
  l2->addWidget(p2Box);
  p2Layout->setLayout(l2);

  l3->addWidget(p3Slider);
  l3->addWidget(p3Box);
  p3Layout->setLayout(l3);

  l4->addWidget(p4Slider);
  l4->addWidget(p4Box);
  p4Layout->setLayout(l4);

  // Add the labels and checkbox widgets to vLayout for vertical alignment
  // (order matters!)
  vLayout->addWidget(trimesh_label);
  vLayout->addWidget(pointCB);
  vLayout->addWidget(bool1CB);
  vLayout->addWidget(bool2CB);
  vLayout->addWidget(width_spacer);
  vLayout->addWidget(params_label);
  vLayout->addWidget(param1_label);
  vLayout->addWidget(p1Layout);
  vLayout->addWidget(param2_label);
  vLayout->addWidget(p2Layout);

  vLayout->addWidget(param3_label);
  vLayout->addWidget(p3Layout);

  vLayout->addWidget(param4_label);
  vLayout->addWidget(p4Layout);
  vLayout->addWidget(exportObj);
  vLayout->addWidget(showWireframeNormals);

  connectParam1();
  connectParam2();
  connectWireframeNormals();
}

//******************************** Handles Parameter 1 UI Changes
//********************************//
void MainWindow::connectParam1() {
  connect(p1Slider, &QSlider::valueChanged, this, &MainWindow::onValChangeP1);
  connect(p1Box, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          this, &MainWindow::onValChangeP1);
}

void MainWindow::onValChangeP1(int newValue) {
  p1Slider->setValue(newValue);
  p1Box->setValue(newValue);
  settings.shapeParameter1 = p1Slider->value();
  glWidget->settingsChange();
}

//******************************** Handles Parameter 2 UI Changes
//********************************//
void MainWindow::connectParam2() {
  connect(p2Slider, &QSlider::valueChanged, this, &MainWindow::onValChangeP2);
  connect(p2Box, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          this, &MainWindow::onValChangeP2);
}

void MainWindow::onValChangeP2(int newValue) {
  p2Slider->setValue(newValue);
  p2Box->setValue(newValue);
  settings.shapeParameter2 = p2Slider->value();
  glWidget->settingsChange();
}

//***************************** Handles Wireframe/Normals UI Changes
//*****************************//
void MainWindow::connectWireframeNormals() {
  connect(showWireframeNormals, &QCheckBox::clicked, this,
          &MainWindow::onWireframeNormalsChange);
}

void MainWindow::onWireframeNormalsChange() {
  settings.showWireframeNormals = !settings.showWireframeNormals;
  glWidget->settingsChange();
}

MainWindow::~MainWindow() {
  delete (glWidget);
  delete (p1Slider);
  delete (p1Box);
  delete (p2Box);
  delete (showWireframeNormals);
}
