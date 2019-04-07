#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QtWidgets>

#include "editorplain.h"
#include "finddialog.h"
#include "replacedialog.h"

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad(QWidget *parent = NULL);
    ~Notepad();

private slots:
    void newDocument();
    void open();
    void save();
    void saveAs();
    void print();
    void exit();
    void selectFont();

    void about();
    void loadUserSetting();
    void storeUserSetting();

    void showStatusLineNumber();
    void findDialog();
    void findText(QString value, bool isChecked, bool isUp);

    void openReplaceDialog();  // open replace dialog
    void findForReplaceSlot(QString, bool);
    void doReplaceSlot(QString, QString, bool, bool);
    void replace(QString, bool);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    CodeEditor *textEdit;
    QString currentFile;
    //bool readFile(const QString &fileName);

    /* statusBar
     * */
    QLabel *lineNumberLabel;
    QLabel *m_secondStatusLabel;
    QTimer *timer;
    QSystemTrayIcon *m_trayIcon;

    void createUI();
    void createMenus();
    void createToolBars();
    void initStatusBar();  // mark
    void settingDialog();
    void createConnect();
    void initTray();
    void showMessage(QString title);

    // action
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *printAction;
    QAction *exitAction;
    QAction *copyAction;
    QAction *cutAction;
    QAction *pasteAction;
    QAction *undoAction;
    QAction *redoAction;
    QAction *fontAction;
    QAction *boldAction;
    QAction *underlineAction;
    QAction *fontItalicAction;
    QAction *aboutAction;
    QAction *settingAction;
    QAction *findAction;
    QAction *replaceAction;

    const int storeInterval = 1000; // 1s
    const QString AppName = "Notpad2";
    const QString WelecomeInfo = "Welecome to Notpad2!";
    const QString WelecomeUrl = tr("欢迎登陆%1");

    bool isFirstFind;

    // find dialog
    FindDialog  *m_findDialog;
    ReplaceDialog *replaceDialog;
};

#endif // WIDGET_H
