#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QGridLayout>

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
    void cancelSlot();
    void textChangeSlot();
    void on_replaceButton_clicked();
    void on_replaceAllButton_clicked();
    void on_findButton_clicked();

private:
    QLabel *findLabel;
    QLineEdit *findEdit;
    QLabel *replaceLabel;
    QLineEdit *replaceEdit;
    QCheckBox *caseSensitiveCheckBox;
    QPushButton *findButton;
    QPushButton *replaceButton;
    QPushButton *replaceAllButton;
    QPushButton *cancelButton;
    QGridLayout *mainLayout;
};
#endif // REPLACEDIALOG_H
