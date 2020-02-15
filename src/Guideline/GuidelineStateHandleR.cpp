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
#include "GuidelineStateHandleR.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateHandleR::GuidelineStateHandleR (GuidelineStateContext &context) :
  GuidelineStateHandleAbstract (context)
{
}

GuidelineStateHandleR::~GuidelineStateHandleR ()
{
}

void GuidelineStateHandleR::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateHandleR::begin";

  beginCommon ();
}

QPointF GuidelineStateHandleR::convertGraphCoordinateToScreenPoint (double valueGraph) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandleR::convertGraphCoordinateToScreenPoint";

  const double ARBITRARY_THETA = 0; // Value that is legal in all cases
  QPointF posScreen;
  context().transformation().transformRawGraphToScreen (QPointF (ARBITRARY_THETA,
                                                                 valueGraph),
                                                        posScreen);
  return posScreen;
}

double GuidelineStateHandleR::convertScreenPointToGraphCoordinate(const QPointF &posScreen) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandleR::convertScreenPointToGraphCoordinate";

  QPointF posGraph;
  context().transformation().transformScreenToRawGraph (posScreen,
                                                        posGraph);
  return posGraph.y();
}

void GuidelineStateHandleR::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateHandleR::end";
}

void GuidelineStateHandleR::handleMouseRelease (const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandleR::handleMouseRelease";

  context().guideline().detachVisibleGuideline (posScene);
  context().requestStateTransition (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE);
}

QString GuidelineStateHandleR::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_HANDLE_R);
}
