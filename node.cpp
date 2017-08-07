#include "edge.h"
#include "node.h"
#include "graphwidget.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

Node::Node(GraphWidget *graphWidget)
    : graph(graphWidget)
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    color=Qt::yellow;
}

void Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}
void Node::removeEdge(Edge *edge)
{
    edgeList.removeOne(edge);
    edge->adjust();
}

QList<Edge *> Node::edges() const
{
    return edgeList;
}

void Node::click()
{
    color=(color==Qt::yellow?Qt::red:Qt::yellow);
    update();

}

QRectF Node::boundingRect() const
{
    return QRectF( -10 , -10 , 23, 23 );
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem * /* option */, QWidget *)
{


    painter->setBrush(color);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (Edge *edge, edgeList)
            edge->adjust();
        graph->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    static bool select2=false;
    if(graph->addEdgeFun){
        if(!select2){
            graph->setNode(this,1);
            select2=true;
        }
        else{
            graph->setNode(this,2);
            select2=false;
            graph->addEdge();
        }
    }
    else if(graph->EraserFun){
        qDebug()<<"delete node";
        foreach (Edge *edge, edgeList) {
            edge->remove();
        }
        graph->removeItem(this);
    }
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
