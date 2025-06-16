#include "wechat.h"
#include <QDebug>
#include <QSettings>
#include <QProcess>
#include <Windows.h>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QThread>
#include <aclapi.h>


Wechat::Wechat(QObject * parent) : QObject {parent} {}

// void Wechat::start(int count) {
// Wechat::elevatePrivileges();
// QThread *thread = QThread::create([](int count){
// for (int i = 0; i < count; i++) {
// QProcess *process = new QProcess();
// process->start("starter/starter_anhkgg.exe");
// process->waitForFinished();
// process->deleteLater();
// }
// }, count);
// thread->start();
// }

void Wechat::multiple() {
    LPCWSTR mutexName = L"XWeChat_App_Instance_Identity_Mutex_Name";
    HANDLE hMutex = CreateMutexW(NULL, FALSE, mutexName);

    SID_IDENTIFIER_AUTHORITY SIDAuthWorld = SECURITY_WORLD_SID_AUTHORITY;
    PSID pEveryoneSID = NULL;
    char szBuffer[4096] = { 0 };
    PACL pAcl = (PACL)szBuffer;

    AllocateAndInitializeSid( & SIDAuthWorld, 1, SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0, & pEveryoneSID);
    InitializeAcl(pAcl, sizeof(szBuffer), ACL_REVISION);
    AddAccessDeniedAce(pAcl, ACL_REVISION, MUTEX_ALL_ACCESS, pEveryoneSID);
    SetSecurityInfo(hMutex, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, pAcl, NULL);
}

QString Wechat::installPath() {
    QString regPath = "HKEY_CURRENT_USER\\Software\\Tencent\\Weixin";
    QSettings settings(regPath, QSettings::NativeFormat);
    return settings.value("InstallPath").toString();
}

void Wechat::start(int count) {
    // 获取安装路径
    QString installPath = Wechat::installPath();
    if (installPath == nullptr || installPath.isEmpty()) {
        return;
    }

    // 屏蔽互斥锁
    multiple();

    // 启动
    QThread * thread = QThread::create([installPath](int count) {
        QString path = installPath + "\\Weixin.exe";
        for (int i = 0; i < count; i++) {
            QProcess::startDetached(path);
            // QDesktopServices::openUrl(QUrl("file:///" + path));
        }
    }, count);
    thread->start();
}


