/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdGuidelines.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"

const QString CMD_DESCRIPTION ("Guidelines");

CmdGuidelines::CmdGuidelines(MainWindow &mainWindow,
                             Document &document) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelines::CmdGuidelines";
}

CmdGuidelines::CmdGuidelines (MainWindow &mainWindow,
                              Document &document,
                              const QString &cmdDescription,
                              QXmlStreamReader & /* reader */) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelines::CmdGuidelines";
}

CmdGuidelines::~CmdGuidelines ()
{
}

void CmdGuidelines::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelines::cmdRedo";

  //mainWindow().sendGuideline ();
}

void CmdGuidelines::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelines::cmdUndo";
}

void CmdGuidelines::saveXml (QXmlStreamWriter & /* writer */) const
{
  // Noop. This command is only for unit testing, and is completely independent of the Document that is being saved
}
