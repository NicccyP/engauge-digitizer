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

void Guidelines::createGuidelineR (double r)
{
  GuidelineAbstract *guideline = createGuideline (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (r);
  }
}

void Guidelines::createGuidelineR (const QPointF &posScreen)
{
  GuidelineAbstract *guideline = createGuideline (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (posScreen);
  }
}

void Guidelines::createGuidelineT (double t)
{
  GuidelineAbstract *guideline = createGuideline (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (t);
  }
}

void Guidelines::createGuidelineT (const QPointF &posScreen)
{
  GuidelineAbstract *guideline = createGuideline (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (posScreen);
  }
}

void Guidelines::createGuidelineX (double x)
{
  GuidelineAbstract *guideline = createGuideline (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (x);
  }
}

void Guidelines::createGuidelineX (const QPointF &posScreen)
{
  GuidelineAbstract *guideline = createGuideline (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (posScreen);
  }
}

void Guidelines::createGuidelineY (double y)
{

  GuidelineAbstract *guideline = createGuideline (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (y);
  }
}

void Guidelines::createGuidelineY (const QPointF &posScreen)
{

  GuidelineAbstract *guideline = createGuideline (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (posScreen);
  }
}

GuidelineContainerPrivate::iterator Guidelines::findClosestGuidelineXT (double value)
{
  bool isFirst = true;
  GuidelineContainerPrivate::iterator itrClosest;
  double missClosest = 0;

  GuidelineContainerPrivate::iterator itr;

  // Find the closest point
  for (itr = m_guidelineContainer.begin (); itr != m_guidelineContainer.end (); itr++) {
    GuidelineAbstract *guideline = *itr;
    double miss = qAbs (guideline->posCursorGraph ().x() - value);
    if (isFirst || (miss < missClosest)) {
      isFirst = false;
      missClosest = miss;
      itrClosest = itr;
    }
  }

  return itrClosest;
}

GuidelineContainerPrivate::iterator Guidelines::findClosestGuidelineYR (double value)
{
  bool isFirst = true;
  GuidelineContainerPrivate::iterator itrClosest;
  double missClosest = 0;

  GuidelineContainerPrivate::iterator itr;

  // Find the closest point
  for (itr = m_guidelineContainer.begin (); itr != m_guidelineContainer.end (); itr++) {
    GuidelineAbstract *guideline = *itr;
    double miss = qAbs (guideline->posCursorGraph ().y() - value);
    if (isFirst || (miss < missClosest)) {
      isFirst = false;
      missClosest = miss;
      itrClosest = itr;
    }
  }

  return itrClosest;
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

void Guidelines::moveGuidelineXT (double valueBefore,
                                  double valueAfter)
{
  GuidelineContainerPrivate::iterator itr = findClosestGuidelineXT (valueBefore);

  // Move it
  if (itr != m_guidelineContainer.end ()) {
    GuidelineAbstract *guideline = *itr;
    guideline->updateGeometry (valueAfter);
  }
}

void Guidelines::moveGuidelineYR (double valueBefore,
                                  double valueAfter)
{
  GuidelineContainerPrivate::iterator itr = findClosestGuidelineYR (valueBefore);

  // Move it
  if (itr != m_guidelineContainer.end ()) {
    GuidelineAbstract *guideline = *itr;
    guideline->updateGeometry (valueAfter);
  }
}

void Guidelines::removeGuidelineXT (double value)
{
  GuidelineContainerPrivate::iterator itr = findClosestGuidelineXT (value);

  // Move it
  if (itr != m_guidelineContainer.end ()) {
    m_guidelineContainer.erase (itr);
  }
}

void Guidelines::removeGuidelineYR (double value)
{
  GuidelineContainerPrivate::iterator itr = findClosestGuidelineYR (value);

  // Move it
  if (itr != m_guidelineContainer.end ()) {
    m_guidelineContainer.erase (itr);
  }
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
