#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>
#include <options.h>
#include <game.h>



namespace Ui {
class Application;
}

class Application : public QWidget
{
    Q_OBJECT

public:
    explicit Application(QWidget *parent = 0);
    ~Application();

private slots:
    void on_play_button_clicked();
    void on_options_button_clicked();
    void on_quit_button_clicked();
    void moveHome();
    void moveHome2();


private:
    Ui::Application *ui;
    Options Settings;
    Game GameChoose;
};


#endif // APPLICATION_H
