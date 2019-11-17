/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CreateScene.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "GuidelineView.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QGridLayout>

CreateScene::CreateScene()
{
}

void CreateScene::create(MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CreateScene::create";
  
  // Dragging of objects from Guideline windows to main window requires all to be children of the same
  // class which is MainWindow for this app
  mw.m_scene = new GraphicsScene (&mw);
  mw.m_sceneGuidelineBottom = new QGraphicsScene (&mw);
  mw.m_sceneGuidelineLeft = new QGraphicsScene (&mw);
  mw.m_sceneGuidelineRight = new QGraphicsScene (&mw);
  mw.m_sceneGuidelineTop = new QGraphicsScene (&mw);

  QString topBottom (tr ("X/Theta Guideline Window\n"
                         "Drag the guideline in this window into the main window to create a guideline "
                         "for the X coordinate for cartesian coordinates, or Theta coordinate for polar "
                         "coordinates"));
  QString leftRight (tr ("Y/R Guideline Window\n"
                         "Drag the guideline in this window into the main window to create a guideline "
                         "for the Y coordinate for cartesian coordinates, or R coordinate for polar "
                         "coordinates"));

  mw.m_view = new GraphicsView (mw.m_scene, mw);
  mw.m_viewGuidelineBottom = new GuidelineView (mw,
                                                mw.m_sceneGuidelineBottom,
                                                topBottom);
  mw.m_viewGuidelineLeft = new GuidelineView (mw,
                                              mw.m_sceneGuidelineLeft,
                                              leftRight);
  mw.m_viewGuidelineRight = new GuidelineView (mw,
                                               mw.m_sceneGuidelineRight,
                                               leftRight);
  mw.m_viewGuidelineTop = new GuidelineView (mw,
                                             mw.m_sceneGuidelineTop,
                                             topBottom);

  const int DEPTH = 8;

  mw.m_viewGuidelineBottom->setFixedHeight (DEPTH);
  mw.m_viewGuidelineLeft->setFixedWidth (DEPTH);
  mw.m_viewGuidelineRight->setFixedWidth (DEPTH);
  mw.m_viewGuidelineTop->setFixedHeight (DEPTH);

  int row = 0;
  mw.m_layout->addWidget (mw.m_viewGuidelineTop, row++, 1);
  mw.m_layout->addWidget (mw.m_viewGuidelineLeft, row, 0);
  mw.m_layout->addWidget (mw.m_view, row, 1);
  mw.m_layout->addWidget (mw.m_viewGuidelineRight, row++, 2);
  mw.m_layout->addWidget (mw.m_viewGuidelineBottom, row++, 1);
}

