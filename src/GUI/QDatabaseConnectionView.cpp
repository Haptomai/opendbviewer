/*
 * QDatabaseConnectionView.cpp
 *
 *  Created on: 8 juin 2016
 *      Author: echopin
 */

#include "Widget/QMidClickClosableTabWidget.h"

#include "QDatabaseConnectionView.h"

QDatabaseConnectionView::QDatabaseConnectionView(QWidget* parent)
		: QWidget(parent)
{
	QVBoxLayout* pMainLayout = new QVBoxLayout();
	setLayout(pMainLayout);

	// Splitter
	QSplitter *pSplitter = new QSplitter();
	pSplitter->setChildrenCollapsible(false);
	pMainLayout->addWidget(pSplitter);

	// Create left panel
	QWidget* pVertConnectionPanel = makeConnectionVerticalPanel(pSplitter);
	pVertConnectionPanel->setMaximumWidth(300);
	pSplitter->addWidget(pVertConnectionPanel);

	// Create left panel
	m_pTabsInConnection = new QMidClickClosableTabWidget(); //Used to create a tab widget in the opened connection tab
	m_pTabsInConnection->setTabsClosable(true);
	m_pTabsInConnection->setMovable(true);
	pSplitter->addWidget(m_pTabsInConnection);
}

QDatabaseConnectionView::~QDatabaseConnectionView()
{

}

void QDatabaseConnectionView::addWorksheetView(QDatabaseWorksheetView* pDatabaseWorksheetView, const QString& szTitle)
{
	m_pTabsInConnection->addTab(pDatabaseWorksheetView, szTitle);
}

int QDatabaseConnectionView::addTableView(QDatabaseTableView* pDatabaseTableView, const QString& szTableTitle)
{
	return m_pTabsInConnection->addTab(pDatabaseTableView, szTableTitle);
}

void QDatabaseConnectionView::switchCurrentTableView(int iIndex)
{
	m_pTabsInConnection->setCurrentIndex(iIndex);
}

QWidget* QDatabaseConnectionView::makeWorksheetTab()
{
	m_pTab1 = new QWidget();
	QVBoxLayout *pWorksheetTabLayout = new QVBoxLayout();
	m_pTab1->setLayout(pWorksheetTabLayout);

	QDatabaseWorksheetView* pWorksheetView = new QDatabaseWorksheetView(this);
	pWorksheetTabLayout->addWidget(pWorksheetView);

	return m_pTab1;
}

QWidget* QDatabaseConnectionView::makeConnectionVerticalPanel(QWidget* pParent)
{
	QWidget *pWidget = new QWidget(pParent);

	QVBoxLayout *pLayout = new QVBoxLayout();
	pLayout->setContentsMargins(0, 0, 0, 0);
	pWidget->setLayout(pLayout);

	QToolBar* pToolbar = makeOptionButtonsToolBar(pWidget);
	pLayout->addWidget(pToolbar);

	m_pTableTreeView = new QTreeView();
	pLayout->addWidget(m_pTableTreeView);

	return pWidget;
}

QToolBar* QDatabaseConnectionView::makeOptionButtonsToolBar(QWidget* pParent)
{
	QToolBar *pToolbar = new QToolBar(pParent);

	m_pRefreshTableListButton = new QPushButton(QIcon::fromTheme("view-refresh"), tr("Refresh"), pToolbar); //TODO needs image rather than text
	pToolbar->addWidget(m_pRefreshTableListButton);

	m_pNewWorksheetButton = new QPushButton(QIcon::fromTheme("document-new"), tr("New worksheet"), pToolbar);//TODO needs image rather than text
	pToolbar->addWidget(m_pNewWorksheetButton);

	return pToolbar;
}

void QDatabaseConnectionView::setTablesModel(QStandardItemModel* pModel)
{
	m_pTableTreeView->setModel(pModel);
	QStandardItem *pHeader = new QStandardItem(tr("Structure"));
	pModel->setHorizontalHeaderItem(0, pHeader);
	m_pTableTreeView->expandAll();

	//Creates the "tables" item in the tree view
	m_pTableItem = new QStandardItem(tr("Tables"));
	m_pTableItem->setEditable(false);
	pModel->appendRow(m_pTableItem);

	//Creates the "structure tables" item in the tree view
	m_pStructureTableItem = new QStandardItem(tr("System tables"));
	m_pStructureTableItem->setEditable(false);
	pModel->appendRow(m_pStructureTableItem);

	//Creates the "views" item in the tree view
	m_pViewItem = new QStandardItem(tr("Views"));
	m_pViewItem->setEditable(false);
	pModel->appendRow(m_pViewItem);
	m_pTableTreeView->expandAll();
}

QPushButton* QDatabaseConnectionView::getNewWorksheetButton() const
{
	return m_pNewWorksheetButton;
}

QPushButton* QDatabaseConnectionView::getRefreshTableListButton() const
{
	return m_pRefreshTableListButton;
}

QAction* QDatabaseConnectionView::getNewWorksheetAction() const
{
	return m_pNewWorksheetAction;
}

QTabWidget* QDatabaseConnectionView::getTabsInConnection() const
{
	return m_pTabsInConnection;
}

QWidget* QDatabaseConnectionView::getWorksheetTab() const
{
	return m_pTab1;
}

QTreeView* QDatabaseConnectionView::getTableTreeView() const
{
	return m_pTableTreeView;
}

QStandardItem* QDatabaseConnectionView::getTableItem() const
{
	return m_pTableItem;
}

QStandardItem* QDatabaseConnectionView::getStructureTableItem() const
{
	return m_pStructureTableItem;
}

QStandardItem* QDatabaseConnectionView::getViewTableItem() const
{
	return m_pViewItem;
}
