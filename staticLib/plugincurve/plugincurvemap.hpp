#ifndef PLUGINCURVEMAP_HPP
#define PLUGINCURVEMAP_HPP

#include <QObject>
#include <QRectF>
class PluginCurveMap : public QObject
{
    Q_OBJECT

// Attributes
private:
    QRectF _scaleRect; /*!< Define points' area in scale coordinate. */
    QRectF _paintRect; /*!< Define points' area in paint coordinate. */

// Methods
public:
    //! Construct a PluginCurveMap.
    /*!
    \param scaleRect The rectangle delimitting the points in scale coordinate.
    \param paintRect The rectangle delimitting the points in paint coordinate.
    */
    PluginCurveMap(QRectF scaleRect, QRectF paintRect);
    /*! Transform a point from scale to paint coordinates. */
    QPointF scaleToPaint(QPointF val);
    /*! Transform a point from paint to scale coordinates. */
    QPointF paintToScale(QPointF pos);
    /*! Returns the point's area in paint coordinate */
    QRectF paintRect();
    /*! Returns the point's area in scale coordinate */
    QRectF scaleRect();
    /*! Set the point's area in paint coordinate. */
    void setScaleRect(QRectF scaleRect);
    /*! Set the point's area in scale coordinate. */
    void setPaintRect(QRectF paintRect);
signals:
    void mapChanged(); //! Indicates if a a cange occured.
public slots:

};

#endif // PLUGINCURVEMAP_HPP