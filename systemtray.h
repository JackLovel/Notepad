/*
 * @file: system tray
 * */

#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QWidget>
#include <QMenu>
#include <QSystemTrayIcon>

class SystemTray : public QSystemTrayIcon
{
    Q_OBJECT

public:
    SystemTray(QWidget *parent);
    ~SystemTray();

private:
    QWidget *widget;
    void initSysTemTray();
    void addSysTrayMenu();
};

#endif // SYSTEMTRAY_H
