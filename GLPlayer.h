#pragma once
#include <QWidget>
#include <QtAV/QtAV>
#include <QtAVWidgets/WidgetRenderer.h>

class QVBoxLayout;
class QHBoxLayout;
class GLPlayerToolBar;

class GLPlayer : public QWidget
{
	Q_OBJECT

public:
	GLPlayer(QWidget *parent = Q_NULLPTR);
	~GLPlayer();

signals:
	void volume_change_signal(int);

public slots:
	//��ť�¼�
	void volume_changed_slot(int val);			//�������ı��ź�
	void previous_clicked_slot(QString path);	//��һ����ť�����¼�
	void slower_clicked_slot();					//���Ű�ť�����¼�
	void play_clicked_slot(QString path);		//���Ű�ť�����¼�
	void stop_clicked_slot();					//ֹͣ��ť�����¼�
	void faster_clicked_slot();					//��Ű�ť�����¼�
	void next_clicked_slot(QString path);		//��һ�װ�ť�����¼�
	void expand_clicked_slot();
	//���ƽ�����
	void progress_move_slot(int val);			//�϶�������
	void progress_move_slot();					//�϶�������
	void progress_changed_slot(int val);		//�������ı��ź�
	//���½�����
	void update_slider(qint64 value);
	void update_slider();
	void update_slider_unit();

private:
	QVBoxLayout *v_layout = nullptr;
	QHBoxLayout *h_layout = nullptr;
	GLPlayerToolBar *tool_bar = nullptr;

	QtAV::WidgetRenderer *m_vo = nullptr;
	QtAV::AVPlayer *m_player = nullptr;
	int m_unit = 0;
	int m_slider_value = 0;
	double speed = 0;
};
