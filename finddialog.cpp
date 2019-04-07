#include "finddialog.h"

#include <QHBoxLayout>
#include <QMessageBox>

FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
{
    createUI();
    createConnect();
}

FindDialog::~FindDialog()
{

}

void FindDialog::createUI()
{
    findButton = new QPushButton("查找");
    cancelButton = new QPushButton("取消");
    findLabel = new QLabel(tr("查找内容:"));
    findLine = new QLineEdit("");
    caseSensitiveCheckBox = new QCheckBox(tr("区分大小写"));

    radioLayout = new QHBoxLayout;
    groupBox = new QGroupBox(tr("方向"));
    upRadio = new QRadioButton(tr("向上"));
    downRadio = new QRadioButton(tr("向下"));
    radioLayout->addWidget(upRadio);
    radioLayout->addWidget(downRadio);
    groupBox->setLayout(radioLayout);

    mainLayout = new QGridLayout;

    mainLayout->addWidget(findLabel, 0, 0);
    mainLayout->addWidget(findLine, 0, 1);
    mainLayout->addWidget(findButton, 0, 2);
    mainLayout->addWidget(caseSensitiveCheckBox, 1, 0);
    mainLayout->addWidget(groupBox, 1, 1);
    mainLayout->addWidget(cancelButton, 1, 2);

    setWindowTitle(tr("查找"));
    setLayout(mainLayout);
}

void FindDialog::createConnect()
{
    connect(findLine, SIGNAL(textChanged(QString)), this, SLOT(textChangeSlot()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(findButton, SIGNAL(clicked()), this, SLOT(on_findButton_clicked()));
}

void FindDialog::showMessage(QString title)
{
    QMessageBox box(QMessageBox::Question, "Notepad - find", title);
    box.setIcon(QMessageBox::NoIcon);
    box.setStandardButtons(QMessageBox::Ok);
    box.setButtonText(QMessageBox::Ok, QString("确认"));
    box.setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
    box.exec();
}

void FindDialog::on_findButton_clicked()
{
    bool checkbox = caseSensitiveCheckBox->isChecked();
    QString value = findLine->text().trimmed();
    bool isUp = false;
    if (upRadio->isChecked())
    {
        isUp = true;
    }

    if (value.isEmpty())
    {
        this->showMessage("请入关键字");
        return;
    }

    emit find(value, checkbox, isUp);
}

void FindDialog::textChangeSlot()
{
    if (findLine->text().trimmed().isEmpty())
    {
        findButton->setEnabled(false);
    }
    else
    {
        findButton->setEnabled(true);
    }
}
