#ifndef EDITORPLAIN_H
#define EDITORPLAIN_H

#include <QPlainTextEdit>
#include <QObject>
#include <QPaintEvent>
#include <QSize>
#include <QWidget>
#include <QtWidgets>

class LineNumberArea;

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEditor(QWidget *parent = 0);
    friend class Notepad;

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

public slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

    QMap<QString, QString> showTextRowAndCol();
private:
    QWidget *lineNumberArea;

    void copy();
    void cut();
    void paste();
    void undo();
    void redo();
    void setText(const QString text);
    void open(const QString fileName);
    void save(const QString fileName);
    void saveAs(const QString fileName);
};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(CodeEditor *editor);
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    CodeEditor *codeEditor;
};

#endif // EDITORPLAIN_H














