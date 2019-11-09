/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GraphicsScene.h"
#include "GuidelineAbstract.h"
#include "GuidelineEllipse.h"
#include "GuidelineFactory.h"
#include "GuidelineLine.h"
#include "Guidelines.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineFactory::GuidelineFactory (GraphicsScene *sceneMain,
                                    QGraphicsScene *sceneGuidelineBottom,
                                    QGraphicsScene *sceneGuidelineLeft,
                                    QGraphicsScene *sceneGuidelineRight,
                                    QGraphicsScene *sceneGuidelineTop) :
  m_sceneMain (sceneMain),
  m_sceneGuidelineBottom (sceneGuidelineBottom),
  m_sceneGuidelineLeft (sceneGuidelineLeft),
  m_sceneGuidelineRight (sceneGuidelineRight),
  m_sceneGuidelineTop (sceneGuidelineTop)
{
  createEllipseMap ();
  createSceneMap ();
}

GuidelineFactory::~GuidelineFactory ()
{
}

GuidelineAbstract *GuidelineFactory::createGuideline (Guidelines &guidelines,
                                                      GuidelineState stateInitial)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineFactory::createGuideline";

  // Main scene or one of the guideline scenes?
  QGraphicsScene *scene = m_sceneMain;

  if (m_mapStateToScene.contains (stateInitial)) {

    scene = m_mapStateToScene [stateInitial];

  }
  
  // Line or ellipse?
  GuidelineAbstract *guideline = nullptr;
  
  if (m_mapStatesWithEllipse.contains (stateInitial)) {

    guideline = new GuidelineEllipse (*scene,
                                      guidelines,
                                      stateInitial);
    
  } else {

    guideline = new GuidelineLine (*scene,
                                    guidelines,
                                    stateInitial);
  }

  return guideline;
}

void GuidelineFactory::createEllipseMap ()
{
  // All other states get a line instead of an ellipse
  m_mapStatesWithEllipse [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE] = true;
  m_mapStatesWithEllipse [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HIDE] = true;
  m_mapStatesWithEllipse [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HOVER] = true;
}

void GuidelineFactory::createSceneMap ()
{
  // All other states get assigned to the main scene
  m_mapStateToScene [GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_HIDE] = m_sceneGuidelineBottom;
  m_mapStateToScene [GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_HOVER] = m_sceneGuidelineBottom;
  m_mapStateToScene [GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_LURKING] = m_sceneGuidelineBottom;
  m_mapStateToScene [GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_HIDE] = m_sceneGuidelineLeft;
  m_mapStateToScene [GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_HOVER] = m_sceneGuidelineLeft;
  m_mapStateToScene [GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_LURKING] = m_sceneGuidelineLeft;
  m_mapStateToScene [GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_HIDE] = m_sceneGuidelineRight;
  m_mapStateToScene [GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_HOVER] = m_sceneGuidelineRight;
  m_mapStateToScene [GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_LURKING] = m_sceneGuidelineRight;
  m_mapStateToScene [GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_HIDE] = m_sceneGuidelineTop;
  m_mapStateToScene [GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_HOVER] = m_sceneGuidelineTop;
  m_mapStateToScene [GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_LURKING] = m_sceneGuidelineTop;
}
