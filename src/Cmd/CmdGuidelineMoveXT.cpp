/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdGuidelineMoveXT.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"

const QString CMD_DESCRIPTION ("GuidelineMoveXT");

CmdGuidelineMoveXT::CmdGuidelineMoveXT(MainWindow &mainWindow,
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
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineMoveXT::CmdGuidelineMoveXT";
}

CmdGuidelineMoveXT::CmdGuidelineMoveXT (MainWindow &mainWindow,
                                        Document &document,
                                        const QString &cmdDescription,
                                        QXmlStreamReader & /* reader */) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineMoveXT::CmdGuidelineMoveXT";
}

CmdGuidelineMoveXT::~CmdGuidelineMoveXT ()
{
}

void CmdGuidelineMoveXT::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineMoveXT::cmdRedo";

  mainWindow().guidelineMoveXT (m_identifier,
                                m_valueAfter);
}

void CmdGuidelineMoveXT::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineMoveXT::cmdUndo";

  mainWindow().guidelineMoveXT (m_identifier,
                                m_valueBefore);
}

void CmdGuidelineMoveXT::saveXml (QXmlStreamWriter & /* writer */) const
{
  // Noop. This command is only for unit testing, and is completely independent of the Document that is being saved
}
