/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINES_H
#define GUIDELINES_H

#include "ColorPalette.h"
#include "CoordsType.h"
#include "GuidelineState.h"
#include <QList>
#include <QString>
#include "Transformation.h"

class DocumentModelCoords;
class GraphicsScene;
class GuidelineAbstract;
class GuidelineFactory;
class MainWindow;
class QGraphicsScene;

typedef QList<GuidelineAbstract*> GuidelineContainerPrivate;

/// This class contains all Guideline objects
class Guidelines
{
  /// For unit testing
  friend class TestGuidelines;

public:
  /// Single constructor.
  Guidelines(MainWindow &mainWindow);
  ~Guidelines();

  /// Remove guidelines since the current Document is about to be closed
  void clear ();

  /// Color to be used for guidelines
  ColorPalette color () const;

  /// Return cartesian or polar
  CoordsType coordsType () const;

  /// Factory method for creating a new Guideline
  GuidelineAbstract *createGuideline (GuidelineState stateInitial);

  /// Factory method for creating a new GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE
  void createGuidelineR (double r);

  /// Factory method for creating a new GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE
  void createGuidelineR (const QPointF &posScreen);

  /// Factory method for creating a new GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE
  void createGuidelineT (double t);

  /// Factory method for creating a new GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE
  void createGuidelineT (const QPointF &posScreen);

  /// Factory method for creating a new GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE
  void createGuidelineX (double x);

  /// Factory method for creating a new GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE
  void createGuidelineX (const QPointF &posScreen);

  /// Factory method for creating a new GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE
  void createGuidelineY (double y);

  /// Factory method for creating a new GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE
  void createGuidelineY (const QPointF &posScreen);

  /// DigitizeState change so active status may (or may not) be toggled 
  void handleActiveChange (bool active);
  
  /// User toggled guideline visibility
  void handleVisibleChange (bool visible);

  /// Initialize Guideline factory
  void initialize (GraphicsScene &scene);

  /// Move an X/T guideline from one value to another. Closest value wins
  void moveGuidelineXT (double valueBefore,
                       double valueAfter);

  /// Move an Y/R guideline from one value to another. Closest value wins
  void moveGuidelineYR (double valueBefore,
                        double valueAfter);

  /// Remove an X/T guideline. Closest value wins
  void removeGuidelineXT (double value);

  /// Remove an Y/R guideline. Closest value wins
  void removeGuidelineYR (double value);

  /// States listed as a string for debugging only
  QString stateDump () const;

  /// Return copy of transformation owned by MainWindow
  Transformation transformation () const;

  /// Force a color update
  void updateColor ();

  /// Update transformation. This is called after a command has been executed
  void updateWithLatestTransformation ();

private:
  Guidelines();

  GuidelineContainerPrivate::iterator findClosestGuidelineXT (double value);
  GuidelineContainerPrivate::iterator findClosestGuidelineYR (double value);

  /// For unit testing
  const GuidelineContainerPrivate &guidelineContainerPrivate () const;

  /// Add a new Guideline to the global list maintained by this class
  void registerGuideline (GuidelineAbstract *guideline);

  GuidelineContainerPrivate m_guidelineContainer; // Save for easy removal later

  MainWindow &m_mainWindow;

  GuidelineFactory *m_guidelineFactory;
};

#endif // GUIDELINES_H
