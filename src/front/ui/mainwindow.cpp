#include "mainwindow.h"

#include "openglgraphics.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
//  setlocale(LC_NUMERIC, "C");
  initConfig();
  QFileInfo file_info(ui->widget->filename);
  fileInfoFilling(file_info);
  ui->dotSize->setValue(ui->widget->dotSize);
  ui->lineWidthValue->setValue(ui->widget->lineWidth);
  ui->lineGapValue->setValue(ui->widget->gapSize);

  animation = new QMovie(":/new/prefix1/icons/cube_1.gif");
  animation->start();
}

MainWindow::~MainWindow() {
  animation->stop();
  delete animation;
  clearPicture(&ui->widget->object);
  delete ui;
}

void MainWindow::initConfig() {
  QString style = QString(
      "background-color: transparent; color: #FFFF00; border-style: solid; "
      "border-width: 1px; border-color: #005500; border-radius: 5px; ");
  ui->pushButton_3->setStyleSheet(style);
  style = QString(
      "background-color: transparent; color: #FFFF00; border-style: solid; "
      "border-width: 1px; border-color: #550000; border-radius: 5px; ");
  ui->pushButton_lineColor->setStyleSheet(style);
  ui->pushButton_dotColor->setStyleSheet(style);

  ui->scale_move->setRange(1, 9);
  ui->scale_move->setSingleStep(1);
  ui->scale_move->setValue(1);
}

void MainWindow::on_pushButton_3_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
  if (color.isValid()) {
    ui->widget->makeCurrent();
    ui->widget->backgroundColor = color;
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_openFile_clicked() {
  QString file = QFileDialog::getOpenFileName(this, "Выбрать файл для открытия",
                                              0, "Text Files (*.obj)");
  if (file.isEmpty()) {
    qDebug() << "Empty file";
  } else {
    ui->widget->filename = file;
    ui->widget->setFileName();
    QFileInfo file_info(file);
    fileInfoFilling(file_info);
  }
}

void MainWindow::on_minus_x_clicked() {
  double value = ui->x_rotate_value->value() * (-1);
  rotate_X(&ui->widget->object, value);
  ui->widget->update();
}

void MainWindow::on_plus_x_clicked() {
  double value = ui->x_rotate_value->value();
  rotate_X(&ui->widget->object, value);
  ui->widget->update();
}

void MainWindow::on_minus_y_clicked() {
  double value = ui->y_rotate_value->value() * (-1);
  rotate_Y(&ui->widget->object, value);
  ui->widget->update();
}

void MainWindow::on_plus_y_clicked() {
  double value = ui->y_rotate_value->value();
  rotate_Y(&ui->widget->object, value);
  ui->widget->update();
}

void MainWindow::on_minus_z_clicked() {
  double value = ui->z_rotate_value->value() * (-1);
  rotate_Z(&ui->widget->object, value);
  ui->widget->update();
}

void MainWindow::on_plus_z_clicked() {
  double value = ui->z_rotate_value->value();
  rotate_Z(&ui->widget->object, value);
  ui->widget->update();
}

void MainWindow::on_move_x_minus_clicked() {
  double value = ui->x_move_value->value() * (-1);
  move_X(&ui->widget->object, value);
  ui->widget->update();
}

void MainWindow::on_move_x_plus_clicked() {
  double value = ui->x_move_value->value();
  move_X(&ui->widget->object, value);
  ui->widget->update();
}

void MainWindow::on_move_y_minus_clicked() {
  double value = ui->y_move_value->value() * (-1);
  move_Y(&ui->widget->object, value);
  ui->widget->update();
}

void MainWindow::on_move_y_plus_clicked() {
  double value = ui->y_move_value->value();
  move_Y(&ui->widget->object, value);
  ui->widget->update();
}

void MainWindow::on_move_z_minus_clicked() {
  double value = ui->z_move_value->value() * (-1);
  move_Z(&ui->widget->object, value);
  ui->widget->update();
}

void MainWindow::on_move_z_plus_clicked() {
  double value = ui->z_move_value->value();
  move_Z(&ui->widget->object, value);
  ui->widget->update();
}

void MainWindow::on_scale_down_clicked() {
  double value = (10 - ui->scale_move->value()) / 10.0;
  scale(&ui->widget->object, value);
  ui->widget->update();
}

void MainWindow::on_scale_up_clicked() {
  double value = (10 - ui->scale_move->value()) / 10.0;
  scale(&ui->widget->object, 1.0 / value);
  ui->widget->update();
}

void MainWindow::on_perpective_mode_clicked() {
  if (ui->widget->perpectiveMode == false) {
    ui->widget->perpectiveMode = true;
    ui->widget->update();
  }
}

void MainWindow::on_paralel_mode_clicked() {
  if (ui->widget->perpectiveMode == true) {
    ui->widget->perpectiveMode = false;
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_lineColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
  if (color.isValid()) {
    ui->widget->lineColor = color;
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_6_clicked() {
  ui->widget->dashObj = false;
  ui->widget->lineObj = false;
  ui->widget->update();
}

void MainWindow::on_pushButton_5_clicked() {
  if (ui->widget->lineObj == false) {
    ui->widget->lineObj = true;
    ui->widget->dashObj = false;
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_4_clicked() {
  if (ui->widget->dashObj == false) {
    ui->widget->dashObj = true;
    ui->widget->lineObj = false;
    ui->widget->update();
  }
}

void MainWindow::on_pushButtonWidth_clicked() {
  ui->widget->lineWidth = ui->lineWidthValue->value();
  ui->widget->update();
}

void MainWindow::on_pushButton_noDot_clicked() {
  ui->widget->dotObj = false;
  ui->widget->squareObj = false;
  ui->widget->update();
}

void MainWindow::on_pushButton_dot_clicked() {
  if (ui->widget->dotObj == false) {
    ui->widget->dotObj = true;
    ui->widget->squareObj = false;
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_dotSquare_clicked() {
  if (ui->widget->squareObj == false) {
    ui->widget->squareObj = true;
    ui->widget->dotObj = false;
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_dotColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
  if (color.isValid()) {
    ui->widget->dotColor = color;
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_dotSize_clicked() {
  ui->widget->dotSize = ui->dotSize->value();
  ui->widget->update();
}

void MainWindow::on_pushButton_bmpSave_clicked() {
  QString filePath = QFileDialog::getSaveFileName(nullptr, "Save Screenshot",
                                                  "", "BMP Files (*.bmp)");
  QPixmap screenshot(ui->widget->size());
  ui->widget->render(&screenshot);
  screenshot.save(filePath, "BMP");
}

void MainWindow::on_pushButton_takeJpeg_clicked() {
  QString filePath = QFileDialog::getSaveFileName(nullptr, "Save Screenshot",
                                                  "", "JPEG Files (*.jpeg)");
  QPixmap screenshot(ui->widget->size());
  ui->widget->render(&screenshot);
  screenshot.save(filePath, "JPEG");
}

void MainWindow::fileInfoFilling(QFileInfo file_info) {
  QString filename = file_info.fileName();
  QString filepath = file_info.absolutePath();
  QString filesize = QString::number(file_info.size() / 1000.0);
  QString v_count = QString::number(ui->widget->object.vertex_count);
  QString f_count = QString::number(ui->widget->object.facets_count);
  QString e_count = QString::number(edgesCounting());
  ui->textEdit->setText(
      "filename: " + filename + "\nfilepath: " + filepath +
      "/\n\nfilesize: " + filesize + " kb\n\nvertices count: " + v_count +
      "\nedges count: " + e_count + "\nfacets count: " + f_count);
}

int MainWindow::edgesCounting() {
  int edges_count = 0;
  for (int i = 0; i < ui->widget->object.facets_count; i++) {
//    edges_count += ui->widget->object.facets->facet_vertices_count;
  }
  return edges_count;
}

void MainWindow::startTimer() {
  gif = new QGifImage(QSize(640, 480));
  timerGIF = new QTimer(this);
  connect(timerGIF, &QTimer::timeout, this, &MainWindow::recordGif);
  timerGIF->start(100);
  frame = 0;
}

void MainWindow::recordGif() {
  if (frame < 50) {
    const QRect rect(0, 0, 640, 480);
    QPixmap pixmap = ui->widget->grab(rect);
    QImage myImage = pixmap.toImage();
    frame++;
    gif->addFrame(myImage, 100);  // цифра это задержка
  } else {
    timerGIF->stop();
    gif->save(pFile);
    pFile->close();
    delete pFile;
    delete gif;
    QMessageBox::about(this, "status", "GIF saved");
  }
}

void MainWindow::on_pushButton_save_gif_clicked() {
  QString filename = QFileDialog::getSaveFileName(this, "Сохранить GIF",
                                                  QDir::homePath(), "*.gif");
  pFile = new QFile(filename);
  if (pFile->open(QIODevice::WriteOnly)) {
    startTimer();
  } else {
    qDebug() << "Error occured";
  }
}
