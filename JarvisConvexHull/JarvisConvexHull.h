#ifndef JARVIS_CONVEX_HULL_H
#define JARVIS_CONVEX_HULL_H

#include <vector>
#include <algorithm>
#include <random>

#include <QPointF>
#include <QDebug>

using namespace std;

class JarvisConvexHull {
public:

    static double const EPS;

    static vector<QPointF> generate_uniform_points(int num, double xmin, double xmax, double ymin, double ymax);

    static vector<QPointF> generate_normal_points(int num, double mu_x, double std_x, double mu_y, double std_y);

    static vector<QPointF> get_jarvis_convex_hull(vector<QPointF> &points);
};

#endif // JARVIS_CONVEX_HULL_H
