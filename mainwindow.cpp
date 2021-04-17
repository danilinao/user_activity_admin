#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsform.h"

#include <QSplitter>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QDate>
#include <QDebug>

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // ui->groupBox_2->layout()->setAlignment(ui->calendarView, Qt::AlignHCenter);
    QChart *chart;
    QChartView *chartView;

    chart  = new QChart;

    QLineSeries *series = new QLineSeries();
    series->append(0, 6);
        series->append(2, 4);
        series->append(3, 8);
        series->append(7, 4);
        series->append(10, 5);
        *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

        chart->legend()->hide();
            chart->addSeries(series);
            chart->createDefaultAxes();
            chart->setTitle("Simple line chart example");
    chartView = new QChartView(chart);
     chartView->setRenderHint(QPainter::Antialiasing);

     ui->groupBox_2->layout()->addWidget(chartView);


     QDate cd = QDate::currentDate();
     QDate ed = cd.addYears(-10);
     QList<QTreeWidgetItem *> years;

     int curYearI = 0;
     int curMothI = -1;
     QTreeWidgetItem *curYear = NULL;
     QTreeWidgetItem *curMonth = NULL;

     while(cd >= ed)
     {
         if(cd.year() != curYearI)
         {
             curYear->addChild(curMonth);
             curMothI = cd.month();
             curMonth = new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(cd.toString("MMMM")));
             ui->calendarWidget->addTopLevelItem(curYear);
             curYearI = cd.year();
             curYear = new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(QString::number(curYearI)));
         }

         if(cd.month() != curMothI)
         {
             curYear->addChild(curMonth);
             curMothI = cd.month();
             curMonth = new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(cd.toString("MMMM")));
         }

         curMonth->addChild(new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(cd.toString(Qt::LocaleDate))));

         cd = cd.addDays(-1);
     }



}

void MainWindow::addTreeRoot(QString name, QString description)
{

    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->calendarWidget);
    treeItem->setText(0, name);
    treeItem->setText(1, description);

}

void MainWindow::addTreeChild(QTreeWidgetItem *parent, QString name, QString description)
{

    QTreeWidgetItem *treeItem = new QTreeWidgetItem();
    treeItem->setText(0, name);
    treeItem->setText(1, description);
    parent->addChild(treeItem);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openSettings_triggered()
{
    SettingsForm *testWindow = new SettingsForm();
    testWindow->show();
}

void MainWindow::on_calendarWidget_itemActivated(QTreeWidgetItem *item, int column)
{

    if(item->childCount() == 0)
    {



    }

}

void MainWindow::on_SearchButton_released()
{

}

void MainWindow::on_cancelSearch_released()
{

    ui->searchField->clear();

}
