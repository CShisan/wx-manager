#ifndef WECHAT_H
#define WECHAT_H

#include <QObject>

class Wechat : public QObject {
    Q_OBJECT
    public:
    explicit Wechat(QObject * parent = nullptr);
    static void start(int count);

    private:
    static void multiple();
    static QString installPath();
};

#endif // WECHAT_H
