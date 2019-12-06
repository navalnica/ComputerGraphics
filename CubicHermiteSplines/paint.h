#ifndef PAINT_H
#define PAINT_H

#include <QWidget>
#include <QTimer>
#include <QResizeEvent>

#include "paintscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Paint; }
QT_END_NAMESPACE

class Paint : public QWidget
{
    Q_OBJECT

public:
    Paint(QWidget *parent = nullptr);
    ~Paint();

private slots:
    void on_clearButton_clicked();

private:
    Ui::Paint *ui;
    PaintScene *scene;  // We declare a custom graphic scene
};

#endif // PAINT_H
