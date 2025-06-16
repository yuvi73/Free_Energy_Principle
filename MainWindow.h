#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include "Agent.h"
#include "Environment.h"

QT_CHARTS_USE_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void stepSimulation();
    void onStart();
    void onPause();
    void onReset();

private:
    Agent* agent;
    Environment* env;
    QTimer* timer;
    int stepCount;

    // Charting
    QChartView* chartView;
    QChart* chart;
    QLineSeries* agentSeries;
    QLineSeries* envSeries;
    QLineSeries* goalSeries;
    QLineSeries* freeEnergySeries;
    QValueAxis* axisX;
    QValueAxis* axisY;

    // Controls
    QPushButton* startButton;
    QPushButton* pauseButton;
    QPushButton* resetButton;

    // Parameters
    int state_dim;
    int sensory_dim;
    double state_lr;
    double model_lr;
    double noise;
    double goal_attraction;
    int num_steps;

    void setupUI();
    void resetSimulation();
    void updatePlots();
};

#endif // MAINWINDOW_H 