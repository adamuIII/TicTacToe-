#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <options.h>
#include <game.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void moveHome();

    void go_back();

    void signals_and_slots();

    void on_settings_button_clicked();

    void on_quit_button_clicked();


private:
    Ui::MainWindow *ui;
    Options options;
    Game game;
};
#endif // MAINWINDOW_H
