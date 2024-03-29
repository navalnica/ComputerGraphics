#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "paintscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);

    ~Widget();

private slots:
    void on_slider_x_valueChanged(int value);

    void on_slider_y_valueChanged(int value);

    void on_slider_z_valueChanged(int value);

    void on_button_reset_clicked();

private:
    Ui::Widget *ui;
    PaintScene* scene;

    int slider_x_prev_value = 0;
    int slider_y_prev_value = 0;
    int slider_z_prev_value = 0;
};
#endif // WIDGET_H
