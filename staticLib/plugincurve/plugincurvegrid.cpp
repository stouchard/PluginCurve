#include "plugincurvegrid.hpp"

PluginCurveGrid::PluginCurveGrid(PluginCurveView *parent, PluginCurveMap *map) :
    QGraphicsObject(parent)
{
    _pDefaultMap = new PluginCurveMap(QRectF(0,0,1,1),QRectF(0,0,1,1));
    if (map == nullptr)
        _pMap = _pDefaultMap;
    else
        _pMap = map;
}

void PluginCurveGrid::setMap(PluginCurveMap *map)
{
    if (_pMap == nullptr)
        _pMap = _pDefaultMap;
    else
        _pMap = map;
}

void PluginCurveGrid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    //QRectF rect = _scaleRect();
    //qreal stepY = floor(log(rect.height()));
    //qreal stepX = floor(log(rect.width()));
    //QPointF firstPoint = _pMap->scaleToPaint(QPointF(floor(rect.x()/stepX)*(stepX+1),floor(rect.y()/stepY)*(stepY+1)));
    //stepY = _pMap->scaleToPaint(stepY) - _pMap->scaleToPaint(0);
    //stepX = _pMap->scaleToPaint(stepX) - _pMap->scaleToPaint(0);
    //QPainterPath grid = QPainterPath(0,origin.y());
    //for (int i = O; stepX*i + origin.x() < _limitRect.x(); i++)
}


QRectF PluginCurveGrid::boundingRect() const
{
    return parentItem()->boundingRect();
}

void PluginCurveGrid::mapChanged()
{
    update();
}
