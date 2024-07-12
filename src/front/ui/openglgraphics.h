#ifndef OPENGLGRAPHICS_H
#define OPENGLGRAPHICS_H

#define GL_SILENCE_DEPRECATION
#include <QFile>
#include <QFileDialog>
// #include <QJsonDocument>
// #include <QJsonObject>
// #include <QMatrix4x4>
// #include <QMouseEvent>
// #include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QtOpenGL>

extern "C" {
#include "../../backend/s21_affine.h"
#include "../../backend/s21_parser.h"
#include "../../backend/s21_viewer.h"
}

#define RGB_MIN 1
#define RGB_MAX 255

class openGLGraphics : public QOpenGLWidget /*, public QOpenGLFunctions*/ {
 public:
  openGLGraphics(QWidget *parent);
  ~openGLGraphics();

  QColor backgroundColor;
  QString filename;
  bool perpectiveMode;
  QColor lineColor, dotColor;
  bool dotObj, squareObj;
  bool lineObj, dashObj;
  float lineWidth;
  float dotSize;
  float gapSize;

  QJsonObject configObject;
  Picture object = {NULL,     NULL,     -INFINITY, -INFINITY, -INFINITY,
                    INFINITY, INFINITY, INFINITY,  0,         0,
                    0,        0,        0,         0};
  float xRot, yRot, zRot;

 public slots:
  void setFileName();
  void normalizeObject();
  void changeBack();
  void changeViewMode();
  void writeToJsonFile();
  void readFromJsonFile();
  void initialSettings();
  void loadConfigSettings();
  void saveConfigSettings();

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private slots:
  void qColorToRGB(const QColor &color, float &r, float &g, float &b) const;
  float normalizeColorValue(float val, float min, float max) const;
  void drawObj();
};

#endif  // OPENGLGRAPHICS_H
