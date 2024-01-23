#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    xmlFilePath = QString("Harta_Luxemburg.xml");
    xmlReader.SetFilePath(xmlFilePath);
    if(!xmlReader.ReadData(graph))
        qDebug() << "Something went wrong with the reading.";
    sourceNode = nullptr;
    destinationNode = nullptr;
    ui.setupUi(this);
    dijkstraButton = new QPushButton("Dijkstra",this);
    resetButton = new QPushButton("Reset",this);
    idSourceNode = new QLabel("Id Source Node: None",this);
    idDestinationNode = new QLabel("Id Destination Node: None",this);
    totalLength = new QLabel("Total length: 0",this);
    PositioningElements();
    connect(dijkstraButton, &QPushButton::clicked, this, &MainWindow::OnDijkstraClicked);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::OnResetClicked);
}

MainWindow::~MainWindow()
{}

void MainWindow::paintEvent(QPaintEvent * event)
{
    QPainter paint(this);
    DrawArches(paint);
    paint.setRenderHint(QPainter::Antialiasing);
    if (sourceNode)
        DrawNode(paint, sourceNode);
    if (destinationNode)
        DrawNode(paint, destinationNode);
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if ((event->button() == Qt::RightButton)&&(sourceNode==nullptr))
    {
        Node* seek1 = new Node;
        seek1->SetCoordinates({event->pos().x(),event->pos().y()});
        Node* nodeFound = SearchClosestNode(seek1);
        sourceNode = nodeFound;
        idSourceNode->setText("Id Source Node: " + QString::fromUtf8(std::to_string(sourceNode->GetValue()).c_str()));
    }
    else if ((event->button() == Qt::LeftButton) && (destinationNode == nullptr))
    {
        Node* seek2 = new Node;
        seek2->SetCoordinates({ event->pos().x(),event->pos().y() });
        Node* nodeFound = SearchClosestNode(seek2);
        destinationNode = nodeFound;
        idDestinationNode->setText("Id Destination Node: " + QString::fromUtf8(std::to_string(destinationNode->GetValue()).c_str()));
    }
    update();
}

void MainWindow::DrawArches(QPainter& paint)
{
    std::vector<Arch*> arches = graph.GetArches();
    QPen pen;
    QPen defaultPen = paint.pen();
    paint.setRenderHint(QPainter::Antialiasing);
    for (Arch*& arch: arches)
    {
        if (arch->GetColor() == 1)
        {
            pen.setWidth(3);
            pen.setColor(Qt::red);
        }
        else
        {
            pen = defaultPen;
            pen.setColor(Qt::black);
        }
        paint.setPen(pen);
        QPoint startP(arch->GetSourceNode()->GetCoordinates().first, arch->GetSourceNode()->GetCoordinates().second);
        QPoint endP(arch->GetDestinationNode()->GetCoordinates().first, arch->GetDestinationNode()->GetCoordinates().second);
        paint.drawLine(startP, endP);
    }
    update();
}

void MainWindow::DrawNode(QPainter& paint,Node*& node)
{
    QPoint P(node->GetCoordinates().first, node->GetCoordinates().second);
    QPen pen;
    pen.setColor(Qt::red);
    paint.setPen(pen);
    QBrush brush(Qt::red);
    paint.setBrush(brush);
    paint.drawEllipse(P, 5, 5);
    update();
}

void MainWindow::PositioningElements()
{
    dijkstraButton->setGeometry(920, 10, 70, 30);
    resetButton->setGeometry(1000, 10, 70, 30);
    idSourceNode->setGeometry(920, 50, 200, 20);
    idDestinationNode->setGeometry(920, 80, 200, 20);
    totalLength->setGeometry(920, 110, 200, 20);
}

Node* MainWindow::SearchClosestNode(Node* seek)
{
    float distance = std::numeric_limits<double>::max();
    Node* nodeFound=nullptr;
    for (Node*& node : graph.GetNodes())
    {
        if (std::abs(*seek - node) < distance)
        {
            distance = std::abs(*seek - node);
            nodeFound = node;
        }
    }
    return nodeFound;
}

void MainWindow::OnResetClicked()
{
    sourceNode = nullptr;
    destinationNode = nullptr;
    if (graph.GetPathDijkstra().empty())
        return;
    for (Arch*& arch : graph.GetPathDijkstra())
        arch->SetColor(0);
    idSourceNode->setText("Id Source Node: None");
    idDestinationNode->setText("Id Destination Node: None");
    totalLength->setText("Total length: 0");
    update();
}

void  MainWindow::OnDijkstraClicked()
{
    if ((sourceNode != nullptr) && (destinationNode != nullptr))
    {
        graph.Dijkstra(sourceNode, destinationNode);
        totalLength->setText("Total length: " + QString::number(graph.GetTotalLength()));
    }
}
