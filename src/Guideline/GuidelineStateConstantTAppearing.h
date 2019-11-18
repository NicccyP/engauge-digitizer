/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_CONSTANT_T_APPEARING_H
#define GUIDELINE_STATE_CONSTANT_T_APPEARING_H

#include "GuidelineStateConstantTAbstract.h"

/// Implements guideline behavior for GUIDELINE_STATE_CONSTANT_T_APPEARING
class GuidelineStateConstantTAppearing : public GuidelineStateConstantTAbstract
{
public:
  /// Single constructor.
  GuidelineStateConstantTAppearing(GuidelineStateContext &context);
  virtual ~GuidelineStateConstantTAppearing();

  virtual void begin ();
  virtual bool doPaint () const;
  virtual void end ();
  virtual void handleAppearingChange (bool appearing);
  virtual void handleHoverEnterEvent ();
  virtual void handleHoverLeaveEvent ();
  virtual void handleMousePress (const QPointF &posScene);
  virtual void handleVisibleChange (bool visible);
  virtual QString stateName () const;

private:
  GuidelineStateConstantTAppearing();

};

#endif // GUIDELINE_STATE_CONSTANT_T_APPEARING_H
