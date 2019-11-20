/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_CONTEXT_H
#define GUIDELINE_STATE_CONTEXT_H

#include "ColorPalette.h"
#include "EllipseParameters.h"
#include "GuidelineState.h"
#include "GuidelineStateAbstractBase.h"
#include <QLineF>
#include <QPointF>
#include <QString>
#include <QVector>

class GuidelineAbstract;
class Guidelines;
class Transformation;

/// Context class for state machine that belongs to the Guideline class. The GuidelineAbstract
/// class owns an instance of this class. The base class for all guideline states is
/// GuidelineStateAbstractBase.
///
/// The state machine graph:
/// \dot
/// digraph guidelines {
///   rankdir = LR;
///
///   Start -> DeployedConstantRAppearing [label = BtnGuidelineR];
///   DeployedConstantRAppearing -> DeployedConstantRActive [label = Timeout];
///
///   Start -> DeployedConstantTAppearing [label = BtnGuidelineT];
///   DeployedConstantRAppearing -> DeployedConstantTActive [label = Timeout];
///
///   Start -> DeployedConstantXAppearing [label = BtnGuidelineX];
///   DeployedConstantXAppearing -> DeployedConstantXActive [label = Timeout];
///
///   Start -> DeployedConstantYAppearing [label = BtnGuidelineY];
///   DeployedConstantYAppearing -> DeployedConstantYActive [label = Timeout];
///
///   Start -> DeployedConstantRHover [label = HoverWithPolarCoordinates];
///   DeployedConstantRHover -> DeployedConstantRActive [label = HoverLeave];
///   DeployedConstantRHover -> Handle [label = MouseClick];
///   DeployedConstantRActive -> Discarded [label = TransformLoss];
///   DeployedConstantRActive -> DeployedConstantRHide [label = TurnedOff];
///   DeployedConstantRHide -> DeployedConstantRActive [label = TurnedOn];
///   DeployedConstantRActive -> DeployedConstantRHover [label = HoverEnter];
///   DeployedConstantRActive -> DeployedConstantRLocked [label = LeaveSelectMode];
///   DeployedConstantRLocked -> DeployedConstantRActive [label = EnterSelectMode];
///
///   Start -> DeployedConstantTHover [label = HoverWithPolarCoordinates];
///   DeployedConstantTHover -> DeployedConstantTActive [label = HoverLeave];
///   DeployedConstantTHover -> Handle [label = MouseClick];
///   DeployedConstantTActive -> Discarded [label = TransformLoss];
///   DeployedConstantTActive -> DeployedConstantTHide [label = TurnedOff];
///   DeployedConstantTHide -> DeployedConstantTActive [label = TurnedOn];
///   DeployedConstantTActive -> DeployedConstantTHover [label = HoverEnter];
///   DeployedConstantTActive -> DeployedConstantTLocked [label = LeaveSelectMode];
///   DeployedConstantTLocked -> DeployedConstantTActive [label = EnterSelectMode];
///
///   Start -> DeployedConstantXHover [label = HoverWithCartesianCoordinates];
///   DeployedConstantXHover -> DeployedConstantXActive [label = HoverLeave];
///   DeployedConstantXHover -> Handle [label = MouseClick];
///   DeployedConstantXActive -> Discarded [label = TransformLoss];
///   DeployedConstantXActive -> DeployedConstantXHide [label = TurnedOff];
///   DeployedConstantXHide -> DeployedConstantXActive [label = TurnedOn];
///   DeployedConstantXActive -> DeployedConstantXHover [label = HoverEnter];
///   DeployedConstantXActive -> DeployedConstantXLocked [label = LeaveSelectMode];
///   DeployedConstantXLocked -> DeployedConstantXActive [label = EnterSelectMode];
///
///   Start -> DeployedConstantYHover [label = HoverWithCartesianCoordinates];
///   DeployedConstantYHover -> DeployedConstantYActive [label = HoverLeave];
///   DeployedConstantYHover -> Handle [label = MouseClick];
///   DeployedConstantYActive -> Discarded [label = TransformLoss];
///   DeployedConstantYActive -> DeployedConstantYHide [label = TurnedOff];
///   DeployedConstantYHide -> DeployedConstantYActive [label = TurnedOn];
///   DeployedConstantYActive -> DeployedConstantYHover [label = HoverEnter];
///   DeployedConstantYActive -> DeployedConstantYLocked [label = LeaveSelectMode];
///   DeployedConstantYLocked -> DeployedConstantYActive [label = EnterSelectMode];
///
///   Handle -> Discarded [label = MouseRelease];
///
/// }
/// \enddot
class GuidelineStateContext
{
public:
  /// Single constructor.
  GuidelineStateContext (GuidelineAbstract &guideline,
                         Guidelines &guidelines,
                         GuidelineState guidelineStateInitial);
  virtual ~GuidelineStateContext();

  /// True/false if coordinates are cartesian/polar
  bool cartesian() const;

  /// Color to be used for guidelines
  ColorPalette color () const;

  /// Factory method for creating a new Guideline
  GuidelineAbstract *createGuideline (GuidelineState stateInitial) const;

  /// Allow/skip painting of the owner Guideline. This prevents display of selection markings on
  /// otherwise-invisible handle Guideline
  bool doPaint () const;

  /// Guideline has been dragged off screen so remove it
  void draggedOffScreen ();

  /// Guideline that owns this context class
  GuidelineAbstract &guideline ();

  /// DigitizeState change so active status may (or may not) be toggled
  void handleActiveChange (bool active);

  /// If transparent then make visible when hover starts
  void handleHoverEnterEvent ();

  /// If previously transparent before hover enter then make transparent again
  void handleHoverLeaveEvent ();

  /// At the start of dragging, convert the original Guideline into an invisible handle and
  /// visible slaved deployed Guideline
  void handleMousePress (const QPointF &posScene);
  
  /// At the end of dragging, clone the Guideline that owns the state machine where these states live
  void handleMouseRelease (const QPointF &posScene);

  /// User toggled Guideline visibility
  void handleVisibleChange (bool visibile);

  /// Return ellipse representing constant range, that passes through the specified point
  EllipseParameters pointToEllipse (const QPointF &posScreen) const;

  /// Return line parallel to an axis line, that passes through the specified point
  QLineF pointToLine (const QPointF &poscreen) const;

  /// Get method for current cursor coordinate when object was last created/dragged
  QPointF posCursorGraph () const;

  /// Request a state transition
  void requestStateTransition (GuidelineState guidelineState);

  /// Pass the current cursor coordinate to the state so it can save the relevant coordinate for
  /// later adjustement when the transformation changes
  void setPosCursorGraph (const QPointF &posGraph);

  /// Pass replacement Guideline state from original Guideline to handle Guideline
  void setStateReplacement (GuidelineState stateReplacement);

  /// Dump state for debugging only
  QString stateDump () const;

  /// State as a string for debugging only
  QString stateName () const;

  /// Get method for replacement state
  GuidelineState stateReplacement () const;

  /// Return copy of transformation owned by MainWindow
  Transformation transformation () const;

  /// Update given Transformation in GuidelineStateContext
  void updateWithLatestTransformation ();

private:
  GuidelineStateContext();

  /// Transition if requested
  void transitionIfRequested ();
  
  GuidelineAbstract &m_guideline;
  Guidelines &m_guidelines;

  QVector<GuidelineStateAbstractBase*> m_states;
  GuidelineState m_currentState;
  GuidelineState m_nextState;

  GuidelineState m_stateReplacement;

  QPointF m_posCursorGraph;
};

#endif // GUIDELINE_STATE_CONTEXT_H
