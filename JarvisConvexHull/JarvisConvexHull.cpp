#include "JarvisConvexHull.h"
#include "PolarComparator.h"

double const JarvisConvexHull::EPS = 1e-10;

vector<QPointF> JarvisConvexHull::generate_uniform_points(int num, double xmin, double xmax, double ymin, double ymax) {
    vector<QPointF> res;
    random_device rd;
    unsigned int seed = rd();
//    cout << "seed: " << seed << endl;
    mt19937 engine(seed);
    uniform_real_distribution<double> distribution_x(
            xmin, nextafter(xmax, numeric_limits<double>::max())
    );
    uniform_real_distribution<double> distribution_y(
            ymin, nextafter(ymax, numeric_limits<double>::max())
    );
    for (int i = 0; i < num; ++i) {
        res.emplace_back(distribution_x(engine), distribution_y(engine));
    }
    return res;
}

vector<QPointF>
JarvisConvexHull::generate_normal_points(int num, double mu_x, double std_x, double mu_y, double std_y) {
    vector<QPointF> res;
    random_device rd;
    unsigned int seed = rd();
//    cout << "seed: " << seed << endl;
    mt19937 engine(seed);
    normal_distribution<double> distribution_x(mu_x, std_x);
    normal_distribution<double> distribution_y(mu_y, std_y);
    for (int i = 0; i < num; ++i) {
        res.emplace_back(distribution_x(engine), distribution_y(engine));
    }
    return res;
}

vector<QPointF> JarvisConvexHull::get_jarvis_convex_hull(vector<QPointF> &points) {
    vector<QPointF> hull;

    QPointF leftmost(-10, -10);
    for (auto &p : points) {
        if (
                (p.x() < leftmost.x()) ||
                (leftmost.x() < 0 && leftmost.y() < 0)) {
            leftmost = QPointF(p);
            continue;
        }
        if (fabs(p.x() - leftmost.x()) < EPS && p.y() < leftmost.y()) {
            leftmost = QPointF(p);
        }
    }
    QPointF rightmost(-10, -10);
    for (auto &p : points) {
        if (
                (p.x() > rightmost.x()) ||
                (rightmost.x() < 0 && rightmost.y() < 0)) {
            rightmost = QPointF(p);
            continue;
        }
        if (fabs(p.x() - rightmost.x()) < EPS && p.y() > rightmost.y()) {
            rightmost = QPointF(p);
        }
    }

    QPointF cur(leftmost);
    while (cur != rightmost) {
//        cout << cur.x() << " " << cur.y() << endl;
        bool has_max_x = fabs(cur.x() - rightmost.x()) < EPS;
        bool has_min_x = fabs(cur.x() - leftmost.x()) < EPS;
        sort(points.begin(), points.end(), PolarComparator(cur, has_max_x, has_min_x));
        for (size_t i = 1; i < points.size(); ++i) {
            if (points[i].x() >= cur.x()) {
                hull.push_back(cur);
                cur = points[i];
                break;
            }
        }
    }
    while (cur != leftmost) {
//        cout << cur.x() << " " << cur.y() << endl;
        bool has_max_x = fabs(cur.x() - rightmost.x()) < EPS;
        bool has_min_x = fabs(cur.x() - leftmost.x()) < EPS;
        sort(points.begin(), points.end(), PolarComparator(cur, has_max_x, has_min_x));
        size_t i = 1;
        for (i; i < points.size(); ++i) {
            if (points[i].x() <= cur.x()) {
                hull.push_back(cur);
                cur = points[i];
                break;
            }
        }
        if (i == points.size()){
            // could not return to the starting point
             hull.push_back(cur);
            break;
        }
    }
    hull.push_back(hull[0]);

    return hull;
}
