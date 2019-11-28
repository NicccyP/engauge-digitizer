/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineOffset.h"
#include <QGraphicsView>
#include "Transformation.h"

const bool ADD_TO_EDGE = true;
const double GUIDELINE_OFFSET_PORTION_OF_SCREEN_WIDTH = 0.05;
const bool SUBTRACT_FROM_EDGE = false;

GuidelineOffset::GuidelineOffset()
{
}

QPointF GuidelineOffset::bottom (const QGraphicsView &view,
                                 const Transformation &transformation) const
{
  return bottomTop (view,
                    transformation,
                    SUBTRACT_FROM_EDGE);
}

QPointF GuidelineOffset::bottomTop (const QGraphicsView &view,
                                    const Transformation &transformation,
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

  QPointF posScene (x, y), posGraph;

  transformation.transformScreenToRawGraph (posScene,
                                            posGraph);

  return posGraph;
}

QPointF GuidelineOffset::left (const QGraphicsView &view,
                               const Transformation &transformation) const
{
  return leftRight (view,
                    transformation,
                    ADD_TO_EDGE);
}
                    
QPointF GuidelineOffset::leftRight(const QGraphicsView &view,
                                   const Transformation &transformation,
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

  QPointF posScene (x, y), posGraph;

  transformation.transformScreenToRawGraph (posScene,
                                            posGraph);

  return posGraph;
}

QPointF GuidelineOffset::right (const QGraphicsView &view,
                                const Transformation &transformation) const
{
  return leftRight (view,
                    transformation,
                    SUBTRACT_FROM_EDGE);
}

QPointF GuidelineOffset::top (const QGraphicsView &view,
                              const Transformation &transformation) const
{
  return bottomTop (view,
                    transformation,
                    ADD_TO_EDGE);
}
