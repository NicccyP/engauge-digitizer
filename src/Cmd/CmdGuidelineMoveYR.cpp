/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdGuidelineMoveYR.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"

const QString CMD_DESCRIPTION ("GuidelineMoveYR");

CmdGuidelineMoveYR::CmdGuidelineMoveYR(MainWindow &mainWindow,
                                       Document &document,
                                       const QString &identifier,
                                       double valueBefore,
                                       double valueAfter) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_identifier (identifier),
  m_valueBefore (valueBefore),
  m_valueAfter (valueAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineMoveYR::CmdGuidelineMoveYR";
}

CmdGuidelineMoveYR::CmdGuidelineMoveYR (MainWindow &mainWindow,
                                        Document &document,
                                        const QString &cmdDescription,
                                        QXmlStreamReader & /* reader */) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineMoveYR::CmdGuidelineMoveYR";
}

CmdGuidelineMoveYR::~CmdGuidelineMoveYR ()
{
}

void CmdGuidelineMoveYR::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineMoveYR::cmdRedo"
                              << " identifier=" << m_identifier.toLatin1().data()
                              << " value=" << m_valueAfter;

  mainWindow().guidelineMoveYR (m_identifier,
                                m_valueAfter);
}

void CmdGuidelineMoveYR::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineMoveYR::cmdUndo"
                              << " identifier=" << m_identifier.toLatin1().data()
                              << " value=" << m_valueBefore;

  mainWindow().guidelineMoveYR (m_identifier,
                                m_valueBefore);
}

void CmdGuidelineMoveYR::saveXml (QXmlStreamWriter & /* writer */) const
{
  // Noop. This command is only for unit testing, and is completely independent of the Document that is being saved
}
