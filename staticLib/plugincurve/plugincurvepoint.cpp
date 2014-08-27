#include "plugincurvepoint.hpp"
#include "plugincurvesection.hpp"
#include "plugincurveview.hpp"
#include "plugincurvepresenter.hpp"
#include <QPainter>
#include <QRectF>
#include <QGraphicsObject>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <iostream>




PluginCurvePoint::PluginCurvePoint(PluginCurveView *parent, QPointF point, QPointF value, MobilityMode mobility, bool removable) :
  QGraphicsObject(parent)
{
  _color = Qt::gray; // Point's color
  _selectColor = Qt::red; // Point's color when selected
  setRemovable(removable);
  setAcceptHoverEvents(true);
  setCacheMode(DeviceCoordinateCache);
  setFlag(ItemIsFocusable,false);
  setZValue(0);
  setValue(value);
  setPos(point);
  setMobility(mobility); // Warning ! setMobility after setPos();
}

PluginCurvePoint::~PluginCurvePoint()
{
}

void PluginCurvePoint::setValue(QPointF value)
{
    _value = value;
}

QPointF PluginCurvePoint::getValue()
{
    return _value;
}

MobilityMode PluginCurvePoint::mobility()
{
  return _mobility;
}

void PluginCurvePoint::setMobility(MobilityMode mode)
{
  _mobility=mode;
  if (mode==Vertical)
    _fixedCoordinate = pos().x();
}

qreal PluginCurvePoint::fixedCoordinate()
{
  return _fixedCoordinate;
}

void PluginCurvePoint::highlight(bool b=true)
{
  _highlight = b;
}

QColor PluginCurvePoint::color()
{
  return _color;
}

QColor PluginCurvePoint::selectColor()
{
  return _selectColor;
}

bool PluginCurvePoint::removable()
{
  return _removable;
}

void PluginCurvePoint::setRemovable(bool b)
{
  _removable = b;
}

void PluginCurvePoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(option)
  Q_UNUSED(widget)
  QColor stdColor = color();
  QColor slctColor = selectColor();
  QRadialGradient gradientExt(0, 0, SHAPERADIUS);
  QRadialGradient gradientNoSelection(2, 2, SHAPERADIUS);
  QRadialGradient gradientSelection(2, 2, SHAPERADIUS);
  gradientExt.setColorAt(RADIUS/SHAPERADIUS, QColor(slctColor).light(120));
  gradientExt.setColorAt(0.8, Qt::transparent);
  gradientNoSelection.setColorAt(0,QColor(stdColor).light(100));
  gradientNoSelection.setColorAt(1,Qt::black);
  gradientSelection.setColorAt(0,QColor(slctColor).light(120));
  gradientSelection.setColorAt(1,Qt::black);

  if (_highlight )
    {
      painter->setPen(Qt::NoPen);
      painter->setBrush(gradientExt);
      painter->drawEllipse(boundingRect());
    }
  if (isSelected())
    {
      painter->setBrush(gradientSelection);
    }
  else
    {
      painter->setBrush(gradientNoSelection);
    }
  //painter->setPen(Qt::NoPen);
  painter->setPen(QPen(Qt::black, 0));
  painter->drawEllipse(-RADIUS, -RADIUS, 2*RADIUS, 2*RADIUS);


}

void PluginCurvePoint::setRightSection(PluginCurveSection *section)
{
  _pRightSection = section;
}

void PluginCurvePoint::setLeftSection(PluginCurveSection *section)
{
  _pLeftSection = section;
}

PluginCurveSection *PluginCurvePoint::rightSection()
{
   return _pRightSection;
}

PluginCurveSection *PluginCurvePoint::leftSection()
{
  return _pLeftSection;
}

void PluginCurvePoint::adjust()
{
  PluginCurveSection *lSection = leftSection();
  PluginCurveSection *rSection = rightSection();
  if (lSection != nullptr)
    lSection->adjust();
  if (rSection != nullptr)
    rSection->adjust();
}

bool PluginCurvePoint::compareXSup(const QPointF &other) const
{
  return this->x()>=other.x();
}

bool PluginCurvePoint::compareXInf(const QPointF &other) const
{
  return this->x()<=other.x();
}

bool PluginCurvePoint::compareYSup(const QPointF &other) const
{
  return this->y()>=other.y();
}

bool PluginCurvePoint::compareYInf(const QPointF &other) const
{
  return this->y()<=other.y();
}

bool PluginCurvePoint::operator>=(const QPointF &other) const
{
  return (this->x()>=other.x());
}

bool PluginCurvePoint::operator<=(const QPointF &other) const
{
  return (this->x()<=other.x());
}

QRectF PluginCurvePoint::boundingRect() const
{
  return QRectF(-SHAPERADIUS,-SHAPERADIUS,2*SHAPERADIUS,2*SHAPERADIUS);
}

QPainterPath PluginCurvePoint::shape() const
{
  QPainterPath circle;
  circle.addEllipse(boundingRect());
  return circle;
}

void PluginCurvePoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  QGraphicsItem::mousePressEvent(event);
}

void PluginCurvePoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  emit(pointPositionHasChanged(this));
  QGraphicsItem::mouseReleaseEvent(event);
}

void PluginCurvePoint::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  QGraphicsItem::mouseMoveEvent(event);
}

void PluginCurvePoint::keyPressEvent(QKeyEvent *event)
{
  QGraphicsItem::keyPressEvent(event);
}

void PluginCurvePoint::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
  highlight();
  QGraphicsItem::hoverEnterEvent(event);
}

void PluginCurvePoint::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
  highlight(false);
  QGraphicsItem::hoverLeaveEvent(event);
}

/// @todo utiliser le signal pointPositionHasChanged !
QVariant PluginCurvePoint::itemChange(GraphicsItemChange change, const QVariant &value)
{
  if (change == ItemPositionHasChanged)
    {
      emit (pointPositionIsChanging(this));
    }
  if (change == ItemSelectedChange)
    {
      // emit (pointSelectedChange(this));
      // update();
    }
  return QGraphicsItem::itemChange(change, value);
}

void PluginCurvePoint::setAllFlags(bool b)
{
  setFlag(QGraphicsItem::ItemIsMovable,b);
  setFlag(QGraphicsItem::ItemIsSelectable,b);
  setFlag(QGraphicsItem::ItemSendsGeometryChanges,b);
}
