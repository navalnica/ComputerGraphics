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

    void set_points_count(int count);

private slots:
    void on_btn_clear_clicked();

    void on_btn_generate_clicked();

    void on_spinBox_valueChanged(int arg1);

public slots:
    void on_points_count_calculated(int count);

private:
    Ui::Widget *ui;
    PaintScene* scene;
};
#endif // WIDGET_H
