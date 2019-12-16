#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QVector3D>
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

    void init();
    void rotate_x(int delta_angle);
    void rotate_y(int delta_angle);
    void rotate_z(int delta_angle);
    void reset();

protected:

    std::vector<QGraphicsEllipseItem*> projection_point_ellipses;
    std::vector<QGraphicsLineItem*> projection_edges;

    std::vector<QVector3D> initial_points{
        QVector3D(0, 0, 0),
        QVector3D(0, 0, 1),
        QVector3D(0, 1, 0),
        QVector3D(0, 1, 1),
        QVector3D(2, 0, 0),
        QVector3D(2, 0, 1),
        QVector3D(2, 1, 0),
        QVector3D(2, 1, 1),
    };
    std::vector<QVector3D> points;
    std::vector<std::pair<int, int>> edges{
      std::make_pair(0, 1),
      std::make_pair(0, 2),
      std::make_pair(1, 3),
      std::make_pair(2, 3),
      std::make_pair(4, 5),
      std::make_pair(4, 6),
      std::make_pair(5, 7),
      std::make_pair(6, 7),
      std::make_pair(0, 4),
      std::make_pair(1, 5),
      std::make_pair(2, 6),
      std::make_pair(3, 7),
    };
    std::vector<QPointF> projections;
    double factor = 150; // factor to multiply the edge len


    // pens and brushes
    QBrush pointBrush = QBrush(Qt::magenta);
    QPen pointPen = QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap);
    QPen edgePen = QPen(Qt::darkRed, 2, Qt::SolidLine, Qt::RoundCap);
    QPen axisPen = QPen(Qt::black, 1, Qt::DashLine, Qt::RoundCap);

    QPointF center;
    double axis_len = 300;

    void update_projection();
    void draw_projection();

};

#endif // PAINTSCENE_H
