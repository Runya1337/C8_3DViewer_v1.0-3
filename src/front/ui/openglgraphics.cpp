#include "openglgraphics.h"

openGLGraphics::openGLGraphics(QWidget *parent) : QOpenGLWidget(parent) {
  setWindowTitle("viv");
  clearPicture(&object);

  QString projectPath = QCoreApplication::applicationDirPath();
  if (QFile::exists(projectPath + "/config.json")) {
    qDebug() << "file is working";
    readFromJsonFile();
    loadConfigSettings();
  } else {
    initialSettings();
  }
  setFileName();
}

void openGLGraphics::writeToJsonFile() {
  QJsonDocument jsonDoc(configObject);
  QString projectPath = QCoreApplication::applicationDirPath();
  QFile file(projectPath + "/config.json");
  file.open(QIODevice::WriteOnly | QIODevice::Truncate);
  file.write(jsonDoc.toJson());
  file.close();
}

void openGLGraphics::readFromJsonFile() {
  QString projectPath = QCoreApplication::applicationDirPath();
  QFile configFile(projectPath + "/config.json");
  configFile.open(QIODevice::ReadOnly);
  QByteArray configData = configFile.readAll();
  QJsonParseError parseError;
  QJsonDocument jsonDoc = QJsonDocument::fromJson(configData, &parseError);
  qDebug().noquote() << jsonDoc.toJson(QJsonDocument::Indented);
  configObject = jsonDoc.object();
  configFile.close();
}

void openGLGraphics::loadConfigSettings() {
  backgroundColor = configObject["backgroundColor"].toString();
  filename = configObject["filename"].toString();
  perpectiveMode = configObject["perpectiveMode"].toBool();
  lineColor = configObject["lineColor"].toString();
  dotColor = configObject["dotColor"].toString();
  dotObj = configObject["dotObj"].toBool();
  lineObj = configObject["lineObj"].toBool();
  squareObj = configObject["squareObj"].toBool();
  dashObj = configObject["dashObj"].toBool();
  lineWidth = static_cast<float>(configObject["lineWidth"].toDouble());
  dotSize = static_cast<float>(configObject["dotSize"].toDouble());
  gapSize = static_cast<float>(configObject["gapSize"].toDouble());
}
void openGLGraphics::saveConfigSettings() {
  configObject["backgroundColor"] = backgroundColor.name(QColor::HexArgb);
  configObject["filename"] = filename;
  configObject["perpectiveMode"] = perpectiveMode;
  configObject["lineColor"] = lineColor.name(QColor::HexArgb);
  configObject["dotColor"] = dotColor.name(QColor::HexArgb);
  configObject["dotObj"] = dotObj;
  configObject["lineObj"] = lineObj;
  configObject["squareObj"] = squareObj;
  configObject["dashObj"] = dashObj;
  configObject["lineWidth"] = lineWidth;
  configObject["dotSize"] = dotSize;
  configObject["gapSize"] = gapSize;
}

void openGLGraphics::initialSettings() {
  backgroundColor = Qt::black;
  filename = "";
  perpectiveMode = false;
  lineColor = Qt::white;
  dotColor = Qt::white;
  dotObj = true;
  lineObj = true;
  squareObj = false;
  dashObj = false;
  lineWidth = 1.0f;
  dotSize = 1.0f;
  gapSize = 1.0f;
}

openGLGraphics::~openGLGraphics() {
  saveConfigSettings();
  writeToJsonFile();
}

void openGLGraphics::initializeGL() {
  glEnable(GL_DEPTH_TEST);
}

void openGLGraphics::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void openGLGraphics::paintGL() {
  changeViewMode();
  changeBack();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  float far = fmax(fabs(object.max_z), fabs(object.min_z)) +
              fmax(fabs(object.max_y), fabs(object.min_y));
  if (far < 5) {
    far = 5;
  }
  glTranslated(0, 0, -far);
  drawObj();
}

void openGLGraphics::drawObj() {

  glVertexPointer(3, GL_DOUBLE, 0, object.vertexes);

  glEnableClientState(GL_VERTEX_ARRAY);

  float r, g, b;
  qColorToRGB(dotColor, r, g, b);
  glColor3f(r, g, b);

  glPointSize(dotSize);

  if (dotObj) {
    glEnable(GL_POINT_SMOOTH);
  }
  if (dotObj || squareObj) {
    glDrawArrays(GL_POINTS, 0, object.vertex_count);
  }

  glDisableClientState(GL_VERTEX_ARRAY);
  if (dotObj) {
    glDisable(GL_POINT_SMOOTH);
  }
  glEnableClientState(GL_VERTEX_ARRAY);

  glLineWidth(lineWidth);
  if (dashObj) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00ff);
  }

  qColorToRGB(lineColor, r, g, b);
  glColor3f(r, g, b);
  glDrawElements(GL_LINES, object.facets_index, GL_UNSIGNED_INT, object.facets);
  if (dashObj) {
    glDisable(GL_LINE_STIPPLE);
  }
  glDisableClientState(GL_VERTEX_ARRAY);
}

void openGLGraphics::qColorToRGB(const QColor &color, float &r, float &g,
                                 float &b) const {
  int red = color.red();
  int green = color.green();
  int blue = color.blue();
  r = normalizeColorValue(red, RGB_MIN, RGB_MAX);
  g = normalizeColorValue(green, RGB_MIN, RGB_MAX);
  b = normalizeColorValue(blue, RGB_MIN, RGB_MAX);
}

float openGLGraphics::normalizeColorValue(float val, float min,
                                          float max) const {
  return (val - min) / (max - min);
}

void openGLGraphics::changeBack() {
  float r, g, b, a = 1;
  qColorToRGB(backgroundColor, r, g, b);
  glClearColor(r, g, b, a);
}

void openGLGraphics::changeViewMode() {
  if (perpectiveMode == false) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, 1, 9999999);
    float value = 0.5 / object.max_y;
    glScalef(value, value, 1.0f);
  } else {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 9999999);
  }
}

void openGLGraphics::setFileName() {
  clearPicture(&object);
  qDebug() << filename;
  QByteArray ba = filename.toLocal8Bit();
  char *fname = ba.data();

  parserMain(fname, &object);
  if (object.status == SUCCESS) {
    normalizeObject();
    update();
  } else {
    clearPicture(&object);
  }
}

void openGLGraphics::normalizeObject() {
  double center_x = 0, center_y = 0, center_z = 0;
  for (int i = 0; i < object.vertex_index; i += 3) {
    center_x += object.vertexes[i];
    center_y += object.vertexes[i + 1];
    center_z += object.vertexes[i + 2];
  }
  center_x /= object.vertex_count;
  center_y /= object.vertex_count;
  center_z /= object.vertex_count;
  for (int i = 0; i < object.vertex_index; i += 3) {
    object.vertexes[i] -= center_x;
    object.vertexes[i + 1] -= center_y;
    object.vertexes[i + 2] -= center_z;
  }
  object.max_x -= center_x;
  object.min_x -= center_x;
  object.max_z -= center_z;
  object.min_z -= center_z;
  object.max_y -= center_y;
  object.min_y -= center_y;
}
