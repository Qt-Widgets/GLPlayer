#pragma once
#include <QWidget>
#include <QMap>
#include <QList>
#include "ListItemWidget.h"

class QListWidget;
class QHBoxLayout;
class QVBoxLayout;
class QPushButton;
class QFileInfo;
class QListWidgetItem;
class GLLabelButton;

class PlayerListDialog : public QWidget
{
	Q_OBJECT

public:
	PlayerListDialog(QWidget *parent = nullptr);
	~PlayerListDialog();

protected:
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);

signals:
	void start_play_signals(QString path,PlayList::VideoType type);

public slots:
	void add_item_slot();		//����ļ�
	void del_item_slot();		//ɾ���ļ�
	void next_play_slot();		//��һ��
	void previous_play_slot();	//��һ��
	void stop_slot();			//ֹͣ
	void add_list_item(QString path);//���
	void item_double_clicked(QListWidgetItem *item);
	
private:
	QList<QFileInfo> GetFileList(QString path);

	QString video;
	QString audio;

	QListWidget *list_widget = nullptr;
	QHBoxLayout *h_layout = nullptr;
	QHBoxLayout *btn_layout = nullptr;
	QHBoxLayout *btn_layout2 = nullptr;
	QVBoxLayout *v_layout = nullptr;
	GLLabelButton *add_item = nullptr;
	GLLabelButton *del_item = nullptr;
	GLLabelButton *loca = nullptr;

	QListWidgetItem *m_current = nullptr;

	QMap<QListWidgetItem*, ListItemWidget*> items;
};
