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

    void generate_uniform_points(int count);

protected:
    std::map<double, int> coord_map_x;
    std::map<double, int> coord_map_y;
    // result of points preprocessing.
    // store number of points that have <= x and <= y coordinates.
    // allows to count points in the specified regions in O(log n) time.
    std::vector<std::vector<int>> locuses;

    std::vector<QPointF> points;
    QPointF rectangle_lb;
    QPointF rectangle_rt;
    QPointF rectangle_temp;

    /*  controls the mouse action mode:
        true: mouse was released after the click -> add point
        false: mouser was moved after the click -> add rectangle
    */
    bool mode_add_point = true;
    // flag to indicate the need for preprocessing
    bool points_preprocessed = true;

    // graphics elements pointers
    std::vector<QGraphicsEllipseItem*> p_point_ellipses;
    QGraphicsRectItem* p_rectangle = nullptr;
    std::vector<QGraphicsLineItem*> p_grid_lines;

    // pens and brushes
    QPen pointPen = QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap);
    QBrush pointBrush = QBrush(Qt::black);
    QPen rectanglePen = QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap);
    QPen rectanglePenTemp = QPen(Qt::red, 1, Qt::DashLine, Qt::RoundCap);
    QPen gridPen = QPen(Qt::darkCyan, 1, Qt::DashLine, Qt::RoundCap);

    // callbacks
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    // methods
    QGraphicsRectItem* draw_rectangle(QPointF second, bool temp);

    void delete_rectangle_if_needed();

    void draw_points();

    void preprocess();

    void count_points();

    void draw_grid();

    int get_lower_left_locus_value(double x, double y);

signals:
    void points_count_calculated(int count);
};

#endif // PAINTSCENE_H
