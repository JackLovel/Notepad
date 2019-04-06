#include "aboutdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("关于记事本");

    QVBoxLayout *vbox = new QVBoxLayout(this);
    QHBoxLayout *hbox = new QHBoxLayout;

    hbox->addWidget(okButton, 1, Qt::AlignRight);
    vbox->addStretch(1);
    vbox->addLayout(hbox);
    setLayout(vbox);
}

AboutDialog::~AboutDialog()
{

}

