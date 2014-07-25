#ifndef PLUGINCURVESECTION_HPP
#define PLUGINCURVESECTION_HPP

#include <QGraphicsItem>
#include "plugincurvepoint.hpp"
#include "plugincurvesection.hpp"
#include "plugincurveview.hpp"
#include "plugincurve2_global.hpp"

class PLUGINCURVESHARED_EXPORT PluginCurveSection : public QGraphicsObject
{
 Q_OBJECT
public:
    // Constructor. Source and destination points must be modified consequently
    PluginCurveSection(PluginCurveView *parent, PluginCurvePoint *source, PluginCurvePoint *dest); // Parent : PluginCurvePoint ? GraphicsCurveView ?
    ~PluginCurveSection();
    // Return source point
    PluginCurvePoint *sourcePoint();
    // return destination point;
    PluginCurvePoint *destPoint();
    // Modifie the source point and adjust the curve. The point must be modified consequently
    void setSourcePoint(PluginCurvePoint *autoPoint);
    // Modifie the destination point and adjust the curve. The point must be modified consequently
    void setDestPoint(PluginCurvePoint *autoPoint);
    // Highlight the item
    void highlight(bool b);
    // Returns the point's color
    QColor color();
    // Returns the point's color when selected
    QColor selectColor();
    // Adjust the curve position
    void adjust();
    // Bounding rectangle;
    virtual QRectF boundingRect() const = 0;
    // Shape
    virtual QPainterPath shape() const = 0;
    // Section's path
    virtual QPainterPath path() const = 0;
    // Paint the curve
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;

protected:
    static const int SHAPEHEIGHT = 5;
    PluginCurvePoint *_pSourcePoint;
    PluginCurvePoint *_pDestPoint;
    bool _highlight{};
    QColor _color; // Section's color
    QColor _selectColor; // Section's color when selected
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
signals:
    void doubleClicked(QGraphicsSceneMouseEvent *event);
public slots:
    void setAllFlags(bool b);



};

#endif // PLUGINCURVESECTION_HPP
