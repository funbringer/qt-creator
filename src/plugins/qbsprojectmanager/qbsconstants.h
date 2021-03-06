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

#pragma once

namespace QbsProjectManager {
namespace Constants {

// Toolchain related settings:
const char QBS_TARGETOS[] = "qbs.targetOS";
const char QBS_SYSROOT[] = "qbs.sysroot";
const char QBS_ARCHITECTURE[] = "qbs.architecture";
const char QBS_TOOLCHAIN[] = "qbs.toolchain";
const char CPP_TOOLCHAINPATH[] = "cpp.toolchainInstallPath";
const char CPP_TOOLCHAINPREFIX[] = "cpp.toolchainPrefix";
const char CPP_COMPILERNAME[] = "cpp.compilerName";
const char CPP_CXXCOMPILERNAME[] = "cpp.cxxCompilerName";
const char CPP_COMPILERVERSIONMAJOR[] = "cpp.compilerVersionMajor";
const char CPP_COMPILERVERSIONMINOR[] = "cpp.compilerVersionMinor";
const char CPP_COMPILERVERSIONPATCH[] = "cpp.compilerVersionPatch";
const char CPP_LINKERNAME[] = "cpp.linkerName";
const char CPP_PLATFORMCFLAGS[] = "cpp.platformCFlags";
const char CPP_PLATFORMCXXFLAGS[] = "cpp.platformCxxFlags";
const char CPP_PLATFORMCOMMONCOMPILERFLAGS[] = "cpp.platformCommonCompilerFlags";
const char CPP_PLATFORMLINKERFLAGS[] = "cpp.platformLinkerFlags";
const char CPP_PLATFORMPATH[] = "cpp.platformPath";
const char CPP_XCODESDKNAME[] = "cpp.xcodeSdkName";
const char CPP_XCODESDKVERSION[] = "cpp.xcodeSdkVersion";

// Settings page
const char QBS_SETTINGS_CATEGORY[]  = "YM.qbs";
const char QBS_SETTINGS_TR_CATEGORY[] = QT_TRANSLATE_NOOP("QbsProjectManager", "Qbs");
const char QBS_SETTINGS_CATEGORY_ICON[]  = ":/projectexplorer/images/build.png";

const char QBS_PROPERTIES_KEY_FOR_KITS[] = "QbsProjectManager.qbs-properties";

} // namespace Constants
} // namespace QbsProjectManager
