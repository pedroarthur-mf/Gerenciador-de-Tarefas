#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // GRÁFICO DAS BOLHAS:
    ui->widget_3->load(QUrl::fromLocalFile("home/pedroarthur-mf/MeuProjeto/index.html"));


    //GRÁFICO DO USO DE CPU DO COMPUTADOR:
    QVector<QColor> colors;
    colors.append(Qt::red);
    colors.append(Qt::blue);
    colors.append(Qt::black);
    colors.append(Qt::green);
    colors.append(Qt::yellow);
    colors.append(Qt::magenta);
    this->cpu.concatenate();
    QString name = "CPU";
    for(int i = 0; i < this->cpu.getNumCPUs(); i++){
        ui->grafCPU->addGraph();
        ui->grafCPU->graph(i)->setPen(QPen(colors.at(i)));
        ui->grafCPU->graph(i)->setName(name + QString::number(i));
    }

    // GRÁFICO DO USO DE MEMÓRIA DO COMPUTADOR:
    ui->grafMEM->addGraph(); // blue line
    ui->grafMEM->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->grafMEM->graph(0)->setName("Memory");
    ui->grafMEM->addGraph(); // red line
    ui->grafMEM->graph(1)->setPen(QPen(QColor(255, 110, 40)));
    ui->grafMEM->graph(1)->setName("Swap");

    //GRAFICO DE CARGA DA BATERIA
    ui->grafSupply->addGraph(); // blue line
    ui->grafSupply->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->grafSupply->graph(0)->setName("Carga(%)");

    //GRÁFICO DE TEMPRO PARA DESCARREGAR
    //GRAFICO DE CARGA DA BATERIA
    ui->grafTimeSupply->addGraph(); // blue line
    ui->grafTimeSupply->graph(0)->setPen(QPen(QColor(255, 110, 40)));
    ui->grafTimeSupply->graph(0)->setName("Tempo de Descarga");

    // Adicionar as legendas de ambos os gráficos:
    ui->grafCPU->legend->setVisible(true);
    ui->grafMEM->legend->setVisible(true);
    ui->grafSupply->legend->setVisible(true);
    ui->grafTimeSupply->legend->setVisible(true);

    // Gerenciamento do tempo dos gráficos (CPU e Mem) e dos tamanhos:
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->grafCPU->xAxis->setTicker(timeTicker);
    ui->grafCPU->axisRect()->setupFullAxesBox();
    ui->grafCPU->yAxis->setRange(-0.3, 100.03);

    ui->grafMEM->xAxis->setTicker(timeTicker);
    ui->grafMEM->axisRect()->setupFullAxesBox();
    ui->grafMEM->yAxis->setRange(-0.3, 100.5);


    // Gerenciamento do tempo dos gráficos de Carga e Tempo de Descarga e dos tamanhos:
    ui->grafSupply->xAxis->setTicker(timeTicker);
    ui->grafSupply->axisRect()->setupFullAxesBox();
    ui->grafSupply->yAxis->setRange(-0.3, 100.3);

    ui->grafTimeSupply->xAxis->setTicker(timeTicker);
    ui->grafTimeSupply->axisRect()->setupFullAxesBox();
    ui->grafTimeSupply->yAxis->setRange(-0.1, 8.1);


    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->grafCPU->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->grafCPU->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->grafCPU->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->grafCPU->yAxis2, SLOT(setRange(QCPRange)));

    connect(ui->grafMEM->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->grafMEM->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->grafMEM->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->grafMEM->yAxis2, SLOT(setRange(QCPRange)));

    connect(ui->grafSupply->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->grafSupply->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->grafSupply->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->grafSupply->yAxis2, SLOT(setRange(QCPRange)));

    connect(ui->grafTimeSupply->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->grafTimeSupply->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->grafTimeSupply->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->grafTimeSupply->yAxis2, SLOT(setRange(QCPRange)));


    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::realtimeDataSlot(){
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds

    // Adicionar informação para o gráfico da CPU:
    this->cpu.calculate();
    for(int i = 0; i < 4; i++){
         ui->grafCPU->graph(i)->addData(key, this->cpu.getData().at(i));
    }

    // Adicionar informações para o gráfico da Memória:
    // graph(0) = Memória
    // graph(1) = Swap
    this->memory.concatenate();
    ui->grafMEM->graph(0)->addData(key, this->memory.calculateMemory());
    ui->grafMEM->graph(1)->addData(key, this->memory.calculateSwap());

    // make key axis range scroll with the data (at a constant range size of 8):
    ui->grafCPU->xAxis->setRange(key, 60, Qt::AlignRight);
    ui->grafCPU->replot();

    ui->grafMEM->xAxis->setRange(key, 60, Qt::AlignRight);
    ui->grafMEM->replot();

    //Graficos de Energia
    this->supply.concatenate();
    ui->grafSupply->graph(0)->addData(key, this->supply.calculateSupply());
    ui->grafTimeSupply->graph(0)->addData(key, this->supply.timeRemaining()); //Está dando erro executar (A janela fecha).

    ui->grafSupply->xAxis->setRange(key, 60, Qt::AlignRight);
    ui->grafSupply->replot();

    ui->grafTimeSupply->xAxis->setRange(key, 60, Qt::AlignRight);
    ui->grafTimeSupply->replot();

}
