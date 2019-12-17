#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QDebug>
#include <vector>
#include <set>
#include <vector>
#include <unordered_set>
#include <map>
#include <random>
#include <fstream>


class PaintScene : public QGraphicsScene
{

    Q_OBJECT

public:
    explicit PaintScene(QObject *parent = nullptr);
    ~PaintScene() override;

    void clearScene();
    void draw_center_rectangle();

protected:
    int TOP = 1;
    int BOTTOM = 1 << 1;
    int LEFT = 1 << 2;
    int RIGHT = 1 << 3;

    QPointF p1, p2;
    QPointF rectangle_lb;
    QPointF rectangle_rt;

    // graphics elements pointers
    QGraphicsLineItem* cur_line;

    // pens and brushes
    QBrush pointBrush = QBrush(Qt::black);
    QPen pointPen = QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap);
    QPen rectanglePen = QPen(Qt::magenta, 2, Qt::SolidLine, Qt::RoundCap);
    QPen linePen = QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap);
    QPen clippedLinePen = QPen(Qt::darkMagenta, 3, Qt::SolidLine, Qt::RoundCap);

    // callbacks
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    int get_outcode(QPointF point);
    void draw_line_in_viewport(QPointF a, QPointF b);
};

#endif // PAINTSCENE_H
