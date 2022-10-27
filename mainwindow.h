#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <options.h>
#include <game.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void moveHome();

private:
    Ui::MainWindow *ui;
    Options options;
    Game game;
};
#endif // MAINWINDOW_H
