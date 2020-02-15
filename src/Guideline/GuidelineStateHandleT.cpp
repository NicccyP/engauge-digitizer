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
#include "GuidelineStateHandleT.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateHandleT::GuidelineStateHandleT (GuidelineStateContext &context) :
  GuidelineStateHandleAbstract (context)
{
}

GuidelineStateHandleT::~GuidelineStateHandleT ()
{
}

void GuidelineStateHandleT::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateHandleT::begin";

  beginCommon ();
}

QPointF GuidelineStateHandleT::convertGraphCoordinateToScreenPoint (double valueGraph) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandleT::convertGraphCoordinateToScreenPoint";

  const double ARBITRARY_RANGE = 0; // Value that is legal in all cases
  QPointF posScreen;
  context().transformation().transformRawGraphToScreen (QPointF (valueGraph,
                                                                 ARBITRARY_RANGE),
                                                        posScreen);
  return posScreen;
}

double GuidelineStateHandleT::convertScreenPointToGraphCoordinate(const QPointF &posScreen) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandleT::convertScreenPointToGraphCoordinate";

  QPointF posGraph;
  context().transformation().transformScreenToRawGraph (posScreen,
                                                        posGraph);
  return posGraph.x();
}

void GuidelineStateHandleT::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateHandleT::end";
}

void GuidelineStateHandleT::handleMouseRelease (const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandleT::handleMouseRelease";

  context().guideline().detachVisibleGuideline (posScene);
  context().requestStateTransition (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE);
}

QString GuidelineStateHandleT::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_HANDLE_T);
}
