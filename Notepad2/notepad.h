#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QSettings>
#include <QCloseEvent>
#include <QContextMenuEvent>
#include <QLabel>

#include "editor.h"



class Notepad : public QMainWindow
{
public:
    Notepad(QWidget *parent = 0);
    ~Notepad();
    void readSettings();
    void writeSetting();

    QAction *newAct;

private slots:
    void newDocument();
    void open();
    void save();
    void saveAs();
    void print();
    void exit();
    void selectFont();
    void setFontBold();
    void setFontUnderline();
    void setFontItalic();
    void about();

    void showStausLineNumber();
    void initStatusBar();
private:
    void createActions();
    void createMenus();
    void createToolBars();

    QString currentFile;           // current file name, default is empty
    Editor *textEdit;           // content area
    QLabel *lineNumberLabel;
    QLabel *m_secondStatusLabel;

    bool boldDone = false;         // default font is not bold
    bool italicDone = false;       // default font is not italic
    bool underLineDone = false;    // default font is not underline

    void settingDialog();
};

#endif // WIDGET_H
