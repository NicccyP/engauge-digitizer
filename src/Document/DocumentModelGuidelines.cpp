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

  // Read until end of this subtree
  while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
  (reader.name() != DOCUMENT_SERIALIZE_GUIDELINES)){

    QXmlStreamReader::TokenType tokenType = loadNextFromReader(reader);

    if ((tokenType == QXmlStreamReader::StartElement) &&
        (reader.name() == DOCUMENT_SERIALIZE_GUIDELINES_X)) {

      loadXmlVector (reader,
                     DOCUMENT_SERIALIZE_GUIDELINES_X,
                     m_valuesX);
    }

    if ((tokenType == QXmlStreamReader::StartElement) &&
        (reader.name() == DOCUMENT_SERIALIZE_GUIDELINES_Y)) {

      loadXmlVector (reader,
                     DOCUMENT_SERIALIZE_GUIDELINES_Y,
                     m_valuesY);
    }

    if (reader.atEnd()) {
      success = false;
      break;
    }
  }

  if (!success) {
    reader.raiseError (QObject::tr ("Cannot read grid display data"));
  }
}

void DocumentModelGuidelines::loadXmlVector (QXmlStreamReader &reader,
                                             const QString &tokenEnd,
                                             GuidelineValues &guidelineValues) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelGuidelines::loadXmlVector";

  while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
  (reader.name() != tokenEnd)){

    QXmlStreamReader::TokenType tokenType = loadNextFromReader(reader);

    if (reader.atEnd()) {
      break;
    }

    if (tokenType == QXmlStreamReader::StartElement) {

      guidelineValues << reader.text().toDouble();
    }
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

  writer.writeStartElement(DOCUMENT_SERIALIZE_GUIDELINES);
  saveXmlVector (writer,
                 DOCUMENT_SERIALIZE_GUIDELINES_X,
                 DOCUMENT_SERIALIZE_GUIDELINE,
                 m_valuesX);
  saveXmlVector (writer,
                 DOCUMENT_SERIALIZE_GUIDELINES_Y,
                 DOCUMENT_SERIALIZE_GUIDELINE,
                 m_valuesX);
  writer.writeEndElement();
}

void DocumentModelGuidelines::saveXmlVector(QXmlStreamWriter &writer,
                                            const QString &tokenAll,
                                            const QString &tokenItem,
                                            const GuidelineValues &values) const
{
  writer.writeStartElement(tokenAll);

  // Loop through values
  GuidelineValues::const_iterator itr;
  for (itr = values.begin(); itr != values.end(); itr++) {
    double value = *itr;
    writer.writeTextElement(tokenItem,
                            QString::number (value));
  }

  writer.writeEndElement();
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
