#ifndef WXMMENUBAR_H
#define WXMMENUBAR_H

#include <QMenuBar>

class WxmMenuBar : public QMenuBar {
public:
    explicit WxmMenuBar(QWidget *parent = nullptr);

};

class CustomQMenu : public QMenu {
public:
    explicit CustomQMenu(const QString &title, QWidget *parent = nullptr);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
};

#endif // WXMMENUBAR_H
