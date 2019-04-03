#include "utils.h"
#include "setting.h"
#include "settingpage.h"

#include <QDebug>
#include <QtWidgets>
#include <QSettings> // ?

Setting::Setting(QWidget *parent)
    : QDialog(parent)
{
    Utils::loadStyleSheet(":/style/buttonStyle.qss", this);

    list = new QListWidget(this);
    list->insertItem(0, tr("快捷键设置"));
    list->insertItem(1, tr("基本设置"));
    list->insertItem(2, tr("高级设置"));

    label2 = new QLabel(tr("windowtest2"));
    label3 = new QLabel(tr("windowtest3"));

    stack = new QStackedWidget(this);

    stack->addWidget(new ShortcutPage);
    stack->addWidget(label2);
    stack->addWidget(label3);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(5);
    mainLayout->setSpacing(5);
    mainLayout->addWidget(list);
    mainLayout->addWidget(stack, 0, Qt::AlignHCenter);
    mainLayout->setStretchFactor(list, 1);
    mainLayout->setStretchFactor(stack, 3);

connect(list,SIGNAL(currentRowChanged(int)),stack,SLOT(setCurrentIndex(int)));

    setLayout(mainLayout);
}

Setting::~Setting()
{

}

