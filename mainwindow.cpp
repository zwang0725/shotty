#include "mainwindow.h"
#include "ui_mainwindow.h"
#ifndef QT_NO_PRINTER
#include <QtPrintSupport/QPrintDialog>
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Qt::WindowFlags flags = 0;

    setMaximumHeight(525);
    setMaximumWidth(779);
    setFixedSize(779,525);
    //setMinimumSize(779,551); // 禁止改变窗口大小。
    this->adjustSize();
    //setWindowFlags(flags); // 设置禁止最大化
    ui->Main_Label->setBackgroundRole(QPalette::Base);
    ui->Main_Label->setAlignment(Qt::AlignTop);
    ui->small_label->setBackgroundRole(QPalette::Base);
    ui->small_label->setAlignment(Qt::AlignTop);
//    V = ui->scrollArea_big->verticalScrollBar();
//    H = ui->scrollArea_big->horizontalScrollBar();
//    V= ui->scrollArea_big->horizontalScrollBar();
//    V->setSliderDown(true);  //set In order that scrollbar emits signal,you need to set here true
    ui->pushButton_write_yml->setEnabled(false);
    ui->pushButton_save_image->setEnabled(false);
    ui->scrollArea_big->setWidget(ui->Main_Label);
    ui->scrollArea_small->setWidget(ui->small_label);

    connect(ui->Main_Label,SIGNAL(mouseRelease()),this,SLOT(preview_crop()));
    //QObject::connect(V, SIGNAL(sliderMoved(int)), this, SLOT(shift_value()));
    msgBoxCloseTimer = new QTimer(this);

    setWindowTitle(tr("Snapshot Tool"));

}
MainWindow::~MainWindow()
{
    delete ui;
}
vector<QRect> MainWindow::get_rects()
{
    return Rects;
}
void MainWindow::on_pushButton_clicked()
{
    if(default_name.isEmpty())
        ImgName = QFileDialog::getOpenFileName(this,
     tr("Open Image"), default_name, tr("Image Files (*.png *.jpg *.bmp)"));
    else
        ImgName = QFileDialog::getOpenFileName(this,
     tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.bmp)"));
    if (!ImgName.isEmpty()) {
        vector<QRect>().swap(Rects);  //Clear the rect info from last opening image
        std::vector<Crop_Info>().swap(writing_info);//Clear the writing info from last opening image
        ui->Main_Label->setPicture(ImgName);
        width = ui->Main_Label->pic_width();
        height = ui->Main_Label->pic_height();
        depth = ui->Main_Label->pic_depth();
    }
}

void MainWindow::on_pushButton_write_yml_clicked()
{


    int point_index = ImgName.lastIndexOf(".");
    int slash_index = ImgName.length() - ImgName.lastIndexOf("/")-1;
    qDebug()<<slash_index;
    QFile file(ImgName.left(point_index + 1)+ "xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
       qDebug() << "Error: cannot open file";
       file.close();
    }
    file.open(QIODevice::ReadWrite);
    if ( file.isOpen() )
    {
        QXmlStreamWriter stream(&file);
        stream.setAutoFormatting(true);
        stream.writeStartDocument();
        stream.writeStartElement("Annotation");
        stream.writeTextElement("folder","VOC2007");
        stream.writeTextElement("filename",ImgName.right(slash_index));
        stream.writeStartElement("size");
        stream.writeTextElement("width", QString::number(width));
        stream.writeTextElement("height",QString::number(height));
        stream.writeTextElement("depth", QString::number(depth));
        stream.writeEndElement();

        stream.writeTextElement("segmented", "0");

        for(size_t i = 0;i < writing_info.size();++i)       //存放兴趣域信息
        {
            stream.writeStartElement("object");
            stream.writeTextElement("name", writing_info[i].class_name);
            stream.writeTextElement("pose", writing_info[i].pose);
            stream.writeTextElement("truncated", "1");
            stream.writeTextElement("difficult", "0");


            QRect test;
            test.topLeft().x();
            stream.writeStartElement("bndbox");
            stream.writeTextElement("xmin", QString::number(writing_info[i].Rectangle.topLeft().x()));
            stream.writeTextElement("ymin", QString::number(writing_info[i].Rectangle.topLeft().y()));
            stream.writeTextElement("xmax", QString::number(writing_info[i].Rectangle.bottomRight().x()));
            stream.writeTextElement("ymax", QString::number(writing_info[i].Rectangle.bottomRight().y()));
            stream.writeEndElement();//end bngbox tag

            stream.writeEndElement();  //end object tag
        }
        stream.writeEndElement();//end size tag

        stream.writeEndDocument();//end annotation tag
        file.close();   
    }

    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setText("<b>Save Successfully</b>");
    msgBox->setStandardButtons(0);


    msgBoxCloseTimer->setInterval(300);
    msgBoxCloseTimer->setSingleShot(true);
    connect(msgBoxCloseTimer, SIGNAL(timeout()), msgBox, SLOT(reject())); // or accept()
    msgBoxCloseTimer->start();

    msgBox->exec();
    vector<Crop_Info>().swap(writing_info);
}
void MainWindow::on_pushButton_confirm_clicked()
{
    writing_info.push_back(Crop_Info(ui->comboBox_pose->currentText(),ui->comboBox_class->currentText(),ui->Main_Label->temp_rect));//存储兴趣域信息
    Rects.push_back(ui->Main_Label->temp_rect);
    ui->Main_Label->setRects(get_rects());
    ui->pushButton_write_yml->setEnabled(true);
    ui->pushButton_save_image->setEnabled(true);

}
void MainWindow::on_pushButton_save_image_clicked()
{
    ui->pushButton_save_image->setEnabled(false);
}

void MainWindow::preview_crop()
{
    ui->small_label->setPixmap(ui->Main_Label->getCrop());
}

//void MainWindow::shift_value()
//{
//    qDebug()<<"test";
//}




