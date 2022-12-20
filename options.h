#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>

namespace Ui {
class Options;
}

class Options : public QWidget
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = nullptr);
    ~Options();

private slots:
    void on_back_button_clicked();

private:
    Ui::Options *ui;

signals:
    void HomeClicked();
};


#endif // OPTIONS_H
