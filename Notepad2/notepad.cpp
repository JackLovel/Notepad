#include "notepad.h"
#include "setting.h"
#include <iostream>

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <qtprintsupportglobal.h>
#include <QPrintDialog>
#include <QPrinter>
#include <QFont>
#include <QFontDialog>
#include <QAction>
#include <QTextEdit>
#include <QCoreApplication>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QWheelEvent>

#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>

#include <QDebug>
#include "utils.h"
#include <QStatusBar>

Notepad::Notepad(QWidget *parent) :
    QMainWindow(parent)
{
    textEdit = new Editor(this);

    readSettings();
    initStatusBar();

    // auto save feature
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Notepad::writeSetting);
    timer->start(1000); // 1s


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


    //QAction *newAct = new QAction(newPix, "&New", this);
    newAct = new QAction(newPix, "&New", this);

    QAction *openAct = new QAction(openPix, "&Open", this);
    QAction *saveAct = new QAction(savePix, "&Save", this);
    QAction *saveAsAct = new QAction(saveAsPix, "&SaveAs", this);
    QAction *printAct = new QAction(printPix, "&Print", this);
    QAction *exitAct = new QAction(exitPix, "&Exit", this);
    QAction *copyAct = new QAction(copyPix, "&Copy", this);
    QAction *cutAct = new QAction(cutPix, "&Cut", this);
    QAction *pasteAct = new QAction(pastePix, "&Paste", this);
    QAction *undoAct = new QAction(undoPix, "&Undo", this);
    QAction *redoAct = new QAction(redoPix, "&Redo", this);
    QAction *fontAct = new QAction(fontPix, "&Font", this);
    QAction *boldAct = new QAction(fontBoldPix, "&Bold", this);
    QAction *underlineAct = new QAction(underlinePix, "&Underline", this);
    QAction *fontItalicAct = new QAction(italicPix, "&FontItalic", this);
    QAction *aboutAct = new QAction(aboutPix, "&about", this);

    QAction *settingAct = new QAction("setting", this);

    newAct->setShortcut(Utils::readJson(this, "menu", "newFile"));
    openAct->setShortcut(Utils::readJson(this, "menu", "openFile"));
    saveAct->setShortcut(Utils::readJson(this, "menu", "saveFile"));
    saveAsAct->setShortcut(Utils::readJson(this, "menu", "saveAsFile"));
    exitAct->setShortcut(Utils::readJson(this, "menu", "exit"));
    copyAct->setShortcut(Utils::readJson(this, "menu", "copy"));
    cutAct->setShortcut(Utils::readJson(this, "menu", "cut"));
    pasteAct->setShortcut(Utils::readJson(this, "menu", "paste"));
    undoAct->setShortcut(Utils::readJson(this, "menu", "undo"));
    redoAct->setShortcut(Utils::readJson(this, "menu", "redo"));
    fontAct->setShortcut(Utils::readJson(this, "menu", "font"));
    redoAct->setShortcut(Utils::readJson(this, "menu", "redo"));

    //printAct->setShortcut(Utils::readJson(this, "menu", "print"));
    //fontAct->setShortcut(QKeySequence("Ctrl+O"));
    //boldAct->setShortcut(QKeySequence("Ctrl+N"));
    //underlineAct->setShortcut(QKeySequence("Ctrl+O"));
    //fontItalicAct->setShortcut(QKeySequence("Ctrl+N"));
    //aboutAct->setShortcut(QKeySequence("Ctrl+O"));



    QMenu *fileMenu = menuBar()->addMenu(tr("&file"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
    fileMenu->addAction(settingAct);

    QMenu *editMenu = menuBar()->addMenu(tr("&edit"));
    editMenu->addAction(copyAct);
    editMenu->addAction(cutAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();
    editMenu->addAction(undoAct);
    fileMenu->addAction(redoAct);
    editMenu->addAction(fontAct);

    QToolBar *toolbar = addToolBar(tr("main toolbar"));
    toolbar->addAction(newAct);
    toolbar->addAction(openAct);
    toolbar->addAction(saveAct);
    toolbar->addAction(saveAsAct);
    toolbar->addAction(printAct);
    toolbar->addSeparator();
    toolbar->addAction(copyAct);
    toolbar->addAction(cutAct);
    toolbar->addAction(pasteAct);
    toolbar->addAction(undoAct);
    toolbar->addAction(redoAct);
    toolbar->addAction(fontAct);
    toolbar->addSeparator();
    toolbar->addAction(exitAct);
    toolbar->addAction(boldAct);
    toolbar->addAction(underlineAct);
    toolbar->addAction(fontItalicAct);
    toolbar->addSeparator();
    toolbar->addAction(aboutAct);


    connect(newAct, &QAction::triggered, this, &Notepad::newDocument);
    connect(openAct, &QAction::triggered, this, &Notepad::open);
    connect(saveAct, &QAction::triggered, this, &Notepad::save);
    connect(saveAsAct, &QAction::triggered, this, &Notepad::saveAs);
    connect(printAct, &QAction::triggered, this, &Notepad::print);
    connect(exitAct, &QAction::triggered, this, &Notepad::exit);

    connect(copyAct, &QAction::triggered, textEdit, &Editor::copy);
    connect(cutAct, &QAction::triggered, textEdit, &Editor::cut);
    connect(pasteAct, &QAction::triggered, textEdit, &Editor::paste);
    connect(undoAct, &QAction::triggered, textEdit, &Editor::undo);
    connect(redoAct, &QAction::triggered, textEdit, &Editor::redo);
    connect(fontAct, &QAction::triggered, this, &Notepad::selectFont);
    connect(boldAct, &QAction::triggered, textEdit, &Editor::setFontBold);
    connect(underlineAct, &QAction::triggered, textEdit, &Editor::setFontUnderline);
    connect(fontItalicAct, &QAction::triggered, textEdit, &Editor::setFontItalic);
    connect(aboutAct, &QAction::triggered, this, &Notepad::about);
    connect(settingAct, &QAction::triggered, this, &Notepad::settingDialog);

    connect(textEdit, &Editor::cursorPositionChanged, this, &Notepad::showStausLineNumber);

    QPixmap windowIcon(":/img/window.png");
    setWindowIcon(windowIcon);


    setCentralWidget(textEdit);
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


Notepad::~Notepad()
{

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

void Notepad::writeSetting()
{
    QSettings settings("JackLovel", "myNotepad");

    settings.setValue("pos", this->pos());
    settings.setValue("size", this->size());
}

void Notepad::readSettings()
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
    m_secondStatusLabel = new QLabel(tr("测试标签"));

    this->statusBar()->addWidget(m_secondStatusLabel, 1);
    this->statusBar()->addWidget(lineNumberLabel, 3);


    m_secondStatusLabel->setAlignment(Qt::AlignCenter);
}

void Notepad::showStausLineNumber()
{

    QMap<QString, QString> lineNumber = textEdit->showTextRowAndCol();

//    QString row = lineNumber["row"];
//    QString col = lineNumber["col"];

    QString row = lineNumber.value("row");
    QString col = lineNumber.value("col");

    qDebug() << "row: " << row
             << "col: " << col;

    lineNumberLabel->setText(QString("第%1行,第%2列").arg(row, col));
    this->statusBar()->addWidget(lineNumberLabel);
    lineNumberLabel->setAlignment(Qt::AlignLeft);
}
