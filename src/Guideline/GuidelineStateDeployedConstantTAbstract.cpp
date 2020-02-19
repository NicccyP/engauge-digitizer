/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineLine.h"
#include "GuidelineProjectorConstantT.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantTAbstract.h"
#include "Logger.h"
#include <QGraphicsScene>
#include "Transformation.h"

GuidelineStateDeployedConstantTAbstract::GuidelineStateDeployedConstantTAbstract (GuidelineStateContext &context) :
  GuidelineStateDeployedAbstract (context)
{
}

GuidelineStateDeployedConstantTAbstract::~GuidelineStateDeployedConstantTAbstract ()
{
}

QPointF GuidelineStateDeployedConstantTAbstract::convertGraphCoordinateToScreenPoint (double valueGraph) const
{
  const double ARBITRARY_RANGE = 1.0; // Value that is legal in all cases, including log scaling
  QPointF posScreen;
  context().transformation().transformRawGraphToScreen (QPointF (valueGraph,
                                                                 ARBITRARY_RANGE),
                                                        posScreen);

  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateDeployedConstantTAbstract::convertGraphCoordinateToScreenPoint"
                               << " pos=(" << posScreen.x() << ", " << posScreen.y() << ")";

  return posScreen;
}

double GuidelineStateDeployedConstantTAbstract::convertScreenPointToGraphCoordinate (const QPointF &posScreen) const
{
  QPointF posGraph;
  context().transformation().transformScreenToRawGraph (posScreen,
                                                        posGraph);

  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateDeployedConstantTAbstract::convertScreenPointToGraphCoordinate"
                               << " pos=(" << posGraph.x() << ", " << posGraph.y() << ")";

  return posGraph.x();
}

EllipseParameters GuidelineStateDeployedConstantTAbstract::pointToEllipse (const QPointF & /* posScreen */) const
{
  // pointToLine applies in this state
  return EllipseParameters();
}

QLineF GuidelineStateDeployedConstantTAbstract::pointToLine (const QPointF &posScreen) const
{
  GuidelineProjectorConstantT projector;

  return projector.fromPosScreen (context().transformation(),
                                  sceneRect (),
                                  posScreen);
}

void GuidelineStateDeployedConstantTAbstract::updateWithLatestTransformation ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTAbstract::updateWithLatestTransformation";

  if (!context().transformation().transformIsDefined()) {
    // Discard this Guideline immediately if the transformation transitions to undefined
    context().requestStateTransition(GUIDELINE_STATE_DISCARDED);
  } else {

    GuidelineProjectorConstantT projector;

    GuidelineLine *line = dynamic_cast<GuidelineLine*> (&context().guideline());
    line->setLine (projector.fromCoordinateT (context().transformation(),
                                              sceneRect (),
                                              context().posCursorGraph().x ()));
  }
}
