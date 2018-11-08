#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMediaPlayer>
#include <QFileDialog>
#include <QDesktopServices>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(QSize(615, 200));

    ui->playButton->setIcon(QIcon(":/icons/resources/play.png"));
    ui->playButton->setIconSize(QSize(60, 60));
    ui->pauseButton->setIcon(QIcon(":/icons/resources/pause.png"));
    ui->pauseButton->setIconSize(QSize(60, 60));
    ui->stopButton->setIcon(QIcon(":/icons/resources/stop.png"));
    ui->stopButton->setIconSize(QSize(60, 60));

    ui->statusBar->showMessage("Load music to start playing...");
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
    if(!(ui->statusBar->currentMessage() == "Load music to start playing..."))
        ui->statusBar->showMessage("Playing...");
}

void MainWindow::on_pauseButton_clicked()
{
    mLiquidPlayer->pause();
    if(!(ui->statusBar->currentMessage() == "Load music to start playing..."))
        ui->statusBar->showMessage("Paused.");
}

void MainWindow::on_stopButton_clicked()
{
    mLiquidPlayer->stop();
    if(!(ui->statusBar->currentMessage() == "Load music to start playing..."))
        ui->statusBar->showMessage("Stopped.");
}

void MainWindow::on_dial_valueChanged(int value)
{
    mLiquidPlayer->setVolume(value);
}

void MainWindow::on_actionNew_File_triggered()
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

void MainWindow::on_actionSenpai_triggered()
{
    QString link = "https://github.com/sayansil";
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_actionR_M_G_triggered()
{
    QString link = "https://github.com/DarkStar1997";
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_actionLiquid_Player_triggered()
{
    QString link = "https://github.com/sayansil/Liquid-Player";
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}
