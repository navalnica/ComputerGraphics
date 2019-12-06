#include "paintscene.h"


PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
}

PaintScene::~PaintScene()
{

}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF cur = event->scenePos();
    qDebug() << "click coordinates: " << cur;

    points.push_back(cur);
    auto res = addEllipse(cur.x() - 2, cur.y() - 2, 4, 4, pointPen, pointBrush);
    points_dots.push_back(res);

    if (points.size() >= 3){
        // print points list to text file so you can debug if something goes wrong
        qDebug() << "printing new points list to 'points.cpp'";
        ofstream fout("points.txt");
        for (auto p : points){
            fout << p.x() << " " << p.y() << endl;
        }

        qDebug() << "rebuilding convex hull";
        remove_lines();
        draw_convex_hull();
    }

    QGraphicsScene::mousePressEvent(event);
}

void PaintScene::draw_points()
{
    for(auto p : points){
        auto res = addEllipse(p.x() - 2, p.y() - 2, 4, 4, pointPen, pointBrush);
        points_dots.push_back(res);
    }
}

void PaintScene::remove_lines(){
    for (QGraphicsLineItem * line : lines){
        removeItem(line);
    }
    lines.clear();
}

void PaintScene::draw_convex_hull(){
    vector<QPointF> hull = JarvisConvexHull::get_jarvis_convex_hull(points);
    for(size_t i = 1; i < hull.size(); ++i){
        auto line = addLine(hull[i - 1].x(), hull[i - 1].y(), hull[i].x(), hull[i].y(), linePen);
        lines.push_back(line);
    }
}

void PaintScene::generate_uniform_points()
{
    clearScene();

    qDebug() << "generating uniform points";
    int margin = 120;
    points = JarvisConvexHull::generate_uniform_points(
                1500, margin, sceneRect().width() - margin, margin, sceneRect().height() - margin);
    draw_points();
    draw_convex_hull();
}

void PaintScene::generate_normal_points()
{
    clearScene();

    qDebug() << "generating uniform points";
    int cx = int(sceneRect().width() / 2);
    int cy = int(sceneRect().height() / 2);
    vector<QPointF> points_tmp = JarvisConvexHull::generate_normal_points(5000, cx, 150, cy, 80);

    // filter points outside of the area within margins from screen border
    int margin = 120;
    points.clear();
    for (auto p : points_tmp){
        if(p.x() > margin && p.x() < sceneRect().width() - margin &&
           p.y() > margin && p.y() < sceneRect().height() - margin){
            points.push_back(p);
        }
    }

    draw_points();
    draw_convex_hull();
}

void PaintScene::clearScene(){
    clear();
    points.clear();
    points_dots.clear();
    lines.clear();
}
