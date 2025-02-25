#include "windowmanager.h"
#include "mainwindow.h"
#include "announcermenu.h"
#include "cctvview.h"
#include "displaymenu.h"
#include "pecustatus.h"
#include "connectionstatus.h"

WindowManager::WindowManager(QObject *parent) : QObject (parent)
{
    m_wndHMI = new MainWindow(this);
    m_wndAnnouncer = new AnnouncerMenu(this);
    m_wndCctv = new CctvView(this);
    m_wndConnection = new ConnectionStatus(this);
    m_wndDisplay = new DisplayMenu(this);
    m_wndPecu = new PecuStatus(this);
}

WindowManager::~WindowManager()
{
    delete m_wndHMI;
}

void WindowManager::showMainWindow()
{
    m_wndHMI -> showFullScreen();
}

void WindowManager::onBtnAnnouncerClick()
{
    m_wndAnnouncer -> showFullScreen();
    m_wndCctv -> hide();
    m_wndConnection -> hide();
    m_wndDisplay -> hide();
    m_wndHMI -> hide();
    m_wndPecu -> hide();
}

void WindowManager::onBtnCctvClick()
{
    m_wndAnnouncer -> hide();
    m_wndCctv -> showFullScreen();
    m_wndConnection -> hide();
    m_wndDisplay -> hide();
    m_wndHMI -> hide();
    m_wndPecu -> hide();
}

void WindowManager::onBtnConnectionStatusClick()
{
    m_wndAnnouncer -> hide();
    m_wndCctv -> hide();
    m_wndConnection -> showFullScreen();
    m_wndDisplay -> hide();
    m_wndHMI -> hide();
    m_wndPecu -> hide();
}

void WindowManager::onBtnDisplayMenuClick()
{
    m_wndAnnouncer -> hide();
    m_wndCctv -> hide();
    m_wndConnection -> hide();
    m_wndDisplay -> showFullScreen();
    m_wndHMI -> hide();
    m_wndPecu -> hide();
}

void WindowManager::onBtnPecuClick()
{
    m_wndAnnouncer -> hide();
    m_wndCctv -> hide();
    m_wndConnection -> hide();
    m_wndDisplay -> hide();
    m_wndHMI -> hide();
    m_wndPecu -> showFullScreen();
}

void WindowManager::onBtnSystemClick()
{
    m_wndAnnouncer -> hide();
    m_wndCctv -> hide();
    m_wndConnection -> hide();
    m_wndDisplay -> hide();
    m_wndHMI -> showFullScreen();
    m_wndPecu -> hide();
}
