#include "paintscene.h"
#include <cmath>


PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
    points = std::vector<QVector3D>(initial_points);
    projections = std::vector<QPointF>(points.size());
}

PaintScene::~PaintScene()
{

}

void PaintScene::init()
{
    center = QPointF(sceneRect().width() / 2, sceneRect().height() * 5 / 9);
    qDebug() << "center (x,y): " << center.x() << center.y();

    // draw the axis
    QPointF axis_x (center.x() - axis_len * sqrt(3) / 2, center.y() + axis_len / 2);
    QPointF axis_y (center.x() + axis_len * sqrt(3) / 2, center.y() + axis_len / 2);
    QPointF axis_z (center.x(), center.y()  - axis_len);
    addLine(center.x(), center.y(), axis_x.x(), axis_x.y(), axisPen);
    addLine(center.x(), center.y(), axis_y.x(), axis_y.y(), axisPen);
    addLine(center.x(), center.y(), axis_z.x(), axis_z.y(), axisPen);

    update_projection();
}

void PaintScene::rotate_x(int delta_angle)
{
    double delta_rad = delta_angle * M_PI / 180.0;
    for(size_t i = 0; i < points.size(); ++i){
        double new_y = points[i].y() * cos(delta_rad) - points[i].z() * sin(delta_rad);
        double new_z = points[i].y() * sin(delta_rad) + points[i].z() * cos(delta_rad);
        points[i].setY(new_y);
        points[i].setZ(new_z);
    }
    update_projection();
}

void PaintScene::rotate_y(int delta_angle)
{
    double delta_rad = delta_angle * M_PI / 180.0;
    for(size_t i = 0; i < points.size(); ++i){
        double new_x = points[i].x() * cos(delta_rad) - points[i].z() * sin(delta_rad);
        double new_z = points[i].x() * sin(delta_rad) + points[i].z() * cos(delta_rad);
        points[i].setX(new_x);
        points[i].setZ(new_z);
    }
    update_projection();
}

void PaintScene::rotate_z(int delta_angle)
{
    double delta_rad = delta_angle * M_PI / 180.0;
    for(size_t i = 0; i < points.size(); ++i){
        double new_x = points[i].x() * cos(delta_rad) - points[i].y() * sin(delta_rad);
        double new_y = points[i].x() * sin(delta_rad) + points[i].y() * cos(delta_rad);
        points[i].setX(new_x);
        points[i].setY(new_y);
    }
    update_projection();
}

void PaintScene::reset()
{
    points = std::vector<QVector3D>(initial_points);
    update_projection();
}

void PaintScene::update_projection()
{
    for(size_t i = 0; i < points.size(); ++i){
        double px = 1.0 * (sqrt(3) * points[i].x() - sqrt(3) * points[i].z()) / sqrt(6);
        double py = 1.0 * (points[i].x() - 2 * points[i].y() + points[i].z()) / sqrt(6);
        px = center.x() + factor * px;
        py = center.y() + factor * py;
        projections[i].rx() = px;
        projections[i].ry() = py;
    }
    draw_projection();
}

void PaintScene::draw_projection()
{
    // draw points
    for(auto el : projection_point_ellipses){
        removeItem(el);
    }
    projection_point_ellipses.clear();
    for(QPointF const & p : projections){
        QGraphicsEllipseItem* ei = addEllipse(p.x() - 4, p.y() - 4, 8, 8, pointPen, pointBrush);
        projection_point_ellipses.push_back(ei);
    }

    // draw edges
    for(auto el : projection_edges){
        removeItem(el);
    }
    projection_edges.clear();
    for(auto & e: edges){
        QGraphicsLineItem* li = addLine(
            projections[e.first].x(), projections[e.first].y(),
            projections[e.second].x(), projections[e.second].y(), edgePen);
        projection_edges.push_back(li);
    }
}
