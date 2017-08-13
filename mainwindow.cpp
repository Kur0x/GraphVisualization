#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "node.h"
#include "edge.h"
#include "graphwidget.h"

#include <QToolBar>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QPushButton>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    widget = new GraphWidget(this,700,700);
    ui->setupUi(this);
    setWindowTitle("GraphVisualization");
    ui->graphLayout->addWidget(widget);
    createToolBar();    //创建一个工具栏

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setNodeAttr(Node *node)
{
    QPalette p,q;
    p.setColor(QPalette::Button, node->getColor());
    qDebug()<<node->getColor();
    ui->setColorButton->setPalette(p);
    ui->setColorButton->setFlat(true);
    q.setColor(QPalette::Button, node->getColor2());
    ui->setColorButton_2->setPalette(q);
    if(node->getColor2()==Qt::white)
        ui->setColorButton_2->setFlat(false);
    else
        ui->setColorButton_2->setFlat(true);

    ui->name->setText(node->getText());
}


//创建工具栏的实现
void MainWindow::createToolBar()
{
    //首先得到一个工具栏
    QToolBar *toolBar = this->addToolBar("Tool");

    QActionGroup *anActionGroup = new QActionGroup(this);

    const QIcon selectIcon =  QIcon(":/images/icons8-Cursor-64.png");
    QAction *selectAct = new QAction(selectIcon, tr("Select"), anActionGroup);
    selectAct->setStatusTip(tr("Please click the graph area to create a new node"));


    const QIcon addNodeIcon =  QIcon(":/images/icons8-Circle-64.png");
    QAction *addNodeAct = new QAction(addNodeIcon, tr("Node"), anActionGroup);
    addNodeAct->setStatusTip(tr("Please click the graph area to create a new node"));
    connect(addNodeAct, &QAction::toggled, widget, &GraphWidget::addNodeSlot);

    const QIcon addEdgeIcon =  QIcon(":/images/icons8-Line-64.png");
    QAction *addEdgeAct = new QAction(addEdgeIcon, tr("Edge"), anActionGroup);
    addEdgeAct->setStatusTip(tr("Please click two nodes to add a new edge"));
    connect(addEdgeAct, &QAction::toggled, widget, &GraphWidget::addEdgeSlot);

    const QIcon EraserIcon =  QIcon(":/images/icons8-Eraser-48.png");
    QAction *EraserAct = new QAction(EraserIcon, tr("Eraser"), anActionGroup);
    EraserAct->setStatusTip(tr("Please click a node or edge to delete"));
    connect(EraserAct, &QAction::toggled, widget, &GraphWidget::eraserSlot);

    foreach(QAction *action,anActionGroup->actions())
        action->setCheckable(true);
    selectAct->trigger();
    toolBar->addActions(anActionGroup->actions());

}


void MainWindow::on_testButton_clicked()
{

}

void MainWindow::on_open_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"","",tr("Graph (*.graph)"));
    widget->open(fileName);
}

void MainWindow::on_save_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,"","",tr("Graph (*.graph)"));
    widget->save(fileName);

}

void MainWindow::on_setColorButton_clicked()
{
    QColor chosenColor = QColorDialog::getColor();
    QPalette p;
    p.setColor(QPalette::Button, chosenColor);
//    qDebug()<<chosenColor;
    ui->setColorButton->setPalette(p);
//    ui->setColorButton->setAutoFillBackground(true);
    if(widget->getNode()){
        widget->getNode()->setColor(chosenColor);
    }
}

void MainWindow::on_name_textChanged(const QString &arg1)
{
        if(widget->getNode()){
            widget->getNode()->setText(arg1);
            widget->update();
        }
}

void MainWindow::on_setColorButton_2_clicked()
{
    QColor chosenColor = QColorDialog::getColor();
    QPalette p;
    p.setColor(QPalette::Button, chosenColor);
    ui->setColorButton_2->setPalette(p);
    ui->setColorButton_2->setFlat(true);
    if(widget->getNode()){
        widget->getNode()->setColor2(chosenColor);
    }
}
