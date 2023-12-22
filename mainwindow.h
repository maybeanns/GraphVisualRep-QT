#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    int findMaxDegreeNode(const std::vector<std::vector<int>>& adjacencyMatrix);
    int findMinDegreeNode(const std::vector<std::vector<int>>& adjacencyMatrix);

void findNeighbours();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void generateGraph();
    void onToggleSwitchStateChanged(int state);
    std::vector<std::vector<int>> adjacencyMatrix;
    int numVertices;

};
#endif // MAINWINDOW_H
