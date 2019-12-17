#include "paintscene.h"


PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{

}

PaintScene::~PaintScene()
{

}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    p1 = event->scenePos();
    cur_line = nullptr;
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    p2 = event->scenePos();
    if(cur_line != nullptr){
        removeItem(cur_line);
    }
    cur_line = addLine(p1.x(), p1.y(), p2.x(), p2.y(), linePen);
}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "====== mouse release event ======";
    qDebug() << "p1: (" << p1.x() << p1.y() <<"). p2: (" << p2.x() << p2.y() << ")";

    while(true){
        int b1 = get_outcode(p1);
        int b2 = get_outcode(p2);
        qDebug() << "b1:" << b1 << " b2:" << b2;

        if((b1 | b2) == 0){
            qDebug() << "both ends of segment belong to the viewport";
            draw_line_in_viewport(p1, p2);
            break;
        }
        if((b1 & b2) != 0){
            qDebug() << "segment is outside the viewport";
            break;
        }

        // find any end of the segment outside the viewport
        int code_nonzero = b1 != 0 ? b1 : b2;
        qDebug() << "clipping segment. code_nonzero:" << code_nonzero;

        double new_x = 0;
        double new_y = 0;
        if((code_nonzero & TOP) != 0){
            // clip the top
            new_y = rectangle_rt.y();
            new_x = (p2.x() - p1.x()) * (new_y - p1.y()) / (p2.y() - p1.y()) + p1.x();
        } else if((code_nonzero & BOTTOM) != 0){
            // clip the bottom
            new_y = rectangle_lb.y();
            new_x = (p2.x() - p1.x()) * (new_y - p1.y()) / (p2.y() - p1.y()) + p1.x();
        } else if((code_nonzero & LEFT) != 0){
            new_x = rectangle_lb.x();
            new_y = (p2.y() - p1.y()) * (new_x - p1.x()) / (p2.x() - p1.x()) + p1.y();
        } else if((code_nonzero) & RIGHT){
            new_x = rectangle_rt.x();
            new_y = (p2.y() - p1.y()) * (new_x - p1.x()) / (p2.x() - p1.x()) + p1.y();
        }

        if(get_outcode(p1) == code_nonzero){
            p1.setX(new_x);
            p1.setY(new_y);
        } else{
            p2.setX(new_x);
            p2.setY(new_y);
        }
    }
}

int PaintScene::get_outcode(QPointF point)
{
    int outcode = 0;
    if(point.x() < rectangle_lb.x()){
        outcode |= LEFT;
    }
    if(point.x() > rectangle_rt.x()){
        outcode |= RIGHT;
    }
    if(point.y() < rectangle_rt.y()){
        outcode |= TOP;
    }
    if(point.y() > rectangle_lb.y()){
        outcode |= BOTTOM;
    }
    return outcode;
}

void PaintScene::draw_line_in_viewport(QPointF a, QPointF b)
{
    addLine(a.x(), a.y(), b.x(), b.y(), clippedLinePen);
}

void PaintScene::draw_center_rectangle(){
    double w = sceneRect().width();
    double h = sceneRect().height();
    double rect_w = w * 6 / 10;
    double rect_h = h * 6 / 10;
    rectangle_lb = QPointF(w * 2 / 10, h * 8 / 10);
    rectangle_rt = QPointF(rectangle_lb.x() + rect_w, rectangle_lb.y() - rect_h);
    addRect(rectangle_lb.x(), rectangle_rt.y(), rect_w, rect_h, rectanglePen);
}

void PaintScene::clearScene(){
    clear();
    draw_center_rectangle();
}
