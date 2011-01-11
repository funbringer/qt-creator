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

#ifndef S60DEBUGGERBLUETOOTHSTARTER_H
#define S60DEBUGGERBLUETOOTHSTARTER_H

#include "communicationstarter.h"
#include "bluetoothlistener_gui.h"

namespace Debugger {
namespace Internal {

/* S60DebuggerBluetoothStarter: Creates a listener in 'Listen' mode
 * parented on the Debugger manager which outputs to the debugger window.
 * Note: This is a "last resort" starter, normally, the run configuration
 * should have already started a listener.
 * Provides a static convenience to prompt for both connection types.  */

class S60DebuggerBluetoothStarter : public trk::AbstractBluetoothStarter
{
public:
    static trk::PromptStartCommunicationResult
        startCommunication(const TrkDevicePtr &trkDevice,
                           QWidget *msgBoxParent,
                           QString *errorMessage);

protected:
    virtual trk::BluetoothListener *createListener();

private:
    explicit S60DebuggerBluetoothStarter(const TrkDevicePtr& trkDevice, QObject *parent = 0);
};

} // namespace Internal
} // namespace Debugger

#endif // S60DEBUGGERBLUETOOTHSTARTER_H
