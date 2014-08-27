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

#ifndef PLUGINCURVEPRESENTER_HPP
#define PLUGINCURVEPRESENTER_HPP

#include <QGraphicsItem>
#include <QCursor>
#include "plugincurvemodel.hpp"
#include "plugincurveview.hpp"
#include "plugincurvepoint.hpp"
#include "plugincurvesection.hpp"
class PluginCurve;


enum EditionMode
{
  LinearSelectionMode, // Select all item betwin 2 positions
  AreaSelectionMode, // Select items in a rubberBand
  PenMode, // Creates points with mouse cursor move
  CreationMode, // Creates points with mouse click
  RecordMode,
  InactivMode
};

class PluginCurvePresenter : public QObject
{
  Q_OBJECT
  //Attributs
public:
 static const int POINTMINDIST= 4; // Minimal Distance on x axis between 2 points
 QRectF _limitRect; // Limit if the points' area in parent coordinates.
 QRectF _scale; // indicates the value of the bottom left point and the topleft point.
 /// @todo Ajouter un attribut scaletype : logarthmic/linear

private:
  PluginCurveModel *_pModel;
  PluginCurveView *_pView;
  ///@todo _editionMode=MainWindow->editionMode().
  ///La valeur par défault doit etre celle choisi par l'utilisateur dans une autre widget (button) .
  EditionMode _editionMode = AreaSelectionMode; // Selection mode
  bool _pointCanCross; // Indicates if a point can cross an other one
  PluginCurvePoint *_lastCreatedPoint; // The last created point
  QPoint _originSelectionRectangle; // Start point of selection Rectangle

  // When the point crossed the previous one, changes the list, curves and the points position
  void crossByRight(PluginCurvePoint *point);
  //When the point crossed the next one, changes the list, curves and the points position
  void crossByLeft(PluginCurvePoint *point);
  // Indicates if a point can be inserted before point
  bool enoughSpaceBefore(PluginCurvePoint *point);
  // Indicates if a point can be inserted after point
  bool enoughSpaceAfter(PluginCurvePoint *point);
  // Returns the value corresponding to the position pos.
  QPointF posToValue(QPointF pos);
  // Returns the position correspondiing to the value val
  QPointF valueToPos(QPointF val);
public:
  PluginCurvePresenter(PluginCurve *parent, PluginCurveModel *model, PluginCurveView *view);
  ~PluginCurvePresenter();
  // Add a curve and updates source and dest points
  PluginCurveSection *addSection(PluginCurvePoint *source, PluginCurvePoint *dest);
  // Add a point at the position qpoint
  PluginCurvePoint *addPoint(QPointF qpoint, MobilityMode mobility = Normal, bool removable = true);
  // Remove a section
  void removeSection(PluginCurveSection *section);
  // Cruelly desintegrate a poor and innocent point
  void removePoint(PluginCurvePoint *point);
  // Change the edition mode
  void setEditionMode(EditionMode editionMode);

signals:
// --> Model
  void stateChanged(bool b);
  void pointRemoved(PluginCurvePoint *point);
  void pointSwapped(int index1,int index2);
  void pointAdded(int,PluginCurvePoint *point);
  void sectionAdded(PluginCurveSection *section);
  void sectionRemoved(PluginCurveSection *section);
// --> View
  void selectionStarted(QPoint point);
  void selectionMoved(QPoint,QPoint);
  void selectItems();
  void changeCursor(QCursor cursor);
// --> PluginCurvePoint
  void setAllFlags(bool b);
// --> PluginCurve, Signals for plugin users
  void notifyPointCreated(QPointF value);
  void notifyPointDeleted(QPointF value);
  void notifyPointMoved(QPointF oldVal, QPointF newVal);
  void notifySectionCreated(QPointF source, QPointF dest, qreal coef);
  void notifySectionChanged(QPointF source, QPointF dest, qreal coef);
  void notifySectionDeleted(QPointF source, QPointF dest);
  void notifySectionMoved(QPointF oldSource, QPointF oldDest, QPointF newSource, QPointF newDest);
public slots:
// View -->
  void doubleClick(QGraphicsSceneMouseEvent *mouseEvent);
  void mousePress(QGraphicsSceneMouseEvent *mouseEvent); // Mouse events reaction
  void mouseMove(QGraphicsSceneMouseEvent *mouseEvent);
  void mouseRelease(QGraphicsSceneMouseEvent *mouseEvent);
  void keyPress(QKeyEvent *keyEvent); // Key event reaction
  void keyRelease(QKeyEvent *keyEvent);
  void viewSceneChanged(QGraphicsScene *);
// PluginCurvePoint -->
  void pointPositionHasChanged(PluginCurvePoint *point);
  void pointPositionIsChanging(PluginCurvePoint *point);

};

#endif // PLUGINCURVEPRESENTER_HPP
