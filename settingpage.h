#ifndef SETTINGPAGE_H
#define SETTINGPAGE_H

#include "globalconfig.h"

#include <QWidget>
#include <QFile>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>
#include <QTableWidget>

class ShortcutPage : public QWidget
{
public:
    ShortcutPage(QWidget *parent = 0);
    ~ShortcutPage();

private slots:

private:
    QGroupBox *shortCutGroupBox;
    QTableWidget *shortCutTable;
    QPushButton *editButton;
    QPushButton *recoverDefaultButton;

    void setTableWidgetSytle();

    QTableWidgetItem *settingItem;
    QTableWidgetItem *settingShortCut;
    QTableWidgetItem *saveItem;
    QTableWidgetItem *saveShortCut;
    QTableWidgetItem *saveAsItem;
    QTableWidgetItem *saveAsShortCut;
};

#endif // SETTINGPAGE_H
