#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QWidget>
#include <QToolButton>

namespace Ui {
class MainWindow;
}
class GraphWidget;
class Node;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setNodeAttr(Node* node);
    friend class GraphWidget;
private slots:
    void on_testButton_clicked();

    void on_open_triggered();

    void on_save_triggered();

    void on_setColorButton_clicked();

    void on_name_textChanged(const QString &arg1);

    void on_setColorButton_2_clicked();

private:
    Ui::MainWindow *ui;
    GraphWidget *widget;
    void createToolBar();
};

#endif // MAINWINDOW_H
