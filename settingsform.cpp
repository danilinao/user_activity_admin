#include "settingsform.h"
#include "ui_settingsform.h"

#include <QDir>
#include <QFileDialog>
#include <QSettings>
#include <QStandardPaths>

SettingsForm::SettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsForm)
{
    ui->setupUi(this);

    QString addin_path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(addin_path);
    if (!dir.exists())
        dir.mkpath(addin_path);
    if (!dir.exists("addins"))
        dir.mkdir("addins");

    dir.cd("addins");
    addin_path = dir.absoluteFilePath("settings.ini");
    QSettings *settings = new QSettings(addin_path,QSettings::IniFormat);
    ui->settingsPath->setText(settings->value("settings/path").value<QString>());

    if(ui->settingsPath->text() != "")
    {
        settings = new QSettings(ui->settingsPath->text(),QSettings::IniFormat);
        ui->logsPath->setText(settings->value("settings/savePath").value<QString>());
        ui->saveInterval->setTime(settings->value("settings/timeInterval").value<QTime>());
    }


}

SettingsForm::~SettingsForm()
{
    delete ui;
}

void SettingsForm::on_GetSettingsPath_clicked()
{
    ui->settingsPath->setText(QFileDialog::getSaveFileName(this, tr("Сохранить файл с настройками"), "", tr("Файл настроек (*.ini)")));
}

void SettingsForm::on_SaveButton_clicked()
{
    QString addin_path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(addin_path);
    if (!dir.exists())
        dir.mkpath(addin_path);
    if (!dir.exists("addins"))
        dir.mkdir("addins");

    dir.cd("addins");
    addin_path = dir.absoluteFilePath("settings.ini");
    QSettings *settings = new QSettings(addin_path,QSettings::IniFormat);
    settings->setValue("settings/path", ui->settingsPath->text());

    settings->sync();


    QDir dirs(ui->settingsPath->text());
    if (!dir.exists())
        dir.mkpath(ui->settingsPath->text());

    settings = new QSettings(ui->settingsPath->text(),QSettings::IniFormat);
    settings->setValue("settings/savePath", ui->logsPath->text());
    settings->setValue("settings/timeInterval", ui->saveInterval->time());

    settings->sync();

}

void SettingsForm::on_CancelButton_clicked()
{
    this->hide();
}

void SettingsForm::on_GetLogsPath_clicked()
{
    ui->logsPath->setText(QFileDialog::getExistingDirectory(this, tr("Выбрать путь сохранения пользовательских логов")));
}
