#include "edge.h"
#include "node.h"
#include "graphwidget.h"

#include <math.h>
#include <QVector>
#include <QPainter>
#include <QPolygonF>
#include <QPointF>
#include <QPoint>
#include <QDebug>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;


Edge::Edge(Node *sourceNode, Node *destNode,GraphWidget *graphWidget)
    : arrowSize(10), graph(graphWidget)
{
//    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);

//    setAcceptedMouseButtons(0);
    source = sourceNode;
    dest = destNode;
    source->addEdge(this);
    dest->addEdge(this);
    adjust();
}

QPainterPath Edge::shape() const
{
    QPainterPath path;
    QVector<QPointF> points;
    QLineF line(sourcePoint, destPoint);
    double ExpandSize = 10;
    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = 2*Pi - angle;
    QPointF P1 = sourcePoint + QPointF(sin(angle + Pi / 3) * ExpandSize,
                                                  cos(angle + Pi / 3) * ExpandSize);
    QPointF P2 = sourcePoint + QPointF(sin(angle + Pi - Pi / 3) * ExpandSize,
                                                  cos(angle + Pi - Pi / 3) * ExpandSize);
    QPointF P3 = destPoint + QPointF(sin(angle - Pi / 3) * ExpandSize,
                                              cos(angle - Pi / 3) * ExpandSize);
    QPointF P4 = destPoint + QPointF(sin(angle - Pi + Pi / 3) * ExpandSize,
                                              cos(angle - Pi + Pi / 3) * ExpandSize);

    points << P1 << P2 << P3 << P4;
    QPolygonF p(points);
    path.addPolygon(p);
    return path;
}

Node *Edge::sourceNode() const
{
    return source;
}

Node *Edge::destNode() const
{
    return dest;
}

void Edge::remove()
{
    source->removeEdge(this);
    dest->removeEdge(this);
    graph->removeItem(this);
}

void Edge::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.)) {
        QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
        sourcePoint = line.p1() + edgeOffset;
        destPoint = line.p2() - edgeOffset;
    } else {
        sourcePoint = destPoint = line.p1();
    }
}



QRectF Edge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

}

void Edge::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(graph->EraserFun){
        qDebug()<<"delete edge";
        remove();
//        delete this;
    }

    update();
    QGraphicsItem::mousePressEvent(event);
}
