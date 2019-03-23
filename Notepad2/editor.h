#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QTextEdit>

class Editor : public QTextEdit
{
    Q_OBJECT

public:
    Editor(QWidget *parent = 0);
    ~Editor();

    void setText(const QString text);
    void setFontUnderline();
    void setFontItalic();
    void setFontBold();

    void open(const QString fileName);
    void save(const QString fileName);
    void saveAs(const QString fileName);
    QMap<QString, QString> showTextRowAndCol();

protected:
    void wheelEvent(QWheelEvent * event);
    void contextMenuEvent(QContextMenuEvent *e);



public slots:
    void copy();
    void cut();
    void paste();
    void undo();
    void redo();

private:
    bool boldDone = false;
    bool italicDone = false;
    bool underLineDone = false;
};

#endif // EDITOR_H
