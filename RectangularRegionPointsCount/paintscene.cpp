#include "paintscene.h"


PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
}

PaintScene::~PaintScene()
{

}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    delete_rectangle_if_needed();
    rectangle_temp = event->scenePos();
    qDebug() << "press coordingates:" << event->scenePos();
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    mode_add_point = false;
    p_rectangle = draw_rectangle(event->scenePos(), true);
}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF cur = event->scenePos();
    qDebug() << "release coordinates:" << cur;

    if(mode_add_point){
        points.push_back(cur);
        points_preprocessed = false;
        auto p_ellipse = addEllipse(cur.x() - 2, cur.y() - 2, 4, 4, pointPen, pointBrush);
        p_point_ellipses.push_back(p_ellipse);
        emit points_count_calculated(0);
    }
    else{
        p_rectangle = draw_rectangle(cur, false);
        count_points();
    }

    mode_add_point = true;
}

QGraphicsRectItem* PaintScene::draw_rectangle(QPointF second, bool temp){
    rectangle_rt = QPointF(std::max(rectangle_temp.x(), second.x()), std::max(rectangle_temp.y(), second.y()));
    rectangle_lb = QPointF(std::min(rectangle_temp.x(), second.x()), std::min(rectangle_temp.y(), second.y()));
    double width = rectangle_rt.x() - rectangle_lb.x();
    double height = rectangle_rt.y() - rectangle_lb.y();

    delete_rectangle_if_needed();
    auto res = addRect(rectangle_lb.x(), rectangle_lb.y(), width, height, temp ? rectanglePenTemp : rectanglePen);
    return res;
}

void PaintScene::delete_rectangle_if_needed()
{
    if (p_rectangle != nullptr){
        removeItem(p_rectangle);
        p_rectangle = nullptr;
    }
}

void PaintScene::generate_uniform_points(int count)
{
    qDebug() << "generating uniformally distributed points";
    clearScene();

    int margin = 50;
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_real_distribution<double> distribution_x (margin, sceneRect().width() - margin);
    std::uniform_real_distribution<double> distribution_y (margin, sceneRect().height() - margin);
    for (int i = 0; i < count; ++i){
        points.emplace_back(distribution_x(engine), distribution_y(engine));
    }
    points_preprocessed = false;

    draw_points();
    emit points_count_calculated(0);
}

void PaintScene::draw_points()
{
    for(auto & p : points){
        auto p_ellipse = addEllipse(p.x() - 2, p.y() - 2, 4, 4, pointPen, pointBrush);
        p_point_ellipses.push_back(p_ellipse);
    }
}

void PaintScene::preprocess(){
    qDebug() << "";
    qDebug() << "preprocessing";

    coord_map_x.clear();
    coord_map_y.clear();
    locuses.clear();

    // find unique values of x and y
    std::set<double> unique_x;
    std::set<double> unique_y;
    for(QPointF & p : points){
        unique_x.insert(p.x());
        unique_y.insert(p.y());
    }
    size_t cnt_x = unique_x.size();
    size_t cnt_y = unique_y.size();

    // map unique x coordinates to the grid indices
    coord_map_x.clear();
    auto x_it = unique_x.begin();
    int dist = 0;
    while(x_it != unique_x.end()){
        coord_map_x.insert(std::make_pair(*x_it, dist + 1));
        ++x_it;
        ++dist;
    }

    // map unique y coordinates to the grid indices
    coord_map_y.clear();
    auto y_it = unique_y.begin();
    dist = 0;
    while(y_it != unique_y.end()){
        coord_map_y.insert(std::make_pair(*y_it, dist + 1));
        ++y_it;
        ++dist;
    }

    // vector grid to check if point on the plane
    // belongs to the point on the grid in constant time
    std::vector<std::vector<char>> grid(cnt_y + 1, std::vector<char>(cnt_x + 1, 0));
    for(auto & p : points){
        grid[coord_map_y[p.y()]][coord_map_x[p.x()]] = 1;
    }
//    std::ofstream grid_out("grid.txt");
//    for(int i = 0; i < cnt_y + 1; ++i){
//        for(int j = 0; j < cnt_x + 1; ++j){
//            grid_out << int(grid[i][j]) << " ";
//        }
//        grid_out << std::endl;
//    }

    locuses = std::vector<std::vector<int>>(cnt_y + 1, std::vector<int>(cnt_x + 1, 0));
    for(int i = 1; i < cnt_y + 1; ++i){
        int row_dots = 0;
        for(int j = 1; j < cnt_x + 1; ++j){
            if(grid[i][j] == 1){
                row_dots += 1;
            }
            locuses[i][j] = locuses[i-1][j] + row_dots;
        }
    }
//    std::ofstream locuses_out("locuses.txt");
//    for(int i = 0; i < cnt_y + 1; ++i){
//        for(int j = 0; j < cnt_x + 1; ++j){
//            locuses_out << locuses[i][j] << " ";
//        }
//        locuses_out << std::endl;
//    }

    qDebug() << "";
}

int PaintScene::get_lower_left_locus_value(double x, double y)
{
    auto x_it = coord_map_x.lower_bound(x);
    auto y_it = coord_map_y.lower_bound(y);
    int value = 0;
    if(x_it != coord_map_x.begin() && y_it != coord_map_y.begin()){
        x_it--;
        y_it--;
        value = locuses[y_it->second][x_it->second];
    }
    qDebug() << "x:" << x <<"y:" << y << "value:" << value;
    return value;
}

void PaintScene::count_points()
{
    qDebug() << "=====================";

    if(false){
        draw_grid();
    }

    if(!points_preprocessed){
        preprocess();
        points_preprocessed = true;
    }

    int lb_value = get_lower_left_locus_value(rectangle_lb.x(), rectangle_lb.y());
    int rb_value = get_lower_left_locus_value(rectangle_rt.x(), rectangle_lb.y());
    int lt_value = get_lower_left_locus_value(rectangle_lb.x(), rectangle_rt.y());
    int rt_value = get_lower_left_locus_value(rectangle_rt.x(), rectangle_rt.y());
    int points_cnt = rt_value - rb_value - lt_value + lb_value;

    emit points_count_calculated(points_cnt);

    qDebug() << "points count:" << points_cnt;
    qDebug() << "=====================";
}

void PaintScene::draw_grid()
{
    // draw grid based on current points

    if(points.empty()){
        qDebug() << "no points to draw grid";
        return;
    }

    if(!p_grid_lines.empty()){
        for(auto & line : p_grid_lines){
            removeItem(line);
        }
    }
    p_grid_lines.clear();

    for(auto & p : coord_map_x){
        QGraphicsLineItem * line = addLine(p.first, 0, p.first, sceneRect().height());
        p_grid_lines.push_back(line);
    }
    for(auto & p : coord_map_y){
        QGraphicsLineItem * line = addLine(0, p.first, sceneRect().width(), p.first);
        p_grid_lines.push_back(line);
    }
}

void PaintScene::clearScene(){
    points.clear();
    coord_map_x.clear();
    coord_map_y.clear();
    locuses.clear();

    p_point_ellipses.clear();
    p_rectangle = nullptr;
    p_grid_lines.clear();
    clear();

    emit points_count_calculated(0);
}
