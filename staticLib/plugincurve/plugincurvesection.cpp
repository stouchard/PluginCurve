#include "plugincurvesection.hpp"
#include "plugincurvepoint.hpp"
#include "plugincurveview.hpp"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QLineF>

PluginCurveSection::PluginCurveSection(PluginCurveView *parent, PluginCurvePoint *source, PluginCurvePoint *dest) :
    QGraphicsObject(parent)
{
    _pSourcePoint = source;
    _pDestPoint = dest;
    _color = QColor(Qt::darkGray);
    _selectColor = QColor(Qt::red);
    setCacheMode(DeviceCoordinateCache);
    setAcceptHoverEvents(true);
    setZValue(0);
    setPos(source->pos());
}

PluginCurveSection::~PluginCurveSection()
{
}

PluginCurvePoint *PluginCurveSection::sourcePoint()
{
  return _pSourcePoint;
}

PluginCurvePoint *PluginCurveSection::destPoint()
{
  return _pDestPoint;
}

void PluginCurveSection::setSourcePoint(PluginCurvePoint *autoPoint)
{
  _pSourcePoint = autoPoint;
  adjust();
}

void PluginCurveSection::setDestPoint(PluginCurvePoint *autoPoint)
{
  _pDestPoint = autoPoint;
  adjust();
}

void PluginCurveSection::highlight(bool b)
{
  _highlight = b;
}

QColor PluginCurveSection::color()
{
  return _color;
}

QColor PluginCurveSection::selectColor()
{
  return _selectColor;
}

void PluginCurveSection::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  Q_UNUSED(event)
  scene()->clearSelection();
  _pSourcePoint->setSelected(true);
  _pDestPoint->setSelected(true);
}

void PluginCurveSection::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
  emit(doubleClicked(event));
}

void PluginCurveSection::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
  highlight(true);
  QGraphicsItem::hoverEnterEvent(event);
}

void PluginCurveSection::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
  highlight(false);
  QGraphicsItem::hoverLeaveEvent(event);
}

QVariant PluginCurveSection::itemChange(GraphicsItemChange change, const QVariant &value)
{
  if (change == ItemPositionHasChanged)
    {
      adjust();
    }
  if (change == ItemSelectedChange)
    {

    }
 return QGraphicsItem::itemChange(change, value);
}

void PluginCurveSection::adjust()
{
    if (_pSourcePoint==NULL || _pDestPoint==NULL)
        return;
    setPos(_pSourcePoint->pos());
    prepareGeometryChange();
    update();//inutile ?
}

void PluginCurveSection::setAllFlags(bool b)
{
  setFlag(QGraphicsItem::ItemIsMovable,b);
  setFlag(QGraphicsItem::ItemIsSelectable,b);
  setFlag(QGraphicsItem::ItemSendsGeometryChanges,b);
}


