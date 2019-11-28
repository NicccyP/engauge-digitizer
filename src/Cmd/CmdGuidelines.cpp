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
                             Document &document,
                             const GuidelineValues &valuesXBefore,
                             const GuidelineValues &valuesYBefore,
                             const GuidelineValues &valuesXAfter,
                             const GuidelineValues &valuesYAfter,
                             const GuidelineValues &valuesXAppearing,
                             const GuidelineValues &valuesYAppearing) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_valuesXTBefore (valuesXBefore),
  m_valuesXTAfter (valuesXAfter),
  m_valuesYRBefore (valuesYBefore),
  m_valuesYRAfter (valuesYAfter),
  m_valuesXTAfterAppearing (valuesXAppearing),
  m_valuesYRAfterAppearing (valuesYAppearing)
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

  mainWindow().updateGuidelines (m_valuesXTAfter,
                                 m_valuesYRAfter,
                                 m_valuesXTAfterAppearing,
                                 m_valuesYRAfterAppearing);
}

void CmdGuidelines::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelines::cmdUndo";

  GuidelineValues emptyListXT, emptyListYR;
  mainWindow().updateGuidelines (m_valuesXTBefore,
                                 m_valuesYRBefore,
                                 emptyListXT,
                                 emptyListYR);
}

void CmdGuidelines::saveXml (QXmlStreamWriter & /* writer */) const
{
  // Noop. This command is only for unit testing, and is completely independent of the Document that is being saved
}
