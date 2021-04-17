#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openSettings_triggered();

    void addTreeRoot(QString name, QString description);
    void addTreeChild(QTreeWidgetItem *parent,
                        QString name, QString description);

    void on_calendarWidget_itemActivated(QTreeWidgetItem *item, int column);

    void on_SearchButton_released();

    void on_cancelSearch_released();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
