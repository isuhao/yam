#include "yeditor.h"

#include "yexport.h"
#include "yrectpacker.h"
#include "quitreeitem.h"

#if defined(OS_WINDOWS)
#include <crtdbg.h>
#endif

#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QSpinBox>
#include <QtGui/QClipboard>

#include <QtGui/QPixmap>
#include <QtGui/QPainter>

#include <QtCore/QTime>

#if defined(MSVC)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#elif defined(GNUC)
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define YEDITOR_VERSION_MAIN			0
#define YEDITOR_VERSION_SUB				1
#ifdef _DEBUG
#define YEDITOR_VERSION_STRING			YTOSTRING(YEDITOR_VERSION_MAIN)"."YTOSTRING(YEDITOR_VERSION_SUB)" Build:["__DATE__" - "__TIME__"]"
#else // _DEBUG
#define YEDITOR_VERSION_STRING			YTOSTRING(YEDITOR_VERSION_MAIN)"."YTOSTRING(YEDITOR_VERSION_SUB)
#endif // _DEBUG
#define YEDITOR_TITLE					YEDITOR_NAME" "YEDITOR_VERSION_STRING


yam::base::YCTree						gs_FileTreeData;

YEditor::YEditor(QWidget* pParent /* = NULL */)
	: QMainWindow(pParent)
	, m_pTreeResHelper(NULL)
	, m_pTreeUiHelper(NULL)
{
	qsrand(QTime::currentTime().msec());

	m_UI.setupUi(this);

	setWindowTitle(YEDITOR_TITLE);

	connect(m_UI.resDock, SIGNAL(visibilityChanged(bool)), this, SLOT(onResDockVisibilityChanged(bool)));
	connect(m_UI.uiDock, SIGNAL(visibilityChanged(bool)), this, SLOT(onUiDockVisibilityChanged(bool)));

	{
		QTreeWidgetItem* pHeaderItem = m_UI.resTree->headerItem();
		if (NULL != pHeaderItem)
		{
			pHeaderItem->setText(0, tr("Tree"));
		}
	}
	{
		QTreeWidgetItem* pHeaderItem = m_UI.resPropertyTreeWidget->headerItem();
		if (NULL != pHeaderItem)
		{
			pHeaderItem->setText(0, tr("Key"));
			pHeaderItem->setText(1, tr("Value"));
		}
	}
	{
		QTreeWidgetItem* pHeaderItem = m_UI.uiTree->headerItem();
		if (NULL != pHeaderItem)
		{
			pHeaderItem->setText(0, tr("Tree"));
		}
	}
	{
		QTreeWidgetItem* pHeaderItem = m_UI.uiPropertyTreeWidget->headerItem();
		if (NULL != pHeaderItem)
		{
			pHeaderItem->setText(0, tr("Key"));
			pHeaderItem->setText(1, tr("Value"));
		}
	}

	m_UI.uiArea->setGrabable(false);

	parseArgument(QApplication::arguments());
}

YEditor::~YEditor()
{
	if (NULL != m_pTreeResHelper)
	{
		delete m_pTreeResHelper;
		m_pTreeResHelper = NULL;
	}
	if (NULL != m_pTreeUiHelper)
	{
		delete m_pTreeUiHelper;
		m_pTreeUiHelper = NULL;
	}
	//
}

void YEditor::onClickedOpen()
{
	m_sFileName = "";
	{
		QString qsFileName = QFileDialog::getOpenFileName(this, tr("Open a yui file"), "", tr("YUI (*.yui)"));
		m_sFileName.append(qsFileName.toLocal8Bit());
	}
	if (0 >= m_sFileName.size())
	{
		return;
	}
	reloadFile(m_sFileName);
}

void YEditor::onClickedSave()
{
	qDebug("on clicked save");
	//
}

void YEditor::onClickedExport()
{
	json::Object jObj;

	int iTopItemCount = m_UI.uiTree->topLevelItemCount();
	for (int i = 0; i < iTopItemCount; ++i)
	{
		QTreeWidgetItem* pTreeItem = m_UI.uiTree->topLevelItem(i);
		exportUiTreeToJson(pTreeItem, jObj);
	}

	json::Array jAry;
	jAry.push_back("aa");
	jObj["aa"] = jAry;

	std::string sRes = json::Serialize(jObj);

	/*yam::yvvec2d vSize;
	yam::YVec2D stSize;
	stSize.X = qrand() % 80 + 1; stSize.Y = qrand() % 80 + 1;
	vSize.push_back(stSize);
	stSize.X = qrand() % 80 + 1; stSize.Y = qrand() % 80 + 1;
	vSize.push_back(stSize);
	stSize.X = qrand() % 80 + 1; stSize.Y = qrand() % 80 + 1;
	vSize.push_back(stSize);
	stSize.X = qrand() % 80 + 1; stSize.Y = qrand() % 80 + 1;
	vSize.push_back(stSize);
	stSize.X = qrand() % 80 + 1; stSize.Y = qrand() % 80 + 1;
	vSize.push_back(stSize);
	stSize.X = qrand() % 80 + 1; stSize.Y = qrand() % 80 + 1;
	vSize.push_back(stSize);
	stSize.X = qrand() % 80 + 1; stSize.Y = qrand() % 80 + 1;
	vSize.push_back(stSize);
	stSize.X = qrand() % 80 + 1; stSize.Y = qrand() % 80 + 1;
	vSize.push_back(stSize);
	stSize.X = qrand() % 80 + 1; stSize.Y = qrand() % 80 + 1;
	vSize.push_back(stSize);
	stSize.X = qrand() % 80 + 1; stSize.Y = qrand() % 80 + 1;
	vSize.push_back(stSize);
	stSize.X = 500; stSize.Y = 500;
	yam::yvrect vRect;
	YCRectPacker::Instance().Do(vSize, stSize, vRect);
	QVector<QRect> vQRects;
	yam::yvrect::const_iterator cit = vRect.begin();
	yam::yvrect::const_iterator citEnd = vRect.end();
	for (; cit != citEnd; ++cit)
	{
		const yam::YRect2D& rstRect2D = *cit;
		vQRects.push_back(QRect(rstRect2D.Pos.X, rstRect2D.Pos.Y, rstRect2D.Size.X, rstRect2D.Size.Y));
	}

	QImage oImage(stSize.X, stSize.Y, QImage::Format_ARGB32);
	oImage.fill(Qt::transparent);
	QPainter oPainter(&oImage);
	for (int i = 0; i < vQRects.size(); ++i)
	{
		QRgb rgb = qRgba((qrand() % 0xFF), (qrand() % 0xFF), (qrand() % 0xFF), ((qrand() % 0xFF) + 0x55) % 0xFF);
		QImage oImageBox(vQRects[i].width(), vQRects[i].height(), QImage::Format_ARGB32);
		oImageBox.fill(rgb);
		oPainter.drawImage(vQRects[i].x(), vQRects[i].y(), oImageBox);
	}
	oImage.save("D:\\workspace\\github\\temp\\temp.png", "PNG");*/
}

void YEditor::onClickedSync()
{
	reloadFile(m_sFileName);
}

void YEditor::onClickedMenuWindowDockRes()
{
	if (m_UI.resDock->isVisible())
	{
		m_UI.resDock->close();
	}
	else
	{
		m_UI.resDock->show();
	}
}

void YEditor::onClickedMenuWindowDockUi()
{
	if (m_UI.uiDock->isVisible())
	{
		m_UI.uiDock->close();
	}
	else
	{
		m_UI.uiDock->show();
	}
}

void YEditor::onClickedMenuWindowAreaRes()
{
	if (m_UI.resAreaGroupBox->isVisible())
	{
		m_UI.resAreaGroupBox->close();
	}
	else
	{
		m_UI.resAreaGroupBox->show();
	}
}

void YEditor::onClickedMenuWindowAreaUi()
{
	if (m_UI.uiAreaGroupBox->isVisible())
	{
		m_UI.uiAreaGroupBox->close();
	}
	else
	{
		m_UI.uiAreaGroupBox->show();
	}
}

void YEditor::onResTreeItemSelected(QTreeWidgetItem* pTreeItem, int iColumn)
{
	YCQUiItem* pUiItem = getUiItem(pTreeItem);
	m_UI.resArea->setSelected(pUiItem);
	refreshResProperty(pUiItem);
}

void YEditor::onResTreeContextMenu(QPoint oPos)
{
	QModelIndex index = m_UI.resTree->currentIndex();
	if (!index.isValid())
	{
		return;
	}
	QMenu menu;
	menu.addAction(tr("Copy Image Source"), this, SLOT(onClickedResMenuItem_CopyImageSource()));
	menu.addAction(tr("Tiled"), this, SLOT(onClickedResMenuItem_Tiled()));
	menu.exec(QCursor::pos());
}

void YEditor::onUiTreeItemSelected(QTreeWidgetItem* pTreeItem, int iColumn)
{
	YCQUiItem* pUiItem = getUiItem(pTreeItem);
	m_UI.uiArea->setSelected(pUiItem);
	refreshUiProperty(pUiItem);
}

void YEditor::onUiTreeContextMenu(QPoint oPos)
{
	QTreeWidgetItem* pCurrentItem = m_UI.uiTree->currentItem();

	QMenu menu;
	QMenu* pMenuCreate = menu.addMenu(tr("Create"));
	{
		QAction* pActionCreate = pMenuCreate->addAction(tr("Scene"), this, SLOT(onClickedUiMenuItem_CreateScene()));
		pActionCreate->setEnabled(0 == m_UI.uiTree->topLevelItemCount());
	}

	{
		QAction* pActionCreate = pMenuCreate->addAction(tr("Panel"), this, SLOT(onClickedUiMenuItem_CreatePanel()));
		pActionCreate->setEnabled(NULL != pCurrentItem);
	}
	{
		QAction* pActionCreate = pMenuCreate->addAction(tr("Image"), this, SLOT(onClickedUiMenuItem_CreateImage()));
		pActionCreate->setEnabled(NULL != pCurrentItem);
	}
	{
		QAction* pActionCreate = pMenuCreate->addAction(tr("Button"), this, SLOT(onClickedUiMenuItem_CreateButton()));
		pActionCreate->setEnabled(NULL != pCurrentItem);
	}
	menu.exec(QCursor::pos());
}

void YEditor::onPressedResItem(YCQUiItem* pUiItem)
{
	YCQUiTreeItem* pTreeItem = getTreeItem(pUiItem);
	if (NULL == pTreeItem)
	{
		return;
	}
	m_UI.resTree->setCurrentItem(pTreeItem);
}

void YEditor::onPressedUiItem(YCQUiItem* pUiItem)
{
	YCQUiTreeItem* pTreeItem = getTreeItem(pUiItem);
	if (NULL == pTreeItem)
	{
		return;
	}
	m_UI.uiTree->setCurrentItem(pTreeItem);
}

void YEditor::onResDockVisibilityChanged(bool bVisible)
{
	m_UI.actionDockRes->setChecked(bVisible);
	m_UI.actionBarDockRes->setChecked(bVisible);
}

void YEditor::onResAreaVisibilityChanged(bool bVisible)
{
	m_UI.actionAreaRes->setChecked(bVisible);
	m_UI.actionBarAreaRes->setChecked(bVisible);
}

void YEditor::onClickedResMenuItem_CopyImageSource()
{
	YCQUiItem* pTreeItem = getUiItem(m_UI.resTree->currentItem());
	if (NULL == pTreeItem)
	{
		return;
	}
	QApplication::clipboard()->setText(pTreeItem->getImageSource());
	QString msg("copy image source from res tree item - "); msg.append(pTreeItem->getImageSource());
	m_UI.statusbar->showMessage(msg, 5000);
}

void YEditor::onClickedResMenuItem_Tiled()
{
	m_UI.resArea->toTiled();
}

void YEditor::onUiDockVisibilityChanged(bool bVisible)
{
	m_UI.actionDockUi->setChecked(bVisible);
	m_UI.actionBarDockUi->setChecked(bVisible);
}

void YEditor::onUiAreaVisibilityChanged(bool bVisible)
{
	m_UI.actionAreaUi->setChecked(bVisible);
	m_UI.actionBarAreaUi->setChecked(bVisible);
}

void YEditor::onClickedUiMenuItem_CreateScene()
{
	yam::base::YIWidget* pWidget = new yam::base::YCWidget;
	pWidget->GetId() = "scene";
	pWidget->GetBound().Size.X = 300;
	pWidget->GetBound().Size.Y = 300;

	YCQUiItem* pUiItem = m_UI.uiArea->addChildItem(pWidget);
	connect(pUiItem, SIGNAL(onPressed(YCQUiItem*)), this, SLOT(onPressedUiItem(YCQUiItem*)));

	YCQUiTreeItem* pTreeItem = new YCQUiTreeItem;
	pTreeItem->setText(0, pWidget->GetId().c_str());
	m_UI.uiTree->insertTopLevelItem(0, pTreeItem);

	SRelationship stRelationship;
	stRelationship._pUiItem = pUiItem;
	stRelationship._pTreeItem = pTreeItem;
	m_mRelationship.insert(std::make_pair(getFullName(pWidget), stRelationship));

	delete pWidget;
	pWidget = YNULL;
}

void YEditor::onClickedUiMenuItem_CreatePanel()
{
	QTreeWidgetItem* pItem = m_UI.uiTree->currentItem();
	if (NULL == pItem)
	{
		return;
	}
	//pItem->addChild();
	//
}

void YEditor::onClickedUiMenuItem_CreateImage()
{
	//
}

void YEditor::onClickedUiMenuItem_CreateButton()
{
	//
}

void YEditor::reloadFile(const yam::ystring& rsFileName)
{
	m_sFileName = rsFileName;

	yam::base::YCBuffer buffer;
	{
		yam::storage::YCFileReader file;
		file.Open(m_sFileName);
		file >> buffer;
		file.Close();
	}

	// clear
	m_UI.resArea->clearChildrenItem();
	m_UI.resTree->clear();
	m_UI.resPropertyTreeWidget->clear();
	m_UI.uiArea->clearChildrenItem();
	m_UI.uiTree->clear();
	m_UI.uiPropertyTreeWidget->clear();
	m_mRelationship.clear();
	gs_FileTreeData.Clear();

	// parse
	gs_FileTreeData << buffer;

	{
		yam::base::YITree* pTreePsRes = gs_FileTreeData.FindChild(YFILE_KEY_RESOURCE);
		if (YNULL != pTreePsRes && YOBJECT_GETCLASSNAME(yam::base::YCFormat) == pTreePsRes->GetClassName())
		{
			const yam::base::YIFormat* pRes = (yam::base::YIFormat*)pTreePsRes;
			reloadRes(pRes, NULL, NULL);
		}
	}
	m_UI.resTree->expandAll();

	{
		yam::base::YITree* pTreeUi = gs_FileTreeData.FindChild(YFILE_KEY_UI);
		if (YNULL != pTreeUi && YOBJECT_GETCLASSNAME(yam::base::YCWidget) == pTreeUi->GetClassName())
		{
			const yam::base::YIWidget* pUi = (yam::base::YIWidget*)pTreeUi;
			reloadUi(pUi, NULL, NULL);
		}
	}
	m_UI.uiTree->expandAll();
}

void YEditor::reloadRes(const yam::base::YIFormat*& rpFormat, YCQUiItem* pUiParent, QTreeWidgetItem* pTreeParent)
{
	if (YNULL == rpFormat)
	{
		return;
	}

	YCQUiItem* pUiItem = m_UI.resArea->addChildItem(rpFormat);
	if (NULL != pUiItem)
	{
		pUiItem->setImageSource(getFullName(rpFormat));
		connect(pUiItem, SIGNAL(onPressed(YCQUiItem*)), this, SLOT(onPressedResItem(YCQUiItem*)));
	}

	YCQUiTreeItem* pTreeItem = new YCQUiTreeItem;
	pTreeItem->setText(0, rpFormat->GetId().c_str());
	pTreeItem->setDataProperty("imagesource", getFullName(rpFormat));
	if (NULL == pTreeParent)
	{
		m_UI.resTree->insertTopLevelItem(0, pTreeItem);
	}
	else
	{
		pTreeParent->insertChild(0, pTreeItem);
	}

	SRelationship stRelationship;
	stRelationship._pUiItem = pUiItem;
	stRelationship._pTreeItem = pTreeItem;
	m_mRelationship.insert(std::make_pair(getFullName(rpFormat), stRelationship));

	const yam::base::YITree* pTreeNext = rpFormat->GetNext();
	if (YNULL != pTreeNext && YOBJECT_GETCLASSNAME(yam::base::YCFormat) == pTreeNext->GetClassName())
	{
		const yam::base::YIFormat* pFormatNext = (const yam::base::YIFormat*)pTreeNext;
		reloadRes(pFormatNext, pUiParent, pTreeParent);
	}

	const yam::base::YITree* pTreeChildren = rpFormat->GetChildren();
	if (YNULL != pTreeChildren && YOBJECT_GETCLASSNAME(yam::base::YCFormat) == pTreeChildren->GetClassName())
	{
		const yam::base::YIFormat* pFormatChildren = (const yam::base::YIFormat*)pTreeChildren;
		reloadRes(pFormatChildren, pUiItem, pTreeItem);
	}
}

void YEditor::reloadUi(const yam::base::YIWidget*& rpWidget, YCQUiItem* pUiParent, QTreeWidgetItem* pTreeParent)
{
	if (NULL == rpWidget)
	{
		return;
	}
	YCQUiItem* pUiItem = m_UI.uiArea->addChildItem(rpWidget);
	if (NULL != pUiItem)
	{
		connect(pUiItem, SIGNAL(onPressed(YCQUiItem*)), this, SLOT(onPressedUiItem(YCQUiItem*)));
	}

	YCQUiTreeItem* pTreeItem = new YCQUiTreeItem;
	pTreeItem->setText(0, rpWidget->GetId().c_str());
	if (NULL == pTreeParent)
	{
		m_UI.uiTree->insertTopLevelItem(0, pTreeItem);
	}
	else
	{
		pTreeParent->insertChild(0, pTreeItem);
	}

	SRelationship stRelationship;
	stRelationship._pUiItem = pUiItem;
	stRelationship._pTreeItem = pTreeItem;
	m_mRelationship.insert(std::make_pair(getFullName(rpWidget), stRelationship));

	const yam::base::YITree* pTreeNext = rpWidget->GetNext();
	if (YNULL != pTreeNext && YOBJECT_GETCLASSNAME(yam::base::YCWidget) == pTreeNext->GetClassName())
	{
		const yam::base::YIWidget* pFormatNext = (const yam::base::YIWidget*)pTreeNext;
		reloadUi(pFormatNext, pUiParent, pTreeParent);
	}

	const yam::base::YITree* pTreeChildren = rpWidget->GetChildren();
	if (YNULL != pTreeChildren && YOBJECT_GETCLASSNAME(yam::base::YCWidget) == pTreeChildren->GetClassName())
	{
		const yam::base::YIWidget* pFormatChildren = (const yam::base::YIWidget*)pTreeChildren;
		reloadUi(pFormatChildren, pUiItem, pTreeItem);
	}
}

QString YEditor::getFullName(const yam::base::YITree* pTree)
{
	QString sRes = "";
	if (YNULL == pTree)
	{
		return sRes;
	}
	const yam::base::YITree* pParent = pTree;
	while (YNULL != pParent)
	{
		if (0 < sRes.size())
		{
			sRes.insert(0, ".");
		}
		sRes.insert(0, pParent->GetId().c_str());
		pParent = pParent->GetParent();

	}
	return sRes;
}

YCQUiItem* YEditor::getUiItem(QTreeWidgetItem* pTreeItem) const
{
	if (NULL == pTreeItem)
	{
		return NULL;
	}

	ymnamerelationship::const_iterator cit = m_mRelationship.begin();
	ymnamerelationship::const_iterator citEnd = m_mRelationship.end();
	for (; cit != citEnd; ++cit)
	{
		if (pTreeItem != cit->second._pTreeItem)
		{
			continue;
		}
		return cit->second._pUiItem;
	}
	return NULL;
}

YCQUiTreeItem* YEditor::getTreeItem(YCQUiItem* pUiItem) const
{
	if (NULL == pUiItem)
	{
		return NULL;
	}

	ymnamerelationship::const_iterator cit = m_mRelationship.begin();
	ymnamerelationship::const_iterator citEnd = m_mRelationship.end();
	for (; cit != citEnd; ++cit)
	{
		if (pUiItem != cit->second._pUiItem)
		{
			continue;
		}
		return cit->second._pTreeItem;
	}
	return NULL;
}

void YEditor::refreshResProperty(YCQUiItem*& rpResItem)
{
	m_UI.resPropertyTreeWidget->clear();
	if (YNULL != rpResItem)
	{
		if (NULL != m_pTreeResHelper)
		{
			delete m_pTreeResHelper;
			m_pTreeResHelper = NULL;
		}
		m_pTreeResHelper = new YCQUiTreeResHelper(m_UI.resPropertyTreeWidget);
		m_pTreeResHelper->setUiItem(rpResItem);

		m_UI.resPropertyTreeWidget->expandAll();
	}
}

void YEditor::refreshUiProperty(YCQUiItem*& rpUiItem)
{
	m_UI.uiPropertyTreeWidget->clear();
	if (NULL != rpUiItem)
	{
		if (NULL != m_pTreeUiHelper)
		{
			delete m_pTreeUiHelper;
			m_pTreeUiHelper = NULL;
		}
		m_pTreeUiHelper = new YCQUiTreeUiHelper(m_UI.uiPropertyTreeWidget);
		m_pTreeUiHelper->setUiItem(rpUiItem);

		m_UI.uiPropertyTreeWidget->expandAll();
	}
}

void YEditor::parseArgument(const QStringList& rvStr)
{
	if (rvStr.empty())
	{
		return;
	}
	if (2 == rvStr.size())
	{
		yam::ystring sFileName;
		sFileName.append(rvStr[1].toLocal8Bit());
		reloadFile(sFileName);
	}
}

void YEditor::exportUiTreeToJson(QTreeWidgetItem* pTreeItem, json::Object& rjObjParent)
{
	if (NULL == pTreeItem)
	{
		return;
	}
	json::Object jObjMy;

	std::string sId(pTreeItem->text(0).toLocal8Bit());
	jObjMy["id"] = sId.c_str();

	YCQUiItem* pUiItem = getUiItem(pTreeItem);
	if (NULL != pUiItem)
	{
		//
	}

	int iChildCount = pTreeItem->childCount();
	for (int i = 0; i < iChildCount; ++i)
	{
		exportUiTreeToJson(pTreeItem->child(i), jObjMy);
	}

	rjObjParent["fff"] = jObjMy;
	//
}

int main(int argc, char* argv[])
{
#if defined(OS_WINDOWS)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	QApplication a(argc, argv);
	YEditor editor;
	editor.show();
	return a.exec();
}
