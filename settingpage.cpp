#include "utils.h"
#include "setting.h"
#include "settingpage.h"

#include <QTableWidgetItem>
#include <QTableView>
#include <QHeaderView>
#include <QAbstractItemView>

ShortcutPage::ShortcutPage(QWidget *parent) : QWidget(parent)
{
    //Utils::loadStyleSheet(":/style/checkBoxStyle.qss", this);
     shortCutGroupBox = new QGroupBox(tr("快捷键设置"));

     this->setTableWidgetSytle();

     // setting
     settingItem = new QTableWidgetItem(tr("Option setting"));
     settingItem->setTextAlignment(Qt::AlignCenter);
     settingShortCut = new QTableWidgetItem;
     settingShortCut->setTextAlignment(Qt::AlignCenter);
     shortCutTable->insertRow(0);
     shortCutTable->setItem(0, 0, settingItem);
     shortCutTable->setItem(0, 1, settingShortCut);

     // save
     saveItem = new QTableWidgetItem(tr("save"));
     saveItem->setTextAlignment(Qt::AlignCenter);
     saveShortCut = new QTableWidgetItem;
     saveShortCut->setTextAlignment(Qt::AlignCenter);
     shortCutTable->insertRow(1);
     shortCutTable->setItem(1, 0, saveItem);
     shortCutTable->setItem(1, 1, saveShortCut);

     // save as
     saveAsItem = new QTableWidgetItem(tr("save as"));
     saveAsItem->setTextAlignment(Qt::AlignCenter);
     saveAsShortCut = new QTableWidgetItem;
     saveAsShortCut->setTextAlignment(Qt::AlignCenter);
     shortCutTable->insertRow(2);
     shortCutTable->setItem(2, 0, saveAsItem);
     shortCutTable->setItem(2, 1, saveAsShortCut);

    // edit button
     editButton = new QPushButton(this);
     editButton->setObjectName("editButton");
     editButton->setText(tr("编辑"));

     // 恢复默认
     recoverDefaultButton = new QPushButton(this);
     recoverDefaultButton->setObjectName("recoverDefaultButton");
     recoverDefaultButton->setText("恢复默认");

     QHBoxLayout *buttonLayout = new QHBoxLayout;
     buttonLayout->addWidget(editButton);
     buttonLayout->addStretch();
     buttonLayout->addWidget(recoverDefaultButton);

     QVBoxLayout *shortCutLayout = new QVBoxLayout;
     shortCutLayout->addWidget(shortCutTable);
     shortCutLayout->addLayout(buttonLayout);
     shortCutGroupBox->setLayout(shortCutLayout);

     QVBoxLayout *mainLayout = new  QVBoxLayout;
     mainLayout->addWidget(shortCutGroupBox);


     setLayout(mainLayout);
}

ShortcutPage::~ShortcutPage()
{

}

void ShortcutPage::setTableWidgetSytle()
{
    shortCutTable = new QTableWidget(this);

    // table style
    shortCutTable->setRowCount(0);      // init row is 0
    shortCutTable->setColumnCount(2);   // init colum is 2

    QStringList headList;
    headList <<  tr("动作") << tr("全局热键");
    shortCutTable->setHorizontalHeaderLabels(headList);
    shortCutTable->verticalHeader()->setVisible(false);
    shortCutTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    shortCutTable->horizontalHeader()->setHighlightSections(false);
    shortCutTable->horizontalHeader()->setSectionsClickable(false);
    shortCutTable->setSelectionMode(QAbstractItemView::SingleSelection);
    shortCutTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    shortCutTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    shortCutTable->setShowGrid(false);
    //shortCutTable->setItemDelegate(new NoFocusDelegate());
}



















