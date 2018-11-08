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

    void on_loadButton_clicked();

    void on_dial_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QMediaPlayer *mLiquidPlayer;
};

#endif // MAINWINDOW_H
