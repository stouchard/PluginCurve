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

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QGraphicsView>
#include <QTextBrowser>
#include <QCheckBox>
class QGraphicsView;
class PluginCurve;

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT


private:
  PluginCurve *_pPluginCurve;
  QGraphicsView *_pView;
  QTextBrowser *_pTextBrowser;
  QMenu *_pMenuMode;
  QCheckBox *_cBPointCross;
  QCheckBox *_cBGrid;
  QCheckBox *_cBMagnet;
  Ui::MainWindow *ui;

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
private:
  void createGraphics();
  void createTextBrowser();
  void createMenu();
  void createCB();
public slots:
  void pointCreated(QPointF point);
  void pointDeleted(QPointF point);
  void pointMoved(QPointF oldPos, QPointF newPos);
  void sectionCreated(QPointF source, QPointF dest, qreal coef);
  void sectionDeleted(QPointF source, QPointF dest);
  void sectionMoved(QPointF oldSource,QPointF oldDest,QPointF newSource, QPointF newDest);
  void setGridVisible(int i);
  void setMagnetism (int i);
  void setPointCanCross(int i);

};

#endif // MAINWINDOW_HPP
