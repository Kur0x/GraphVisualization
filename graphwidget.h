#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>

class Node;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);
    void setNode(Node *node,int no);
    void addEdge();
    void removeItem(QGraphicsItem * item);
    void itemMoved();
    bool addEdgeFun=false;
    bool addNodeFun=false;
    bool EraserFun=false;
public slots:
    void addNodeSlot(bool b);
    void addEdgeSlot(bool b);
    void EraserSlot(bool b);
//    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event) override;
//    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
//#ifndef QT_NO_WHEELEVENT
//    void wheelEvent(QWheelEvent *event) override;
//#endif
    void drawBackground(QPainter *painter, const QRectF &rect) override;

//    void scaleView(qreal scaleFactor);


private:
    int timerId;
    QList<Node*> nodes;
    QGraphicsScene *scene;
    Node *node1;
    Node *node2;
};

#endif // GRAPHWIDGET_H
