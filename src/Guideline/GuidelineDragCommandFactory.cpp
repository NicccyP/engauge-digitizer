/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdAbstract.h"
#include "DocumentModelGuidelines.h"
#include "GuidelineDragCommandFactory.h"
#include "Guidelines.h"
#include "Logger.h"

GuidelineDragCommandFactory::GuidelineDragCommandFactory ()
{
}

CmdAbstract *GuidelineDragCommandFactory::createAfterDrag (const DocumentModelGuidelines &modelGuidelinesDisplay,
                                                           const DocumentModelGuidelines &modelGuidelinesDocument)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineDragCommandFactory::GuidelineDragCommandFactory";

  GuidelineValues::iterator itr;

  GuidelineValues valuesXDisplay = modelGuidelinesDisplay.valuesX ();
  GuidelineValues valuesXDocument = modelGuidelinesDocument.valuesX ();

  removeAllMatchesExceptTheWorst (valuesXDisplay,
                                  valuesXDocument);

  GuidelineValues valuesYDisplay = modelGuidelinesDisplay.valuesY ();
  GuidelineValues valuesYDocument = modelGuidelinesDocument.valuesY ();

  removeAllMatchesExceptTheWorst (valuesYDisplay,
                                  valuesYDocument);

  return 0;
}

void GuidelineDragCommandFactory::removeAllMatchesExceptTheWorst (GuidelineValues &valuesDisplay,
                                                                  GuidelineValues &valuesDocument) const
{
  // Each pass removes the worst match. We repeat N-1 times until one pair is left. This algorithm
  // is robust, and simple. Since the two lists are small, efficiency is not an issue
  for (int pass = 0; pass < valuesDisplay.size () - 1; pass++) {

    bool isFirst = true;
    double distanceWorst = 0; // Initial value is ignored
    double valueDisplayWorst = 0, valueDocumentWorst = 0;

    GuidelineValues::iterator itrDisplay;
    for (itrDisplay = valuesDisplay.begin (); itrDisplay != valuesDisplay.end (); itrDisplay++) {
      double valueDisplay = *itrDisplay;
      GuidelineValues::iterator itrDocument;
      for (itrDocument = valuesDocument.begin (); itrDocument != valuesDocument.end (); itrDocument++) {
        double valueDocument = *itrDocument;
        double distance = qAbs (valueDisplay - valueDocument);
        if (isFirst || (distance > distanceWorst)) {
          isFirst = false;
          distanceWorst = distance;
          valueDisplayWorst = valueDisplay;
          valueDocumentWorst = valueDocument;
        }
      }
    }

    valuesDisplay.removeOne (valueDisplayWorst);
    valuesDocument.removeOne (valueDocumentWorst);
  }
}

