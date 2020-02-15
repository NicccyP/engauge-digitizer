/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineState.h"
#include "GuidelineStateConstantTAppearing.h"
#include "GuidelineStateContext.h"
#include "Logger.h"
#include <QGraphicsScene>
#include "Transformation.h"

GuidelineStateConstantTAppearing::GuidelineStateConstantTAppearing (GuidelineStateContext &context) :
  GuidelineStateConstantTAbstract (context)
{
}

GuidelineStateConstantTAppearing::~GuidelineStateConstantTAppearing ()
{
}

void GuidelineStateConstantTAppearing::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateConstantTAppearing::begin";

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible from GuidelineStateConstantTHide

  beginCommon (GuidelineFormat::HOVER_OFF);
}

bool GuidelineStateConstantTAppearing::doPaint () const
{
  return true;
}

void GuidelineStateConstantTAppearing::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateConstantTAppearing::end";
}

void GuidelineStateConstantTAppearing::handleAppearingChange (bool /* active */)
{
}

void GuidelineStateConstantTAppearing::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_CONSTANT_T_HOVER);
}

void GuidelineStateConstantTAppearing::handleHoverLeaveEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_CONSTANT_T_HOVER
}

void GuidelineStateConstantTAppearing::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_T);
}

void GuidelineStateConstantTAppearing::handleVisibleChange (bool visible)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_CONSTANT_T_HIDE);
  }
}

QString GuidelineStateConstantTAppearing::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_CONSTANT_T_APPEARING);
}
