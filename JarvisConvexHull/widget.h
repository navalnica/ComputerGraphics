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
    void on_btn_clear_clicked();

    void on_btn_uniform_clicked();

    void on_btn_normal_clicked();

private:
    Ui::Widget *ui;
    PaintScene *scene;  // We declare a custom graphic scene
};
#endif // WIDGET_H
