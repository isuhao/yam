#include "yeditor.h"

#include "yexport.h"
#include "yrectpacker.h"

#include <crtdbg.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QBoxLayout>

#include <QtGui/QPixmap>
#include <QtGui/QPainter>

#ifdef _WINDOWS
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif // _WINDOWS_

const QString YEditor::ms_sTitle = "Yam Editor";

YEditor::YEditor(QWidget* pParent /* = NULL */)
	: QMainWindow(pParent)
{
	setWindowTitle(ms_sTitle);

	m_UI.setupUi(this);

	m_UI.formatTree->setContextMenuPolicy(Qt::CustomContextMenu);
	//
}

YEditor::~YEditor()
{
	//
}

void YEditor::onClickedOpen()
{
	qDebug("on clicked open");

	m_sFileName = "";
	{
		QString qsFileName = QFileDialog::getOpenFileName(this, tr("Open a yui file"), "", tr("YUI (*.yui)"));
		m_sFileName.append(qsFileName.toLocal8Bit());
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

void YEditor::onSelectedFormatTree(QTreeWidgetItem* pTreeItem, int iIndex)
{
	m_UI.formatArea->setSelected(getUiItem(pTreeItem));
}

void YEditor::onFormatTreeContextMenu(QPoint oPos)
{
	QModelIndex index = m_UI.formatTree->currentIndex();
	if (!index.isValid())
	{
		return;
	}
	QMenu menu;
	menu.addAction(tr("Show/Hide"), this, SLOT(onClickedFormatMenuItem_ShowHide()));
	menu.exec(QCursor::pos());
}

void YEditor::onUiTreeContextMenu(QPoint oPos)
{
	QModelIndex index = m_UI.uiTree->currentIndex();
	if (0 < m_UI.uiTree->children().size() && !index.isValid())
	{
		return;
	}

	QMenu menu;

	QMenu* pMenuCreate = menu.addMenu(tr("Create"));
	if (!index.isValid())
	{
		pMenuCreate->addAction(tr("Scene"), this, SLOT(onClickedUiWidgetMenuItem_CreateScene()));
		//
	}
	else
	{
		pMenuCreate->addAction(tr("Panel"), this, SLOT(onClickedUiWidgetMenuItem_CreatePanel()));
		pMenuCreate->addAction(tr("Image"), this, SLOT(onClickedUiWidgetMenuItem_CreateImage()));
		pMenuCreate->addAction(tr("Button"), this, SLOT(onClickedUiWidgetMenuItem_CreateButton()));
		//
	}
	menu.exec(QCursor::pos());
}

void YEditor::onPressedUiItem(YCQUiItem* pUiItem)
{
	QTreeWidgetItem* pTreeItem = getTreeItem(pUiItem);
	if (NULL == pTreeItem)
	{
		return;
	}
	m_UI.formatTree->setCurrentItem(pTreeItem);
}

void YEditor::onClickedFormatMenuItem_ShowHide()
{
	QList<QTreeWidgetItem*> lItems = m_UI.formatTree->selectedItems();
	if (0 >= lItems.size())
	{
		return;
	}
	QList<QTreeWidgetItem*>::iterator it = lItems.begin();
	QList<QTreeWidgetItem*>::iterator itEnd = lItems.end();
	for (; it != itEnd; ++it)
	{
		YCQUiItem* pUiItem = getUiItem(*it);
		if (NULL == pUiItem)
		{
			continue;
		}
		pUiItem->setVisible(!pUiItem->isVisible());
	}
	//
}

void YEditor::onClickedUiWidgetMenuItem_CreateScene()
{
	//
}

void YEditor::onClickedUiWidgetMenuItem_CreatePanel()
{
	//
}

void YEditor::onClickedUiWidgetMenuItem_CreateImage()
{
	//
}

void YEditor::onClickedUiWidgetMenuItem_CreateButton()
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

	m_UI.formatArea->clearChildrenItem();
	m_UI.formatArea->setScale(1.0f);
	m_UI.formatTree->clear();
	m_UI.uiArea->clearChildrenItem();
	m_UI.uiArea->setScale(1.0f);
	m_mRelationship.clear();
	m_FileTreeData.Clear();

	m_FileTreeData << buffer;

	{
		yam::base::YITree* pTreePsFormat = m_FileTreeData.FindChild(YNAME_FILE_PSFORMAT);
		if (YNULL != pTreePsFormat && YOBJECT_GETCLASSNAME(yam::base::YCFormat) == pTreePsFormat->GetClassName())
		{
			const yam::base::YIFormat* pFormat = (yam::base::YIFormat*)pTreePsFormat;
			reloadFormat(pFormat, NULL, NULL);
		}
	}
	{
		yam::base::YITree* pTreeUiWidget = m_FileTreeData.FindChild(YNAME_FILE_UIWIDGET);
		if (YNULL != pTreeUiWidget && YOBJECT_GETCLASSNAME(yam::base::YCWidget) == pTreeUiWidget->GetClassName())
		{
			const yam::base::YIWidget* pWidget = (yam::base::YIWidget*)pTreeUiWidget;
			reloadWidget(pWidget, NULL, NULL);
		}
	}
}

void YEditor::reloadFormat(const yam::base::YIFormat*& rpFormat, YCQUiItem* pUiParent, QTreeWidgetItem* pTreeParent)
{
	if (YNULL == rpFormat)
	{
		return;
	}

	YCQUiItem* pUiItem = m_UI.formatArea->addChildItem(rpFormat);
	connect(pUiItem, SIGNAL(onPressed(YCQUiItem*)), this, SLOT(onPressedUiItem(YCQUiItem*)));

	QTreeWidgetItem* pTreeItem = new QTreeWidgetItem;
	pTreeItem->setText(0, rpFormat->GetId().c_str());
	if (NULL == pTreeParent)
	{
		m_UI.formatTree->insertTopLevelItem(0, pTreeItem);
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
		reloadFormat(pFormatNext, pUiParent, pTreeParent);
	}

	const yam::base::YITree* pTreeChildren = rpFormat->GetChildren();
	if (YNULL != pTreeChildren && YOBJECT_GETCLASSNAME(yam::base::YCFormat) == pTreeChildren->GetClassName())
	{
		const yam::base::YIFormat* pFormatChildren = (const yam::base::YIFormat*)pTreeChildren;
		reloadFormat(pFormatChildren, pUiItem, pTreeItem);
	}
}

void YEditor::reloadWidget(const yam::base::YIWidget*& rpWidget, YCQUiItem* pUiParent, QTreeWidgetItem* pTreeParent)
{
	//
}

QString YEditor::getFullName(const yam::base::YITree* pTree)
{
	QString sRes = "";
	if (YNULL != pTree)
	{
		sRes.append(".");
		sRes.append(pTree->GetId().c_str());
		sRes.append(getFullName(pTree->GetParent()));
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

QTreeWidgetItem* YEditor::getTreeItem(YCQUiItem* pUiItem) const
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

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	QApplication a(argc, argv);
	YEditor editor;
	editor.setWindowTitle(YEditor::ms_sTitle);
	editor.show();
	return a.exec();
}