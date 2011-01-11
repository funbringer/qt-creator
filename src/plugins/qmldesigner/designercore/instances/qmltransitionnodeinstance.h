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

#ifndef QMLTRANSITIONNODEINSTANCE_H
#define QMLTRANSITIONNODEINSTANCE_H

#include "objectnodeinstance.h"

QT_BEGIN_NAMESPACE
class QDeclarativeTransition;
QT_END_NAMESPACE

namespace QmlDesigner {
namespace Internal {

class QmlTransitionNodeInstance : public ObjectNodeInstance
{
public:
    typedef QSharedPointer<QmlTransitionNodeInstance> Pointer;
    typedef QWeakPointer<QmlTransitionNodeInstance> WeakPointer;

    static Pointer create(QObject *objectToBeWrapped);

    void setPropertyVariant(const QString &name, const QVariant &value);

    bool isTransition() const;

protected:
    QDeclarativeTransition *qmlTransition() const;

private:
    QmlTransitionNodeInstance(QDeclarativeTransition *transition);
};
}
}
#endif // QMLTRANSITIONNODEINSTANCE_H
