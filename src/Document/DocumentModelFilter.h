#ifndef DOCUMENT_MODEL_FILTER_H
#define DOCUMENT_MODEL_FILTER_H

#include "CurveFilter.h"
#include "DocumentModelAbstractBase.h"
#include <QHash>

// Lookup-table by curve name
typedef QHash<QString, CurveFilter> CurveFilters;

class Document;

/// Model for DlgSettingsFilter and CmdSettingsFilter.
class DocumentModelFilter : public DocumentModelAbstractBase
{
public:
  /// Default constructor.
  DocumentModelFilter();

  /// Initial constructor from Document.
  DocumentModelFilter(const Document &document);

  /// Copy constructor.
  DocumentModelFilter(const DocumentModelFilter &other);

  /// Assignment constructor.
  DocumentModelFilter &operator=(const DocumentModelFilter &other);

  /// Get method for copying one curve filter. Cannot return just a reference or else there is a warning about returning reference to temporary
  const CurveFilter curveFilter (const QString &curveName) const;

  /// Get method for copying all curve filters in one step.
  const CurveFilters &curveFilters () const;

  /// Get method for filter mode.
  FilterMode filterMode(const QString &curveName) const;

  /// Get method for foreground higher bound.
  int foregroundHigh (const QString &curveName) const;

  /// Get method for foreground lower bound.
  int foregroundLow (const QString &curveName) const;

  /// High value of foreground, hue, intensity, saturation or value according to current filter mode.
  /// normalized to 0 to 1.
  double high (const QString &curveName) const;

  /// Get method for hue higher bound.
  int hueHigh (const QString &curveName) const;

  /// Get method for hue lower bound.
  int hueLow (const QString &curveName) const;

  /// Get method for intensity higher bound.
  int intensityHigh (const QString &curveName) const;

  /// Get method for intensity lower bound.
  int intensityLow (const QString &curveName) const;

  /// Low value of foreground, hue, intensity, saturation or value according to current filter mode
  /// normalized to 0 to 1.
  double low (const QString &curveName) const;

  /// Get method for saturation higher bound.
  int saturationHigh (const QString &curveName) const;

  /// Get method for saturation lower bound.
  int saturationLow (const QString &curveName) const;

  virtual void saveModel(QXmlStreamWriter &stream) const;

  /// Set method for filter mode.
  void setFilterMode(const QString &curveName,
                     FilterMode filterMode);

  /// Set method for foreground higher bound.
  void setForegroundHigh (const QString &curveName,
                          int foregroundHigh);

  /// Set method for foreground lower bound.
  void setForegroundLow (const QString &curveName,
                         int foregroundLow);

  /// Set the high value for the current filter mode.
  void setHigh (const QString &curveName,
                double s0To1);

  /// Set method for hue higher bound.
  void setHueHigh (const QString &curveName,
                   int hueHigh);

  /// Set method for hue lower bound.
  void setHueLow (const QString &curveName,
                  int hueLow);

  /// Set method for intensity higher bound.
  void setIntensityHigh (const QString &curveName,
                         int intensityHigh);

  /// Set method for intensity lower bound.
  void setIntensityLow (const QString &curveName,
                        int intensityLow);

  /// Set the low value for the current filter mode.
  void setLow (const QString &curveName,
               double s0To1);

  /// Set method for saturation high.
  void setSaturationHigh (const QString &curveName,
                          int saturationHigh);

  /// Set method for saturation low.
  void setSaturationLow (const QString &curveName,
                         int saturationLow);

  /// Set method for value high.
  void setValueHigh (const QString &curveName,
                     int valueHigh);

  /// Set method for value low.
  void setValueLow (const QString &curveName,
                    int valueLow);

  /// Get method for value high.
  int valueHigh (const QString &curveName) const;

  /// Get method for value low.
  int valueLow (const QString &curveName) const;

private:

  CurveFilters m_curveFilters;
};

#endif // DOCUMENT_MODEL_FILTER_H
