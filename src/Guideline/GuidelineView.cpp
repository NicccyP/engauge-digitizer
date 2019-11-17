/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineView.h"
#include "MainWindow.h"
#include <QGraphicsScene>
#include <QMouseEvent>

GuidelineView::GuidelineView (MainWindow &mw,
                              QGraphicsScene *scene,
                              const QString &whatsThis) :
  QGraphicsView (scene)
{
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setWhatsThis (whatsThis);
  setStyleSheet ("background-color: rgba(0, 0, 0, 0)");

  // Update status bar when mouse moves
  connect (this, SIGNAL (signalMouseMoved (QPointF)),
           &mw, SLOT (slotMouseMove (QPointF)));
}

GuidelineView::~GuidelineView ()
{
}

void GuidelineView::mouseMoveEvent (QMouseEvent *event)
{
  emit signalMouseMoved (event->pos ());

  QGraphicsView::mouseMoveEvent (event);
}
