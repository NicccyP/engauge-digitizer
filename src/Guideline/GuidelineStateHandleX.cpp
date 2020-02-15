/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GraphicsScene.h"
#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateHandleX.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateHandleX::GuidelineStateHandleX (GuidelineStateContext &context) :
  GuidelineStateHandleAbstract (context)
{
}

GuidelineStateHandleX::~GuidelineStateHandleX ()
{
}

void GuidelineStateHandleX::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateHandleX::begin";

  beginCommon ();
}

QPointF GuidelineStateHandleX::convertGraphCoordinateToScreenPoint (double valueGraph) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandleX::convertGraphCoordinateToScreenPoint";

  const double ARBITRARY_Y = 0; // Value that is legal in all cases
  QPointF posScreen;
  context().transformation().transformRawGraphToScreen (QPointF (valueGraph,
                                                                 ARBITRARY_Y),
                                                        posScreen);
  return posScreen;
}

double GuidelineStateHandleX::convertScreenPointToGraphCoordinate(const QPointF &posScreen) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandleX::convertScreenPointToGraphCoordinate";

  QPointF posGraph;
  context().transformation().transformScreenToRawGraph (posScreen,
                                                        posGraph);
  return posGraph.x();
}

void GuidelineStateHandleX::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateHandleX::end";
}

void GuidelineStateHandleX::handleMouseRelease (const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandleX::handleMouseRelease";

  context().guideline().detachVisibleGuideline (posScene);
  context().requestStateTransition (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE);
}

QString GuidelineStateHandleX::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_HANDLE_X);
}
