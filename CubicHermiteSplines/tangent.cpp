#include "tangent.h"

QPen const Tangent::linePen = QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap);

QBrush const Tangent::startCapBrush = QBrush(Qt::magenta);
QPen const Tangent::startCapPen = QPen(Tangent::startCapBrush, 1, Qt::SolidLine, Qt::RoundCap);

QBrush const Tangent::endCapBrush = QBrush(Qt::green);
QPen const Tangent::endCapPen = QPen(Tangent::endCapBrush, 1, Qt::SolidLine, Qt::RoundCap);

Tangent::Tangent(QPointF startPoint) : startPoint(startPoint) {}

void Tangent::setEndPoint(QPointF const & point) {
    endPoint = QPointF(point);
    vectorCoordinates = endPoint - startPoint;
    vectorCoordinates *= 5; // make spline more intense by increasing vector magnitude
}
