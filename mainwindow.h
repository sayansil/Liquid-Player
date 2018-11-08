#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QMediaPlayer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_playButton_clicked();

    void on_pauseButton_clicked();

    void on_stopButton_clicked();

    void on_dial_valueChanged(int value);

    void on_actionNew_File_triggered();

    void on_actionSenpai_triggered();

    void on_actionR_M_G_triggered();

    void on_actionLiquid_Player_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *mLiquidPlayer;
};

#endif // MAINWINDOW_H
