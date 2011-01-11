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

#ifndef BINPATCH_H
#define BINPATCH_H

#include <string.h>

typedef unsigned long ulong;
typedef unsigned int uint;

class BinPatch
{
public:
    BinPatch(const char *file)
        : useLength(false), insertReplace(false)
    {
        strcpy(endTokens, "");
        strcpy(fileName, file);
    }

    void enableUseLength(bool enabled)
    { useLength = enabled; }
    void enableInsertReplace(bool enabled)
    { insertReplace = enabled; }
    void setEndTokens(const char *tokens)
    { strcpy(endTokens, tokens); }

    bool patch(const char *oldstr, const char *newstr);

private:
    long getBufferStringLength(char *data, char *end);
    bool endsWithTokens(const char *data);

    bool patchHelper(char *inbuffer, const char *oldstr,
        const char *newstr, size_t len, long *rw);

    bool useLength;
    bool insertReplace;
    char endTokens[1024];
    char fileName[1024];
};

#endif
