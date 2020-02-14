/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DataKey.h"
#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include "GraphicsItemType.h"
#include "GuidelineAbstract.h"
#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "Guidelines.h"
#include "GuidelineStateContext.h"
#include "Logger.h"
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QLineF>
#include <qmath.h>
#include <QMouseEvent>
#include <QPen>
#include <QTextStream>
#include <QWidget>
#include "Transformation.h"
#include "ZValues.h"

GuidelineAbstract::GuidelineAbstract(QGraphicsScene &scene) :
  m_scene (scene),
  m_context (nullptr),
  m_guidelineVisible (nullptr)
{
}

GuidelineAbstract::~GuidelineAbstract ()
{
  delete m_context;
}

void GuidelineAbstract::bindGuidelineVisible (GuidelineAbstract *guidelineVisible)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineAbstract::bindGuidelineVisible state=" << m_context->stateName ().toLatin1().data();

  m_guidelineVisible = guidelineVisible;

  connect (this, SIGNAL (signalHandleMoved (QPointF)),
           guidelineVisible, SLOT (slotHandleMoved (QPointF)));
}

GuidelineStateContext *GuidelineAbstract::context ()
{
  return m_context;
}

const GuidelineStateContext *GuidelineAbstract::context () const
{
  return m_context;
}

void GuidelineAbstract::detachVisibleGuideline (const QPointF &posScene)
{
  if (m_guidelineVisible != nullptr) {

    // If scene position is off-screen then user is removing the visible Guideline
    bool offscreen = false;
    if (!m_scene.sceneRect().contains (posScene)) {

      m_guidelineVisible->draggedOffScreen ();
      offscreen = true;
    }

    emit signalGuidelineDragged(m_guidelineVisible->identifier(),
                                offscreen);

    m_guidelineVisible = nullptr;
  }
}

void GuidelineAbstract::draggedOffScreen ()
{
  m_context->draggedOffScreen ();
}

void GuidelineAbstract::handleActiveChange (bool active)
{
  m_context->handleActiveChange (active);
}

void GuidelineAbstract::handleHoverEnterEvent()
{
  m_context->handleHoverEnterEvent ();
}

void GuidelineAbstract::handleHoverLeaveEvent()
{
  m_context->handleHoverLeaveEvent ();
}

void GuidelineAbstract::handleMouseMoveEvent (const QPointF &posScene)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineAbstract::handleMouseMoveEvent";

  // Skip if there is no bound visible Guideline
  if (m_guidelineVisible != nullptr) {

    emit signalHandleMoved (posScene);
  }
}

void GuidelineAbstract::handleMousePressEvent(const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineAbstract::handleMousePressEvent state=" << m_context->stateName ().toLatin1().data();

  m_context->handleMousePress(posScene);
}

void GuidelineAbstract::handleMouseReleaseEvent (const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineAbstract::handleMouseReleaseEvent state=" << m_context->stateName ().toLatin1().data();

  // Current Guideline is the temporary visible Guideline and not the permanent Guideline (see detachVisibleGuideline)

  m_context->handleMouseRelease (posScene);
}

void GuidelineAbstract::handleVisibleChange (bool visible)
{
  m_context->handleVisibleChange (visible);
}

bool GuidelineAbstract::isDiscarded () const
{
  return m_context->isDiscarded ();
}

QGraphicsScene &GuidelineAbstract::scene ()
{
  return m_scene;
}

QPointF GuidelineAbstract::posCursorGraph () const
{
  return m_context->posCursorGraph ();
}

void GuidelineAbstract::setContext (GuidelineStateContext *context)
{
  m_context = context;
}

void GuidelineAbstract::slotHandleMoved (QPointF posScreen)
{
  // Update geometry
  updateGeometry (posScreen);
}

QString GuidelineAbstract::stateDump () const
{
  // This is used by Guidelines::stateDump and GuidelineStateContext::stateDump
  QString out;
  QTextStream str (&out);

  str << " " << m_context->stateName ();
  str << " (";
  str << (getGraphicsItemSelected() ? "selected" : "unselected") << " ";
  str << (getGraphicsItemAcceptHover() ? "hoverable" : "unhoverable") << " ";
  str << ((graphicsItemFlags () & QGraphicsItem::ItemIsFocusable ) != 0 ? "focusable"  : "unfocusable") << " ";
  str << ((graphicsItemFlags () & QGraphicsItem::ItemIsMovable   ) != 0 ? "movable"    : "unmovable") << " ";
  str << ((graphicsItemFlags () & QGraphicsItem::ItemIsSelectable) != 0 ? "selectable" : "unselectable") << " ";
  str << ")";

  return out;
}

QString GuidelineAbstract::stateName () const
{
  return m_context->stateName ();
}

void GuidelineAbstract::updateWithLatestTransformation ()
{
  m_context->updateWithLatestTransformation ();
}
