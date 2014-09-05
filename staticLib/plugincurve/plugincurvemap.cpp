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
//    pos.setY( (val.y()-_scaleRect.y())*_paintRect.height() / _scaleRect.height() + _paintRect.y());
    pos.setY( _paintRect.height() + _paintRect.y() - (_paintRect.height()*(val.y() - _scaleRect.y())/_scaleRect.height()));
    return pos;
}

QRectF PluginCurveMap::scaleToPaint(QRectF rect)
{
    QRectF res;
    res.setBottomLeft(scaleToPaint(rect.bottomLeft()));
    res.setBottomRight(scaleToPaint(rect.bottomRight()));
    res.setTopLeft(scaleToPaint(rect.topLeft()));
    res.setTopRight(scaleToPaint(rect.topRight()));
    return res;
}

QPointF PluginCurveMap::paintToScale(QPointF pos)
{
    QPointF val;
    val.setX( (pos.x()-_paintRect.x())*_scaleRect.width() /_paintRect.width() + _scaleRect.x() );
    val.setY( _scaleRect.y() + (_paintRect.height() + _paintRect.y() - pos.y()) / _paintRect.height() * _scaleRect.height());
    return val;
}

QRectF PluginCurveMap::paintToScale(QRectF rect)
{
    QRectF res;
    res.setBottomLeft(paintToScale(rect.bottomLeft()));
    res.setBottomRight(paintToScale(rect.bottomRight()));
    res.setTopLeft(paintToScale(rect.topLeft()));
    res.setTopRight(paintToScale(rect.topRight()));
    return res;
}

QRectF PluginCurveMap::paintRect()
{
    return _paintRect;
}

QRectF PluginCurveMap::scaleRect()
{
    return _scaleRect;
}

void PluginCurveMap::setPaintRect(QRectF paintRect)
{
    _paintRect = paintRect;
    //update scale rect !
    setScaleRect(paintToScale(paintRect));
    emit(mapChanged());
}

void PluginCurveMap::setScaleRect(QRectF scaleRect)
{
    _scaleRect = scaleRect;
    emit(mapChanged());
}
