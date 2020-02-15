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

GuidelineAbstract *Guidelines::createGuideline (const QString &identifier,
                                                GuidelineState stateInitial)
{
  GuidelineAbstract *guideline = m_guidelineFactory->createGuideline (*this,
                                                                      stateInitial,
                                                                      m_mainWindow,
                                                                      identifier);

  return guideline;
}

void Guidelines::createGuidelineR (const QString &identifier,
                                   double r)
{
  GuidelineAbstract *guideline = createGuideline (identifier,
                                                  GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (r);
  }

  m_guidelineContainerYR.append (guideline);
}

void Guidelines::createGuidelineR (const QString &identifier,
                                   const QPointF &posScreen)
{
  GuidelineAbstract *guideline = createGuideline (identifier,
                                                  GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (posScreen);
  }

  m_guidelineContainerYR.append (guideline);
}

void Guidelines::createGuidelineT (const QString &identifier,
                                   double t)
{
  GuidelineAbstract *guideline = createGuideline (identifier,
                                                  GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (t);
  }

  m_guidelineContainerXT.append (guideline);
}

void Guidelines::createGuidelineT (const QString &identifier,
                                   const QPointF &posScreen)
{
  GuidelineAbstract *guideline = createGuideline (identifier,
                                                  GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (posScreen);
  }

  m_guidelineContainerXT.append (guideline);
}

void Guidelines::createGuidelineX (const QString &identifier,
                                   double x)
{
  GuidelineAbstract *guideline = createGuideline (identifier,
                                                  GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (x);
  }

  m_guidelineContainerXT.append (guideline);
}

void Guidelines::createGuidelineX (const QString &identifier,
                                   const QPointF &posScreen)
{
  GuidelineAbstract *guideline = createGuideline (identifier,
                                                  GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (posScreen);
  }

  m_guidelineContainerXT.append (guideline);
}

void Guidelines::createGuidelineY (const QString &identifier,
                                   double y)
{
  GuidelineAbstract *guideline = createGuideline (identifier,
                                                  GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (y);
  }

  m_guidelineContainerYR.append (guideline);
}

void Guidelines::createGuidelineY (const QString &identifier,
                                   const QPointF &posScreen)
{
  GuidelineAbstract *guideline = createGuideline (identifier,
                                                  GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE);
  if (guideline) {
    guideline->updateGeometry (posScreen);
  }

  m_guidelineContainerYR.append (guideline);
}

GuidelineContainerPrivate::iterator Guidelines::findIdentifierXT (const QString &identifier)
{
  GuidelineContainerPrivate::iterator itr;

  // Find the closest point
  for (itr = m_guidelineContainerXT.begin (); itr != m_guidelineContainerXT.end (); itr++) {
    GuidelineAbstract *guideline = *itr;
    if (identifier == guideline->identifier()) {
        return itr;
    }
  }

  LOG4CPP_DEBUG_S ((*mainCat)) << "Guidelines::findIdentifierXT could not find " << identifier.toLatin1().data();

  return m_guidelineContainerXT.end();
}

GuidelineContainerPrivate::iterator Guidelines::findIdentifierYR (const QString &identifier)
{
  GuidelineContainerPrivate::iterator itr;

  // Find the closest point
  for (itr = m_guidelineContainerYR.begin (); itr != m_guidelineContainerYR.end (); itr++) {
    GuidelineAbstract *guideline = *itr;
    if (identifier == guideline->identifier()) {
      return itr;
    }
  }

  LOG4CPP_DEBUG_S ((*mainCat)) << "Guidelines::findIdentifierYR could not find " << identifier.toLatin1().data();

  return m_guidelineContainerYR.end(); // Return something
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
    QString identifier = guideline->identifier();
    double value = guideline->posCursorGraph().x();
    valuesXT [identifier] = value;
  }

  for (itr = m_guidelineContainerYR.begin(); itr != m_guidelineContainerYR.end(); itr++) {
    const GuidelineAbstract *guideline = *itr;
    QString identifier = guideline->identifier();
    double value = guideline->posCursorGraph().y();
    valuesYR [identifier] = value;
  }
  
  DocumentModelGuidelines model (valuesXT,
                                 valuesYR);

  return model;
}

void Guidelines::moveGuidelineXT (const QString &identifier,
                                  double valueAfter)
{
  GuidelineContainerPrivate::iterator itr = findIdentifierXT (identifier);

  // Move it
  if (itr != m_guidelineContainerXT.end ()) {
    GuidelineAbstract *guideline = *itr;
    guideline->updateGeometry (valueAfter);
  }
}

void Guidelines::moveGuidelineYR (const QString &identifier,
                                  double valueAfter)
{
  GuidelineContainerPrivate::iterator itr = findIdentifierYR (identifier);

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

void Guidelines::removeGuideline (const QString &identifier)
{
  // Try to remove XT entry
  GuidelineContainerPrivate::iterator itrXT = findIdentifierXT (identifier);
  if (itrXT != m_guidelineContainerXT.end ()) {
    m_guidelineContainerXT.erase (itrXT);
    delete *itrXT;
    return;
  }

  // Try to remove YR entry
  GuidelineContainerPrivate::iterator itrYR = findIdentifierYR (identifier);
  if (itrYR != m_guidelineContainerYR.end ()) {
    m_guidelineContainerYR.erase (itrYR);
    delete *itrYR;
    return;
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
