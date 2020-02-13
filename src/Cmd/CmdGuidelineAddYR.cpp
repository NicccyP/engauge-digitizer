/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdGuidelineAddYR.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "GuidelineIdentifierGenerator.h"
#include "Logger.h"
#include "MainWindow.h"

const QString CMD_DESCRIPTION ("GuidelineAddYR");

CmdGuidelineAddYR::CmdGuidelineAddYR(MainWindow &mainWindow,
                                     Document &document,
                                     double value) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_identifier (GuidelineIdentifierGenerator::next ()),
  m_value (value)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineAddYR::CmdGuidelineAddYR";
}

CmdGuidelineAddYR::CmdGuidelineAddYR (MainWindow &mainWindow,
                                      Document &document,
                                      const QString &cmdDescription,
                                      QXmlStreamReader & /* reader */) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineAddYR::CmdGuidelineAddYR";
}

CmdGuidelineAddYR::~CmdGuidelineAddYR ()
{
}

void CmdGuidelineAddYR::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineAddYR::cmdRedo";

  mainWindow().guidelineAddYR (m_identifier,
                               m_value);
}

void CmdGuidelineAddYR::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineAddYR::cmdUndo";

  mainWindow().guidelineRemoveYR (m_identifier);
}

void CmdGuidelineAddYR::saveXml (QXmlStreamWriter & /* writer */) const
{
  // Noop. This command is only for unit testing, and is completely independent of the Document that is being saved
}
