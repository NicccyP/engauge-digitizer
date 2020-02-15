/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineState.h"
#include "GuidelineStateConstantRAppearing.h"
#include "GuidelineStateContext.h"
#include "Logger.h"
#include <QGraphicsScene>
#include "Transformation.h"

GuidelineStateConstantRAppearing::GuidelineStateConstantRAppearing (GuidelineStateContext &context) :
  GuidelineStateConstantRAbstract (context)
{
}

GuidelineStateConstantRAppearing::~GuidelineStateConstantRAppearing ()
{
}

void GuidelineStateConstantRAppearing::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateConstantRAppearing::begin";

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible from GuidelineStateConstantRHide

  beginCommon (GuidelineFormat::HOVER_OFF);
}

bool GuidelineStateConstantRAppearing::doPaint () const
{
  return true;
}

void GuidelineStateConstantRAppearing::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateConstantRAppearing::end";
}

void GuidelineStateConstantRAppearing::handleAppearingChange (bool /* appearing */)
{
}

void GuidelineStateConstantRAppearing::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_CONSTANT_R_HOVER);
}

void GuidelineStateConstantRAppearing::handleHoverLeaveEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_CONSTANT_R_HOVER
}

void GuidelineStateConstantRAppearing::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_R);
}

void GuidelineStateConstantRAppearing::handleVisibleChange (bool visible)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_CONSTANT_R_HIDE);
  }
}

QString GuidelineStateConstantRAppearing::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_CONSTANT_R_APPEARING);
}
