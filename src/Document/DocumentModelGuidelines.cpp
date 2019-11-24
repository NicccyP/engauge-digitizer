/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "DocumentModelGuidelines.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include <QObject>
#include <QTextStream>
#include "QtToString.h"
#include <QXmlStreamWriter>
#include "Xml.h"

DocumentModelGuidelines::DocumentModelGuidelines()
{
}

DocumentModelGuidelines::DocumentModelGuidelines(const Document &document) :
  m_valuesX (document.modelGuidelines().valuesX ()),
  m_valuesY (document.modelGuidelines().valuesY ())
{
}

DocumentModelGuidelines::DocumentModelGuidelines(const DocumentModelGuidelines &other) :
  m_valuesX (other.valuesX ()),
  m_valuesY (other.valuesY ())
{
}

DocumentModelGuidelines &DocumentModelGuidelines::operator=(const DocumentModelGuidelines &other)
{
  m_valuesX = other.valuesX ();
  m_valuesY = other.valuesY ();

  return *this;
}

void DocumentModelGuidelines::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelGuidelines::loadXml";

  bool success = true;

  QXmlStreamAttributes attributes = reader.attributes();

  if (!success) {
    reader.raiseError (QObject::tr ("Cannot read grid display data"));
  }
}

void DocumentModelGuidelines::printStream(QString indentation,
                                           QTextStream &str) const
{
  str << indentation << "DocumentModelGuidelines\n";

  indentation += INDENTATION_DELTA;
}

void DocumentModelGuidelines::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelGuidelines::saveXml";
}

void DocumentModelGuidelines::setValuesX (const GuidelineValues &valuesX)
{
  m_valuesX = valuesX;
}

void DocumentModelGuidelines::setValuesY (const GuidelineValues &valuesY)
{
  m_valuesY = valuesY;
}

GuidelineValues DocumentModelGuidelines::valuesX () const
{
  return m_valuesX;
}

GuidelineValues DocumentModelGuidelines::valuesY () const
{
  return m_valuesY;
}
