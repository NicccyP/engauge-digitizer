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
