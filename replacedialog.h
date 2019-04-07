#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>
#include <QtWidgets>

class ReplaceDialog : public QDialog
{
   Q_OBJECT

public:
    ReplaceDialog(QWidget *parent = 0);
    ~ReplaceDialog();

signals:
    void find(QString, bool);
    void replace(QString, QString, bool, bool);

private slots:
    void on_cancelButton_clicked();
    void textChangeSlot();
    void on_replaceButton_clicked();
    void on_replaceAllButton_clicked();
};
#endif // REPLACEDIALOG_H
