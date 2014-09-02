/*
Copyright: LaBRI / SCRIME

This software is governed by the CeCILL license under French law and
abiding by the rules of distribution of free software.  You can  use,
modify and/ or redistribute the software under the terms of the CeCILL
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability.

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and,  more generally, to use and operate it in the
same conditions as regards security.

The fact that you are presently reading this means that you have had
knowledge of the CeCILL license and that you accept its terms.
*/

#include "plugincurve.hpp"
#include "plugincurvepresenter.hpp"
#include "plugincurveview.hpp"
#include "plugincurvemodel.hpp"
#include "plugincurvesection.hpp"
#include "plugincurvesectionlinear.hpp"
#include "plugincurvepoint.hpp"
#include "plugincurvemap.hpp"
#include "plugincurvegrid.hpp"
#include <QGraphicsSceneEvent>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QCursor>

PluginCurvePresenter::PluginCurvePresenter(PluginCurve *parent, PluginCurveModel *model, PluginCurveView *view) :
  QObject(parent),_pModel(model),_pView(view)
{
  // ** Initialisation **
  qreal minXValue = -2.78;
  qreal minYValue = -19988;
  qreal maxXValue = 5.94;
  qreal maxYValue = 16672;
  // Point's area
  /// @todo prendre l'echelle en paramètre du constructeur (?)
  // Point's area in scale coordinate
  _scale = QRectF(minXValue,minYValue,maxXValue-minXValue,maxYValue-minYValue);
  _limitRect = QRectF(0 + PluginCurvePoint::SHAPERADIUS,
                      0 + PluginCurvePoint::SHAPERADIUS,
                      _pView->boundingRect().width() - 2*PluginCurvePoint::SHAPERADIUS - 2,
                      _pView->boundingRect().height() - 2*PluginCurvePoint::SHAPERADIUS); // Define the points area in paint coordinate
  //
  _pMap = new PluginCurveMap(_scale,_limitRect);
  _pGrid = new PluginCurveGrid(_pView,_pMap);
  // Points behavior
  //_pointCanCross = mainWindow()->pointCanCross();
  _pointCanCross = true;
  _magnetism = true;
  // ** Connections **
  // Presenter --> Model
  connect(this,SIGNAL(stateChanged(bool)),_pModel,SLOT(setState(bool)));
  connect(this,SIGNAL(pointAdded(int,PluginCurvePoint*)),_pModel,SLOT(pointInsert(int,PluginCurvePoint *)));
  connect(this,SIGNAL(pointRemoved(PluginCurvePoint*)),_pModel,SLOT(pointRemoveOne(PluginCurvePoint*)));
  connect(this,SIGNAL(pointSwapped(int,int)),_pModel,SLOT(pointSwap(int,int)));
  connect(this,SIGNAL(sectionAdded(PluginCurveSection *)),_pModel,SLOT(sectionAppend(PluginCurveSection *)));
  connect(this,SIGNAL(sectionRemoved(PluginCurveSection *)),_pModel,SLOT(sectionRemoveOne(PluginCurveSection *)));
  // Presenter --> view
  connect(this,SIGNAL(selectionStarted(QPoint)),_pView,SLOT(startDrawSelectionRectangle(QPoint)));
  connect(this,SIGNAL(selectionMoved(QPoint,QPoint)),_pView,SLOT(drawSelectionrectangle(QPoint,QPoint)));
  connect(this,SIGNAL(selectItems()),_pView,SLOT(selectItems()));
  connect(this,SIGNAL(changeCursor(QCursor)),_pView,SLOT(changeCursor(QCursor)));
  // View --> Presenter
  connect(_pView,SIGNAL(doubleClicked(QGraphicsSceneMouseEvent*)),this,SLOT(doubleClick(QGraphicsSceneMouseEvent*)));
  connect(_pView,SIGNAL(mousePressed(QGraphicsSceneMouseEvent *)),this,SLOT(mousePress(QGraphicsSceneMouseEvent *)));
  connect(_pView,SIGNAL(mouseMoved(QGraphicsSceneMouseEvent *)),this,SLOT(mouseMove(QGraphicsSceneMouseEvent *)));
  connect(_pView,SIGNAL(mouseReleased(QGraphicsSceneMouseEvent *)),this,SLOT(mouseRelease(QGraphicsSceneMouseEvent *)));
  connect(_pView,SIGNAL(keyPressed(QKeyEvent *)),this,SLOT(keyPress(QKeyEvent *)));
  connect(_pView,SIGNAL(keyReleased(QKeyEvent *)),this,SLOT(keyRelease(QKeyEvent *)));
  connect(_pView,SIGNAL(viewSceneChanged(QGraphicsScene *)),this,SLOT(viewSceneChanged(QGraphicsScene *)));
  // Presenter --> PluginCurve
  connect(this,SIGNAL(notifyPointCreated(QPointF)),parent,SIGNAL(notifyPointCreated(QPointF)));
  connect(this,SIGNAL(notifyPointDeleted(QPointF)),parent,SIGNAL(notifyPointDeleted(QPointF)));
  connect(this,SIGNAL(notifyPointMoved(QPointF, QPointF)),parent,SIGNAL(notifyPointMoved(QPointF, QPointF)));
  connect(this,SIGNAL(notifySectionCreated(QPointF, QPointF, qreal)),parent,SIGNAL(notifySectionCreated(QPointF, QPointF, qreal)));
  connect(this,SIGNAL(notifySectionChanged(QPointF, QPointF, qreal)),parent,SIGNAL(notifySectionChanged(QPointF, QPointF, qreal)));
  connect(this,SIGNAL(notifySectionDeleted(QPointF, QPointF)),parent,SIGNAL(notifySectionDeleted(QPointF, QPointF)));
  connect(this,SIGNAL(notifySectionMoved(QPointF, QPointF, QPointF, QPointF)),parent,SIGNAL(notifySectionMoved(QPointF, QPointF, QPointF, QPointF)));

}

PluginCurvePresenter::~PluginCurvePresenter()
{
  //Remove all points
  foreach (PluginCurvePoint *point, _pModel->points())
    {
      removePoint(point);
    }
  delete _pMap;
  delete _pGrid;
}

  ///@todo customize cursors !!!
void PluginCurvePresenter::setEditionMode(EditionMode editionMode)
{
  QPoint origin;
  QPoint dest;
  switch (editionMode)
    {
    case CreationMode:
    case PenMode:
     emit(changeCursor(Qt::CrossCursor));
     emit(setAllFlags(false));
     break;
    case AreaSelectionMode:
      emit(changeCursor(Qt::ArrowCursor));
      emit(setAllFlags(true));
      break;
    case LinearSelectionMode:
      origin = QPoint(_originSelectionRectangle.x(),_pView->boundingRect().y());

      //dest = QPoint(_pView->mapFromGlobal(QCursor::pos()).x(),_pView->boundingRect().y() +_pView->boundingRect().height());
      emit(changeCursor(Qt::IBeamCursor));
      emit(selectionMoved(origin,dest)); // If selection already start, change its size.
      emit(setAllFlags(true));
    default:
      break;
    }
  _editionMode = editionMode;
}

void PluginCurvePresenter::setGridVisible(bool b)
{
    _pGrid->setVisible(b);
}

void PluginCurvePresenter::setMagnetism(bool b)
{
    _magnetism = b;
}

void PluginCurvePresenter::setPointCanCross(bool b)
{
    _pointCanCross = b;
}

void PluginCurvePresenter::crossByLeft(PluginCurvePoint *point)
{
  PluginCurveSection * lSection = point->leftSection();
  PluginCurveSection * rSection = point->rightSection();
  PluginCurveSection * tmpCurve = nullptr; // The 3rd modified curve
  QPointF p = point->pos();
  PluginCurvePoint *next = nullptr;
  int index = -1;
  // Schema :
  // (point)Previous -- (curve)lSection -- (point)This -- (curve)rSection -- (point)Next -- (curve)tmpCurve
  if (rSection != nullptr)
    next=rSection->destPoint(); // else nullptr
  if (next != nullptr)
    tmpCurve = next->rightSection(); // else nullptr
  // if no space
  if (tmpCurve==nullptr || rSection==nullptr || lSection==nullptr || !enoughSpaceAfter(next))
    {
      point->setPos(next->x() - POINTMINDIST,
             p.y());
    }
  else
    {
      //Modifie tmpCurve
      tmpCurve->setSourcePoint(point);
      point->setRightSection(tmpCurve);
      //Modifie lSection
      lSection->setDestPoint(next);
      next->setLeftSection(lSection);
      //Modifie rSection
      rSection->setSourcePoint(next);
      next->setRightSection(rSection);
      rSection->setDestPoint(point);
      point->setLeftSection(rSection);
      // Swap points in the list
      index=_pModel->pointIndexOf(point);
      emit(pointSwapped(index,index+1));
      // Set the point in the other side
      point->setPos(next->x() + POINTMINDIST,
             p.y());
    }
  //point->adjust();
}

void PluginCurvePresenter::crossByRight(PluginCurvePoint *point)
{
  PluginCurveSection * lSection = point->leftSection();
  PluginCurveSection * rSection = point->rightSection();
  PluginCurveSection * tmpCurve = nullptr; // The 3rd modified curve
  QPointF p = point->pos();
  PluginCurvePoint *previous = nullptr;
  int index = -1;
  // Schema :
  // (curve)tmpCurve -- (point)Previous -- (curve)lSection -- (point)This -- (curve)rSection -- (point)Next
  if (lSection != nullptr)
    previous = lSection->sourcePoint(); // else nullptr
  if (previous != nullptr)
    tmpCurve = previous->leftSection();
  if (tmpCurve == nullptr || rSection == nullptr || lSection == nullptr || !enoughSpaceBefore(previous))
    {
      point->setPos(previous->x() + POINTMINDIST,
             p.y());
    }
  else
    {
      //Modifie rSection
      rSection->setSourcePoint(previous);
      previous->setRightSection(rSection);
      //Modifie tmpCurve
      tmpCurve->setDestPoint(point);
      point->setLeftSection(tmpCurve);
      //Modifie lSection
      lSection->setSourcePoint(point);
      point->setRightSection(lSection);
      lSection->setDestPoint(previous);
      previous->setLeftSection(lSection);
      // Swap points in the list
      index=_pModel->pointIndexOf(point);
      emit(pointSwapped(index,index-1));
      // Set the point in the other side
      point->setPos(previous->x() - POINTMINDIST,
             p.y());
    }
  //point->adjust();
}

bool PluginCurvePresenter::enoughSpaceBefore(PluginCurvePoint *point)
{
  PluginCurvePoint *previous = _pModel->previousPoint(point);
  if (previous != NULL)
    return (point->x() - previous->x() >= 2*POINTMINDIST);
  else
    return (point->x() - _limitRect.x() >= POINTMINDIST);
}

bool PluginCurvePresenter::enoughSpaceAfter(PluginCurvePoint *point)
{
  PluginCurvePoint *next = _pModel->nextPoint(point);
  if (next != NULL)
    return (next->x() - point->x() >= 2*POINTMINDIST);
  else
    return (_limitRect.x() + _limitRect.width() - point->x() >= POINTMINDIST);
}

PluginCurveSection *PluginCurvePresenter::addSection(PluginCurvePoint *source, PluginCurvePoint *dest)
{
  // Create the curve in the view
  PluginCurveSection *section = new PluginCurveSectionLinear(_pView,source,dest);
  source->setRightSection(section);
  dest->setLeftSection(section);
  // Emit signal for modifie model
  emit (sectionAdded(section));
  emit (notifySectionCreated(section->sourcePoint()->getValue(),section->destPoint()->getValue(),section->bendingCoef()));
  connect(this,SIGNAL(setAllFlags(bool)),section,SLOT(setAllFlags(bool)));
  connect(section,SIGNAL(doubleClicked(QGraphicsSceneMouseEvent*)),this,SLOT(doubleClick(QGraphicsSceneMouseEvent*)));
  return section;
}

PluginCurvePoint *PluginCurvePresenter::addPoint(QPointF qpoint, MobilityMode mobility, bool removable)
{
  QPointF newPos = qpoint;
  PluginCurvePoint *point = nullptr;
  PluginCurvePoint *previousPoint = nullptr;
  PluginCurvePoint *nextPoint = nullptr;
  PluginCurveSection *rightSection = nullptr;

  // Magnetism
  if (_magnetism == true)
  {
      QPointF magnetPoint = _pGrid->nearestMagnetPoint(newPos);
    if (qAbs(newPos.x() - magnetPoint.x()) <= MAGNETDIST)
    {
        newPos.setX(magnetPoint.x());
    }
    if (qAbs(newPos.y() - magnetPoint.y()) <= MAGNETDIST)
    {
        newPos.setY(magnetPoint.y());
    }
  }

  // Where place the point in the list
  int index = _pModel->pointSearchIndex(newPos);
  // No point added if out the aera
  if (!(_limitRect.contains(newPos)))
    {
      return nullptr;
    }
  // Determine the previous point
  if (index>=0) // There is a previous point
    {
      previousPoint = _pModel->pointAt(index); // else nullptr
    }
  // Determine the next point
  if (index < _pModel->pointSize()-1) // There is a next point
    {
      nextPoint = _pModel->pointAt(index+1); // else nullptr
    }
  // No point added if not enough space
  if ((previousPoint != nullptr && !enoughSpaceAfter(previousPoint)) || // if there is a previous point and not enough space
      (nextPoint != nullptr && !enoughSpaceBefore(nextPoint)) || //  or if there is a next point and not enough space
      (_limitRect.width()<0)) // or there is no points and no space at all
    {
      return nullptr;
    }
  // Correct the point position if too close of another one
  if (previousPoint != nullptr && newPos.x()-previousPoint->x() < POINTMINDIST)
    {
      newPos = QPointF(previousPoint->x() + POINTMINDIST,
                       newPos.y());
    }
  if (nextPoint != nullptr && nextPoint->x() - newPos.x() < POINTMINDIST)
    {
      newPos = QPointF(nextPoint->x() - POINTMINDIST,
                      newPos.y());
    }
  // Instanciation and initialisation
  // -----> DELETE
  //newPos = _pGrid->nearestMagnetPoint(newPos);
  // <----- DELETE
  point = new PluginCurvePoint(_pView,newPos,_pMap->paintToScale(newPos),mobility,removable);
  emit(notifyPointCreated(_pMap->paintToScale(newPos))); // Notify the user
  //Create a new curve, update previousPoint and point.
  if (previousPoint != nullptr)
    addSection(previousPoint,point);
  /// @todo Creer une fonction setSourcePoint / setDestPoint (pour regrouper ces trois lignes) ???
  //Modifie the old one and updates the points.
  if (nextPoint != nullptr)
    {
      rightSection = nextPoint->leftSection();
      if (rightSection != nullptr)
        {
          QPointF oldSourcePoint =  previousPoint->getValue();
          QPointF oldDestPoint = nextPoint->getValue();
          rightSection->setSourcePoint(point);
          point->setRightSection(rightSection);
          emit(notifySectionMoved(oldSourcePoint,oldDestPoint,point->getValue(),oldDestPoint));
        }
      else // No curve, a new one need to be created
        {
          rightSection = addSection(point,nextPoint);
        }
    }
  // Add points and curves in the view

  emit(pointAdded(index+1,point));
  connect(point,SIGNAL(pointPositionHasChanged()),this,SLOT(pointPositionHasChanged()));
  connect(point,SIGNAL(pointPositionIsChanging(PluginCurvePoint*)),this,SLOT(pointPositionIsChanging(PluginCurvePoint*)));
  connect(this,SIGNAL(setAllFlags(bool)),point,SLOT(setAllFlags(bool)));
  return point;
}

void PluginCurvePresenter::removeSection(PluginCurveSection *section)
{
  if (section == nullptr)
    return;
  PluginCurvePoint *source = section->sourcePoint();
  PluginCurvePoint *dest = section->destPoint();
  if (source != nullptr)
    source->setRightSection(nullptr);
  if (source != nullptr)
    dest->setLeftSection(nullptr);
  //section->scene()->removeItem(section);
  emit(sectionRemoved(section));
  emit(notifySectionDeleted(section->sourcePoint()->getValue(),section->destPoint()->getValue()));
  //section->hide();
  section->deleteLater();
}

void PluginCurvePresenter::removePoint(PluginCurvePoint *point)
{
  if (point == nullptr)
    return;
  point->setSelected(false);
  PluginCurvePoint *previous = nullptr;
  PluginCurveSection *leftSection = point->leftSection();
  PluginCurveSection *rightSection = point->rightSection();
//  point->setRightSection(nullptr);
//  point->setLeftSection(nullptr);
  if (leftSection != nullptr) // There is a previous point
    {
      previous = leftSection->sourcePoint(); // else NULL
      removeSection(leftSection); // Delete the left curve
      leftSection = nullptr; // Pointer useless now
    }
  if (rightSection != nullptr)
    {
      //next = rightSection->destPoint(); // else Null
      if (previous != nullptr) // There is a previous point
        {
          rightSection->setSourcePoint(previous); // Keep the right curve, change its source point
          rightSection->adjust();
        }
      else // No previous point
        {
          removeSection(rightSection);
          rightSection = nullptr; // Pointer useless now
        }
    }
  if (previous != nullptr)
    {
      previous->setRightSection(rightSection);
    }
//  if (next != nullptr)
//    {
//      next->setLeftSection(rightSection);
//    }
  emit (pointRemoved(point));
  emit (notifyPointDeleted(point->getValue()));
  //point->scene()->removeItem(point);
  //point->hide();
  point->deleteLater();
}

void PluginCurvePresenter::doubleClick(QGraphicsSceneMouseEvent *mouseEvent)
{
  if (mouseEvent->button() == Qt::LeftButton)
    {
      _pView->scene()->clearSelection();
      _lastCreatedPoint = addPoint(_pView->mapFromScene(mouseEvent->scenePos())); // ->pos() isn't correct here
      emit(setAllFlags(true));
    }
}

void PluginCurvePresenter::mousePress(QGraphicsSceneMouseEvent *mouseEvent)
{
    switch (_editionMode)
      {
      case CreationMode :
      case PenMode :
        if (mouseEvent->button() == Qt::LeftButton)
          {
            _pView->scene()->clearSelection();
            _lastCreatedPoint = addPoint(mouseEvent->pos());
            emit(setAllFlags(true));
          }
        break;
      case AreaSelectionMode :
        mouseEvent->accept();
        if (mouseEvent->button() == Qt::LeftButton)
          {
            _originSelectionRectangle = mouseEvent->pos().toPoint();
            _pView->scene()->clearSelection();
            emit(selectionStarted(_originSelectionRectangle));
          }
        break;
      case LinearSelectionMode :
        mouseEvent->accept();
        if (mouseEvent->button() == Qt::LeftButton)
          {
            _originSelectionRectangle = mouseEvent->pos().toPoint();
            _pView->scene()->clearSelection();
            emit(selectionStarted(QPoint(_originSelectionRectangle.x(),_pView->boundingRect().y())));
          }
        break;
      default :
        break;
      }
}

void PluginCurvePresenter::mouseMove(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPoint destinationSelectionRectangle;
    QRect boundingRect = _pView->boundingRect().toRect();
    switch (_editionMode)
      {
      case CreationMode :
        if (_lastCreatedPoint != nullptr)
          _lastCreatedPoint->setPos(mouseEvent->pos());
        break;
      case PenMode :
        addPoint(mouseEvent->pos());
        break;
      case AreaSelectionMode :
        destinationSelectionRectangle = mouseEvent->pos().toPoint();
        emit(selectionMoved(_originSelectionRectangle,destinationSelectionRectangle));
        break;
      case LinearSelectionMode :
        destinationSelectionRectangle = QPoint(mouseEvent->pos().x(),boundingRect.y()+boundingRect.height());
        emit(selectionMoved(QPoint(_originSelectionRectangle.x(),boundingRect.y()),destinationSelectionRectangle));
        break;
      default :
        break;
      }
}

void PluginCurvePresenter::mouseRelease(QGraphicsSceneMouseEvent *mouseEvent)
{
    switch (_editionMode)
      {
      case CreationMode :
        if (mouseEvent->button() == Qt::LeftButton)
          {
            _lastCreatedPoint = nullptr;
          }
        break;
      case AreaSelectionMode :
      case LinearSelectionMode :
        if (mouseEvent->button() == Qt::LeftButton)
          {
            emit (selectItems());
          }
        break;
      default :
        break;
      }
}

void PluginCurvePresenter::keyPress(QKeyEvent *keyEvent)
{
  switch (keyEvent->key())
    {
    case Qt::Key_Shift:
      setEditionMode(LinearSelectionMode);
      break;
    case Qt::Key_Alt :
      setEditionMode(PenMode);
      break;
    case Qt::Key_Backspace :
      QListIterator<PluginCurvePoint *> iterator(_pModel->points());
      PluginCurvePoint *point;
      //QGraphicsItem *item;
      while (iterator.hasNext())
        {
          point = iterator.next();
          if (point != nullptr && point->removable() && point->isSelected())
            {
              removePoint(point);
            }
        }
    }
  //QGraphicsObject::keyPressEvent(keyEvent);
}

void PluginCurvePresenter::keyRelease(QKeyEvent *keyEvent)
{
    switch (keyEvent->key())
    {
      case Qt::Key_Alt:
      case Qt::Key_Shift:
        //setEditionMode(mainwindow()->editionMode());
        setEditionMode(AreaSelectionMode);
        break;
      default :
        break;
    }
   // QGraphicsObject::keyReleaseEvent(keyEvent);
}

void PluginCurvePresenter::viewSceneChanged(QGraphicsScene * scene)
{
  Q_UNUSED(scene);
  _limitRect = QRectF(0 + PluginCurvePoint::SHAPERADIUS,
                                          0 + PluginCurvePoint::SHAPERADIUS,
                                          _pView->boundingRect().width() - 2*PluginCurvePoint::SHAPERADIUS - 2,
                                          _pView->boundingRect().height() - 2*PluginCurvePoint::SHAPERADIUS);
  _pMap->setPaintRect(_limitRect);

}

void PluginCurvePresenter::pointPositionIsChanging(PluginCurvePoint *point)
{
  if (point == nullptr)
    return;
  PluginCurveSection * lSection = point->leftSection();
  PluginCurveSection * rSection = point->rightSection();
  QRectF rect = _limitRect; // define limit points positions
  QPointF oldPos = point->pos();
  QPointF newPos = point->pos();
  PluginCurvePoint * previous = nullptr;
  PluginCurvePoint * next = nullptr;
  if (lSection != nullptr)
    previous=lSection->sourcePoint(); // else nullptr
  if (rSection != nullptr)
    next=rSection->destPoint(); // else nullptr
  // Schema :
  // (point)Previous -- (curve)lSection -- (point)This -- (curve)rSection -- (point)Next

  // Magnetism
  if (_magnetism == true)
  {
      QPointF magnetPoint = _pGrid->nearestMagnetPoint(oldPos);
    if (qAbs(newPos.x() - magnetPoint.x()) <= MAGNETDIST)
    {
        newPos.setX(magnetPoint.x());
    }
    if (qAbs(newPos.y() - magnetPoint.y()) <= MAGNETDIST)
    {
        newPos.setY(magnetPoint.y());
    }
  }
  //Respect the minimum distance between points
  if (previous != nullptr && oldPos.x() < previous->x() + POINTMINDIST)
    newPos.setX(previous->x() + POINTMINDIST);
  if (next != nullptr && oldPos.x() > next->x() - POINTMINDIST)
    newPos.setX(next->x() - POINTMINDIST);

  // if the point is out the storey
  if (rect.x() > newPos.x())
    newPos.setX(rect.x());
  if (rect.y() > newPos.y())
    newPos.setY(rect.y());
  if (rect.x() + rect.width() < newPos.x())
    newPos.setX(rect.x() + rect.width());
  if (rect.y() + rect.height() < newPos.y())
    newPos.setY(rect.y() + rect.height());
  //if the point can't move horizontally
  if (point->mobility() == Vertical && point->fixedCoordinate() != oldPos.x())
    {
      //oldPos.setX(point->fixedCoordinate());
      newPos.setX(point->fixedCoordinate());
    }
  point->setPos(newPos);

  // When the point reach another one
  // 3 curve must be modified.
  if (_pointCanCross)
    {
      if (next != nullptr && oldPos.x() > next->x())
        {
          crossByLeft(point);
        }
      if (previous != nullptr && oldPos.x() < previous->x())
        {
          crossByRight(point);
        }
    }
  //Adjust the Curves position.
  point->adjust();
}

void PluginCurvePresenter::pointPositionHasChanged()
{
    QListIterator<PluginCurvePoint *> iterator(_pModel->points());
    PluginCurvePoint *point;
    //QGraphicsItem *item;
    while (iterator.hasNext())
      {
        point = iterator.next();
        if (point != nullptr && point->isSelected())
          {
            // Update the point value
            QPointF oldvalue = point->getValue();
            point->setValue(_pMap->paintToScale(point->pos()));
            // Notify the plugin users
            emit(notifyPointMoved(oldvalue,point->getValue()));
            //emit(notifySectionMoved());
          }
      }

}
