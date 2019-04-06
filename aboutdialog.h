#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

class AboutDialog : public QDialog
{
public:
    AboutDialog(QWidget *parent = 0);
    ~AboutDialog();

private:
    QPushButton *okButton;
};

#endif // ABOUTDIALOG_H
