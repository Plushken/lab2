#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &Widget::on_pushButton_clicked);
     currentPath = "D:/";
         filters << "*.tif" << "*.gif" <<  "*.jpg"<< "*.bmp" << "*.pcx" <<  "*.png"<< "*.jpeg";
         dir.setNameFilters(filters);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QStringList fileName = QFileDialog ::getOpenFileNames(this, "Open Files","D:/","Image(*jpg *gif *tif *bmp *png *pcx *jpeg);;Archieve(*zip)");
        if(fileName.isEmpty())
            return;

        ui->tableWidget->setSortingEnabled(false);

        if (fileName[0].contains("zip"))
        {
            tempPath = QDir::currentPath() + "/temp";
            dir.setPath(tempPath);
            dir.mkdir(tempPath);

            fileInfo.setFile(fileName[0]);
            currentPath = fileInfo.path();

            QZipReader zipReader(fileName[0]);
            zipReader.extractAll(tempPath);

            QFileInfoList files = dir.entryInfoList();
            if (files.empty())
            {
                QMessageBox::information(this, "Information", "There are no files in the archive in the correct format");
                return;
            }

            fileInfo = files[0];
            //QString saveCurrPath = currentPath;
            currentPath = fileInfo.path();

            for (int i = 0; i < files.size(); i++)
            {
                fileInfo = files[i];
                image.load(currentPath + "/" + fileInfo.fileName());

                    QString resolution = QVariant(image.width()).toString()+ "x" +QVariant(image.height()).toString();
                    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(fileInfo.fileName()));
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(fileInfo.suffix().toUpper()));
                    QTableWidgetItem *item = new QTableWidgetItem();
                    item->setData(Qt::DisplayRole, fileInfo.size());

                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, item);
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, new QTableWidgetItem(resolution));
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, new QTableWidgetItem(QVariant(image.bitPlaneCount()).toString()));

                    item = new QTableWidgetItem();
                    item->setData(Qt::DisplayRole, round(image.dotsPerMeterX()/39.37));
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 5, item);
            }

            dir.removeRecursively();
            //currentPath = saveCurrPath;
        }

        else
        {
            fileInfo.setFile(fileName[0]);
            currentPath = fileInfo.path();

            for (int i = 0; i < fileName.size(); i++)
            {
                fileInfo.setFile(fileName[i]);
                image.load(currentPath + "/" + fileInfo.fileName());
                QString str = fileInfo.fileName();
                QString suffix = fileInfo.suffix();
                    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(str));
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(suffix));
                    QTableWidgetItem *item = new QTableWidgetItem();
                    item->setData(Qt::DisplayRole, fileInfo.size());
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, item);
                QString resolution = QVariant(image.width()).toString()+ "x" +QVariant(image.height()).toString();
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, new QTableWidgetItem(resolution));
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, new QTableWidgetItem(QVariant(image.bitPlaneCount()).toString()));

                    item = new QTableWidgetItem();
                    item->setData(Qt::DisplayRole, round(image.dotsPerMeterX()/39.37));
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 5, item);
            }
        }

        ui->tableWidget->sortByColumn(0,Qt::AscendingOrder);
        ui->tableWidget->setSortingEnabled(true);
}


