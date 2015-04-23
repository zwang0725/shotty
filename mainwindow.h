#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <QString>
#include <QImage>
#include <QScrollArea>
#include <QMessageBox>
#include <QRect>
#include <QXmlStreamWriter>
#include <QFile>
#include <QMessageBox>
#include <QTimer>
#include <QScrollBar>
#include <vector>
#include "my_label.h"
#include "crop_rect.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    struct Crop_Info
    {
        QString pose;
        QString class_name;
        QRect Rectangle;
        Crop_Info(QString pose_,QString class_name_,QRect Rectange_):pose(pose_),class_name(class_name_),Rectangle(Rectange_){}
    };

    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString ImgName;
    QString default_name;
    QTimer *msgBoxCloseTimer;
//    QScrollBar *H;
//    QScrollBar *V;
//    QScrollBar *scrollBar;
public:
    std::vector<Crop_Info> writing_info;
    vector<QRect> get_rects() ;
private:
    vector<QRect> Rects;
    QPixmap crop;
    int width;
    int height;
    int depth;
private slots:

    void on_pushButton_clicked();
    void on_pushButton_write_yml_clicked();
    void on_pushButton_save_image_clicked();
    void on_pushButton_confirm_clicked();
    void preview_crop();
    //void shift_value();
};

#endif // MAINWINDOW_H
