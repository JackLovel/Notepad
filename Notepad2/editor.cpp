#include <QWheelEvent>
#include <QFontDialog>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QMenu>
#include <QAction>

#include "editor.h"

Editor::Editor(QWidget *parent)
    : QTextEdit(parent)
{

}

Editor::~Editor()
{

}

void Editor::wheelEvent(QWheelEvent *event)
{
        if (event->delta() > 0)
        {
            this->zoomIn();     // enlarge
        }
        else
        {
            this->zoomOut();    // narrow
        }
}

void Editor::copy()
{
    QTextEdit::copy();
}

void Editor::cut()
{
    QTextEdit::cut();
}

void Editor::paste()
{
    QTextEdit::paste();
}

void Editor::undo()
{
    QTextEdit::undo();
}

void Editor::redo()
{
    QTextEdit::redo();
}

void Editor::setFontUnderline()
{
    if (!underLineDone)
    {
        underLineDone = true;
    }
    else
    {
        underLineDone = false;
    }

    QTextEdit::setFontUnderline(underLineDone);
}

void Editor::setFontItalic()
{
    if (!italicDone)
    {
        italicDone = true;
    }
    else
    {
        italicDone = false;
    }

    QTextEdit::setFontItalic(italicDone);
}

void Editor::setFontBold()
{
    if (!boldDone)
    {
        boldDone = true;
    }
    else
    {
        boldDone = false;
    }

    qint32 font = boldDone ? QFont::Bold : QFont::Normal;
    QTextEdit::setFontWeight(font);
}

void Editor::setText(const QString text)
{
    QTextEdit::setText(text);
}

void Editor::open(const QString fileName)
{

    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QString text = file.readAll();
    setText(text);

    file.close();
}

void Editor::save(const QString fileName)
{
    QString content = this->toPlainText();

    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    file.write(content.toUtf8());
    file.close();
}

void Editor::saveAs(const QString fileName)
{
    QString content = this->toPlainText();

    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    file.write(content.toUtf8());
    file.close();
}

void Editor::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = new QMenu;
    QAction *undo = menu->addAction(tr("撤消(&U)"), this, SLOT(undo()), QKeySequence::Undo);
    undo->setEnabled(document()->isUndoAvailable());

    QAction *redo = menu->addAction(tr("恢复(&R)"), this, SLOT(redo()),
                                    QKeySequence::Redo);
    redo->setEnabled(document()->isRedoAvailable());
    menu->addSeparator();

    QAction *cut = menu->addAction(tr("剪切(&T)"), this, SLOT(cut()), QKeySequence::Cut);
    cut->setEnabled(textCursor().hasSelection());


    QAction *copy = menu->addAction(tr("复制(&C)"), this,
                                    SLOT(copy()), QKeySequence::Copy);

    copy->setEnabled(textCursor().hasSelection());

    QAction *clear = menu->addAction(tr("清空"), this, SLOT(clear()));
    clear->setEnabled(!document()->isEmpty());

    QAction *select = menu->addAction(tr("全选"), this, SLOT(selectAll()), QKeySequence::SelectAll);
    select->setEnabled(!document()->isEmpty());

    menu->exec(event->globalPos());
    delete menu;
}

