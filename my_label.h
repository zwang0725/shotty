#ifndef MY_LABEL_H
#define MY_LABEL_H

#include <QLabel>
#include <QPainter>
#include <QString>
#include <QMessageBox>
#include <QRect>
#include <QMouseEvent>
#include <vector>
#include "crop_rect.h"

using namespace std;
class My_Label : public QLabel
{
    Q_OBJECT
public:
    explicit My_Label(QWidget *parent = 0);
public:
    CropRect cropRect;
    QRect temp_rect;
    vector<QRect> paint_rects;
    QPixmap picture;
    int width;
    int height;
    int depth;
    int x_shift;
    int y_shift;
public:
    void setPicture(const QString &ImgName);
    void setRects(const vector<QRect> &input);
    QPixmap getCrop();
    int pic_width() const;
    int pic_height() const;
    int pic_depth() const;
    void set_shift(int x_shift_,int y_shift_);
private:
    void paintEvent(QPaintEvent *e);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
signals:
    void mouseRelease();
public slots:
    
};

#endif // MY_LABEL_H
