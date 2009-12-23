/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Creator.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
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
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "maemosshrunner.h"

#ifdef USE_SSH_LIB

namespace Qt4ProjectManager {
namespace Internal {

MaemoSshRunner::MaemoSshRunner(const MaemoDeviceConfig &devConf, const QString &command)
    : m_devConf(devConf), m_command(command)
{
}

void MaemoSshRunner::run()
{
    try {
        m_connection = MaemoSshConnection::connect(m_devConf, true);
        emit connectionEstablished();
        connect(m_connection.data(), SIGNAL(remoteOutput(QString)),
                this, SIGNAL(remoteOutput(QString)));
        m_connection->runCommand(m_command);
    } catch (const MaemoSshException &e) {
        m_error = e.error();
    }
}

void MaemoSshRunner::stop()
{
    if (!m_connection.isNull())
        m_connection->stopCommand();
    wait();
}

} // namespace Internal
} // namespace Qt4ProjectManager

#endif
