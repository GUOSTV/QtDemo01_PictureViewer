#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QSettings>
#include <QStandardPaths>
#include <QDebug>
#include <memory>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->label_image->clear();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::open1()
{
    QString filename= QFileDialog::getOpenFileName(this,"Select the image","D:/","image(*.png *.jpg)");
    if(filename.isEmpty()){
        return;
    }
    ui->lineEdit_path->setText(filename);
    ui->label_image->setPixmap(QPixmap(filename));

}

void Widget::open2()
{
    QString confPath=qApp->applicationDirPath()+"/config/setting.ini";
    qDebug()<<confPath;
    //使用智能指针
    std::unique_ptr<QSettings> inifile(new QSettings(confPath,QSettings::IniFormat));
    //QSettings *inifile=new QSettings(confPath,QSettings::IniFormat);
    QString lastpath=inifile->value("/LastPath/path").toString();
    if(lastpath.isEmpty()){
        lastpath=QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    }
    qDebug()<<lastpath;
    QString filename= QFileDialog::getOpenFileName(this,"Select the image",lastpath,"image(*.png *.jpg)");
    if(filename.isEmpty()){
        return;
    }
    ui->lineEdit_path->setText(filename);
    //ui->label_image->setPixmap(QPixmap(filename));
    //图片缩放
    std::unique_ptr<QPixmap> pix(new QPixmap(filename));
    //QPixmap *pix=new QPixmap(filename);
    pix->scaled(ui->label_image->size(),Qt::KeepAspectRatio);
    ui->label_image->setScaledContents(true);
    ui->label_image->setPixmap(*pix);
    int end=filename.lastIndexOf("/");
    QString _path=filename.left(end);
    inifile->setValue("/LastPath/path",_path);
    //delete inifile;
    //inifile=NULL;
}

void Widget::on_Btnpush_clicked()
{
    //open1();
    open2();
}

