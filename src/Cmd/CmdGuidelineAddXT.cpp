/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdGuidelineAddXT.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"

const QString CMD_DESCRIPTION ("GuidelineAddXT");

CmdGuidelineAddXT::CmdGuidelineAddXT(MainWindow &mainWindow,
                                     Document &document,
                                     double value) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_value (value)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineAddXT::CmdGuidelineAddXT";
}

CmdGuidelineAddXT::CmdGuidelineAddXT (MainWindow &mainWindow,
                                      Document &document,
                                      const QString &cmdDescription,
                                      QXmlStreamReader & /* reader */) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineAddXT::CmdGuidelineAddXT";
}

CmdGuidelineAddXT::~CmdGuidelineAddXT ()
{
}

void CmdGuidelineAddXT::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineAddXT::cmdRedo";

  mainWindow().guidelineAddXT (m_value);
}

void CmdGuidelineAddXT::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineAddXT::cmdUndo";

  mainWindow().guidelineRemoveXT (m_value);
}

void CmdGuidelineAddXT::saveXml (QXmlStreamWriter & /* writer */) const
{
  // Noop. This command is only for unit testing, and is completely independent of the Document that is being saved
}
