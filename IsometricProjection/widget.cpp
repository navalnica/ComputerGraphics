#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    scene = new PaintScene();
    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);

    qDebug() << "created scene with SceneRect:";
    qDebug() << "width, height: " << scene->sceneRect().width() << scene->sceneRect().height();

    scene->init();

    ui->graphicsView->setScene(scene);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_slider_x_valueChanged(int value)
{
    scene->rotate_z(value - slider_x_prev_value);
    slider_x_prev_value = value;
}

void Widget::on_slider_y_valueChanged(int value)
{
    scene->rotate_x(value - slider_y_prev_value);
    slider_y_prev_value = value;
}

void Widget::on_slider_z_valueChanged(int value)
{
    scene->rotate_y(value - slider_z_prev_value);
    slider_z_prev_value = value;
}

void Widget::on_button_reset_clicked()
{
    scene->reset();
    slider_x_prev_value = 0;
    slider_y_prev_value = 0;
    slider_z_prev_value = 0;
    ui->slider_x->setValue(0);
    ui->slider_y->setValue(0);
    ui->slider_z->setValue(0);
}
