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
#include <QGridLayout>

CreateScene::CreateScene()
{
}

void CreateScene::create(MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CreateScene::create";
  
  mw.m_scene = new GraphicsScene (&mw);
  mw.m_view = new GraphicsView (mw.m_scene, mw);

  QGraphicsScene *sceneBottom = new QGraphicsScene ();
  QGraphicsScene *sceneLeft = new QGraphicsScene ();
  QGraphicsScene *sceneRight = new QGraphicsScene ();
  QGraphicsScene *sceneTop = new QGraphicsScene ();

  QGraphicsView *viewBottom = new QGraphicsView (sceneBottom);
  QGraphicsView *viewLeft = new QGraphicsView (sceneLeft);
  QGraphicsView *viewRight = new QGraphicsView (sceneRight);
  QGraphicsView *viewTop = new QGraphicsView (sceneTop);

  const int DEPTH = 6;

  viewBottom->setFixedHeight (DEPTH);
  viewLeft->setFixedWidth (DEPTH);
  viewRight->setFixedWidth (DEPTH);
  viewTop->setFixedHeight (DEPTH);

  viewBottom->setStyleSheet ("background-color: rgba(0, 0, 0, 0)");
  viewLeft->setStyleSheet ("background-color: rgba(0, 0, 0, 0)");
  viewRight->setStyleSheet ("background-color: rgba(0, 0, 0, 0)");
  viewTop->setStyleSheet ("background-color: rgba(0, 0, 0, 0)");

  int row = 0;
  mw.m_layout->addWidget (viewTop, row++, 1);
  mw.m_layout->addWidget (viewLeft, row, 0);
  mw.m_layout->addWidget (mw.m_view, row, 1);
  mw.m_layout->addWidget (viewRight, row++, 2);
  mw.m_layout->addWidget (viewBottom, row++, 1);
}

