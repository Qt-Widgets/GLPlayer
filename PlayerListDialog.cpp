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
	if (event->mimeData()->hasUrls())//�����Ƿ����URls
		event->acceptProposedAction();//���ն���
	else
		event->ignore();//�����¼�
}

void PlayerListDialog::dropEvent(QDropEvent *event)
{
	const QMimeData *mimeData = event->mimeData();//��ȡmimie����
	if (mimeData->hasUrls())
	{
		QList<QUrl> urlList = mimeData->urls();//��ȡurl�б�
		QString fileName = urlList.at(0).toLocalFile();//����һ��URL��Ϊ�����ļ�·��
	}
}