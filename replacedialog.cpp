#include "replacedialog.h"

ReplaceDialog::ReplaceDialog(QWidget *parent)
    : QDialog(parent)
{
    QLabel *findLabel = new QLabel("查找内容");
    QLineEdit *findEdit = new QLineEdit;
    QLabel *replaceLabel = new QLabel("替换为");
    QLineEdit *replaceEdit = new QLineEdit;

    QCheckBox *caseSensitiveCheckBox = new QCheckBox("区分大小写");
    QPushButton *findButton = new QPushButton("查找下一个");
    QPushButton *replaceButton = new QPushButton("替换");
    QPushButton *replaceAllButton = new QPushButton("全部替换");
    QPushButton *cancelButton = new QPushButton("取消");

    QGridLayout *mainLayout = new QGridLayout;

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
    setLayout(mainLayout);
}

ReplaceDialog::~ReplaceDialog()
{

}

void ReplaceDialog::on_cancelButton_clicked()
{

}

void ReplaceDialog::textChangeSlot()
{

}

void ReplaceDialog::on_replaceButton_clicked()
{

}

void ReplaceDialog::on_replaceAllButton_clicked()
{

}

