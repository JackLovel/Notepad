/*
 * unrealised feature
 */

#include "utils.h"
#include "setting.h"
#include "settingpage.h"

#include <QFile>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QGridLayout>


ShortcutPage::ShortcutPage(QWidget *parent) : QWidget(parent)
{
    Utils::loadStyleSheet(":/style/checkBoxStyle.qss", this);

    QGridLayout *mainLayout = new QGridLayout;

    QLabel *setting = new QLabel(tr("setting: "));
    QLineEdit *settingLine = new QLineEdit(tr("F1"));


    QLabel *handleLoadFile = new QLabel(tr("load file: "));
    QLineEdit *handLoadFileLine = new QLineEdit(tr("CTRL+F4"));

    QLabel *sendFile = new QLabel(tr("send file: "));
    QLineEdit *sendFileLine = new QLineEdit(tr("F2"));

    QLabel *loadFile = new QLabel(tr("load file: "));
    QLineEdit *loadFileLine = new QLineEdit(tr("F3"));

    QLabel *changeGroup = new QLabel(tr("chage group"));
    QLineEdit *changeGroupLabel = new QLineEdit(tr("F5"));

    QLabel *pause = new QLabel(tr("pause: "));
    QLineEdit *pauseLine = new QLineEdit(tr("Return"));

    QPushButton *defaultBtn = new QPushButton("恢复默认", this);
    QPushButton *okBtn = new QPushButton("确认", this);
    QPushButton *cancelBtn = new QPushButton("取消", this);

    QCheckBox *pCheckBox = new QCheckBox(this);
    pCheckBox->setText(tr("three status"));

    mainLayout->addWidget(setting, 0, 0);
    mainLayout->addWidget(settingLine, 0, 1);
    mainLayout->addWidget(handleLoadFile, 0, 2);
    mainLayout->addWidget(handLoadFileLine, 0, 3);

    mainLayout->addWidget(sendFile, 1, 0);
    mainLayout->addWidget(sendFileLine, 1, 1);
    mainLayout->addWidget(loadFile, 1, 2);
    mainLayout->addWidget(loadFileLine, 1, 3);

    mainLayout->addWidget(changeGroup, 2, 0);
    mainLayout->addWidget(changeGroupLabel, 2, 1);
    mainLayout->addWidget(pause, 2, 2);
    mainLayout->addWidget(pauseLine, 2, 3);

    mainLayout->addWidget(defaultBtn, 3, 0);
    mainLayout->addWidget(okBtn, 3, 1);
    mainLayout->addWidget(cancelBtn, 3, 2);

    // CheckBox
    mainLayout->addWidget(pCheckBox);

    //connect(cancelBtn, &QPushButton::clicked, this, &Setting::close);

    setLayout(mainLayout);
}

ShortcutPage::~ShortcutPage()
{

}

