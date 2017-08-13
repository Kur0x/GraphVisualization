#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>

class Node;
class Edge;
class MainWindow;
class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(MainWindow *parent);
    GraphWidget(MainWindow *parent,qreal w, qreal h);
    void save(const QString &fileName);
    void addNode(QString text,qreal x,qreal y,QColor color = Qt::yellow,QColor color2 = Qt::white);
    void setSceneRect(qreal w, qreal h);
    void autoArrange();
    void setNodeToAddEdge(Node *node,int no);
    void addEdge(Node *node1,Node *node2);
    void addEdge();
    void removeItem(QGraphicsItem * item);
    bool addEdgeFun=false;
    bool addNodeFun=false;
    bool EraserFun=false;
    void open(const QString &fileName);
    void select(Node* node);
    Node *getNode() const;
    void setNode(Node *value);
    void removeEdge(Edge *edge);
public slots:
    void addNodeSlot(bool b);
    void addEdgeSlot(bool b);
    void eraserSlot(bool b);
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event) override;
//    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *event) override;
#endif
//    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void scaleView(qreal scaleFactor);


private:

    MainWindow *window;
    QList<Node*> nodes;
    QList<Edge*> edges;
    QGraphicsScene *scene;
    Node *node;
    Node *node1;
    Node *node2;
};

#endif // GRAPHWIDGET_H
