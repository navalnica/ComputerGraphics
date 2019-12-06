#ifndef TANGENT_H
#define TANGENT_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>

class Tangent{
private:
    QPointF startPoint;
    QPointF endPoint;
    QPointF vectorCoordinates;
public:
    static QPen const linePen;
    static QPen const startCapPen;
    static QPen const endCapPen;
    static QBrush const startCapBrush;
    static QBrush const endCapBrush;

    QGraphicsLineItem* line = nullptr;
    QGraphicsEllipseItem* startCap = nullptr;
    QGraphicsEllipseItem* endCap = nullptr;

    Tangent(QPointF startPoint);

    void setStartPoint(QPointF const & point) { startPoint = QPointF(point); }
    QPointF getStartPoint() { return startPoint; }

    void setEndPoint(QPointF const & point);
    QPointF getEndPoint() { return endPoint; }

    QPointF getVectorCoordinates() { return vectorCoordinates; }
};

#endif // TANGENT_H
