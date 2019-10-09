#include "CmdAddPointAxis.h"
#include "CmdGong.h"
#include "GuidelineAbstract.h"
#include "Guidelines.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QApplication>
#include <qdebug.h>
#include <QSettings>
#include <QTextStream>
#include <QThread>
#include "Settings.h"
#include "Test/TestGuidelines.h"

using namespace std;

int main (int argc, char **argv)
{
  QApplication app (argc, argv);

  TestGuidelines test;
  test.initTestCase();
}

TestGuidelines::TestGuidelines(QObject *parent) :
  QObject(parent),
  m_mainWindow (0)
{
}

void TestGuidelines::cleanupTestCase ()
{
}

bool TestGuidelines::compareExpectedAndGot (const QVector<int> &countsExpected)
{
  Guidelines &guidelines = m_mainWindow->guidelines();
  const GuidelineContainerPrivate &container = guidelines.guidelineContainerPrivate();

  QVector<int> countsGot (NUM_GUIDELINE_STATES);
  GuidelineContainerPrivate::const_iterator itr;
  for (itr = container.begin(); itr != container.end(); itr++) {
    const GuidelineAbstract *guideline = *itr;

    GuidelineState state = guidelineStateFromString (guideline->state ());
    countsGot [state] += 1;
  }

  // Compare expected and got counts
  bool success = true;
  for (int state = 0; state < NUM_GUIDELINE_STATES; state++) {

    // We look for a difference, except for the discarded state which is not important
    if ((countsExpected [state] != countsGot [state]) &&
        (state != GUIDELINE_STATE_DISCARDED)) {

      success = false;  // Noop
      break;
    }
  }

  // Debug
  if (!success) {

    QString text;
    QTextStream str (&text);
    for (int state = 0; state < NUM_GUIDELINE_STATES; state++) {
      if ((countsExpected [state] != 0) || (countsGot [state] != 0)) {
        if (state != GUIDELINE_STATE_DISCARDED) {

          str << guidelineStateAsString (static_cast<GuidelineState> (state)) << "=" << countsExpected [state] << "/" << countsGot [state] << " ";
        }
      }
    }
    qDebug() << "expected/got = " << text;
  }

  return success;
}

GuidelineState TestGuidelines::guidelineStateFromString (const QString &string) const
{
  for (int i = 0; i < NUM_GUIDELINE_STATES; i++) {
    GuidelineState state = static_cast<GuidelineState> (i);
    if (string == guidelineStateAsString (state)) {
      return state;
    }
  }

  return GUIDELINE_STATE_DISCARDED;
}

void TestGuidelines::initTestCase ()
{
  turnOffChecklist ();

  // Start MainWindow
  const bool NO_DROP_REGRESSION = false;
  const QString NO_ERROR_REPORT_LOG_FILE;
  const QString NO_REGRESSION_OPEN_FILE;
  const bool NO_GNUPLOT_LOG_FILES = false;
  const bool NO_REGRESSION_IMPORT = false;
  const bool NO_RESET = false;
  const bool NO_EXPORT_ONLY = false;
  const bool NO_EXPORT_IMAGE_ONLY = false;
  const QString NO_EXPORT_IMAGE_EXTENSION;
  const bool DEBUG_FLAG = false;
  QStringList importFile;
  const QStringList NO_COMMAND_LINE;

  importFile << "../samples/inverse.jpg";

  initializeLogging ("engauge_test",
                     "engauge_test.log",
                     DEBUG_FLAG);

  m_mainWindow = new MainWindow (NO_ERROR_REPORT_LOG_FILE,
                                 NO_REGRESSION_OPEN_FILE,
                                 NO_DROP_REGRESSION,
                                 NO_REGRESSION_IMPORT,
                                 NO_GNUPLOT_LOG_FILES,
                                 NO_RESET,
                                 NO_EXPORT_ONLY,
                                 NO_EXPORT_IMAGE_ONLY,
                                 NO_EXPORT_IMAGE_EXTENSION,
                                 importFile,
                                 NO_COMMAND_LINE);

  // This signal will trigger a callback until after this method has finished executing
  connect (m_mainWindow, SIGNAL (signalShowEvent ()),
           this, SLOT (test00StartupWithoutTransformation ()));

  m_mainWindow->show ();
}

void TestGuidelines::processEventsElsewhere ()
{
  // Need time to let MainWindow import the file, which involves a QTimer
  for (int i = 0; i < 1000; i++) {
    qApp->processEvents();
  }
}

void TestGuidelines::test00StartupWithoutTransformation ()
{
  // Expected and got counts
  QVector<int> countsExpected (NUM_GUIDELINE_STATES);
  countsExpected [GUIDELINE_STATE_DISCARDED] = 4;
  
  bool success = compareExpectedAndGot (countsExpected);

  qDebug() << (success ? "[PASS]" : "[FAIL]") << __FUNCTION__;

  test01AfterAddingTransformationPrepare ();
  
  // Setup for next test in the chain
  connect (m_mainWindow, SIGNAL (signalGong ()),
           this, SLOT (test01AfterAddingTransformation ()));
}

void TestGuidelines::test01AfterAddingTransformation ()
{
  // Expected and got counts
  QVector<int> countsExpected (NUM_GUIDELINE_STATES);
  countsExpected [GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_LURKING] = 1;
  countsExpected [GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_LURKING   ] = 1;
  countsExpected [GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_LURKING    ] = 1;
  countsExpected [GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_LURKING   ] = 1;

  bool success = compareExpectedAndGot (countsExpected);

  qDebug() << (success ? "[PASS]" : "[FAIL]") << __FUNCTION__;
}

void TestGuidelines::test01AfterAddingTransformationPrepare ()
{
  QPointF posScreen0 (400, 400);
  QPointF posScreen1 (600, 400);
  QPointF posScreen2 (400, 200);
  QPointF posGraph0 (40, 40);
  QPointF posGraph1 (60, 40);
  QPointF posGraph2 (40, 20);
  CmdAddPointAxis *cmd0 = new CmdAddPointAxis (*m_mainWindow,
                                               m_mainWindow->cmdMediator()->document(),
                                               posScreen0,
                                               posGraph0,
                                               0.0,
                                               false);
  CmdAddPointAxis *cmd1 = new CmdAddPointAxis (*m_mainWindow,
                                               m_mainWindow->cmdMediator()->document(),
                                               posScreen1,
                                               posGraph1,
                                               1.0,
                                               false);
  CmdAddPointAxis *cmd2 = new CmdAddPointAxis (*m_mainWindow,
                                               m_mainWindow->cmdMediator()->document(),
                                               posScreen2,
                                               posGraph2,
                                               2.0,
                                               false);
  CmdGong *cmd3 = new CmdGong (*m_mainWindow,
                               m_mainWindow->cmdMediator()->document());
                               
  m_mainWindow->cmdMediator()->push (cmd0);
  m_mainWindow->cmdMediator()->push (cmd1);
  m_mainWindow->cmdMediator()->push (cmd2);
  m_mainWindow->cmdMediator()->push (cmd3);  
}

void TestGuidelines::turnOffChecklist ()
{
  // Turn off checklist
  QSettings settings (SETTINGS_ENGAUGE, SETTINGS_DIGITIZER);
  
  settings.beginGroup (SETTINGS_GROUP_MAIN_WINDOW);
  settings.setValue (SETTINGS_CHECKLIST_GUIDE_WIZARD, false);
  settings.endGroup ();
}
