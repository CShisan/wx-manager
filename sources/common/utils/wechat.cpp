#include "wechat.h"
#include <QDebug>
#include <QSettings>
#include <QProcess>
#include <Windows.h>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QThread>


Wechat::Wechat(QObject *parent) : QObject{parent} {
}


//启动微信
void Wechat::start(int count) {
    Wechat::elevatePrivileges();
    QThread *thread = QThread::create([](int count){
        for (int i = 0; i < count; i++) {
            QProcess *process = new QProcess();
            process->start("starter/starter_anhkgg.exe");
            process->waitForFinished();
            process->deleteLater();
        }
    }, count);
    thread->start();
}

//权限提升
bool Wechat::elevatePrivileges() {
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;

    // 打开当前进程的访问令牌
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        qWarning() << "Failed to open process token.";
        return false;
    }

    tkp.PrivilegeCount = 1;

    // 查找 SE_DEBUG_NAME 权限
    if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tkp.Privileges[0].Luid)) {
        qWarning() << "Failed to look up privilege value.";
        CloseHandle(hToken); // 确保关闭句柄
        return false;
    }

    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    // 调整令牌的权限
    if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(TOKEN_PRIVILEGES), NULL, NULL)) {
        qWarning() << "Failed to adjust token privileges.";
        CloseHandle(hToken); // 确保关闭句柄
        return false;
    }

    CloseHandle(hToken); // 确保关闭句柄
    return true;
}


