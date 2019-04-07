#include "notepad.h"
#include "setting.h"

#include <qtprintsupportglobal.h>
#include <QPrintDialog>
#include <QPrinter>
#include <QFontDialog>
#include <QIODevice>
#include <QTextCursor>
#include <QDebug>

#include "utils.h"

Notepad::Notepad(QWidget *parent) :
    QMainWindow(parent)
{
    createUI();
    createMenus();
    createToolBars();
    createConnect();
}

Notepad::~Notepad()
{

}

void Notepad::newDocument()
{
    currentFile.clear();
    textEdit->setText(QString());
}

void Notepad::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "open file");
    currentFile = fileName;
    textEdit->open(fileName);
}

void Notepad::createUI()
{
    isFirstFind = true;//是否第一次搜索 替换时用
    /*
     * 加载用户之前状态：比如 窗口大小、窗口位置
     **/
    loadUserSetting();

    QPixmap newPix(":/img/new.png");
    QPixmap openPix(":/img/open.png");
    QPixmap savePix(":/img/save.png");
    QPixmap saveAsPix(":/img/save_as.png");
    QPixmap printPix(":/img/print.png");
    QPixmap copyPix(":/img/copy.png");
    QPixmap cutPix(":/img/cut.png");
    QPixmap pastePix(":/img/paste.png");
    QPixmap redoPix(":/img/edit_redo.png");
    QPixmap undoPix(":/img/edit_undo.png");
    QPixmap fontPix(":/img/font.png");
    QPixmap exitPix(":/img/exit.png");
    QPixmap fontBoldPix(":/img/bold.png");
    QPixmap underlinePix(":/img/underline.png");
    QPixmap italicPix(":/img/italic.png");
    QPixmap aboutPix(":/img/about.png");

    newAction = new QAction(newPix, "&New", this);
    openAction = new QAction(openPix, "&Open", this);
    saveAction = new QAction(savePix, "&Save", this);
    saveAsAction = new QAction(saveAsPix, "&SaveAs", this);
    printAction = new QAction(printPix, "&Print", this);
    exitAction = new QAction(exitPix, "&Exit", this);
    copyAction = new QAction(copyPix, "&Copy", this);
    cutAction = new QAction(cutPix, "&Cut", this);
    pasteAction = new QAction(pastePix, "&Paste", this);
    undoAction = new QAction(undoPix, "&Undo", this);
    redoAction = new QAction(redoPix, "&Redo", this);
    fontAction = new QAction(fontPix, "&Font", this);
    boldAction = new QAction(fontBoldPix, "&Bold", this);
    underlineAction = new QAction(underlinePix, "&Underline", this);
    fontItalicAction = new QAction(italicPix, "&FontItalic", this);
    aboutAction = new QAction(aboutPix, "&about", this);

    settingAction = new QAction("setting", this);

    findAction = new QAction("find", this);
    replaceAction = new QAction("replace", this);

    newAction->setShortcut(Utils::readJson(this, "menu", "newFile"));
    openAction->setShortcut(Utils::readJson(this, "menu", "openFile"));
    saveAction->setShortcut(Utils::readJson(this, "menu", "saveFile"));
    saveAsAction->setShortcut(Utils::readJson(this, "menu", "saveAsFile"));
    exitAction->setShortcut(Utils::readJson(this, "menu", "exit"));
    copyAction->setShortcut(Utils::readJson(this, "menu", "copy"));
    cutAction->setShortcut(Utils::readJson(this, "menu", "cut"));
    pasteAction->setShortcut(Utils::readJson(this, "menu", "paste"));
    undoAction->setShortcut(Utils::readJson(this, "menu", "undo"));
    redoAction->setShortcut(Utils::readJson(this, "menu", "redo"));
    fontAction->setShortcut(Utils::readJson(this, "menu", "font"));
    redoAction->setShortcut(Utils::readJson(this, "menu", "redo"));

    timer = new QTimer(this);
    timer->start(storeInterval);

    /* 编辑器内容区域
      **/
    textEdit = new CodeEditor(this);
    setCentralWidget(textEdit);
    setWindowIcon(QPixmap(":/img/window.png"));

    /*
     * 底部状态栏
     * */
    initStatusBar();

    /*
     * 系统托盘
     * */
    initTray();

    /*
     * findDialog
     * */
     m_findDialog = new FindDialog(this);

    /*
     * drag file
     * */
     textEdit->setAcceptDrops(false);
     setAcceptDrops(true);

     /*
      * replace dialog
      * */
     bool isFindFind = false;
     replaceDialog = new ReplaceDialog(this);

}

void Notepad::createMenus()
{
    // system tray menu
    // menu
    QMenu *m_trayMenu = new QMenu(this);
    m_trayMenu->addAction(exitAction);
    m_trayMenu->addAction(copyAction);
    m_trayMenu->addSeparator();
    m_trayMenu->addAction(openAction);
    m_trayMenu->addAction(aboutAction);
    m_trayIcon->setContextMenu(m_trayMenu); // system tray add menu
    m_trayIcon->show();

    QMenu *fileMenu = menuBar()->addMenu(tr("&file"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(printAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    fileMenu->addAction(settingAction);
    fileMenu->addAction(findAction);
    fileMenu->addAction(replaceAction);

    QMenu *editMenu = menuBar()->addMenu(tr("&edit"));
    editMenu->addAction(copyAction);
    editMenu->addAction(cutAction);
    editMenu->addAction(pasteAction);
    editMenu->addSeparator();
    editMenu->addAction(undoAction);
    fileMenu->addAction(redoAction);
    editMenu->addAction(fontAction);
}

void Notepad::createToolBars()
{
    QToolBar *toolbar = addToolBar(tr("main toolbar"));
    toolbar->addAction(newAction);
    toolbar->addAction(openAction);
    toolbar->addAction(saveAction);
    toolbar->addAction(saveAsAction);
    toolbar->addAction(printAction);
    toolbar->addSeparator();
    toolbar->addAction(copyAction);
    toolbar->addAction(cutAction);
    toolbar->addAction(pasteAction);
    toolbar->addAction(undoAction);
    toolbar->addAction(redoAction);
    toolbar->addAction(fontAction);
    toolbar->addSeparator();
    toolbar->addAction(exitAction);
    toolbar->addSeparator();
    toolbar->addAction(aboutAction);
}

void Notepad::createConnect()
{
    connect(newAction, &QAction::triggered, this, &Notepad::newDocument);
    connect(openAction, &QAction::triggered, this, &Notepad::open);
    connect(saveAction, &QAction::triggered, this, &Notepad::save);
    connect(saveAsAction, &QAction::triggered, this, &Notepad::saveAs);
    connect(printAction, &QAction::triggered, this, &Notepad::print);
    connect(exitAction, &QAction::triggered, this, &Notepad::exit);

    connect(copyAction, &QAction::triggered, textEdit, &CodeEditor::copy);
    connect(cutAction, &QAction::triggered, textEdit, &CodeEditor::cut);
    connect(pasteAction, &QAction::triggered, textEdit, &CodeEditor::paste);
    connect(undoAction, &QAction::triggered, textEdit, &CodeEditor::undo);
    connect(redoAction, &QAction::triggered, textEdit, &CodeEditor::redo);
    connect(fontAction, &QAction::triggered, this, &Notepad::selectFont);
    connect(aboutAction, &QAction::triggered, this, &Notepad::about);
    connect(settingAction, &QAction::triggered, this, &Notepad::settingDialog);
    connect(textEdit, &CodeEditor::cursorPositionChanged, this, &Notepad::showStatusLineNumber);
    connect(timer, &QTimer::timeout, this, &Notepad::storeUserSetting);

    connect(findAction, &QAction::triggered, this, &Notepad::findDialog);

    // findDialog
    connect(m_findDialog, SIGNAL(find(QString, bool, bool)), this, SLOT(findText(QString, bool, bool)));

    // replace
    connect(replaceAction, &QAction::triggered, this, &Notepad::openReplaceDialog);
    connect(replaceDialog, SIGNAL(find(QString, bool)), this, SLOT(findForReplaceSlot(QString, bool)));
    connect(replaceDialog, SIGNAL(replace(QString,QString,bool,bool)), this, SLOT(doReplaceSlot(QString, QString, bool, bool)));
}

void Notepad::save()
{
    QString fileName;
    if (currentFile.isEmpty())
    {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        currentFile = fileName;
    }
    else
    {
        fileName = currentFile;
    }


    textEdit->save(fileName);
    setWindowTitle(fileName);
}

void Notepad::saveAs()
{
    QString fileName = QFileDialog
            ::getSaveFileName(this, "Save as");

    setWindowTitle(fileName);

    textEdit->saveAs(fileName);
}

void Notepad::print()
{
    QPrinter printDev;
    QPrintDialog dialog(&printDev, this);
    if (dialog.exec() == QDialog::Rejected)
    {
        return;
    }
    textEdit->print(&printDev);
}

void Notepad::exit()
{
    QCoreApplication::quit();
}

void Notepad::selectFont()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if (fontSelected)
        textEdit->setFont(font);
}

void Notepad::about()
{
    QMessageBox::about(this, tr("About Notepad"),
                       tr("The <b>Notepad</b> example demonstrace  how to code a basic"
                          "text editor using QtWidgets"));
}

void Notepad::settingDialog()
{
    Setting dialog;
    dialog.exec();
}

void Notepad::storeUserSetting()
{
    QSettings settings("JackLovel", "myNotepad");

    settings.setValue("pos", this->pos());  // save current  postion
    settings.setValue("size", this->size()); // save current windows size
}

void Notepad::loadUserSetting()
{
    QSettings settings("JackLovel", "myNotepad");

    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();

    this->move(pos);
    this->resize(size);
}

void Notepad::initStatusBar()
{
    lineNumberLabel = new QLabel();
    m_secondStatusLabel = new QLabel(tr("test label"));

    this->statusBar()->addWidget(lineNumberLabel, 1);
    this->statusBar()->addWidget(m_secondStatusLabel, 3);

    m_secondStatusLabel->setAlignment(Qt::AlignCenter);
}

void Notepad::showStatusLineNumber()
{

    QMap<QString, QString> lineNumber = textEdit->showTextRowAndCol();

    QString row = lineNumber.value("row");
    QString col = lineNumber.value("col");
    lineNumberLabel->setText(QString("第%1行,第%2列").arg(row, col));

    this->statusBar()->addWidget(lineNumberLabel);
    lineNumberLabel->setAlignment(Qt::AlignLeft);
}

void Notepad::initTray()
{
    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->show();
    m_trayIcon->showMessage(AppName, WelecomeUrl);
    m_trayIcon->setToolTip(AppName);
}

void Notepad::findDialog()
{
    // findDialog
    textEdit->moveCursor(QTextCursor::Start);
    m_findDialog->exec();
}

void Notepad::showMessage(QString title)
{
    QMessageBox box(QMessageBox::Question,"记事本 - 查找",title);
    box.setIcon(QMessageBox::NoIcon);
    box.setStandardButtons (QMessageBox::Ok);
    box.setButtonText (QMessageBox::Ok,QString("确定"));
    box.setWindowFlags( Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint );
    box.exec();
}

void Notepad::findText(QString value, bool isChecked, bool isUp)
{
    if (isUp)
    {
        if (!isChecked)
        {
            if (!textEdit->find(value, QTextDocument::FindBackward))
            {
                showMessage("找不到\""+value+"\"");
            }
        } else {
            if (!textEdit->find(value, QTextDocument::FindBackward | QTextDocument::FindCaseSensitively))
            {
                showMessage("找不到\""+value+"\"");
            }
        }
    } else {
        if (!isChecked)
        {
            if (!textEdit->find(value)) {
                showMessage("找不到\""+value+"\"");
            }
        } else {
            if (!textEdit->find(value, QTextDocument::FindCaseSensitively))
            {
                showMessage("找不到\""+value+"\"");
            }
        }

    }

    QPalette palette = textEdit->palette();
    palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
    textEdit->setPalette(palette);
}

void Notepad::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list")) {
        event->acceptProposedAction();
    }
}

void Notepad::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) {
        return;
    }

    QString fileName = urls.first().toLocalFile();
    if (fileName.isEmpty()) {
        return;
    }

    textEdit->open(fileName);
}

void Notepad::openReplaceDialog()
{
    replaceDialog->exec();
}

void Notepad::findForReplaceSlot(QString value, bool isChecked)
{
    if (isFirstFind) {
        textEdit->moveCursor(QTextCursor::Start);
        isFirstFind = false;
    }

    this->findText(value, isChecked, false);
}

void Notepad::replace(QString value, bool checkDone)
{
    QTextCursor cursor = textEdit->textCursor();
    // replace single word
    cursor.insertText(value);
    // Move the cursor to the previous position
    textEdit->moveCursor(cursor.PreviousCharacter);
    //是否区别大小写，查找替换后的值光亮
    if (!checkDone)
    {
        textEdit->find(value);
    } else {
        textEdit->find(value, QTextDocument::FindCaseSensitively);
    }
}

void Notepad::doReplaceSlot(QString target, QString value, bool checkedDone,  bool replaceAllDone)
{
    if (isFirstFind) {
        textEdit->moveCursor(QTextCursor::Start);
        isFirstFind = false;
    }

    if (!checkedDone){
      if (!textEdit->find(target)) {
          showMessage("找不到\"" + target + "\"");
          return;
      }
    } else {
        if (!textEdit->find(target, QTextDocument::FindCaseSensitively)) {
           showMessage("找不到\"" + target + "\"");
           return;
        }
    }

    // 高亮选中
    QPalette palette = textEdit->palette();
    palette.setColor(QPalette::Highlight, palette.color(QPalette::Active, QPalette::Highlight));
    textEdit->setPalette(palette);

    // 替换
    if (replaceAllDone) {
        if (!textEdit->textCursor().atEnd()) {
            replace(value, checkedDone);
            doReplaceSlot(target, value, checkedDone, replaceAllDone);
        }
    } else {
        replace(value, checkedDone);
    }
}
