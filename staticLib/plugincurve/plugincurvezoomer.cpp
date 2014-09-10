#include <QPainter>
#include "plugincurvezoomer.hpp"

PluginCurveZoomer::PluginCurveZoomer(QGraphicsObject *parent) :
    QGraphicsObject(parent)
{
}

void PluginCurveZoomer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    //----> SUPPRIMER
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::blue);
    painter->drawRect(boundingRect());
    painter->drawEllipse(100,100,40,40);
    //<---- SUPPRIMER
}

QRectF PluginCurveZoomer::boundingRect() const
{
    return mapRectFromParent(parentItem()->boundingRect());
}

void PluginCurveZoomer::zoom(QPointF origin, qreal delta)
{
    QPointF mapOrigin = mapFromParent(origin); // Parent = View
    //QPointF mapOrigin(120,120);
    //qreal scaleY = transform().m22();
    //qreal scaleX = transform().m11();
    qreal scaleFact = scale();
    qreal fact = delta / 120;
    setTransformOriginPoint(mapOrigin);
//    QTransform tr = QTransform::fromScale(qMax((fact/10)+scaleX,0.1),qMax((fact/10)+scaleY,0.1)); /// @todo Mieux gerer les facteurs.
//    QTransform tr = QTransform::fromScale(1+fact/10,1+fact/10); /// @todo Mieux gerer les facteurs.
//    QPointF p = transformOriginPoint();
//    setTransform(tr,true);
    setScale(qMax((fact/20)+scaleFact,0.1));
    prepareGeometryChange();
    update();
}

void PluginCurveZoomer::translateX(qreal dx)
{
    setX(pos().x() + dx);
}

void PluginCurveZoomer::translateY(qreal dy)
{
    setY(pos().y() + dy);
}
