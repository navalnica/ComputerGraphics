#ifndef POLARCOMPARATOR_H
#define POLARCOMPARATOR_H

#include <QPointF>
#include "JarvisConvexHull.h"

struct PolarComparator {

    /// Compare points based on the polar angle

    QPointF pivot_point;
    bool has_max_x = false;
    bool has_min_x = false;
    double const EPS = JarvisConvexHull::EPS;

    PolarComparator(const QPointF &pivotPoint, bool hasMaxX, bool hasMinX) :
            pivot_point(pivotPoint),
            has_max_x(hasMaxX),
            has_min_x(hasMinX) {}

    bool operator()(QPointF const &lhs, QPointF const &rhs) {
        double dxl = lhs.x() - pivot_point.x();
        double dxr = rhs.x() - pivot_point.x();
        double dyl = lhs.y() - pivot_point.y();
        double dyr = rhs.y() - pivot_point.y();

        // check if rhs == lhs
        if((fabs(lhs.x() - rhs.x()) < EPS) && (fabs(lhs.y() - rhs.y()) < EPS)){
            return false;
        }

        // check if the point is the pivot point
        if ((fabs(dxl) < EPS) && (fabs(dyl) < EPS)) { return true; }
        if ((fabs(dxr) < EPS) && (fabs(dyr) < EPS)) { return false; }

        if (fabs(dxl) < EPS && fabs(dxr) < EPS) {
            // points and pivot lie on the same vertical line
            if (has_max_x) {
                if (dyl * dyr > 0) { return lhs.y() < rhs.y(); }
                if (dyl < 0) { return false; }
                if (dyr < 0) { return true; }
            }
            if (has_min_x) {
                if (dyl * dyr > 0) { return lhs.y() > rhs.y(); }
                if (dyl > 0) { return false; }
                if (dyr > 0) { return true; }
            }
            return lhs.y() > rhs.y();
        }
        if (fabs(dxl) < EPS) {
            // left point lies on the same vertical line

            if (!has_max_x && !has_min_x){ return false; }

            if ((dyl < 0) && (dxr > 0)) { return true; }
            if ((dyl < 0) && (dxr < 0)) { return false; }
            if ((dyl > 0) && (dxr > 0)) { return false; }
            if ((dyl > 0) && (dxr < 0)) { return true; }
        }
        if (fabs(dxr) < EPS) {
            // right point lies on the same vertical line

            if (!has_max_x && !has_min_x) { return true; }

            if ((dyr < 0) && (dxl > 0)) { return false; }
            if ((dyr < 0) && (dxl < 0)) { return true; }
            if ((dyr > 0) && (dxl > 0)) { return true; }
            if ((dyr > 0) && (dxl < 0)) { return false; }
        }

        return (dyl / dxl) < (dyr / dxr);
    }
};

#endif // POLARCOMPARATOR_H
