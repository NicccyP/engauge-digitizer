#ifndef TEST_GUIDELINES_H
#define TEST_GUIDELINES_H

#include "GuidelineState.h"
#include <QObject>
#include <QString>

class MainWindow;

/// Unit test of guidelines. This does not use QtTest framework since we need to let
/// CmdMediator command stack work its way through the commands between tests, and
/// prior to the first test, using asynchronous signals and slots. The QtTest framework
/// flies through all tests without stopping, and even pausing with calls to
/// QCoreApplication::processEvents does not clear off the stack so queued signals
/// can be processed
///
/// Some signals specific to unit testing are received by this class so it must
/// inherit from QObject
class TestGuidelines : public QObject
{
  Q_OBJECT
public:
  /// Single constructor.
  explicit TestGuidelines(QObject *parent = 0);

  /// Initialize and start chain of tests
  void initTestCase ();

public slots:
  // These would be private slots but we want to control when they are called so
  // these are moved outside of the private slots (which qttest automatically calls)
  void cleanupTestCase ();
  void test00StartupWithoutTransformation ();
  void test01AfterAddingTransformation ();

private:

  bool compareExpectedAndGot (const QVector<int> &countsExpected);
  GuidelineState guidelineStateFromString (const QString &string) const;
  void processEventsElsewhere ();
  void test01AfterAddingTransformationPrepare ();
  void turnOffChecklist ();

  MainWindow *m_mainWindow;

};

#endif // TEST_GUIDELINES_H
