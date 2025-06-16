#include "MainWindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), agent(nullptr), env(nullptr), timer(new QTimer(this)), stepCount(0),
      state_dim(4), sensory_dim(4), state_lr(0.02), model_lr(0.01), noise(0.2), goal_attraction(0.08), num_steps(100)
{
    setupUI();
    resetSimulation();
    connect(timer, &QTimer::timeout, this, &MainWindow::stepSimulation);
}

MainWindow::~MainWindow() {
    delete agent;
    delete env;
}

void MainWindow::setupUI() {
    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    // Chart setup
    chart = new QChart();
    agentSeries = new QLineSeries();
    envSeries = new QLineSeries();
    goalSeries = new QLineSeries();
    freeEnergySeries = new QLineSeries();
    chart->addSeries(agentSeries);
    chart->addSeries(envSeries);
    chart->addSeries(goalSeries);
    chart->addSeries(freeEnergySeries);
    chart->setTitle("FEP Simulation");
    axisX = new QValueAxis;
    axisY = new QValueAxis;
    axisX->setTitleText("Step");
    axisY->setTitleText("Value");
    chart->setAxisX(axisX, agentSeries);
    chart->setAxisY(axisY, agentSeries);
    chart->setAxisX(axisX, envSeries);
    chart->setAxisY(axisY, envSeries);
    chart->setAxisX(axisX, goalSeries);
    chart->setAxisY(axisY, goalSeries);
    chart->setAxisX(axisX, freeEnergySeries);
    chart->setAxisY(axisY, freeEnergySeries);
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    mainLayout->addWidget(chartView);

    // Controls
    QHBoxLayout *controls = new QHBoxLayout();
    startButton = new QPushButton("Start");
    pauseButton = new QPushButton("Pause");
    resetButton = new QPushButton("Reset");
    controls->addWidget(startButton);
    controls->addWidget(pauseButton);
    controls->addWidget(resetButton);
    mainLayout->addLayout(controls);

    connect(startButton, &QPushButton::clicked, this, &MainWindow::onStart);
    connect(pauseButton, &QPushButton::clicked, this, &MainWindow::onPause);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::onReset);

    setCentralWidget(central);
    setWindowTitle("Free Energy Principle Simulation");
    resize(800, 600);
}

void MainWindow::resetSimulation() {
    if (agent) delete agent;
    if (env) delete env;
    agent = new Agent(state_dim, sensory_dim, state_lr, model_lr);
    env = new Environment(sensory_dim, noise, goal_attraction);
    stepCount = 0;
    agentSeries->clear();
    envSeries->clear();
    goalSeries->clear();
    freeEnergySeries->clear();
    updatePlots();
}

void MainWindow::onStart() {
    timer->start(50); // 20 FPS
}

void MainWindow::onPause() {
    timer->stop();
}

void MainWindow::onReset() {
    timer->stop();
    resetSimulation();
}

void MainWindow::stepSimulation() {
    if (stepCount >= num_steps) {
        timer->stop();
        return;
    }
    std::vector<double> sensory_input = env->get_sensory_input();
    agent->update_state(sensory_input);
    agent->update_model();
    std::vector<double> action = agent->act();
    env->step(action);
    double free_energy = agent->calculate_free_energy();
    // For plotting, use the first dimension of each state as a representative
    agentSeries->append(stepCount, agent->get_state()[0]);
    envSeries->append(stepCount, env->get_state()[0]);
    goalSeries->append(stepCount, env->get_goal_state()[0]);
    freeEnergySeries->append(stepCount, free_energy);
    stepCount++;
    updatePlots();
}

void MainWindow::updatePlots() {
    axisX->setRange(0, std::max(num_steps, stepCount+10));
    axisY->setRange(-5, 5);
    chart->update();
} 