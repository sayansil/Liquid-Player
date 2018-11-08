#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMediaPlayer>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("Load music...");
    mLiquidPlayer = new QMediaPlayer(this);

    connect(mLiquidPlayer, &QMediaPlayer::positionChanged, [&](qint64 pos){
        ui->progressBar->setValue(pos);
    });

    connect(mLiquidPlayer, &QMediaPlayer::durationChanged, [&](qint64 dur){
       ui->progressBar->setMaximum(dur);
    });
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_playButton_clicked()
{
    mLiquidPlayer->play();
    if(!(ui->statusBar->currentMessage() == "Load music..."))
        ui->statusBar->showMessage("Playing...");
}

void MainWindow::on_pauseButton_clicked()
{
    mLiquidPlayer->pause();
    if(!(ui->statusBar->currentMessage() == "Load music..."))
        ui->statusBar->showMessage("Paused.");
}

void MainWindow::on_stopButton_clicked()
{
    mLiquidPlayer->stop();
    if(!(ui->statusBar->currentMessage() == "Load music..."))
        ui->statusBar->showMessage("Stopped.");
}

void MainWindow::on_loadButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Load music file");
    if(!filename.isEmpty()){
        mLiquidPlayer->setMedia(QUrl::fromLocalFile(filename));
        mLiquidPlayer->setVolume(ui->dial->value());
        ui->SongName->setText(filename.mid(filename.lastIndexOf("/")+1));
        ui->statusBar->showMessage("");
        on_playButton_clicked();
    }
}

void MainWindow::on_dial_valueChanged(int value)
{
    mLiquidPlayer->setVolume(value);
}
