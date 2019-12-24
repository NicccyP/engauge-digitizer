/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdGuidelineRemoveYR.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"

const QString CMD_DESCRIPTION ("GuidelineRemoveYR");

CmdGuidelineRemoveYR::CmdGuidelineRemoveYR(MainWindow &mainWindow,
                                           Document &document,
                                           double value) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_value (value)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineRemoveYR::CmdGuidelineRemoveYR";
}

CmdGuidelineRemoveYR::CmdGuidelineRemoveYR (MainWindow &mainWindow,
                                            Document &document,
                                            const QString &cmdDescription,
                                            QXmlStreamReader & /* reader */) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineRemoveYR::CmdGuidelineRemoveYR";
}

CmdGuidelineRemoveYR::~CmdGuidelineRemoveYR ()
{
}

void CmdGuidelineRemoveYR::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineRemoveYR::cmdRedo";

  mainWindow().guidelineRemoveYR (m_value);
}

void CmdGuidelineRemoveYR::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineRemoveYR::cmdUndo";

  mainWindow().guidelineAddYR (m_value);
}

void CmdGuidelineRemoveYR::saveXml (QXmlStreamWriter & /* writer */) const
{
  // Noop. This command is only for unit testing, and is completely independent of the Document that is being saved
}
