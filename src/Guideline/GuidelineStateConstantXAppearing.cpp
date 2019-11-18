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
#include "GuidelineStateConstantXAppearing.h"
#include "Logger.h"
#include <QGraphicsScene>
#include "Transformation.h"

GuidelineStateConstantXAppearing::GuidelineStateConstantXAppearing (GuidelineStateContext &context) :
  GuidelineStateConstantXAbstract (context)
{
}

GuidelineStateConstantXAppearing::~GuidelineStateConstantXAppearing ()
{
}

void GuidelineStateConstantXAppearing::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateConstantXAppearing::begin";

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible from GuidelineStateConstantXHide

  beginCommon (GuidelineFormat::HOVER_OFF);
}

bool GuidelineStateConstantXAppearing::doPaint () const
{
  return true;
}

void GuidelineStateConstantXAppearing::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateConstantXAppearing::end";
}

void GuidelineStateConstantXAppearing::handleAppearingChange (bool /* appearing */)
{
}

void GuidelineStateConstantXAppearing::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_CONSTANT_X_HOVER);
}

void GuidelineStateConstantXAppearing::handleHoverLeaveEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_CONSTANT_X_HOVER
}

void GuidelineStateConstantXAppearing::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_CONSTANT_X_APPEARING,
                          GUIDELINE_STATE_DISCARDED);
}

void GuidelineStateConstantXAppearing::handleVisibleChange (bool visible)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_CONSTANT_X_HIDE);
  }
}

QString GuidelineStateConstantXAppearing::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_CONSTANT_X_APPEARING);
}
