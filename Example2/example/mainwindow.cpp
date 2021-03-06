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

#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "plugincurve.hpp"
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  createTextBrowser();
  createGraphics();
  createMenu();
  createCB();
}

void MainWindow::createGraphics()
{
  _pView = ui->graphicsView;
  QGraphicsScene *scene = new QGraphicsScene(_pView->rect(),0);
  scene->setBackgroundBrush(Qt::gray);
  _pView->setScene(scene);
  QGraphicsRectItem *rect = new QGraphicsRectItem();
  rect->setRect(0,0,200,200);
  _pPluginCurve = new PluginCurve(0);
  connect(_pPluginCurve,SIGNAL(notifyPointCreated(QPointF)),this,SLOT(pointCreated(QPointF)));
  connect(_pPluginCurve,SIGNAL(notifyPointDeleted(QPointF)),this,SLOT(pointDeleted(QPointF)));
  connect(_pPluginCurve,SIGNAL(notifyPointMoved(QPointF,QPointF)),this,SLOT(pointMoved(QPointF,QPointF)));
  connect(_pPluginCurve,SIGNAL(notifySectionCreated(QPointF,QPointF,qreal)),this,SLOT(sectionCreated(QPointF,QPointF,qreal)));
  connect(_pPluginCurve,SIGNAL(notifySectionDeleted(QPointF,QPointF)),this,SLOT(sectionDeleted(QPointF,QPointF)));
  connect(_pPluginCurve,SIGNAL(notifySectionMoved(QPointF,QPointF,QPointF,QPointF)),this,SLOT(sectionMoved(QPointF,QPointF,QPointF,QPointF)));
//  PluginCurve *plugincurve = new PluginCurve(rect->toGraphicsObject());
//  scene->addItem(rect);
  scene->addItem(_pPluginCurve->view());
  rect->show();
  _pView->update();
  _pView->show();
}

void MainWindow::createTextBrowser()
{
  _pTextBrowser = ui->textBrowser;
  _pTextBrowser->setReadOnly(true);
}

void MainWindow::createMenu()
{

}

void MainWindow::createCB()
{
  _cBGrid = ui->cBGrid;
  _cBMagnet = ui->cBMagnet;
  _cBPointCross = ui->cBPointCross;

  connect(_cBGrid,SIGNAL(stateChanged(int)),this,SLOT(setGridVisible(int)));
  connect(_cBMagnet,SIGNAL(stateChanged(int)),this,SLOT(setMagnetism(int)));
  connect(_cBPointCross,SIGNAL(stateChanged(int)),this,SLOT(setPointCanCross(int)));
}

void MainWindow::pointCreated(QPointF point)
{
  QString str = QString("Point created : (%1 , %2)").arg(point.x()).arg(point.y());
  _pTextBrowser->append(str);
}

void MainWindow::pointDeleted(QPointF point)
{
  QString str = QString("Point deleted : (%1 , %2)").arg(point.x()).arg(point.y());
  _pTextBrowser->append(str);
}

void MainWindow::pointMoved(QPointF oldPos, QPointF newPos)
{
  QString str = QString("Point Moved from (%1 , %2) to (%3 , %4)")
          .arg(oldPos.x()).arg(oldPos.y()).arg(newPos.x()).arg(newPos.y());
  _pTextBrowser->append(str);
}

void MainWindow::sectionCreated(QPointF source, QPointF dest, qreal coef)
{
  QString str = QString("Section created (%1 , %2) - (%3 , %4), coefficient : %5")
            .arg(source.x()).arg(source.y()).arg(dest.x()).arg(dest.y()).arg(coef);
  _pTextBrowser->append(str);
}

void MainWindow::sectionDeleted(QPointF source, QPointF dest)
{

  QString str = QString("Section deleted (%1 , %2) - (%3 , %4)")
              .arg(source.x()).arg(source.y()).arg(dest.x()).arg(dest.y());
  _pTextBrowser->append(str);
}

void MainWindow::sectionMoved(QPointF oldSource, QPointF oldDest, QPointF newSource, QPointF newDest)
{
  QString str = QString("Section moved from (%1 , %2) - (%3 , %4) to (%5 , %6) - (%7 , %8)")
            .arg(oldSource.x()).arg(oldSource.y())
            .arg(oldDest.x()).arg(oldDest.y())
            .arg(newSource.x()).arg(newSource.y())
            .arg(newDest.x()).arg(newDest.y());
  _pTextBrowser->append(str);
}

void MainWindow::setGridVisible(int i)
{
  if (i==0)
    _pPluginCurve->setGridVisible(false);
  else
    _pPluginCurve->setGridVisible(true);
}

void MainWindow::setMagnetism(int i)
{
    if (i==0)
      _pPluginCurve->setMagnetism(false);
    else
      _pPluginCurve->setMagnetism(true);
}

void MainWindow::setPointCanCross(int i)
{
  if (i==0)
    _pPluginCurve->setPointCanCross(false);
  else
    _pPluginCurve->setPointCanCross(true);
}

MainWindow::~MainWindow()
{
  delete ui;
}
