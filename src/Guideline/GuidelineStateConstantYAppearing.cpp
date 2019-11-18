/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateConstantYAppearing.h"
#include "Logger.h"
#include <QGraphicsScene>
#include "Transformation.h"

GuidelineStateConstantYAppearing::GuidelineStateConstantYAppearing (GuidelineStateContext &context) :
  GuidelineStateConstantYAbstract (context)
{
}

GuidelineStateConstantYAppearing::~GuidelineStateConstantYAppearing ()
{
}

void GuidelineStateConstantYAppearing::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateConstantYAppearing::begin";

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible from GuidelineStateConstantYHide

  beginCommon (GuidelineFormat::HOVER_OFF);
}

bool GuidelineStateConstantYAppearing::doPaint () const
{
  return true;
}

void GuidelineStateConstantYAppearing::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateConstantYAppearing::end";
}

void GuidelineStateConstantYAppearing::handleAppearingChange (bool /* appearing */)
{
}

void GuidelineStateConstantYAppearing::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_CONSTANT_Y_HOVER);
}

void GuidelineStateConstantYAppearing::handleHoverLeaveEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_CONSTANT_Y_HOVER
}

void GuidelineStateConstantYAppearing::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_CONSTANT_Y_APPEARING,
                          GUIDELINE_STATE_DISCARDED);
}

void GuidelineStateConstantYAppearing::handleVisibleChange (bool visible)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_CONSTANT_Y_HIDE);
  }
}

QString GuidelineStateConstantYAppearing::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_CONSTANT_Y_APPEARING);
}
