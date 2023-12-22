#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGlobal>
#include <QTime>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QCoreApplication>
#include <cmath>
#include <QDebug>
#include <QCheckBox>
#include "graphfunctions.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QIcon icon("C:\\Users\\LEGEND\\Documents\\Assignment\\qt.png");
    this->setWindowIcon(icon);

    this->setStyleSheet("background-color: #9ac2ed;");

    // Customize button styles
    QString buttonStyle = "QPushButton {"
                          "    background-color: #4CAF50; /* Green background color */"
                          "    border: none; /* No border */"
                          "    color: white; /* White text color */"

                          "    text-decoration: none; /* No underline */"

                          "    cursor: pointer; /* Cursor on hover */"
                          "    border-radius: 2px; /* Rounded corners */"
                          "    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.4); /* Subtle shadow */"
                          "}"
                          "QPushButton:hover {"
                          "    background-color: #45a049; /* Darker green on hover */"
                          "}";



    // Customize input box styles
    QString inputBoxStyle = "QLineEdit, QTextEdit {"

                            "    border-radius: 5px; /* Rounded corners */"
                            "    background-color: #FFFFFF;"
                            "    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1); /* Subtle shadow */"
                            "}";

    ui->lineEdit_vertices->setStyleSheet(inputBoxStyle);
    ui->lineEdit_density->setStyleSheet(inputBoxStyle);
    ui->node_input->setStyleSheet(inputBoxStyle);

    // Customize adjacency matrix box style
    QString adjacencyMatrixStyle = "QTextEdit#textEdit_adjacency_matrix {"

                                   "    border-radius: 5px; /* Rounded corners */"
                                   "    background-color: #FFFFFF;"
                                   "    padding: 5px; /* Padding for better appearance */"
                                   "    box-shadow: 0 4px 8px rgba(1, 0, 0, 1); /* Subtle shadow */"
                                   "}";

    ui->textEdit_adjacency_matrix->setStyleSheet(adjacencyMatrixStyle);

    // Customize graph box style
    QString graphBoxStyle = "QGraphicsView#graphicsView {"

                            "    border-radius: 5px; /* Rounded corners */"
                             "    background-color: #FFFFFF;"
                            "    padding: 5px; /* Padding for better appearance */"
                            "    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.6); /* Subtle shadow */"
                            "}";

    ui->graphicsView->setStyleSheet(graphBoxStyle);

    // Customize neighbors box style
    QString neighborsBoxStyle = "QMessageBox#MessageBox {"
                                "    border: 1px solid #999; /* Thin border */"
                                "    border-radius: 5px; /* Rounded corners */"
                                "    padding: 5px; /* Padding for better appearance */"
                                "    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1); /* Subtle shadow */"
                                "}";

    // Set style for QMessageBox
    QMessageBox msgBox;
    msgBox.setStyleSheet(neighborsBoxStyle);

    ui->btn_generate->setStyleSheet(buttonStyle);
    ui->btn_find_neighbors->setStyleSheet(buttonStyle);

    connect(ui->btn_generate, &QPushButton::clicked, this, &MainWindow::generateGraph);
    connect(ui->btn_find_neighbors, &QPushButton::clicked, this, &MainWindow::findNeighbours);

    srand(QTime::currentTime().msec());


    // Connect the stateChanged signal of the toggleSwitch to a slot
    // connect(ui->toggleSwitch, &QCheckBox::stateChanged, this, &MainWindow::onToggleSwitchStateChanged);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateGraph()
{

        // Retrieve user input
        bool okVertices, okDensity;
        numVertices = ui->lineEdit_vertices->text().toInt(&okVertices);
        double density = ui->lineEdit_density->text().toDouble(&okDensity);
        // std::vector<std::vector<int>> adjacencyMatrix = generateAdjacencyMatrix(numVertices, density);
        adjacencyMatrix = generateAdjacencyMatrix(numVertices, density);

        QVector<QGraphicsEllipseItem*> vertices;

        if (okVertices && okDensity) {
            // Create a scene for the graph
            // numVertices = ui->lineEdit_vertices->text().toInt(&okVertices);
            QGraphicsScene* scene = new QGraphicsScene(this);
            qreal centerX = 300;
            qreal centerY = 200;
            qreal radius = 100;

            // Calculate angle increment based on the number of vertices
            qreal angleIncrement = 2.0 * M_PI / numVertices;
            qreal currentAngle = 0;

            // Example: Display vertices in a circular shape
            for (int i = 0; i < numVertices; ++i) {
                qreal x = centerX + radius * qCos(currentAngle);
                qreal y = centerY + radius * qSin(currentAngle);

                QGraphicsEllipseItem* vertex = new QGraphicsEllipseItem(x, y, 5,5);
                scene->addItem(vertex);
                vertices.append(vertex);

                // Increment the angle for the next vertex
                currentAngle += angleIncrement;
            }

            // Example: Display edges (connect vertices based on adjacency matrix)
            for (int i = 0; i < numVertices; ++i) {
                for (int j = i + 1; j < numVertices; ++j) {
                    if (adjacencyMatrix[i][j] == 1) {
                        // Get the center points of the vertices
                        QPointF centerI = vertices[i]->sceneBoundingRect().center();
                        QPointF centerJ = vertices[j]->sceneBoundingRect().center();

                        // Draw an edge between vertices i and j
                        QGraphicsLineItem* edge = new QGraphicsLineItem(centerI.x(), centerI.y(),
                                                                        centerJ.x(), centerJ.y());
                        scene->addItem(edge);
                    }
                }
            }

            QString adjacencyMatrixStr;
            for (const auto& row : adjacencyMatrix) {
                for (int value : row) {
                    adjacencyMatrixStr += QString::number(value) + " ";
                }
                adjacencyMatrixStr += "\n";
            }
            ui->textEdit_adjacency_matrix->clear();
            ui->textEdit_adjacency_matrix->insertPlainText(adjacencyMatrixStr);


            int maxDegreeNode = findMaxDegreeNode(adjacencyMatrix);
            int minDegreeNode = findMinDegreeNode(adjacencyMatrix);

            ui->label_max_degree->setText("Node with maximum degree: " + QString::number(maxDegreeNode));
            ui->label_min_degree->setText("Node with minimum degree: " + QString::number(minDegreeNode));

            // Set the scene to the QGraphicsView
            ui->graphicsView->setScene(scene);
        } else {
            // Handle invalid input
        }
    }

int MainWindow::findMaxDegreeNode(const std::vector<std::vector<int>>& adjacencyMatrix)
{
    int maxDegree = 0;
    int maxDegreeNode = -1;

    for (int i = 0; i < adjacencyMatrix.size(); ++i) {
        int degree = 0;

        for (int j = 0; j < adjacencyMatrix[i].size(); ++j) {
            if (adjacencyMatrix[i][j] == 1) {
                ++degree;
            }
        }

        if (degree > maxDegree) {
            maxDegree = degree;
            maxDegreeNode = i;
        }
    }

    return maxDegreeNode;
}
int MainWindow::findMinDegreeNode(const std::vector<std::vector<int>>& adjacencyMatrix)
{   int minDegree = std::numeric_limits<int>::max();
    int minDegreeNode = -1;

    for (int i = 0; i < adjacencyMatrix.size(); ++i) {
        int degree = 0;
        for (int j = 0; j < adjacencyMatrix[i].size(); ++j) {
            if (adjacencyMatrix[i][j] == 1) {
                ++degree;
            }
        }

        if (degree < minDegree) {
            minDegree = degree;
            minDegreeNode = i;
        }
    }

    return minDegreeNode;
}

void MainWindow::findNeighbours()
{
    // Get the user input from the QLineEdit
    QString userInput = ui->node_input->text();
    bool ok;
    int node = userInput.toInt(&ok);

    qDebug() << "Entered node: " << node;

    if (!ok) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid node number.");
        return;
    }

    // Check if the entered node is within the valid range
    if (node < 0 || node >= numVertices) {
        QMessageBox::warning(this, "Invalid Node", "Please enter a node within the valid range."); //warning shows red message box
        return;
    }

    // Find neighbors of the entered node
    QVector<int> neighbors;
    for (int i = 0; i < adjacencyMatrix[node].size(); ++i) {
        if (adjacencyMatrix[node][i] == 1) {
            neighbors.append(i);
        }
    }

    qDebug() << "Neighbors: " << neighbors;

    // Display the neighbors
    QString neighborsStr = "Neighbors of Node " + QString::number(node) + ": ";
    for (int neighbor : neighbors) {
        neighborsStr += QString::number(neighbor) + " ";
    }

    qDebug() << "Neighbors string: " << neighborsStr;

    // Display the neighbors in a QMessageBox
    QMessageBox::information(this, "Node Neighbors", neighborsStr + "\n\✨by Anns Khan✨");
}
