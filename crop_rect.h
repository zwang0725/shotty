#ifndef CROP_RECT_H
#define CROP_RECT_H
#include <QPoint>
#include <QPainter>

class CropRect
{
public:
  CropRect(){}
  ~CropRect(){}
  void setStart(QPoint s);

  void setEnd(QPoint e);

  QPoint startPoint() const;

  QPoint endPoint() const;
  void reset();
  QSize& size() const;

  int height() const;

  int width() const;
  bool empty() const;
private:
  QPoint start;
  QPoint end;
};


inline void CropRect::setStart(QPoint s)
{
    start = s;
}

inline void CropRect::setEnd(QPoint e)
{
  end = e;
}

inline QPoint CropRect::startPoint() const
{
  return start;
}

inline QPoint CropRect::endPoint() const
{
  return end;
}
inline void CropRect::reset()
{
  QPoint P(0,0);
  start = P;
  end = P;
}

inline QSize& CropRect::size() const
{
  return QSize(width(), height());
}

inline int CropRect::height() const
{
  return qAbs(startPoint().y() - endPoint().y());
}

inline int CropRect::width() const
{
  return qAbs(startPoint().x() - endPoint().x());
}
inline bool CropRect::empty() const
{
    return ((height() == 0)||(width() == 0));
}
#endif // CROP_RECT_H
