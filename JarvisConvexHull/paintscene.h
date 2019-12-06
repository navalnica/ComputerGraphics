#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QDebug>
#include <vector>
#include <fstream>

#include "JarvisConvexHull.h"

class PaintScene : public QGraphicsScene
{
    Q_OBJECT

public:
//    PaintScene();
    explicit PaintScene(QObject *parent = nullptr);
    ~PaintScene() override;

    void clearScene();

    void generate_uniform_points();

    void generate_normal_points();

protected:
    std::vector<QPointF> points;
    std::vector<QGraphicsEllipseItem*> points_dots;
    std::vector<QGraphicsLineItem*> lines;

    QPen linePen = QPen(Qt::blue, 2, Qt::SolidLine, Qt::RoundCap);
    QPen pointPen = QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap);
    QBrush pointBrush = QBrush(Qt::black);

    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;

    void draw_points();

    void draw_convex_hull();

    void remove_lines();
};

#endif // PAINTSCENE_H
