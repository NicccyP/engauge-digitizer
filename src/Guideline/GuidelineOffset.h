/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_OFFSET_H
#define GUIDELINE_OFFSET_H

#include <QPointF>

class QGraphicsView;

/// Calculate offset from edge for new Guidelines
class GuidelineOffset
{
public:
  GuidelineOffset();
  
  /// Compute offset from bottom side
  QPointF bottom (const QGraphicsView &view) const;
  
  /// Compute offset from left side
  QPointF left (const QGraphicsView &view) const;
  
  /// Compute offset from right side
  QPointF right (const QGraphicsView &view) const;
  
  /// Compute offset from top side
  QPointF top (const QGraphicsView &view) const;

private:

  QPointF bottomTop (const QGraphicsView &view,
                     bool add) const;
  QPointF leftRight (const QGraphicsView &view,
                     bool add) const;    
  
};

#endif // GUIDELINE_OFFSET_H
