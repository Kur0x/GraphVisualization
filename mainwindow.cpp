#include "mainwindow.h"
#include "edge.h"
#include "graphwidget.h"
#include "ui_mainwindow.h"

#include <QToolBar>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    widget = new GraphWidget;
    ui->setupUi(this);

    ui->gridLayout->addWidget(widget);
     createToolBar();    //创建一个工具栏
}

MainWindow::~MainWindow()
{
    delete ui;
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


    const QIcon addNodeIcon =  QIcon(":/images/icons8-Circle-32.png");
    QAction *addNodeAct = new QAction(addNodeIcon, tr("Node"), anActionGroup);
    addNodeAct->setStatusTip(tr("Please click the graph area to create a new node"));
    connect(addNodeAct, &QAction::toggled, widget, &GraphWidget::addNodeSlot);

    const QIcon addEdgeIcon =  QIcon(":/images/icons8-Line-32.png");
    QAction *addEdgeAct = new QAction(addEdgeIcon, tr("Edge"), anActionGroup);
    addEdgeAct->setStatusTip(tr("Please click two nodes to add a new edge"));
    connect(addEdgeAct, &QAction::toggled, widget, &GraphWidget::addEdgeSlot);

    foreach(QAction *action,anActionGroup->actions())
        action->setCheckable(true);
    selectAct->trigger();
    toolBar->addActions(anActionGroup->actions());

}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "C2ebug Message";
}
