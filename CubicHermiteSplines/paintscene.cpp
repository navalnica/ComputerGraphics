#include "paintscene.h"
#include "HermiteSplineGenerator.h"

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
    splinePen = QPen(Qt::blue, 2, Qt::SolidLine, Qt::RoundCap);
}

PaintScene::~PaintScene()
{

}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "click coordinates: " << event->scenePos();
    tangents.emplace_back(Tangent(event->scenePos()));
    curSplineLines.clear();
    QGraphicsScene::mousePressEvent(event);
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // draw tangent
    if (!tangents.empty()){
        Tangent &t = tangents[tangents.size() - 1];
        t.setEndPoint(event->scenePos());
        if (t.line != nullptr){
            removeItem(t.line);
            removeItem(t.startCap);
            removeItem(t.endCap);
        }
        t.line = addLine(
            t.getStartPoint().x(), t.getStartPoint().y(),
            t.getEndPoint().x(), t.getEndPoint().y(), Tangent::linePen);
        t.startCap = addEllipse(
            t.getStartPoint().x() - 3, t.getStartPoint().y() - 3,
            6, 6, Tangent::startCapPen, Tangent::startCapBrush);
        t.endCap = addEllipse(
            t.getEndPoint().x() - 3, t.getEndPoint().y() - 3,
            6, 6, Tangent::endCapPen, Tangent::endCapBrush);
    }

    // draw spline
    if (tangents.size() > 1){
        size_t ix = tangents.size() - 1;
        HermiteSplineGenerator generator(
            tangents[ix-1].getStartPoint(), tangents[ix].getStartPoint(),
            tangents[ix-1].getVectorCoordinates(), tangents[ix].getVectorCoordinates()
        );
        std::vector<QPointF> dots = generator.getDots(splineDotsCnt);

        if(!curSplineLines.empty()){
            for (QGraphicsLineItem * line : curSplineLines){
                removeItem(line);
            }
            curSplineLines.clear();
        }
        for (size_t i = 1; i < dots.size(); ++i){
            curSplineLines.push_back(addLine(
                dots[i-1].x(), dots[i-1].y(), dots[i].x(), dots[i].y(), splinePen
            ));
        }
    }
}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "mouse released. tangent count: " << tangents.size();
    Tangent & t = tangents[tangents.size() - 1];
    qDebug() << "start: " << t.getStartPoint();
    qDebug() << "end: " << t.getEndPoint();
    qDebug() << "vector: " << t.getVectorCoordinates() << "\n";

    QGraphicsScene::mouseReleaseEvent(event);
}

void PaintScene::clearScene(){
    clear();
    tangents.clear();
    curSplineLines.clear();
}
