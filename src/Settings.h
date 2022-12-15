#pragma once

// Enumeration values for the Shapes that the user can select in the GUI.
enum ShapeType {
  SHAPE_TRIANGLE,
  SHAPE_CUBE,
  SHAPE_CONE,
  SHAPE_SPHERE,
  SHAPE_CYLINDER
};

struct Settings {
  int shapeType;
  int shapeParameter1 = 1;
  int shapeParameter2 = 1;
  int shapeParameter3 = 1;
  int shapeParameter4 = 1;
  bool useHex = false;
  bool showWireframeNormals = true;
};

// The global Settings object, will be initialized by MainWindow
extern Settings settings;
