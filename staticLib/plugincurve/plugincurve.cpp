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
#include <QGraphicsItem>
#include "plugincurveview.hpp"
#include "plugincurvemodel.hpp"
#include "plugincurvepresenter.hpp"

PluginCurve::PluginCurve(QGraphicsObject *parent) :
  QObject(parent), _pParent(parent)
{
  //_pStorey = storey;
  _pModel = new PluginCurveModel(this,parent);
  _pView = new PluginCurveView(parent,_pPresenter);
  _pPresenter = new PluginCurvePresenter(this,_pModel,_pView);
  connect(this,SIGNAL(stateChanged(bool)),_pPresenter,SIGNAL(stateChanged(bool)));
  // Creates the last and first points
//  _pPresenter->addPoint(_pPresenter->_limitRect.bottomLeft(),Vertical,false);
//  _pPresenter->addPoint(_pPresenter->_limitRect.topRight(),Vertical,false);
  // edition mode
  // setEditionMode(mainWindow()->editionMode());
  _pPresenter->setEditionMode(AreaSelectionMode); ///@todo Put this line in the presenter ?
}

PluginCurve::~PluginCurve()
{
  delete _pPresenter;
  delete _pView;
  delete _pModel;
  _pModel = NULL;
  _pView = NULL;
  _pPresenter = NULL;
}

QGraphicsObject *PluginCurve::view()
{
  return _pView;
}
