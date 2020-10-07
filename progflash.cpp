#include "progflash.h"
#include "ui_progflash.h"
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>


ProgFlash::ProgFlash(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::ProgFlash) {
  ui->setupUi(this);
  ui->setInterface->addItem("jtag3",QVariant(QString("jtag3")));
  ui->setInterface->addItem("jtag1",QVariant(QString("jtag1")));
  ui->setMCU->addItem("m644p",QVariant(QString("m644p")));
  ui->setMCU->addItem("m32",QVariant(QString("m32")));
  ui->setPresetFuse->addItem("0xCF,0xB9,0xFD",
                             QVariant(QString("0xCF,0xB9,0xFD")));
}

ProgFlash::~ProgFlash() {
  delete ui;
}

//avrdude -p m128 -u -U flash:w:diag.hex -U eeprom:w:eeprom.hex -U efuse:w:0xff:m -U hfuse:w:0x89:m -U lfuse:w:0x2e:m

void ProgFlash::on_buttonProgram_clicked() {

  programmer = ui->setInterface->itemData(
                 ui->setInterface->currentIndex()).toString();
  MCU = ui->setMCU->itemData(
          ui->setMCU->currentIndex()).toString();

  QString buffer;
  buffer = ui->setPresetFuse->itemData(
             ui->setPresetFuse->currentIndex()).toString();

  QStringList pieces = buffer.split(",");
  fuseE = pieces.value(pieces.length() - 1);
  fuseH = pieces.value(pieces.length() - 2);
  fuseL = pieces.value(pieces.length() - 3);

  command = QString("avrdude -p ") + MCU +
            QString(" -c ") + programmer +
            QString(" -u -U flash:w:") + pathFile +
            QString(" -U efuse:w:") + fuseE + QString(":m") +
            QString(" -U hfuse:w:") + fuseH + QString(":m") +
            QString(" -U lfuse:w:") + fuseL + QString(":m") +
            QString(" -l logfile.txt");

  ui->console->setText(command);
  system(command.toStdString().data());

  QString out = buffer;
  char b;
  FILE *log;
  buffer.clear();
  log = fopen("logfile.txt","r");
  while ((b = getc(log)) != EOF) {
    buffer.push_back(QChar(b));
  }
  ui->console->setText(buffer);
}

void ProgFlash::on_buttonOpenFile_clicked() {
  pathFile = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("*"));
  ui->showOpenFile->setText(pathFile);
}
