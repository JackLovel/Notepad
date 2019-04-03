/**
  @title can setting notepad some argument
  @author JackLovel
  @link
  */

#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include <QListWidget>
#include <QStackedWidget>
#include <QLabel>

class Setting : public QDialog
{
public:
    Setting(QWidget *parent = 0);
    ~Setting();

private:
    QListWidget *list;
    QStackedWidget *stack;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
};

#endif // SETTING_H
