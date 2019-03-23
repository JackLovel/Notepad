#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QWidget>
#include <QMenu>

class SystemTray : public QMenu
{
    Q_OBJECT

public:
    SystemTray(QWidget *parent = 0);
    ~SystemTray();

signals:
    void showWindow();

private:
    void initActions();   // add menu item

private:
    QAction *m_pShowAction;
    QAction *m_pSettingAction;
    QAction *m_HomePageAction;
    QAction *m_pHelpAction;
    QAction *m_pAboutAction;
    QAction *m_pUpgradeAction;
    QAction *m_pQuitAction;
};

#endif // SYSTEMTRAY_H
