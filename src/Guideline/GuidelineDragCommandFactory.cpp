/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdAbstract.h"
#include "GuidelineDragCommandFactory.h"
#include "Guidelines.h"
#include "Logger.h"

GuidelineDragCommandFactory::GuidelineDragCommandFactory ()
{
}

CmdAbstract *GuidelineDragCommandFactory::create (const Guidelines &guidelines)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineDragCommandFactory::GuidelineDragCommandFactory";

  return 0;
}
