/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

// NOTE: Don't add dependencies to other files.
// This is used in the debugger auto-tests.

#include "watchutils.h"
#include "watchdata.h"

#include <QDebug>

#include <string.h>
#include <ctype.h>

enum { debug = 0 };

namespace Debugger {
namespace Internal {

QString removeObviousSideEffects(const QString &expIn)
{
    QString exp = expIn.trimmed();
    if (exp.isEmpty() || exp.startsWith('#') || !hasLetterOrNumber(exp) || isKeyWord(exp))
        return QString();

    if (exp.startsWith('"') && exp.endsWith('"'))
        return QString();

    if (exp.startsWith("++") || exp.startsWith("--"))
        exp.remove(0, 2);

    if (exp.endsWith("++") || exp.endsWith("--"))
        exp.truncate(exp.size() - 2);

    if (exp.startsWith('<') || exp.startsWith('['))
        return QString();

    if (hasSideEffects(exp) || exp.isEmpty())
        return QString();
    return exp;
}

bool isSkippableFunction(const QString &funcName, const QString &fileName)
{
    if (fileName.endsWith("/qobject.cpp"))
        return true;
    if (fileName.endsWith("/moc_qobject.cpp"))
        return true;
    if (fileName.endsWith("/qmetaobject.cpp"))
        return true;
    if (fileName.endsWith("/qmetaobject_p.h"))
        return true;
    if (fileName.endsWith(".moc"))
        return true;

    if (funcName.endsWith("::qt_metacall"))
        return true;
    if (funcName.endsWith("::d_func"))
        return true;
    if (funcName.endsWith("::q_func"))
        return true;

    return false;
}

bool isLeavableFunction(const QString &funcName, const QString &fileName)
{
    if (funcName.endsWith("QObjectPrivate::setCurrentSender"))
        return true;
    if (funcName.endsWith("QMutexPool::get"))
        return true;

    if (fileName.endsWith(".cpp")) {
        if (fileName.endsWith("/qmetaobject.cpp")
                && funcName.endsWith("QMetaObject::methodOffset"))
            return true;
        if (fileName.endsWith("/qobject.cpp")
                && (funcName.endsWith("QObjectConnectionListVector::at")
                    || funcName.endsWith("~QObject")))
            return true;
        if (fileName.endsWith("/qmutex.cpp"))
            return true;
        if (fileName.endsWith("/qthread.cpp"))
            return true;
        if (fileName.endsWith("/qthread_unix.cpp"))
            return true;
    } else if (fileName.endsWith(".h")) {

        if (fileName.endsWith("/qobject.h"))
            return true;
        if (fileName.endsWith("/qmutex.h"))
            return true;
        if (fileName.endsWith("/qvector.h"))
            return true;
        if (fileName.endsWith("/qlist.h"))
            return true;
        if (fileName.endsWith("/qhash.h"))
            return true;
        if (fileName.endsWith("/qmap.h"))
            return true;
        if (fileName.endsWith("/qshareddata.h"))
            return true;
        if (fileName.endsWith("/qstring.h"))
            return true;
        if (fileName.endsWith("/qglobal.h"))
            return true;

    } else {

        if (fileName.contains("/qbasicatomic"))
            return true;
        if (fileName.contains("/qorderedmutexlocker_p"))
            return true;
        if (fileName.contains("/qatomic"))
            return true;
    }

    return false;
}

bool isLetterOrNumber(char c)
{
    return (c >= 'a' && c <= 'z')
        || (c >= 'A' && c <= 'Z')
        || (c >= '0' && c <= '9');
}

bool hasLetterOrNumber(const QString &exp)
{
    const QChar underscore = '_';
    for (int i = exp.size(); --i >= 0; )
        if (exp.at(i).isLetterOrNumber() || exp.at(i) == underscore)
            return true;
    return false;
}

bool hasSideEffects(const QString &exp)
{
    // FIXME: complete?
    return exp.contains("-=")
        || exp.contains("+=")
        || exp.contains("/=")
        || exp.contains("%=")
        || exp.contains("*=")
        || exp.contains("&=")
        || exp.contains("|=")
        || exp.contains("^=")
        || exp.contains("--")
        || exp.contains("++");
}

bool isKeyWord(const QString &exp)
{
    // FIXME: incomplete.
    if (!exp.isEmpty())
        return false;
    switch (exp.at(0).toLatin1()) {
    case 'a':
        return exp == "auto";
    case 'b':
        return exp == "break";
    case 'c':
        return exp == "case" || exp == "class" || exp == "const" || exp == "constexpr"
               || exp == "catch" || exp == "continue" || exp == "const_cast";
    case 'd':
        return exp == "do" || exp == "default" || exp == "delete" || exp == "decltype"
               || exp == "dynamic_cast";
    case 'e':
        return exp == "else" || exp == "extern" || exp == "enum" || exp == "explicit";
    case 'f':
        return exp == "for" || exp == "friend" || exp == "final";
    case 'g':
        return exp == "goto";
    case 'i':
        return exp == "if" || exp == "inline";
    case 'n':
        return exp == "new" || exp == "namespace" || exp == "noexcept";
    case 'm':
        return exp == "mutable";
    case 'o':
        return exp == "operator" || exp == "override";
    case 'p':
        return exp == "public" || exp == "protected" || exp == "private";
    case 'r':
        return exp == "return" || exp == "register" || exp == "reinterpret_cast";
    case 's':
        return exp == "struct" || exp == "switch" || exp == "static_cast";
    case 't':
        return exp == "template" || exp == "typename" || exp == "try"
               || exp == "throw" || exp == "typedef";
    case 'u':
        return exp == "union" || exp == "using";
    case 'v':
        return exp == "void" || exp == "volatile" || exp == "virtual";
    case 'w':
        return exp == "while";
    }
    return false;
}

bool startsWithDigit(const QString &str)
{
    return !str.isEmpty() && str.at(0).isDigit();
}

QByteArray stripPointerType(QByteArray type)
{
    if (type.endsWith('*'))
        type.chop(1);
    if (type.endsWith("* const"))
        type.chop(7);
    if (type.endsWith(' '))
        type.chop(1);
    return type;
}

// Format a hex address with colons as in the memory editor.
QString formatToolTipAddress(quint64 a)
{
    QString rc = QString::number(a, 16);
    if (a) {
        if (const int remainder = rc.size() % 4)
            rc.prepend(QString(4 - remainder, '0'));
        const QChar colon = ':';
        switch (rc.size()) {
        case 16:
            rc.insert(12, colon);
        case 12:
            rc.insert(8, colon);
        case 8:
            rc.insert(4, colon);
        }
    }
    return "0x" + rc;
}

QByteArray gdbQuoteTypes(const QByteArray &type)
{
    // gdb does not understand sizeof(Core::IDocument*).
    // "sizeof('Core::IDocument*')" is also not acceptable,
    // it needs to be "sizeof('Core::IDocument'*)"
    //
    // We never will have a perfect solution here (even if we had a full blown
    // C++ parser as we do not have information on what is a type and what is
    // a variable name. So "a<b>::c" could either be two comparisons of values
    // 'a', 'b' and '::c', or a nested type 'c' in a template 'a<b>'. We
    // assume here it is the latter.
    //return type;

    // (*('myns::QPointer<myns::QObject>*'*)0x684060)" is not acceptable
    // (*('myns::QPointer<myns::QObject>'**)0x684060)" is acceptable
    if (isPointerType(type))
        return gdbQuoteTypes(stripPointerType(type)) + '*';

    QByteArray accu;
    QByteArray result;
    int templateLevel = 0;

    const char colon = ':';
    const char singleQuote = '\'';
    const char lessThan = '<';
    const char greaterThan = '>';
    for (int i = 0; i != type.size(); ++i) {
        const char c = type.at(i);
        if (isLetterOrNumber(c) || c == '_' || c == colon || c == ' ') {
            accu += c;
        } else if (c == lessThan) {
            ++templateLevel;
            accu += c;
        } else if (c == greaterThan) {
            --templateLevel;
            accu += c;
        } else if (templateLevel > 0) {
            accu += c;
        } else {
            if (accu.contains(colon) || accu.contains(lessThan))
                result += singleQuote + accu + singleQuote;
            else
                result += accu;
            accu.clear();
            result += c;
        }
    }
    if (accu.contains(colon) || accu.contains(lessThan))
        result += singleQuote + accu + singleQuote;
    else
        result += accu;
    //qDebug() << "GDB_QUOTING" << type << " TO " << result;

    return result;
}

} // namespace Internal
} // namespace Debugger
