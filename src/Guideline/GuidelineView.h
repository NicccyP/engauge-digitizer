/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_VIEW_H
#define GUIDELINE_VIEW_H

#include <QGraphicsView>
#include <QPointF>

class MainWindow;
class QGraphicsScene;
class QMouseEvent;

/// This class adds a signal to QGraphicsView so the cursor position can be updated in the status bar
class GuidelineView : public QGraphicsView
{
  Q_OBJECT;
  
public:
  /// Single constructor.
  GuidelineView (MainWindow &mw,
                 QGraphicsScene *scene,
                 const QString &whatsThis);
  ~GuidelineView ();

  /// Intercept mouse move event and relay the information through the signal
  virtual void mouseMoveEvent (QMouseEvent *event);
  
signals:
  /// Signal to send cursor coordinates to MainWindow for display in the status bar
  void signalMouseMoved (QPointF pos);

private:
  GuidelineView();
};

#endif // GUIDELINE_VIEW_H
