#ifndef PROGFLASH_H
#define PROGFLASH_H

#include <QMainWindow>
#include <QFileDialog>

namespace Ui {
class ProgFlash;
}

class ProgFlash : public QMainWindow {
  Q_OBJECT

 public:
  explicit ProgFlash(QWidget *parent = nullptr);

  QString command;
  QString fuse;
  QString fuseE;
  QString fuseH;
  QString fuseL;
  QString MCU;
  QString programmer;
  QString pathFile;
  QFileDialog openFile;
  ~ProgFlash();

 private slots:
  void on_buttonProgram_clicked();

  void on_buttonOpenFile_clicked();

 private:
  Ui::ProgFlash *ui;
};

#endif // PROGFLASH_H
