#ifndef HERMITESPLINEGENERATOR_H
#define HERMITESPLINEGENERATOR_H

#include <vector>
#include <QPointF>
#include "Eigen/Dense"

using namespace Eigen;

class HermiteSplineGenerator {
private:
    Matrix<double, 4, 4> M;
    Matrix<double, 4, 2> G;
    Matrix<double, 4, 2> C;

public:
    HermiteSplineGenerator(QPointF leftOrigin, QPointF rightOrigin, QPointF leftVector, QPointF rightVector) {
        M <<
            2., -2., 1., 1.,
            -3., 3., -2., -1.,
            0., 0., 1., 0.,
            1., 0., 0., 0.;

        G <<
            leftOrigin.x(), leftOrigin.y(),
            rightOrigin.x(), rightOrigin.y(),
            leftVector.x(), leftVector.y(),
            rightVector.x(), rightVector.y();

        C = M * G;
    }

    std::vector<QPointF> getDots(int cnt){
        std::vector<QPointF> res;
        for (int i = 0; i < cnt; ++i) {
            double t = i * (1.0 / (cnt - 1));
//            cout << "i: " << i << " t: " << t << endl;
            Matrix<double, 1, 4> t_vec;
            t_vec << t * t * t, t * t, t, 1;
//            cout << "t_vec:" << endl << t_vec << endl;
            Matrix<double, 1, 2> d = t_vec * C;
//            cout << res << endl << endl;
            res.emplace_back(QPointF(d(0), d(1)));
        }
        return res;
    }
};


#endif // HERMITESPLINEGENERATOR_H
