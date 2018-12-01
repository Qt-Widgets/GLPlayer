#pragma once
#include <QWidget>
#include <QTimer>

class QVBoxLayout;
class QHBoxLayout;
class GLPlaySlider;
class GLLabelButton;
class PlayerDialog;
class PlayerListDialog;

class GLPlayerToolBar : public QWidget
{
	Q_OBJECT

public:
	GLPlayerToolBar(QWidget *parent = nullptr);
	~GLPlayerToolBar();
	inline GLPlaySlider* getSlider()
	{
		return this->progress_bar;
	}
signals:
	void progress_changed_signal(int val);		//�������ı��ź�
	void progress_move_signal(int val);			//�������϶�
	void progress_pressed_signal();				//����������

	void volume_changed_signal(int val);		//�������ı��ź�
	//void list_clicked_signal();					//�б�ť�����¼�
	//void open_clicked_signal();					//���ļ���ť�����¼�
	void previous_clicked_signal(QString path);			//��һ����ť�����¼�
	void slower_clicked_signal();						//���Ű�ť�����¼�
	void play_clicked_signal(QString path);				//���Ű�ť�����¼�
	void stop_clicked_signal();							//ֹͣ��ť�����¼�
	void faster_clicked_signal();						//��Ű�ť�����¼�
	void next_clicked_signal(QString path);				//��һ�װ�ť�����¼�
	//void setting_clicked_signal();			//���ð�ť�����¼�
	//void expand_clicked_signal();				//ȫƴ��ť�����¼�

public slots:
	//void play_time_slot(QString total, QString now);
	void volume_changed_slot(int);
	void update_time_slot(qint64);
	void show_time_out_slot(qint64);

protected:
	//�ػ��¼�
	void paintEvent(QPaintEvent *);

private:
	QString transform_msec(qint64 mss);

	//����Ƶ��ַ
	QString m_path;

	//ʱ��
	qint64 duration = 0;

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
	PlayerDialog *list_dialog = nullptr;
};
