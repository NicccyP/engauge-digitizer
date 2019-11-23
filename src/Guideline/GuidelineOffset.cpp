/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineOffset.h"
#include <QGraphicsView>

const bool ADD_TO_EDGE = true;
const double GUIDELINE_OFFSET_PORTION_OF_SCREEN_WIDTH = 0.05;
const bool SUBTRACT_FROM_EDGE = false;

GuidelineOffset::GuidelineOffset()
{
}

QPointF GuidelineOffset::bottom (const QGraphicsView &view) const
{
  return bottomTop (view,
                    SUBTRACT_FROM_EDGE);
}

QPointF GuidelineOffset::bottomTop (const QGraphicsView &view,
                                    bool add) const
{
  // Get scrolled extent so new Guideline appears in visible portion
  QRect viewportRect = view.viewport()->rect();
  QRect scrolledRect = view.viewportTransform ().inverted ().mapRect (viewportRect);

  double offset = scrolledRect.height () * GUIDELINE_OFFSET_PORTION_OF_SCREEN_WIDTH;
  
  // Halfway across and a little above-bottom/below-top if offsetVertical is negative/positive
  double x = scrolledRect.center().x();
  double y = (add ?
              scrolledRect.y () + offset :
              scrolledRect.y () + scrolledRect.height () - offset);

  return QPointF (x, y);
}

QPointF GuidelineOffset::left (const QGraphicsView &view) const
{
  return leftRight (view,
                    ADD_TO_EDGE);
}
                    
QPointF GuidelineOffset::leftRight(const QGraphicsView &view,
                                   bool add) const
{
  // Get scrolled extent so new Guideline appears in visible portion
  QRect viewportRect = view.viewport()->rect();
  QRect scrolledRect = view.viewportTransform ().inverted ().mapRect (viewportRect);

  double offset = scrolledRect.width () * GUIDELINE_OFFSET_PORTION_OF_SCREEN_WIDTH;
  
  // Halfway down and a little left-of-right/right-of-left if offsetHorizontal is negative/positive
  double x = (add ?
              scrolledRect.x () + offset :
              scrolledRect.x () + scrolledRect.width () - offset);
  double y =  scrolledRect.center().y();

  return QPointF (x, y);
}

QPointF GuidelineOffset::right (const QGraphicsView &view) const
{
  return leftRight (view,
                    SUBTRACT_FROM_EDGE);
}

QPointF GuidelineOffset::top (const QGraphicsView &view) const
{
  return bottomTop (view,
                    ADD_TO_EDGE);
}
