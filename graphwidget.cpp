#include "graphwidget.h"
#include "mainwindow.h"
#include "edge.h"
#include "node.h"

#include <math.h>

#include <QApplication>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>
GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent), timerId(0)
{
    scene = new QGraphicsScene(this);
    //    QGraphicsView::fitInView();
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    //    int a=parent->frameSize().width();
    scene->setSceneRect(0, 0,400 ,400);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    //    scale(qreal(1), qreal(1));

    setMinimumSize(400, 400);

    //    Node *node1 = new Node(this);
    //    Node *node2 = new Node(this);
    //    nodes<<node1;
    //    nodes<<node2;
    //    scene->addItem(node1);
    //    scene->addItem(node2);

    //    scene->addItem(new Edge(node1, node2));


    //    node1->setPos(50, 50);
    //    node2->setPos(0, 0);

}

void GraphWidget::setNode(Node *node, int no)
{
    if(no==1){
        node1=node;
    }
    else{
        node2=node;
    }
    node->click();
}

void GraphWidget::addEdge()
{
    bool already_connected=false;
    for(const Edge *edge : node1->edges()){
        if(edge->destNode()==node2){
            already_connected=true;
            break;
        }
    }
    if(!(node1==node2||already_connected))
        scene->addItem(new Edge(node1, node2));
    node1->click();
    node2->click();
    node1=NULL;
    node2=NULL;
}

void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}

void GraphWidget::addNodeSlot(bool b)
{
    addNodeFun=b;
}

void GraphWidget::addEdgeSlot(bool b)
{
    addEdgeFun=b;
}


void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    //!TODO: add
    switch (event->key()) {
    case Qt::Key_Up:
        //        centerNode->moveBy(0, -20);
        break;
    case Qt::Key_Down:
        //        centerNode->moveBy(0, 20);
        break;
    case Qt::Key_Left:
        //        centerNode->moveBy(-20, 0);
        break;
    case Qt::Key_Right:
        //        centerNode->moveBy(20, 0);
        break;
    case Qt::Key_Plus:
        //        zoomIn();
        break;
    case Qt::Key_Minus:
        //        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void GraphWidget::mousePressEvent(QMouseEvent *event)
{
    if(addNodeFun){
        Node *node=new Node(this);
        node->setPos(event->pos().x()-5,event->pos().y()-22);
        nodes<<node;
        scene->addItem(node);
    }
    //    if(addEdge){
    //        QWidget *action = QApplication::widgetAt(event->globalPos());
    //        qDebug()<<action;

    //    }
    QGraphicsView::mousePressEvent(event);
}

//void GraphWidget::resizeEvent(QResizeEvent *event)
//{

//        fitInView(scene->sceneRect());;
//        qreal x=scene->sceneRect().x();
//                qreal y=scene->sceneRect().y();
//    QGraphicsView::resizeEvent(event);
//}



//#ifndef QT_NO_WHEELEVENT

//void GraphWidget::wheelEvent(QWheelEvent *event)
//{
//    scaleView(pow((double)2, event->delta() / 240.0));
//}

//#endif

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    //    // Shadow
    QRectF sceneRect = this->sceneRect();
    //    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    //    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    //    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
    //        painter->fillRect(rightShadow, Qt::darkGray);
    //    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
    //        painter->fillRect(bottomShadow, Qt::darkGray);

    //     Fill

    painter->fillRect(rect.intersected(sceneRect), Qt::white);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

    // Text
    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
                    sceneRect.width() - 4, sceneRect.height() - 4);
    QString message(tr("Click and drag the nodes around, and zoom with the mouse "
                       "wheel or the '+' and '-' keys"));

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(textRect.translated(2, 2), message);
    painter->setPen(Qt::black);
    painter->drawText(textRect, message);
}

//void GraphWidget::scaleView(qreal scaleFactor)
//{
//    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
//    if (factor < 0.07 || factor > 100)
//        return;

//    scale(scaleFactor, scaleFactor);
//}

//void GraphWidget::zoomIn()
//{
//    scaleView(qreal(1.2));
//}

//void GraphWidget::zoomOut()
//{
//    scaleView(1 / qreal(1.2));
//}
