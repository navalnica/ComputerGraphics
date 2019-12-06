#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <vector>

#include "tangent.h"

class PaintScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit PaintScene(QObject *parent = nullptr);
    ~PaintScene() override;
    void clearScene();

protected:
    std::vector<Tangent> tangents;

    QPen splinePen;
    int splineDotsCnt = 200;
    std::vector<QGraphicsLineItem*> curSplineLines;

    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void drawHermiteSpline();
};

#endif // PAINTSCENE_H
