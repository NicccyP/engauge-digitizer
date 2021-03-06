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
#include "GuidelineStateDeployedConstantRAppearing.h"
#include "Logger.h"
#include <QObject>
#include <QTimer>
#include "Transformation.h"

GuidelineStateDeployedConstantRAppearing::GuidelineStateDeployedConstantRAppearing (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantRAbstract (context),
  m_timer (nullptr)
{
  m_timer = new QTimer ();
  m_timer->setSingleShot (true);  
}

GuidelineStateDeployedConstantRAppearing::~GuidelineStateDeployedConstantRAppearing ()
{
}

void GuidelineStateDeployedConstantRAppearing::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRAppearing::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_ON,
               false);

  // (Re)connect to timer
  QObject::connect (m_timer, SIGNAL (timeout ()), &context(), SLOT (slotTimeout ()));
  m_timer->start (APPEARING_TIMEOUT);
}

bool GuidelineStateDeployedConstantRAppearing::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantRAppearing::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRAppearing::end";

  // Cancel timer if active so it does not interrupt the next state
  QObject::disconnect (m_timer, SIGNAL (timeout ()), &context(), SLOT (slotTimeout ()));
}

void GuidelineStateDeployedConstantRAppearing::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantRAppearing::handleGuidelineMode (bool visible,
                                                                    bool locked)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HIDE);
  } else if (locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_LOCKED);
  }
}

void GuidelineStateDeployedConstantRAppearing::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HOVER);
}

void GuidelineStateDeployedConstantRAppearing::handleHoverLeaveEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HOVER
}

void GuidelineStateDeployedConstantRAppearing::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_R,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_R_APPEARING);
}

void GuidelineStateDeployedConstantRAppearing::handleTimeout ()
{
  context().requestStateTransition (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE);
}

QString GuidelineStateDeployedConstantRAppearing::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_APPEARING);
}

