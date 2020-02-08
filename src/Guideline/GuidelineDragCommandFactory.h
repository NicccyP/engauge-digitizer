/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_DRAG_COMMAND_FACTORY_H
#define GUIDELINE_DRAG_COMMAND_FACTORY_H

class CmdAbstract;
class Guidelines;

/// Determine if inputs that were collected after a Guideline drag should result in a Cmd to move or
/// Cmd to delete, and then generate the appropriate Cmd
class GuidelineDragCommandFactory
{
public:
  /// Single constructor.
  GuidelineDragCommandFactory();

  /// Create delete or move Cmd
  CmdAbstract *create (const Guidelines &guidelines);
};

#endif // GUIDELINE_DRAG_COMMAND_FACTORY_H
