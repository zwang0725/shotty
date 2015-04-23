#include "my_label.h"

My_Label::My_Label(QWidget *parent) :
    QLabel(parent)
{
    x_shift = 0;
    y_shift = 0;
}
void My_Label::setPicture(const QString &ImgName)
{
    QImage image(ImgName);
    if (image.isNull()) {
        QMessageBox::information(this, tr("Image Viewer"),
                                 tr("Cannot load %1.").arg(ImgName));
        return;
    }
    paint_rects.swap(vector<QRect>());
    cropRect.reset();
   picture = QPixmap::fromImage(image);
   this->setPixmap(picture);
}
int My_Label::pic_width() const
{
    return picture.width();
}
int My_Label::pic_height() const
{
    return picture.height();
}
int My_Label::pic_depth() const
{
    return picture.depth();
}

void My_Label::set_shift(int x_shift_, int y_shift_)
{
}

void My_Label::setRects(const vector<QRect> &input)
{
    paint_rects = input;
}

QPixmap My_Label::getCrop()
{
    return picture.copy(temp_rect);
}

void My_Label::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);   //需要调用父类的事件来显示背景
    QPainter painter(this);
    painter.setPen(QPen(Qt::red,2));
    if(!cropRect.empty())
        painter.drawRect(QRect(cropRect.startPoint(),cropRect.endPoint()));
    for(size_t i = 0;i < paint_rects.size();++i)
    {
        painter.drawRect(paint_rects[i]);
    }
}

void My_Label::mousePressEvent(QMouseEvent *event)
{
  if ((event->buttons() == Qt::LeftButton)/* && isContainPoint(event->pos())*/)
  {
//      if( event->pos().x()< 500 && event->pos().y() < 500)
//      {
        cropRect.setStart(event->pos());
        cropRect.setEnd(event->pos());
      //}
  }
}

void My_Label::mouseMoveEvent(QMouseEvent *event)
{
  if (event->buttons() == Qt::LeftButton)
  {
//      if( event->pos().x()< 500 && event->pos().y() < 500)
//      {
          cropRect.setEnd(event->pos());
          update();
    //  }
  }
}
void My_Label::mouseReleaseEvent(QMouseEvent *e)
{
    if(!picture.isNull())
    {
         temp_rect = QRect(QRect(cropRect.startPoint(),cropRect.endPoint()));
         emit mouseRelease();
    }
}
