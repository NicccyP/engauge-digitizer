/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_GUIDELINES_H
#define CMD_GUIDELINES_H

#include "CmdAbstract.h"
#include "GuidelineValues.h"

class QXmlStreamReader;

/// Command for changing from one set of Guideline values to another. This applies to
/// Guideline creation, removal and modification (=value change)
class CmdGuidelines : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdGuidelines(MainWindow &mainWindow,
                Document &document,
                const GuidelineValues &valuesXBefore,
                const GuidelineValues &valuesYBefore,
                const GuidelineValues &valuesXAfter,
                const GuidelineValues &valuesYAfter,
                const GuidelineValues &valuesXAppearing,
                const GuidelineValues &valuesYAppearing);

  /// Constructor for parsing error report file xml
  CmdGuidelines(MainWindow &mainWindow,
                Document &document,
                const QString &cmdDescription,
                QXmlStreamReader &reader);

  virtual ~CmdGuidelines();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdGuidelines();

  // Values before redo and after undo
  GuidelineValues m_valuesXTBefore;
  GuidelineValues m_valuesXTAfter;

  // Values after redo and before undo
  GuidelineValues m_valuesYRBefore;
  GuidelineValues m_valuesYRAfter;

  // Special handling for just-created Guidelines just after redo. Although conceptually belonging to
  // m_valuesXTAfter and m_valuesYRAfter, they are instantiated as Guidelines in the appearing state,
  // which involves animation
  GuidelineValues m_valuesXTAfterAppearing;
  GuidelineValues m_valuesYRAfterAppearing;
};

#endif // CMD_GUIDELINES_H
