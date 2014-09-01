#include "plugincurvegrid.hpp"
#include <QPainter>
#include <iostream>

PluginCurveGrid::PluginCurveGrid(PluginCurveView *parent, PluginCurveMap *map) :
    QGraphicsObject(parent)
{
    _pDefaultMap = new PluginCurveMap(QRectF(0,0,100,100),QRectF(0,0,3,3));
    if (map == nullptr)
        _pMap = _pDefaultMap;
    else
        _pMap = map;
    connect(_pMap,SIGNAL(mapChanged()),this,SLOT(mapChanged()));
    updateMagnetPoints();
    setZValue(-1);
}

PluginCurveGrid::~PluginCurveGrid()
{
    delete _pDefaultMap;
}

QPointF PluginCurveGrid::nearestMagnetPoint(QPointF p)
{
    QPointF res = _pMap->paintToScale(p);
    qreal x,y;
    x = floor(res.x()/stepX)*stepX;
    y = floor(res.y()/stepY)*stepY;
    if (res.x() - x > stepX/2)
        res.setX(x + stepX);
    else
        res.setX(x);
    if (res.y() - y > stepY/2)
        res.setY(y + stepY);
    else
        res.setY(y);
    return _pMap->scaleToPaint(res);
}

void PluginCurveGrid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setPen(Qt::lightGray);
    qreal x,y;
    QRectF paintRect = _pMap->paintRect();
    QVector<qreal>::iterator iteratorX;
    QVector<qreal>::iterator iteratorY;
    for (iteratorX = magnetPointX.begin(); iteratorX != magnetPointX.end(); iteratorX++)
    {
        x = *iteratorX;
        painter->drawLine(QLineF(x,paintRect.y(),x,paintRect.y()+paintRect.height()));
    }
    for (iteratorY = magnetPointY.begin(); iteratorY != magnetPointY.end(); iteratorY++)
    {
        y = *iteratorY;
        painter->drawLine(QLineF(paintRect.x(),y,paintRect.x()+paintRect.width(),y));
    }
}


QRectF PluginCurveGrid::boundingRect() const
{
    return parentItem()->boundingRect();
}

void PluginCurveGrid::updateMagnetPoints()
{
    qreal x,y;
    QRectF scaleRect = _pMap->scaleRect();
    QRectF paintRect = _pMap->paintRect();
    stepY = pow(10,floor(log10f(scaleRect.height()))-1);
    stepX = pow(10,floor(log10f(scaleRect.width()))-1);
    QPointF firstPoint = _pMap->scaleToPaint(QPointF(floor(scaleRect.x()/stepX)*(stepX+1),floor(scaleRect.y()/stepY)*(stepY+1)));
    qreal paintStepY = qAbs(_pMap->scaleToPaint(QPointF(0,stepY)).y() - _pMap->scaleToPaint(QPointF(0,0)).y());
    qreal paintStepX = _pMap->scaleToPaint(QPointF(stepX,0)).x() - _pMap->scaleToPaint(QPointF(0,0)).x();
    std::cout << "paintstep y =" << _pMap->scaleToPaint(QPointF(0,stepY)).y() << " - " << _pMap->scaleToPaint(QPointF(0,0)).y();
    for (x = firstPoint.x(); x <= paintRect.x() + paintRect.width(); x += paintStepX)
    {
        magnetPointX.append(x);
    }
    for (y = firstPoint.y(); y <= paintRect.y() + paintRect.height(); y += paintStepY)
    {
        magnetPointY.append(y);
    }
}

void PluginCurveGrid::mapChanged()
{
    updateMagnetPoints();
    update();
}
