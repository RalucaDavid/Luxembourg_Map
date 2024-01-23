#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <QPushbutton>
#include <QLabel>
#include <QMouseEvent>
#include <QVBoxLayout>
#include "XmlReader.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    void DrawArches(QPainter& paint);
    void DrawNode(QPainter& paint,Node*& node);
    void PositioningElements();
    Node* SearchClosestNode(Node* seek);
public slots:
    void OnDijkstraClicked();
    void OnResetClicked();
private:
    Ui::MainWindowClass ui;
    Graph graph;
    QString xmlFilePath;
    XmlReader xmlReader;
    Node* sourceNode, * destinationNode;
    QPushButton* dijkstraButton,* resetButton;
    QLabel* idSourceNode,* idDestinationNode,*totalLength;
};
