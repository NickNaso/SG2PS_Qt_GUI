// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#ifdef _WIN32
#include <windows.h>
#include <ShellApi.h>
#include <QString>
#else
#include <QProcess>
#endif

#include "Launcher.hpp"

#ifdef _WIN32

void openWithDefaultApp(const QString& file) {

    ShellExecute(GetDesktopWindow(), L"open", (wchar_t*)file.utf16(), NULL, NULL, SW_SHOWNORMAL);

}

void openDirectoryWithFileManager(const QString& directory) {

    ShellExecute(GetDesktopWindow(), L"explore", (wchar_t*)directory.utf16(), NULL, NULL, SW_SHOWMAXIMIZED);
}

#else

void openWithDefaultApp(const QString& file) {

    QProcess::startDetached("xdg-open "+file);

}

void openDirectoryWithFileManager(const QString& directory) {

    openWithDefaultApp(directory);
}

#endif
