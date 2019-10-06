/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineState.h"
#include <QHash>

typedef QHash<GuidelineState, QString> GuidelineStateHash;

static GuidelineStateHash guidelineStateHash;

QString guidelineStateAsString (GuidelineState state)
{
  if (guidelineStateHash.size () == 0) {

    // First time through we load the hash
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE]         = "DeployedConstantRActive";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HIDE]           = "DeployedConstantRHide";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HOVER]          = "DeployedConstantRHover";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_LOCKED]         = "DeployedConstantRLocked";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE]         = "DeployedConstantTActive";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_T_HIDE]           = "DeployedConstantTHide";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_T_HOVER]          = "DeployedConstantTHover";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_T_LOCKED]         = "DeployedConstantTLocked";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE]         = "DeployedConstantXActive";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HIDE]           = "DeployedConstantXHide";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HOVER]          = "DeployedConstantXHover";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_X_LOCKED]         = "DeployedConstantXLocked";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE]         = "DeployedConstantYActive";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_HIDE]           = "DeployedConstantYHide";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_HOVER]          = "DeployedConstantYHover";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_LOCKED]         = "DeployedConstantYLocked";
    guidelineStateHash [GUIDELINE_STATE_DISCARDED]                          = "Discarded";
    guidelineStateHash [GUIDELINE_STATE_HANDLE]                             = "Handle";
    guidelineStateHash [GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_HIDE]    = "TemplateHorizontalBottomHide";
    guidelineStateHash [GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_HOVER]   = "TemplateHorizontalBottomHover";
    guidelineStateHash [GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_LURKING] = "TemplateHorizontalBottomLurking";
    guidelineStateHash [GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_HIDE]       = "TemplateHorizontalTopHide";
    guidelineStateHash [GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_HOVER]      = "TemplateHorizontalTopHover";
    guidelineStateHash [GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_LURKING]    = "TemplateHorizontalTopLurking";
    guidelineStateHash [GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_HIDE]        = "TemplateVerticalLeftHide";
    guidelineStateHash [GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_HOVER]       = "TemplateVerticalLeftHover";
    guidelineStateHash [GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_LURKING]     = "TemplateVerticalLeftLurking";
    guidelineStateHash [GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_HIDE]       = "TemplateVerticalRightHide";
    guidelineStateHash [GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_HOVER]      = "TemplateVerticalRightHover";
    guidelineStateHash [GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_LURKING]    = "TemplateVerticalRightLurking";
  }

  if (guidelineStateHash.contains (state)) {
    return guidelineStateHash [state];
  } else {
    return "?";
  }
}
