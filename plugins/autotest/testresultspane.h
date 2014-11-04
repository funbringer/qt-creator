/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Creator Enterprise Auto Test Add-on.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

#ifndef TESTRESULTSPANE_H
#define TESTRESULTSPANE_H

#include <coreplugin/ioutputpane.h>

QT_BEGIN_NAMESPACE
class QAction;
class QModelIndex;
class QMenu;
class QToolButton;
QT_END_NAMESPACE

namespace Core {
class IContext;
}

namespace Utils {
class ListView;
}

namespace Autotest {
namespace Internal {

class TestResult;
class TestResultModel;
class TestResultFilterModel;

class TestResultsPane : public Core::IOutputPane
{
    Q_OBJECT
public:
    virtual ~TestResultsPane();
    static TestResultsPane *instance();

    void addTestResult(const TestResult &result);

    // IOutputPane interface
    QWidget *outputWidget(QWidget *parent);
    QList<QWidget *> toolBarWidgets() const;
    QString displayName() const;
    int priorityInStatusBar() const;
    void clearContents();
    void visibilityChanged(bool);
    void setFocus();
    bool hasFocus() const;
    bool canFocus() const;
    bool canNavigate() const;
    bool canNext() const;
    bool canPrevious() const;
    void goToNext();
    void goToPrev();

signals:

public slots:

private slots:
    void onItemActivated(const QModelIndex &index);
    void onRunAllTriggered();
    void onRunSelectedTriggered();
    void initializeFilterMenu();
    void filterMenuTriggered(QAction *action);

private:
    explicit TestResultsPane(QObject *parent = 0);
    void createToolButtons();
    void onTestRunStarted();
    void onTestRunFinished();
    void onTestTreeModelChanged();

    Utils::ListView *m_listView;
    TestResultModel *m_model;
    TestResultFilterModel *m_filterModel;
    Core::IContext *m_context;
    QToolButton *m_runAll;
    QToolButton *m_runSelected;
    QToolButton *m_stopTestRun;
    QToolButton *m_filterButton;
    QMenu *m_filterMenu;
};

} // namespace Internal
} // namespace Autotest

#endif // TESTRESULTSPANE_H
