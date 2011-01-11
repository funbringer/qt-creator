/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** No Commercial Usage
**
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**************************************************************************/

#ifndef QMLJSINSPECTOR_H
#define QMLJSINSPECTOR_H

#include "qmljsprivateapi.h"

#include <debugger/debuggerconstants.h>
#include <qmlprojectmanager/qmlprojectrunconfiguration.h>
#include <utils/fileinprojectfinder.h>

#include <qmljs/qmljsdocument.h>
#include <qmljs/parser/qmljsastfwd_p.h>

#include <QtGui/QAction>
#include <QtCore/QObject>

namespace ProjectExplorer {
    class Project;
    class Environment;
}

namespace TextEditor {
    class ITextEditor;
}

namespace Core {
    class IContext;
}

namespace QmlJS {
    class ModelManagerInterface;
}

namespace QmlJSInspector {
namespace Internal {

class QmlInspectorToolbar;
class QmlJSObjectTree;
class ClientProxy;
class InspectorSettings;
class ContextCrumblePath;
class QmlJSLiveTextPreview;

class InspectorUi : public QObject
{
    Q_OBJECT

public:
    enum DebugMode {
        StandaloneMode,
        CppProjectWithQmlEngines,
        QmlProjectWithCppPlugins
    };
public:
    InspectorUi(QObject *parent = 0);
    virtual ~InspectorUi();

    void saveSettings() const;
    void restoreSettings();

    bool showExperimentalWarning();
    void setShowExperimentalWarning(bool value);

    static InspectorUi *instance();

    // returns the project being currently debugged, or 0 if not debugging anything
    ProjectExplorer::Project *debugProject() const;
    QString debugProjectBuildDirectory() const;
    bool isShadowBuildProject() const;

    void setupUi();
    bool isConnected() const;
    void connected(ClientProxy *clientProxy);
    void disconnected();
    void setDebuggerEngine(QObject *qmlEngine);
    QObject *debuggerEngine() const;

signals:
    void statusMessage(const QString &text);
    void livePreviewActivated(bool isActivated);

public slots:
    void reloadQmlViewer();
    void serverReloaded();
    void setApplyChangesToQmlObserver(bool applyChanges);

private slots:
    void enable();
    void disable();
    void gotoObjectReferenceDefinition(const QDeclarativeDebugObjectReference &obj);
    void gotoObjectReferenceDefinition(QList<QDeclarativeDebugObjectReference> objectReferences);
    void changeSelectedItems(const QList<QDeclarativeDebugObjectReference> &objects);

    void updateEngineList();


    void removePreviewForEditor(Core::IEditor *newEditor);
    QmlJSLiveTextPreview *createPreviewForEditor(Core::IEditor *newEditor);

    void disableLivePreview();
    void crumblePathElementClicked(int);

    void currentDebugProjectRemoved();
    void updatePendingPreviewDocuments(QmlJS::Document::Ptr doc);
    void showDebuggerTooltip(const QPoint &mousePos, TextEditor::ITextEditor *editor, int cursorPos);
    void debugQueryUpdated(QDeclarativeDebugQuery::State);

private:
    bool addQuotesForData(const QVariant &value) const;
    void resetViews();

    void initializeDocuments();
    void applyChangesToQmlObserverHelper(bool applyChanges);
    void setupToolbar(bool doConnect);
    void setupDockWidgets();
    QString filenameForShadowBuildFile(const QString &filename) const;

private:
    bool m_listeningToEditorManager;

    QmlInspectorToolbar *m_toolbar;
    ContextCrumblePath *m_crumblePath;
    QmlJSObjectTree *m_objectTreeWidget;

    InspectorSettings *m_settings;
    ClientProxy *m_clientProxy;
    QObject *m_qmlEngine;
    QDeclarativeDebugExpressionQuery *m_debugQuery;
    int m_lastSelectedDebugId;

    // Qml/JS integration
    QHash<QString, QmlJSLiveTextPreview *> m_textPreviews;
    QmlJS::Snapshot m_loadedSnapshot; //the snapshot loaded by the viewer

    // project is needed for matching filenames, esp. with shadow builds.
    ProjectExplorer::Project *m_debugProject;
    QString m_debugProjectBuildDir;

    QStringList m_pendingPreviewDocumentNames;
    Utils::FileInProjectFinder m_projectFinder;

    static InspectorUi *m_instance;
};

} // Internal
} // QmlJSInspector

#endif // QMLJSINSPECTOR_H
