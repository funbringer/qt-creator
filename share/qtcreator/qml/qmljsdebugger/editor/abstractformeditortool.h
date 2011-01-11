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

#ifndef ABSTRACTFORMEDITORTOOL_H
#define ABSTRACTFORMEDITORTOOL_H

#include <qglobal.h>
#include <QList>
#include <QObject>

QT_BEGIN_NAMESPACE
class QMouseEvent;
class QGraphicsItem;
class QDeclarativeItem;
class QKeyEvent;
class QGraphicsScene;
class QGraphicsObject;
class QWheelEvent;
class QDeclarativeView;
QT_END_NAMESPACE

namespace QmlJSDebugger {

class QDeclarativeViewObserver;

class FormEditorView;

class AbstractFormEditorTool : public QObject
{
    Q_OBJECT
public:
    AbstractFormEditorTool(QDeclarativeViewObserver* observer);

    virtual ~AbstractFormEditorTool();

    virtual void mousePressEvent(QMouseEvent *event) = 0;
    virtual void mouseMoveEvent(QMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *event) = 0;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) = 0;

    virtual void hoverMoveEvent(QMouseEvent *event) = 0;
    virtual void wheelEvent(QWheelEvent *event) = 0;

    virtual void keyPressEvent(QKeyEvent *event) = 0;
    virtual void keyReleaseEvent(QKeyEvent *keyEvent) = 0;
    virtual void itemsAboutToRemoved(const QList<QGraphicsItem*> &itemList) = 0;

    virtual void clear() = 0;

    void updateSelectedItems();
    QList<QGraphicsItem*> items() const;

    void enterContext(QGraphicsItem *itemToEnter);

    bool topItemIsMovable(const QList<QGraphicsItem*> &itemList);
    bool topItemIsResizeHandle(const QList<QGraphicsItem*> &itemList);
    bool topSelectedItemIsMovable(const QList<QGraphicsItem*> &itemList);

    static QString titleForItem(QGraphicsItem *item);
    static QList<QGraphicsObject*> toGraphicsObjectList(const QList<QGraphicsItem*> &itemList);
    static QGraphicsItem* topMovableGraphicsItem(const QList<QGraphicsItem*> &itemList);
    static QDeclarativeItem* topMovableDeclarativeItem(const QList<QGraphicsItem*> &itemList);
    static QDeclarativeItem *toQDeclarativeItem(QGraphicsItem *item);

protected:
    virtual void selectedItemsChanged(const QList<QGraphicsItem*> &objectList) = 0;

    QDeclarativeViewObserver *observer() const;
    QDeclarativeView *view() const;
    QGraphicsScene* scene() const;

private:
    QDeclarativeViewObserver *m_observer;
    QList<QGraphicsItem*> m_itemList;
};

}

#endif // ABSTRACTFORMEDITORTOOL_H
