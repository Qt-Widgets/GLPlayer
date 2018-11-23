#pragma once
#include <QWidget>

class QVBoxLayout;
class QHBoxLayout;
class GLLabelButton;
class GLPlaySlider;
class PlayerDialog;

class GLPlayerToolBar : public QWidget
{
	Q_OBJECT

public:
	GLPlayerToolBar(QWidget *parent = nullptr);
	~GLPlayerToolBar();

signals:
	void progress_changed_signal(int val);	//�������ı��ź�
	void volume_changed_signal(int val);	//�������ı��ź�
	void list_clicked_signal();				//�б�ť�����¼�
	void open_clicked_signal();				//���ļ���ť�����¼�
	void previous_clicked_signal();			//��һ����ť�����¼�
	void slower_clicked_signal();			//���Ű�ť�����¼�
	void play_clicked_signal();				//���Ű�ť�����¼�
	void stop_clicked_signal();				//ֹͣ��ť�����¼�
	void faster_clicked_signal();			//��Ű�ť�����¼�
	void next_clicked_signal();				//��һ�װ�ť�����¼�
	void setting_clicked_signal();			//���ð�ť�����¼�
	void expand_clicked_signal();			//ȫƴ��ť�����¼�

public slots:
	//void play_time_slot(QString total, QString now);

private:
	//���ַ�ʽ
	QVBoxLayout *v_layout = nullptr;
	QHBoxLayout *h_layout = nullptr;

	//������
	GLPlaySlider *progress_bar = nullptr;

	//�ؼ�
	GLLabelButton *lab_time = nullptr;
	GLLabelButton *btn_list = nullptr;
	GLLabelButton *btn_open = nullptr;
	GLLabelButton *btn_previous = nullptr;
	GLLabelButton *btn_slower = nullptr;
	GLLabelButton *btn_play = nullptr;
	GLLabelButton *btn_stop = nullptr;
	GLLabelButton *btn_faster = nullptr;
	GLLabelButton *btn_next = nullptr;
	GLLabelButton *btn_setting = nullptr;
	GLLabelButton *btn_volume = nullptr;
	GLLabelButton *btn_expand = nullptr;
	GLLabelButton *btn_dropper = nullptr;

	//�Ի���
	PlayerDialog *color_dialog = nullptr;
	PlayerDialog *vol_dialog = nullptr;
	PlayerDialog *open_file = nullptr;

};
