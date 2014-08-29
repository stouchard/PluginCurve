#include "plugincurvemap.hpp"
#include <iostream>

PluginCurveMap::PluginCurveMap(QRectF scaleRect, QRectF paintRect) :
    QObject(), _scaleRect(scaleRect), _paintRect(paintRect)
{
}

QPointF PluginCurveMap::scaleToPaint(QPointF val)
{
    QPointF pos;
    pos.setX( (val.x()-_scaleRect.x())*_paintRect.width() / _scaleRect.width() + _paintRect.x() );
    pos.setY( (val.y()-_scaleRect.y())*_paintRect.height() / _scaleRect.height() + _paintRect.y());
    return pos;
}

QPointF PluginCurveMap::paintToScale(QPointF pos)
{
    std::cout << "Scale Rect : " << _scaleRect.x() << " " << _scaleRect.y() << " " << _scaleRect.width() << " " << _scaleRect.height();
    std::cout << "paint Rect : " << _paintRect.x() << " " << _paintRect.y() << " " << _paintRect.width() << " " << _paintRect.height();
    QPointF val;
    val.setX( (pos.x()-_paintRect.x())*_scaleRect.width() /_paintRect.width() + _scaleRect.x() );
    val.setY( _scaleRect.y() + (_paintRect.height() + _paintRect.y() - pos.y()) / _paintRect.height() * _scaleRect.height());
    return val;
}

void PluginCurveMap::setPaintRect(QRectF paintRect)
{
    _paintRect = paintRect;
    emit(mapChanged());
}

void PluginCurveMap::setScaleRect(QRectF scaleRect)
{
    _paintRect = scaleRect;
    emit(mapChanged());
}
