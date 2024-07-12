#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QMovie>
#include <QPalette>
#include <QTimer>

#include "openglgraphics.h"
#include "src/3rdParty/giflib/gif_lib.h"
#include "src/gifimage/qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
  QColor widgetColor = Qt::black;
 private slots:
  void on_pushButton_3_clicked();
  void on_pushButton_openFile_clicked();
  void on_minus_x_clicked();
  void on_plus_x_clicked();
  void on_minus_y_clicked();
  void on_plus_y_clicked();
  void on_minus_z_clicked();
  void on_plus_z_clicked();
  void on_move_x_minus_clicked();
  void on_move_x_plus_clicked();
  void on_move_y_minus_clicked();
  void on_move_y_plus_clicked();
  void on_move_z_minus_clicked();
  void on_move_z_plus_clicked();
  void on_scale_down_clicked();
  void on_scale_up_clicked();
  void on_perpective_mode_clicked();
  void on_paralel_mode_clicked();
  void on_pushButton_lineColor_clicked();
  void on_pushButton_6_clicked();
  void on_pushButton_5_clicked();
  void on_pushButton_4_clicked();
  void on_pushButtonWidth_clicked();
  void on_pushButton_noDot_clicked();
  void on_pushButton_dot_clicked();
  void on_pushButton_dotSquare_clicked();
  void on_pushButton_dotColor_clicked();
  void on_pushButton_dotSize_clicked();
  void on_pushButton_bmpSave_clicked();
  void on_pushButton_takeJpeg_clicked();
  void on_pushButton_save_gif_clicked();
  void fileInfoFilling(QFileInfo file_info);
  int edgesCounting();
  void startTimer();
  void recordGif();

 private:
  Ui::MainWindow* ui;
  void initConfig();
  QTimer timerUi;
  QTimer* timerGIF;
  int frame;
  QGifImage* gif;
  QFile* pFile;
  QMovie* animation;
};
#endif  // MAINWINDOW_H
/// https://youtu.be/W3-SMvMa8D4
