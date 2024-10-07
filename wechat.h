#ifndef WECHAT_H
#define WECHAT_H

class Wechat
{
public:
    Wechat();
    static void start(int count);

protected:
    static bool elevatePrivileges();
};

#endif // WECHAT_H
