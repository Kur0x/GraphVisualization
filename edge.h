#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

class Node;
class GraphWidget;

class Edge : public QGraphicsItem
{
public:
    Edge(Node *sourceNode, Node *destNode,GraphWidget *graphWidget);
    QPainterPath shape() const override;
    void SetColor(QColor color);
    Node *sourceNode() const;
    Node *destNode() const;
    void remove();
    void adjust();

//    enum { Type = UserType + 2 };
//    int type() const override { return Type; }

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private:
    Node *source, *dest;
    GraphWidget *graph;
    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;
    QColor color;
};
//! [0]

#endif // EDGE_H
