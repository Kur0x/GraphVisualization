#include "graphwidget.h"
#include "mainwindow.h"
#include "edge.h"
#include "node.h"

#include <math.h>

#include <QApplication>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMessageBox>
#include <QFile>
#include <QDataStream>
#include <QDebug>
GraphWidget::GraphWidget(MainWindow *parent)
    : window(parent),node(nullptr),node1(nullptr),node2(nullptr)
{
    scene = new QGraphicsScene(this);
    //    QGraphicsView::fitInView();
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    //    int a=parent->frameSize().width();
    scene->setSceneRect(0, 0,400,400);
    //    scene->setSceneRect(0,0
    //    ,static_cast<QWidget *>(scene->parent())->size().width()
    //    ,static_cast<QWidget *>(scene->parent())->size().height());
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    //    setMinimumSize(400, 400);


}

GraphWidget::GraphWidget(MainWindow *parent, qreal w, qreal h)
    : window(parent),node(nullptr),node1(nullptr),node2(nullptr)
{
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0,w,h);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
}

void GraphWidget::save(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly)){
        QMessageBox::warning(this,"warning","file not open");
        return;
    }
    QDataStream out(&file);
    out << nodes.size();
    foreach (Node * node, nodes) {
        out<<node->pos().x();
        out<<node->pos().y();
        out<<node->getText();
        out<<node->getColor();
        out<<node->getColor2();
    }
    out<<edges.size();
    foreach (Edge *edge, edges) {
        out <<nodes.indexOf(edge->sourceNode());
        out <<nodes.indexOf(edge->destNode());
    }
}
void GraphWidget::open(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly)){
        QMessageBox::warning(this,"warning","file not open");
        return;
    }
    QDataStream in(&file);
    int n;
    in >>n;
    for(int i=0;i<n;i++){
        qreal x,y;
        QString text;
        in >> x >>y;
        in >>text;
        QColor color;
        QColor color2;
        in>>color>>color2;
        addNode(text,x,y,color,color2);
    }
    in >>n;
    for(int i=0;i<n;i++){
        int a,b;
        in >> a >>b;
        addEdge(nodes[a],nodes[b]);
    }
}

void GraphWidget::select(Node *node)
{
    if(this->node==nullptr){
        node->setPenWidth(2);
    }
    else{
        if(this->node==node&&this->node->getPenWidth()==2)
            node->setPenWidth(1);
        else{
            this->node->setPenWidth(1);
            node->setPenWidth(2);
//            this->node->update();
//            node->update();
        }
    }
    this->node=node;
    window->setNodeAttr(node);
//    window->print(1);
//    foreach (Node* node, nodes) {
//        qDebug()<<node->getPenWidth();
//    }
//    qDebug()<<"!!!!!";
//    update();
}

void GraphWidget::addNode(QString text, qreal x, qreal y,QColor color,QColor color2)
{
    Node *node=new Node(this,text);
    node->setPos(x,y);
    node->setColor(color);
    node->setColor2(color2);
    scene->addItem(node);
    nodes<<node;
}

void GraphWidget::setSceneRect(qreal w, qreal h)
{
    scene->setSceneRect(0, 0,w,h);
}

void GraphWidget::autoArrange()
{
    int size=sqrt(nodes.size()-0.1);
    int dx=scene->width()/(size+1);
    int dy=scene->height()/(size+1);
    for(int i=0;i<nodes.size();i++){
        nodes[i]->setPos(i%(size+1)*dx+10,i/(size+1)*dy+10);
    }
    update();
}

void GraphWidget::setNodeToAddEdge(Node *node, int no)
{
    if(no==1){
        node1=node;
    }
    else{
        node2=node;
    }
    node->click();
}

void GraphWidget::addEdge(Node *node1, Node *node2)
{
    setNodeToAddEdge(node1, 1);
    setNodeToAddEdge(node2, 2);
    addEdge();
}
void GraphWidget::removeItem(QGraphicsItem * item){
    scene->removeItem(item);
    update();
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
    if(!(node1==node2||already_connected)){
        Edge *edge=new Edge(node1, node2,this);
        scene->addItem(edge);
        edges << edge;
    }
    node1->click();
    node2->click();
    node1=NULL;
    node2=NULL;
    update();
}



void GraphWidget::addNodeSlot(bool b)
{
    addNodeFun=b;
}

void GraphWidget::addEdgeSlot(bool b)
{
    addEdgeFun=b;
}

void GraphWidget::eraserSlot(bool b)
{
    EraserFun=b;
}


void GraphWidget::keyPressEvent(QKeyEvent *event)
{
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
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
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
        node->setPos(mapToScene(event->pos()));
        nodes<<node;
        scene->addItem(node);
    }
    QGraphicsView::mousePressEvent(event);
}

//void GraphWidget::resizeEvent(QResizeEvent *event)
//{

//    scene->setSceneRect(this->rect());

////    fitInView(scene->sceneRect(), Qt::IgnoreAspectRatio);


////        fitInView(scene->sceneRect());;
//    QGraphicsView::resizeEvent(event);
//}



#ifndef QT_NO_WHEELEVENT

void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, event->delta() / 240.0));
}

#endif

//void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
//{
//    Q_UNUSED(rect);

//    QRectF sceneRect = this->sceneRect();



//    painter->fillRect(rect.intersected(sceneRect), Qt::white);
//    painter->setBrush(Qt::NoBrush);
//    painter->drawRect(sceneRect);

//    // Text
//    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
//                    sceneRect.width() - 4, sceneRect.height() - 4);
//    QString message(tr("Click and drag the nodes around, and zoom with the mouse "
//                       "wheel or the '+' and '-' keys"));

//    QFont font = painter->font();
//    font.setBold(true);
//    font.setPointSize(14);
//    painter->setFont(font);
//    painter->setPen(Qt::lightGray);
//    painter->drawText(textRect.translated(2, 2), message);
//    painter->setPen(Qt::black);
//    painter->drawText(textRect, message);
//}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

Node *GraphWidget::getNode() const
{
    return node;
}

void GraphWidget::setNode(Node *value)
{
    node = value;
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void GraphWidget::removeEdge(Edge *edge)
{
    edges.removeOne(edge);
}
