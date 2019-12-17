#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    scene = new PaintScene();
    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
    scene->draw_center_rectangle();

    qDebug() << "created scene with SceneRect:";
    qDebug() << "width, height: " << scene->sceneRect().width() << scene->sceneRect().height();

    ui->graphicsView->setScene(scene);
}

Widget::~Widget()
{
    delete ui;
}


