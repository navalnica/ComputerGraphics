#include "paint.h"
#include "ui_paint.h"

Paint::Paint(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Paint)
{
    ui->setupUi(this);

    scene = new PaintScene();
    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
    qDebug() << "created scene with SceneRect:";
    qDebug() << "x, y: " << scene->sceneRect().x() << scene->sceneRect().y();
    qDebug() << "width, height: " << scene->sceneRect().width() << scene->sceneRect().height();

    ui->graphicsView->setScene(scene);
}

Paint::~Paint()
{
    delete ui;
}


void Paint::on_clearButton_clicked()
{
    scene->clearScene();
}
