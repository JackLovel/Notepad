#include "editorplain.h"
#include <QtWidgets>

/* CodeEditor s*/
CodeEditor::CodeEditor(QWidget *parent)
    : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect, int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

int CodeEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    /**
     * @anwer: Qt's QFontMetrics::horizontalAdvance() missing for Code Editor Implementation
     * @link: https://stackoverflow.com/questions/50864893/qts-qfontmetricshorizontaladvance-missing-for-code-editor-implementation
     */
    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}


void CodeEditor::updateLineNumberAreaWidth(int /*newBlockCount*/)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}


void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
   if (dy)
        lineNumberArea->scroll(0, dy);
   else
       lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

   if (rect.contains(viewport()->rect()))
       updateLineNumberAreaWidth(0);
}


void CodeEditor::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly())
    {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}


void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom())
    {
        if (block.isVisible() && bottom >= event->rect().top())
        {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}

// ways
void CodeEditor::wheelEvent(QWheelEvent *event)
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

void CodeEditor::copy()
{
    QPlainTextEdit::copy();
}

void CodeEditor::cut()
{
    QPlainTextEdit::cut();
}

void CodeEditor::paste()
{
    QPlainTextEdit::paste();
}

void CodeEditor::undo()
{
    QPlainTextEdit::undo();
}

void CodeEditor::redo()
{
    QPlainTextEdit::redo();
}

void CodeEditor::setText(const QString text)
{
    QPlainTextEdit::setPlainText(text);
}

void CodeEditor::open(const QString fileName)
{

    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QString content = file.readAll();
    setText(content);

    file.close();
}

void CodeEditor::save(const QString fileName)
{
    QString content = this->toPlainText();

    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(content.toUtf8());

    file.close();
}

void CodeEditor::saveAs(const QString fileName)
{
    QString content = this->toPlainText();

    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    file.write(content.toUtf8());
    file.close();
}

/* LineNumberArea */
LineNumberArea::LineNumberArea(CodeEditor *editor)
    : QWidget(editor)
{
    codeEditor = editor;
}

QSize LineNumberArea::sizeHint() const
{
    return QSize(codeEditor->lineNumberAreaWidth(), 0);
}

void LineNumberArea::paintEvent(QPaintEvent *event)
{
    codeEditor->lineNumberAreaPaintEvent(event);
}

/*
 * display current cursor's col and row
 * */
QMap<QString, QString> CodeEditor::showTextRowAndCol()
{
    QMap<QString, QString> lineNumber;

    QTextCursor *textCursor = new QTextCursor(this->textCursor());
    QString row = QString::number(textCursor->blockNumber() + 1);
    QString col = QString::number(textCursor->columnNumber() + 1);

    lineNumber.insert("col", col);
    lineNumber.insert("row", row);

    return lineNumber;
}













