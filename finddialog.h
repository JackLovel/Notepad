#ifndef FINDDIALOG_H
#define FINDDIALOG_H


#include <QWidget>
#include <QGroupBox>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QCloseEvent>

class FindDialog : public QDialog
{
   Q_OBJECT

public:
    FindDialog(QWidget *parent = 0);
    ~FindDialog();

signals:
    void find(QString, bool, bool);

private slots:
    void on_findButton_clicked();
    // when text change
    void textChangeSlot();

private:
    void createUI();
    void createConnect();

    QString m_text;
    QWidget *widget;

    QPushButton *findButton;
    QPushButton *cancelButton;
    QLabel *findLabel;
    QLineEdit *findLine;
    QCheckBox *caseSensitiveCheckBox;

    QGroupBox *groupBox;
    QHBoxLayout *radioLayout;
    QRadioButton *upRadio;
    QRadioButton *downRadio;
    QGridLayout *mainLayout;

    void showMessage(QString title);
};
#endif // FINDDIALOG_H
