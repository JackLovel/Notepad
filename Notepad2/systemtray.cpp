#include "systemtray.h"


SystemTray::SystemTray(QWidget *parent)
    :QMenu(parent)
{
    initActions();
}

SystemTray::~SystemTray()
{

}

void SystemTray::initActions()
{
    m_pShowAction = new QAction(tr("diplay"), this);
    m_pSettingAction = new QAction(tr("setting"), this);

    m_pShowAction = new QAction(tr("diplay"), this);
    m_pSettingAction = new QAction(tr("setting"), this);
    m_pShowAction = new QAction(tr("diplay"), this);
    m_pSettingAction = new QAction(tr("setting"), this);
    m_pShowAction = new QAction(tr("diplay"), this);
    m_pSettingAction = new QAction(tr("setting"), this);
    m_pShowAction = new QAction(tr("diplay"), this);
    m_pSettingAction = new QAction(tr("setting"), this);

    addAction(m_pShowAction);
}













