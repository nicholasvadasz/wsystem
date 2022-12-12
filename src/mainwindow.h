#pragma once

#include <QCheckBox>
#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QSlider>
#include <QSpinBox>

#include "glwidget.h"

class MainWindow : public QWidget {
  Q_OBJECT

public:
  void setupUI();
  ~MainWindow();

private:
  GLWidget *glWidget;

  QSlider *p1Slider;
  QSlider *p2Slider;
  QSpinBox *p1Box;
  QSpinBox *p2Box;

  QSlider *p3Slider;
  QSlider *p4Slider;
  QSpinBox *p3Box;
  QSpinBox *p4Box;

  QPushButton *exportObj;

  QCheckBox *showWireframeNormals;

  QRadioButton *triangleCB;
  QRadioButton *cubeCB;
  QRadioButton *sphereCB;
  QRadioButton *cylinderCB;
  QRadioButton *coneCB;

  QRadioButton *pointCB;
  QRadioButton *bool1CB;
  QRadioButton *bool2CB;

  void connectParam1();
  void connectParam2();
  ;
  void connectWireframeNormals();

  void connectTriangle();
  void connectCube();
  void connectSphere();
  void connectCylinder();
  void connectCone();
  void connectExportObj();


private slots:
  void onValChangeP1(int newValue);
  void onValChangeP2(int newValue);
  void onWireframeNormalsChange();
  void onExportObj();

};
