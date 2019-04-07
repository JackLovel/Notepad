#include "replacedialog.h"

ReplaceDialog::ReplaceDialog(QWidget *parent)
    : QDialog(parent)
{
    findLabel = new QLabel("查找内容");
    findEdit = new QLineEdit;
    replaceLabel = new QLabel("替换为");
    replaceEdit = new QLineEdit;

    caseSensitiveCheckBox = new QCheckBox("区分大小写");
    findButton = new QPushButton("查找下一个");
    replaceButton = new QPushButton("替换");
    replaceAllButton = new QPushButton("全部替换");
    cancelButton = new QPushButton("取消");
    mainLayout = new QGridLayout;

    mainLayout->addWidget(findLabel, 0, 0);
    mainLayout->addWidget(findEdit, 0, 1);
    mainLayout->addWidget(findButton, 0, 2);
    mainLayout->addWidget(replaceLabel, 1, 0);
    mainLayout->addWidget(replaceEdit, 1, 1);
    mainLayout->addWidget(replaceButton, 1, 2);
    mainLayout->addWidget(replaceAllButton, 2, 2);
    mainLayout->addWidget(cancelButton, 3, 2);
    mainLayout->addWidget(caseSensitiveCheckBox, 4, 0);

    //widget->setLayout(mai);
    setWindowTitle("replace");

    connect(findEdit, SIGNAL(textChanged(QString)), this, SLOT(textChangeSlot()));
    connect(findButton, SIGNAL(clicked()), this, SLOT(on_findButton_clicked()));
    connect(replaceButton, SIGNAL(clicked()), this, SLOT(on_replaceButton_clicked()));
    connect(replaceAllButton, SIGNAL(clicked()), this, SLOT(on_replaceAllButton_clicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelSlot()));



    setLayout(mainLayout);
}

ReplaceDialog::~ReplaceDialog()
{

}

void ReplaceDialog::cancelSlot()
{
    this->close();
}

void ReplaceDialog::textChangeSlot()
{
    if (findEdit->text().trimmed().isEmpty())
    {
        findButton->setEnabled(false);
        replaceButton->setEnabled(false);
        replaceButton->setEnabled(false);
    } else {
        findButton->setEnabled(true);
        replaceButton->setEnabled(true);
        replaceAllButton->setEnabled(true);
    }
}

void ReplaceDialog::on_findButton_clicked()
{
    bool checkbox = caseSensitiveCheckBox->isChecked();
    QString value = findEdit->text().trimmed();

    emit this->find(value, checkbox);
}

void ReplaceDialog::on_replaceButton_clicked()
{
    bool checkbox = caseSensitiveCheckBox->isChecked();
    QString target = findEdit->text().trimmed();
    QString value = replaceEdit->text().trimmed();

    emit this->replace(target, value, checkbox, false);
}

void ReplaceDialog::on_replaceAllButton_clicked()
{
    bool checkbox = caseSensitiveCheckBox->isChecked();
    QString target = findEdit->text().trimmed();
    QString value = replaceEdit->text().trimmed();

    emit this->replace(target, value, checkbox, true);
}























