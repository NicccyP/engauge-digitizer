/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CreateScene.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QGraphicsView>
#include <QGridLayout>

CreateScene::CreateScene()
{
}

void CreateScene::create(MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CreateScene::create";
  
  mw.m_scene = new GraphicsScene (&mw);
  mw.m_view = new GraphicsView (mw.m_scene, mw);

  mw.m_sceneGuidelineBottom = new QGraphicsScene ();
  mw.m_sceneGuidelineLeft = new QGraphicsScene ();
  mw.m_sceneGuidelineRight = new QGraphicsScene ();
  mw.m_sceneGuidelineTop = new QGraphicsScene ();

  mw.m_viewGuidelineBottom = new QGraphicsView (mw.m_sceneGuidelineBottom);
  mw.m_viewGuidelineLeft = new QGraphicsView (mw.m_sceneGuidelineLeft);
  mw.m_viewGuidelineRight = new QGraphicsView (mw.m_sceneGuidelineRight);
  mw.m_viewGuidelineTop = new QGraphicsView (mw.m_sceneGuidelineTop);

  mw.m_viewGuidelineBottom->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  mw.m_viewGuidelineLeft->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  mw.m_viewGuidelineRight->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  mw.m_viewGuidelineTop->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  mw.m_viewGuidelineBottom->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  mw.m_viewGuidelineLeft->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  mw.m_viewGuidelineRight->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  mw.m_viewGuidelineTop->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  const int DEPTH = 16;

  mw.m_viewGuidelineBottom->setFixedHeight (DEPTH);
  mw.m_viewGuidelineLeft->setFixedWidth (DEPTH);
  mw.m_viewGuidelineRight->setFixedWidth (DEPTH);
  mw.m_viewGuidelineTop->setFixedHeight (DEPTH);

  mw.m_viewGuidelineBottom->setStyleSheet ("background-color: rgba(0, 0, 0, 0)");
  mw.m_viewGuidelineLeft->setStyleSheet ("background-color: rgba(0, 0, 0, 0)");
  mw.m_viewGuidelineRight->setStyleSheet ("background-color: rgba(0, 0, 0, 0)");
  mw.m_viewGuidelineTop->setStyleSheet ("background-color: rgba(0, 0, 0, 0)");

  int row = 0;
  mw.m_layout->addWidget (mw.m_viewGuidelineTop, row++, 1);
  mw.m_layout->addWidget (mw.m_viewGuidelineLeft, row, 0);
  mw.m_layout->addWidget (mw.m_view, row, 1);
  mw.m_layout->addWidget (mw.m_viewGuidelineRight, row++, 2);
  mw.m_layout->addWidget (mw.m_viewGuidelineBottom, row++, 1);
}

