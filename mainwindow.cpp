#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->firstTime = true;

//    qRegisterMetaType<QVector<double> >("QVector<double>");
    connect(this, SIGNAL(signalMemoryGraph()), SLOT(slotMemoryGraph()));
    connect(this,SIGNAL(signalCPUGraph()),SLOT(slotCPUGraph()));
    connect(this, SIGNAL(signalSupplyGraph()), SLOT(slotSupplyGraph()));
    connect(this, SIGNAL(signalProcGraph()), SLOT(slotProcGraph()));

    configMemoryGraph();
    configCPUGraph();
    configSupplyGraph();
    configProcGraph();

    run();

//    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
//    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
//    dataTimer.start(0); // Interval 0 means to refresh as fast as possible

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::run(){
    if(this->firstTime){
        this->thMemory = std::thread(&MainWindow::memoryGraph, this);
        this->thCPU = std::thread(&MainWindow::CPUGraph, this);
        this->thSupply = std::thread(&MainWindow::SupplyGraph, this);
        this->thProc = std::thread(&MainWindow::procGraph, this);
        this->firstTime = false;
    }
}

void MainWindow::configMemoryGraph(){
    ui->grafMEM->addGraph();
    ui->grafMEM->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->grafMEM->graph(0)->setName("Memory");

    ui->grafMEM->addGraph();
    ui->grafMEM->graph(1)->setPen(QPen(QColor(255, 110, 40)));
    ui->grafMEM->graph(1)->setName("Swap");

    ui->grafMEM->legend->setVisible(true);

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");

    ui->grafMEM->xAxis->setTicker(timeTicker);
    ui->grafMEM->axisRect()->setupFullAxesBox();
    ui->grafMEM->yAxis->setRange(-0.3, 100.3);

    connect(ui->grafMEM->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->grafMEM->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->grafMEM->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->grafMEM->yAxis2, SLOT(setRange(QCPRange)));

}

void MainWindow::configCPUGraph(){
    QVector<QColor> colors;
    colors.append(QColor(255, 140, 0));
    colors.append(Qt::red);
    colors.append(Qt::green);
    colors.append(Qt::blue);
    colors.append(Qt::black);
    colors.append(Qt::yellow);

    QString name = "CPU";
    for(int i = 0; i < this->cpu.getNumCPUs(); i++){
        ui->grafCPU->addGraph();
        ui->grafCPU->graph(i)->setPen(QPen(colors.at(i)));
        ui->grafCPU->graph(i)->setName(name + QString::number(i+1));
    }

    ui->grafCPU->legend->setVisible(true);

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");

    ui->grafCPU->xAxis->setTicker(timeTicker);
    ui->grafCPU->axisRect()->setupFullAxesBox();
    ui->grafCPU->yAxis->setRange(-0.3, 100.03);

    connect(ui->grafCPU->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->grafCPU->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->grafCPU->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->grafCPU->yAxis2, SLOT(setRange(QCPRange)));
}

void MainWindow::configSupplyGraph(){
    ui->grafSupply->addGraph(); // blue line
    ui->grafSupply->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->grafSupply->graph(0)->setName("Carga(%)");

    ui->grafTimeSupply->addGraph(); // blue line
    ui->grafTimeSupply->graph(0)->setPen(QPen(QColor(255, 110, 40)));
    ui->grafTimeSupply->graph(0)->setName("Tempo de Descarga");

    ui->grafSupply->legend->setVisible(true);
    ui->grafTimeSupply->legend->setVisible(true);

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");

    ui->grafSupply->xAxis->setTicker(timeTicker);
    ui->grafSupply->axisRect()->setupFullAxesBox();
    ui->grafSupply->yAxis->setRange(-0.3, 100.3);

    ui->grafTimeSupply->xAxis->setTicker(timeTicker);
    ui->grafTimeSupply->axisRect()->setupFullAxesBox();
    ui->grafTimeSupply->yAxis->setRange(-0.1, 8.1);

    connect(ui->grafSupply->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->grafSupply->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->grafSupply->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->grafSupply->yAxis2, SLOT(setRange(QCPRange)));

    connect(ui->grafTimeSupply->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->grafTimeSupply->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->grafTimeSupply->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->grafTimeSupply->yAxis2, SLOT(setRange(QCPRange)));

}

void MainWindow::configProcGraph(){
    ui->widget_3->load(QUrl::fromLocalFile("/home/yurialessandro/Documentos/C++/Gerenciador-de-Tarefas/index.html"));
}

void MainWindow::memoryGraph(){
    while(true){
        this->memory.concatenate();
        emit(signalMemoryGraph());
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void MainWindow::CPUGraph(){
    while(true){
        this->cpu.calculate();
        emit(signalCPUGraph());
        std::this_thread::sleep_for(std::chrono::milliseconds(350));
    }
}

void MainWindow::SupplyGraph(){
    while(true){
        this->supply.concatenate();
        emit(signalSupplyGraph());
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

void MainWindow::procGraph(){
    while(true){
        emit(signalProcGraph());
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

void MainWindow::slotMemoryGraph(){
    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0;

    ui->grafMEM->graph(0)->addData(key, this->memory.calculateMemory());
    ui->grafMEM->graph(1)->addData(key, this->memory.calculateSwap());

    ui->grafMEM->xAxis->setRange(key, 60, Qt::AlignRight);
    ui->grafMEM->replot();
}

void MainWindow::slotCPUGraph(){
    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0;

    for(int i = 0; i < 4; i++){
         ui->grafCPU->graph(i)->addData(key, cpu.getDataCPU(i));
    }

    ui->grafCPU->xAxis->setRange(key, 60, Qt::AlignRight);
    ui->grafCPU->replot();

}

void MainWindow::slotSupplyGraph(){
    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0;

    ui->grafSupply->graph(0)->addData(key, this->supply.calculateSupply());
    ui->grafTimeSupply->graph(0)->addData(key, this->supply.timeRemaining());

    ui->grafSupply->xAxis->setRange(key, 60, Qt::AlignRight);
    ui->grafSupply->replot();

    ui->grafTimeSupply->xAxis->setRange(key, 60, Qt::AlignRight);
    ui->grafTimeSupply->replot();
}

void MainWindow::slotProcGraph(){
    int comp = ui->comboBox->currentIndex();
    this->json.generateJson(comp);
}

void MainWindow::on_updateButton_clicked()
{
    int comp = ui->comboBox->currentIndex();
    json.update(comp);
    ui->widget_3->repaint();
    ui->widget_3->reload();
    ui->widget_3->update();
}

void MainWindow::on_killButton_clicked()
{
    int pid = ui->txtPID->text().toInt();

    std::string tm = "kill -9 " + std::to_string(pid);
    if(pid != 0) system(tm.c_str());

    ui->txtPID->setText(" ");

    this->on_updateButton_clicked();
}
