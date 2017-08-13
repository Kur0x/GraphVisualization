#include "edge.h"
#include "node.h"
#include "graphwidget.h"
#include "mainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QLinearGradient>
#include <QDebug>

Node::Node(GraphWidget *graphWidget, QString text)
    : graph(graphWidget),text(text),penWidth(1),highlight(false)
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    color=Qt::yellow;
    color2=Qt::white;
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
    highlight=!highlight;
    update();

}


QRectF Node::boundingRect() const
{
    return QRectF( -50 , -10 , 100, 40 );
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem * /* option */, QWidget *)
{

    painter->setRenderHint(QPainter::Antialiasing, true);
    QLinearGradient linearGradient(-10,0, 10, 0);
    linearGradient.setColorAt(0, color);
    linearGradient.setColorAt(0.499,color);
    linearGradient.setColorAt(0.501,color2);
    linearGradient.setColorAt(1.0, color2);

    if(highlight)
        painter->setBrush(Qt::red);
    else if(color2!=Qt::white)
        painter->setBrush(QBrush(linearGradient));
    else
        painter->setBrush(color);


    painter->setPen(QPen(Qt::black,penWidth));
    painter->drawEllipse(-10, -10, 20, 20);
    QRectF rect(-50,10,100,20);
    painter->setFont(QFont("微软雅黑", 13));
    painter->drawText(rect,Qt::AlignCenter,text);
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (Edge *edge, edgeList)
            edge->adjust();
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
            graph->setNodeToAddEdge(this,1);
            select2=true;
        }
        else{
            graph->setNodeToAddEdge(this,2);
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
    else{
        graph->select(this);
    }
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

QColor Node::getColor2() const
{
    return color2;
}

void Node::setColor2(const QColor &value)
{
    color2 = value;
    update();
}

qreal Node::getPenWidth() const
{
    return penWidth;
}

void Node::setPenWidth(const qreal &value)
{
    penWidth = value;
    update();
}

QColor Node::getColor() const
{
    return color;
}

void Node::setColor(const QColor &value)
{
    color = value;
    update();
}

QString Node::getText() const
{
    return text;
}

void Node::setText(const QString &value)
{
    text = value;
    update();
}
