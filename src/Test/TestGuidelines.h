#ifndef TEST_GUIDELINES_H
#define TEST_GUIDELINES_H

#include "GuidelineState.h"
#include <QObject>
#include <QString>
#include <QTimer>

class MainWindow;

/// Unit test of guidelines
class TestGuidelines : public QObject
{
  Q_OBJECT
public:
  /// Single constructor.
  explicit TestGuidelines(QObject *parent = 0);

private slots:
  void cleanupTestCase ();
  void initTestCase ();

  void test00StartupWithoutTransformation ();
  void test01AfterAddingTransformation ();

private:

  bool compareExpectedAndGot (const QVector<int> &countsExpected);
  GuidelineState guidelineStateFromString (const QString &string) const;
  void processEventsElsewhere ();
  void turnOffChecklist ();

  MainWindow *m_mainWindow;

  QTimer m_timerStartupWithoutTransformation;

};

#endif // TEST_GUIDELINES_H
