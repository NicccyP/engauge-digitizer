/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_FACTORY_H
#define GUIDELINE_FACTORY_H

#include "Guidelines.h"
#include "GuidelineState.h"
#include <QMap>

class GraphicsScene;
class GuidelineAbstract;
class Guidelines;
class QGraphicsScene;

typedef QMap<GuidelineState, QGraphicsScene*> MapStateToScene;
typedef QMap<GuidelineState, bool> MapStatesWithEllipse;

/// Factory for generating Guideline objects. The complications are:
/// -# Some guidelines are lines (GuidelineLine) and some are ellipses (GuidelineEllipse)
/// -# Template guidelines belong to narrow scenes/views around the main scene perimeter, and
///    all other guidelines belong to the main scene/view
class GuidelineFactory
{
public:
  /// Single constructor.
  GuidelineFactory (GraphicsScene *sceneMain,
                    QGraphicsScene *sceneGuidelineBottom,
                    QGraphicsScene *sceneGuidelineLeft,
                    QGraphicsScene *sceneGuidelineRight,
                    QGraphicsScene *sceneGuidelineTop);
  virtual ~GuidelineFactory();

  GuidelineAbstract *createGuideline (Guidelines &guidelines,
                                      GuidelineState stateInitial);
  
private:
  GuidelineFactory ();

  void createEllipseMap ();
  void createSceneMap ();

  GraphicsScene *m_sceneMain;
  QGraphicsScene *m_sceneGuidelineBottom;
  QGraphicsScene *m_sceneGuidelineLeft;
  QGraphicsScene *m_sceneGuidelineRight;
  QGraphicsScene *m_sceneGuidelineTop;

  MapStateToScene m_mapStateToScene;
  MapStatesWithEllipse m_mapStatesWithEllipse;  
};

#endif // GUIDELINE_FACTORY_H
