#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include "PlayerListDialog.h"

PlayerListDialog::PlayerListDialog(QWidget *parent)
	: QWidget(parent)
{
	setAcceptDrops(true);
}

PlayerListDialog::~PlayerListDialog()
{
}

void PlayerListDialog::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasUrls())//数据是否包含URls
		event->acceptProposedAction();//接收动作
	else
		event->ignore();//忽略事件
}

void PlayerListDialog::dropEvent(QDropEvent *event)
{
	const QMimeData *mimeData = event->mimeData();//获取mimie数据
	if (mimeData->hasUrls())
	{
		QList<QUrl> urlList = mimeData->urls();//获取url列表
		QString fileName = urlList.at(0).toLocalFile();//将第一个URL作为本地文件路径
	}
}