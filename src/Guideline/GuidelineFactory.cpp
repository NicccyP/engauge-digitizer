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
#include "MainWindow.h"
#include <QGraphicsScene>

GuidelineFactory::GuidelineFactory (GraphicsScene *sceneMain) :
  m_sceneMain (sceneMain),
  m_guidelineCounter (0)
{
  createEllipseMap ();
}

GuidelineFactory::~GuidelineFactory ()
{
}

GuidelineAbstract *GuidelineFactory::createGuideline (Guidelines &guidelines,
                                                      GuidelineState stateInitial,
                                                      MainWindow &mainWindow)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineFactory::createGuideline";

  // Main scene or one of the guideline scenes?
  QGraphicsScene *scene = m_sceneMain;
  
  // Line or ellipse?
  GuidelineAbstract *guideline = nullptr;
  
  if (m_mapStatesWithEllipse.contains (stateInitial)) {

    guideline = new GuidelineEllipse (*scene,
                                      guidelines,
                                      stateInitial,
                                      m_guidelineCounter++);
    
  } else {

    guideline = new GuidelineLine (*scene,
                                   guidelines,
                                   stateInitial,
                                   m_guidelineCounter++);
  }

  QObject::connect (guideline, SIGNAL (signalGuidelineDragged (QString, bool)),
                    &mainWindow, SLOT (slotGuidelineDragged (QString, bool)));

  return guideline;
}

void GuidelineFactory::createEllipseMap ()
{
  // All other states get a line instead of an ellipse
  m_mapStatesWithEllipse [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE] = true;
  m_mapStatesWithEllipse [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HIDE] = true;
  m_mapStatesWithEllipse [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HOVER] = true;
}
