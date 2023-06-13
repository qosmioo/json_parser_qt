#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->open_file_btn, &QPushButton::clicked, this, &MainWindow::on_open_file_clicked);
    connect(ui->check_file_btn, &QPushButton::clicked, this, &MainWindow::on_check_file_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_open_file_clicked() {
    fp = QFileDialog::getOpenFileName(this, " ", "C:\\Users", "*.json").toStdString();
    if (fp == "") {
        ui->file_path_label->setText("File was not opened");
    }
    else {
        Work_with_file wf;
        Json_checker js;
        Facade facade(wf, js);
        facade.fp = fp;
        ui->file_path_label->setText(QString::fromStdString(fp));
        std::string res = facade.read_operation(facade.fp);
        ui->json_label->setText(QString::fromStdString(res));
    }
}

void MainWindow::on_check_file_clicked() {
    try {
        Work_with_file wf;
        Json_checker js;
        Facade facade(wf, js);
        facade.fp = fp;
        std::string res_new = facade.read_operation(facade.fp);
        facade.check_operation(res_new);
        std::string message = "File is correct!";
        ui->check_result_label->setText(QString::fromStdString(message));
    }  catch (Json_errors& errors) {
        const char* json_error = errors.what();
        ui->check_result_label->setText(json_error);
    } catch (System_errors& errors) {
        const char* system_error = errors.what();
        ui->check_result_label->setText(system_error);
    }
}

