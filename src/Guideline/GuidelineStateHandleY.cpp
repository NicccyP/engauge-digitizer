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
#include "GuidelineStateHandleY.h"
#include "Logger.h"

GuidelineStateHandleY::GuidelineStateHandleY (GuidelineStateContext &context) :
  GuidelineStateHandleAbstract (context)
{
}

GuidelineStateHandleY::~GuidelineStateHandleY ()
{
}

void GuidelineStateHandleY::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateHandleY::begin";

  beginCommon ();
}

void GuidelineStateHandleY::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateHandleY::end";
}

void GuidelineStateHandleY::handleMouseRelease (const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandleY::handleMouseRelease";

  context().guideline().detachVisibleGuideline (posScene);
  context().requestStateTransition (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE);
}

QString GuidelineStateHandleY::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_HANDLE_Y);
}
