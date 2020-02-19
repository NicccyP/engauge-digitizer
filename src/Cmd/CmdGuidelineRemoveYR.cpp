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
                                           const QString &identifier,
                                           double valueBefore) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_identifier (identifier),
  m_valueBefore (valueBefore)
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
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineRemoveYR::cmdRedo"
                              << " identifier=" << m_identifier.toLatin1().data();

  mainWindow().guidelineRemove (m_identifier);
}

void CmdGuidelineRemoveYR::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineRemoveYR::cmdUndo"
                              << " identifier=" << m_identifier.toLatin1().data()
                              << " value=" << m_valueBefore;

  mainWindow().guidelineAddYR (m_identifier,
                               m_valueBefore);
}

void CmdGuidelineRemoveYR::saveXml (QXmlStreamWriter & /* writer */) const
{
  // Noop. This command is only for unit testing, and is completely independent of the Document that is being saved
}
