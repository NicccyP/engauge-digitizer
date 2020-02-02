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
  
  for (itr = m_guidelineContainerXT.begin(); itr != m_guidelineContainerXT.end(); itr++) {
    GuidelineAbstract *guideline = *itr;

    // Remove the guideline from its scene
    QGraphicsScene *scene = &guideline->scene();

    if (scene != nullptr) {

      guideline->removeFromScene (scene);

    }
  }

  for (itr = m_guidelineContainerYR.begin(); itr != m_guidelineContainerYR.end(); itr++) {
    GuidelineAbstract *guideline = *itr;

    // Remove the guideline from its scene
    QGraphicsScene *scene = &guideline->scene();

    if (scene != nullptr) {

      guideline->removeFromScene (scene);

    }
  }

  m_guidelineContainerXT.clear ();
  m_guidelineContainerYR.clear ();
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

  m_guidelineContainerYR.append (guideline);
}

void Guidelines::createGuidelineR (const QPointF &posScreen)
{
  GuidelineAbstract *guideline = createGuideline (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (posScreen);
  }

  m_guidelineContainerYR.append (guideline);
}

void Guidelines::createGuidelineT (double t)
{
  GuidelineAbstract *guideline = createGuideline (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (t);
  }

  m_guidelineContainerXT.append (guideline);
}

void Guidelines::createGuidelineT (const QPointF &posScreen)
{
  GuidelineAbstract *guideline = createGuideline (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (posScreen);
  }

  m_guidelineContainerXT.append (guideline);
}

void Guidelines::createGuidelineX (double x)
{
  GuidelineAbstract *guideline = createGuideline (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (x);
  }

  m_guidelineContainerXT.append (guideline);
}

void Guidelines::createGuidelineX (const QPointF &posScreen)
{
  GuidelineAbstract *guideline = createGuideline (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (posScreen);
  }

  m_guidelineContainerXT.append (guideline);
}

void Guidelines::createGuidelineY (double y)
{

  GuidelineAbstract *guideline = createGuideline (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (y);
  }

  m_guidelineContainerYR.append (guideline);
}

void Guidelines::createGuidelineY (const QPointF &posScreen)
{

  GuidelineAbstract *guideline = createGuideline (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (posScreen);
  }

  m_guidelineContainerYR.append (guideline);
}

GuidelineContainerPrivate::iterator Guidelines::findClosestGuidelineXT (double value)
{
  bool isFirst = true;
  GuidelineContainerPrivate::iterator itrClosest;
  double missClosest = 0;

  GuidelineContainerPrivate::iterator itr;

  // Find the closest point
  for (itr = m_guidelineContainerXT.begin (); itr != m_guidelineContainerXT.end (); itr++) {
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
  for (itr = m_guidelineContainerYR.begin (); itr != m_guidelineContainerYR.end (); itr++) {
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

const GuidelineContainerPrivate &Guidelines::guidelineContainerPrivateXT () const
{
  return m_guidelineContainerXT;
}

const GuidelineContainerPrivate &Guidelines::guidelineContainerPrivateYR () const
{
  return m_guidelineContainerYR;
}

void Guidelines::handleActiveChange (bool active)
{
  GuidelineContainerPrivate::iterator itr;

  for (itr = m_guidelineContainerXT.begin(); itr != m_guidelineContainerXT.end(); itr++) {
    GuidelineAbstract *guideline = *itr;

    guideline->handleActiveChange (active);
  }

  for (itr = m_guidelineContainerYR.begin(); itr != m_guidelineContainerYR.end(); itr++) {
    GuidelineAbstract *guideline = *itr;

    guideline->handleActiveChange (active);
  }
}

void Guidelines::handleVisibleChange (bool visible)
{
  GuidelineContainerPrivate::iterator itr;

  for (itr = m_guidelineContainerXT.begin(); itr != m_guidelineContainerXT.end(); itr++) {
    GuidelineAbstract *guideline = *itr;

    guideline->handleVisibleChange (visible);
  }

  for (itr = m_guidelineContainerYR.begin(); itr != m_guidelineContainerYR.end(); itr++) {
    GuidelineAbstract *guideline = *itr;

    guideline->handleVisibleChange (visible);
  }
}

void Guidelines::initialize (GraphicsScene &scene)
{
  m_guidelineFactory = new GuidelineFactory (&scene);
}

DocumentModelGuidelines Guidelines::modelGuidelines () const
{
  GuidelineValues valuesXT, valuesYR;

  GuidelineContainerPrivate::const_iterator itr;

  for (itr = m_guidelineContainerXT.begin(); itr != m_guidelineContainerXT.end(); itr++) {
    const GuidelineAbstract *guideline = *itr;
    valuesXT << guideline->posCursorGraph().x();
  }

  for (itr = m_guidelineContainerYR.begin(); itr != m_guidelineContainerYR.end(); itr++) {
    const GuidelineAbstract *guideline = *itr;
    valuesYR << guideline->posCursorGraph().y();
  }
  
  DocumentModelGuidelines model (valuesXT,
                                 valuesYR);

  return model;
}

void Guidelines::moveGuidelineXT (double valueBefore,
                                  double valueAfter)
{
  GuidelineContainerPrivate::iterator itr = findClosestGuidelineXT (valueBefore);

  // Move it
  if (itr != m_guidelineContainerXT.end ()) {
    GuidelineAbstract *guideline = *itr;
    guideline->updateGeometry (valueAfter);
  }
}

void Guidelines::moveGuidelineYR (double valueBefore,
                                  double valueAfter)
{
  GuidelineContainerPrivate::iterator itr = findClosestGuidelineYR (valueBefore);

  // Move it
  if (itr != m_guidelineContainerYR.end ()) {
    GuidelineAbstract *guideline = *itr;
    guideline->updateGeometry (valueAfter);
  }
}

void Guidelines::registerGuidelineXT (GuidelineAbstract *guideline)
{
  m_guidelineContainerXT.push_back (guideline);
}

void Guidelines::registerGuidelineYR (GuidelineAbstract *guideline)
{
  m_guidelineContainerYR.push_back (guideline);
}

void Guidelines::removeGuidelineXT (double value)
{
  GuidelineContainerPrivate::iterator itr = findClosestGuidelineXT (value);

  // Remove it
  if (itr != m_guidelineContainerXT.end ()) {
    m_guidelineContainerXT.erase (itr);
    delete *itr;
  }
}

void Guidelines::removeGuidelineYR (double value)
{
  GuidelineContainerPrivate::iterator itr = findClosestGuidelineYR (value);

  // Remove it
  if (itr != m_guidelineContainerYR.end ()) {
    m_guidelineContainerYR.erase (itr);
    delete *itr;
  }
}

QString Guidelines::stateDump () const
{
  // Sort the entries
  QStringList sortedXT, sortedYR;
  GuidelineContainerPrivate::const_iterator itrSort;

  for (itrSort = m_guidelineContainerXT.begin(); itrSort != m_guidelineContainerXT.end(); itrSort++) {
    GuidelineAbstract *guideline = *itrSort;
    sortedXT << guideline->stateDump ();
  }

  for (itrSort = m_guidelineContainerYR.begin(); itrSort != m_guidelineContainerYR.end(); itrSort++) {
    GuidelineAbstract *guideline = *itrSort;
    sortedYR << guideline->stateDump ();
  }

  qSort (sortedXT.begin(),
         sortedXT.end());
  qSort (sortedYR.begin(),
         sortedYR.end());

  // Convert entries to output text
  QString out;
  QTextStream str (&out);

  str << "Guidelines::stateDump:\n";

  QStringList::const_iterator itrOut;

  for (itrOut = sortedXT.begin(); itrOut != sortedXT.end(); itrOut++) {
    QString entry = *itrOut;
    str << "                    " << entry << "\n";
  }

  for (itrOut = sortedYR.begin(); itrOut != sortedYR.end(); itrOut++) {
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

  for (itr = m_guidelineContainerXT.begin(); itr != m_guidelineContainerXT.end(); itr++) {
    GuidelineAbstract *guideline = *itr;
    guideline->updateColor ();
  }

  for (itr = m_guidelineContainerYR.begin(); itr != m_guidelineContainerYR.end(); itr++) {
    GuidelineAbstract *guideline = *itr;
    guideline->updateColor ();
  }
}

void Guidelines::updateWithLatestTransformation ()
{
  GuidelineContainerPrivate::iterator itr;

  for (itr = m_guidelineContainerXT.begin(); itr != m_guidelineContainerXT.end(); itr++) {
    GuidelineAbstract *guideline = *itr;
    guideline->updateWithLatestTransformation ();
  }

  for (itr = m_guidelineContainerYR.begin(); itr != m_guidelineContainerYR.end(); itr++) {
    GuidelineAbstract *guideline = *itr;
    guideline->updateWithLatestTransformation ();
  }
}
