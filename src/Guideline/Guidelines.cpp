/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "Document.h"
#include "DocumentModelCoords.h"
#include "EngaugeAssert.h"
#include "GraphicsScene.h"
#include "GuidelineAbstract.h"
#include "GuidelineEllipse.h"
#include "GuidelineFactory.h"
#include "GuidelineLine.h"
#include "Guidelines.h"
#include "Logger.h"
#include "MainWindow.h"
#include "MainWindowModel.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QMap>
#include <qmath.h>
#include <QTextStream>

Guidelines::Guidelines (MainWindow &mainWindow) :
  m_mainWindow (mainWindow),
  m_guidelineFactory (nullptr)
{
}

Guidelines::~Guidelines ()
{
  clear ();
}

void Guidelines::clear ()
{
  GuidelineContainerPrivate::iterator itr;
  for (itr = m_guidelineContainer.begin(); itr != m_guidelineContainer.end(); itr++) {
    GuidelineAbstract *guideline = *itr;

    // Remove the guideline from its scene
    QGraphicsScene *scene = &guideline->scene();

    if (scene != nullptr) {

      guideline->removeFromScene (scene);

    }
  }

  m_guidelineContainer.clear ();
}

ColorPalette Guidelines::color () const
{
  return m_mainWindow.modelMainWindow().guidelineColor();
}

CoordsType Guidelines::coordsType () const
{
  return m_mainWindow.cmdMediator()->document().modelCoords().coordsType();
}

GuidelineAbstract *Guidelines::createGuideline (GuidelineState stateInitial)
{
  GuidelineAbstract *guideline = m_guidelineFactory->createGuideline (*this,
                                                                      stateInitial);

  return guideline;
}

void Guidelines::createGuidelineR (const QPointF &posScene)
{
  GuidelineAbstract *guideline = createGuideline (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (posScene);
  }
}

void Guidelines::createGuidelineT (const QPointF &posScene)
{
  GuidelineAbstract *guideline = createGuideline (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (posScene);
  }
}

void Guidelines::createGuidelineX (const QPointF &posScene)
{
  GuidelineAbstract *guideline = createGuideline (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (posScene);
  }
}

void Guidelines::createGuidelineY (const QPointF &posScene)
{

  GuidelineAbstract *guideline = createGuideline (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (posScene);
  }
}

const GuidelineContainerPrivate &Guidelines::guidelineContainerPrivate () const
{
  return m_guidelineContainer;
}

void Guidelines::handleActiveChange (bool active)
{
  GuidelineContainerPrivate::iterator itr;
  for (itr = m_guidelineContainer.begin(); itr != m_guidelineContainer.end(); itr++) {
    GuidelineAbstract *guideline = *itr;

    guideline->handleActiveChange (active);
  }
}

void Guidelines::handleVisibleChange (bool visible)
{
  GuidelineContainerPrivate::iterator itr;
  for (itr = m_guidelineContainer.begin(); itr != m_guidelineContainer.end(); itr++) {
    GuidelineAbstract *guideline = *itr;

    guideline->handleVisibleChange (visible);
  }
}

void Guidelines::initialize (GraphicsScene &scene)
{
  m_guidelineFactory = new GuidelineFactory (&scene);
}

void Guidelines::registerGuideline (GuidelineAbstract *guideline)
{
  m_guidelineContainer.push_back (guideline);
}

QString Guidelines::stateDump () const
{
  // Sort the entries
  QStringList sorted;
  GuidelineContainerPrivate::const_iterator itrSort;
  for (itrSort = m_guidelineContainer.begin(); itrSort != m_guidelineContainer.end(); itrSort++) {
    GuidelineAbstract *guideline = *itrSort;

    sorted << guideline->stateDump ();
  }

  qSort (sorted.begin(),
         sorted.end());

  // Convert entries to output text
  QString out;
  QTextStream str (&out);

  str << "Guidelines::stateDump:\n";

  QStringList::const_iterator itrOut;
  for (itrOut = sorted.begin(); itrOut != sorted.end(); itrOut++) {
    QString entry = *itrOut;

    str << "                    " << entry << "\n";
  }

  return out;
}

Transformation Guidelines::transformation() const
{
  return m_mainWindow.transformation ();
}

void Guidelines::updateColor ()
{
  GuidelineContainerPrivate::const_iterator itr;
  for (itr = m_guidelineContainer.begin(); itr != m_guidelineContainer.end(); itr++) {
    GuidelineAbstract *guideline = *itr;

    guideline->updateColor ();
  }
}

void Guidelines::updateWithLatestTransformation ()
{
  GuidelineContainerPrivate::iterator itr;
  for (itr = m_guidelineContainer.begin(); itr != m_guidelineContainer.end(); itr++) {
    GuidelineAbstract *guideline = *itr;
    guideline->updateWithLatestTransformation ();
  }
}
