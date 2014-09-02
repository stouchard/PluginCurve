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

#ifndef PLUGINCURVE_HPP
#define PLUGINCURVE_HPP

#include <QObject>
#include <QGraphicsItem>
#include "plugincurvemodel.hpp"
#include "plugincurveview.hpp"
#include "plugincurvepresenter.hpp"

class PluginCurve : public QObject
{
  Q_OBJECT

public:
  //! Construct a PluginCurve.
  /*!
  \param parent Parent item. Should be large enough.
  */
  PluginCurve(QGraphicsObject *parent);
  ~PluginCurve();
  /*! Returns the view. */
  QGraphicsObject *view();
  /*! Hide the grid if b is false. Show the grid if b is true. */
  void setGridVisible(bool b);
  /*! Allow point to cross others points. */
  void setPointCanCross(bool b);
  /*! Activate grid magnetism. */
  void setMagnetism(bool b);
private:
  QGraphicsObject *_pParent;
  PluginCurveModel *_pModel;
  PluginCurvePresenter *_pPresenter;
  PluginCurveView *_pView;
signals :

  // Signals for the plugin users
  void notifyPointCreated(QPointF value);
  void notifyPointDeleted(QPointF value);
  void notifyPointMoved(QPointF oldVal, QPointF newVal);
  void notifySectionCreated(QPointF source, QPointF dest, qreal coef);
  void notifySectionChanged(QPointF source, QPointF dest, qreal coef);
  void notifySectionDeleted(QPointF source, QPointF dest);
  void notifySectionMoved(QPointF oldSource, QPointF oldDest, QPointF newSource, QPointF newDest);

public slots :
};

#endif // PLUGINCURVE_HPP
