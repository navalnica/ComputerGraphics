#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    scene = new PaintScene();

    QObject::connect(scene, &PaintScene::points_count_calculated, this, &Widget::on_points_count_calculated);

    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
    qDebug() << "created scene with SceneRect:";
    qDebug() << "width, height: " << scene->sceneRect().width() << scene->sceneRect().height();

    ui->graphicsView->setScene(scene);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btn_clear_clicked()
{
    scene->clearScene();
}

void Widget::on_btn_generate_clicked()
{
    int count = ui->spinBox->value();
    scene->generate_uniform_points(count);
}

void Widget::on_spinBox_valueChanged(int arg1)
{
    qDebug() << "spin_box value:" << arg1;
}

void Widget::on_points_count_calculated(int count)
{
    QString count_str = QString::number(count);
    ui->label_points_count->setText(count_str);
}

