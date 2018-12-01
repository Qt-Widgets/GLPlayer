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
	void progress_changed_signal(int val);		//进度条改变信号
	void progress_move_signal(int val);			//进度条拖动
	void progress_pressed_signal();				//进度条按下

	void volume_changed_signal(int val);		//音量条改变信号
	//void list_clicked_signal();					//列表按钮单击事件
	//void open_clicked_signal();					//打开文件按钮单击事件
	void previous_clicked_signal(QString path);			//上一曲按钮单击事件
	void slower_clicked_signal();						//慢放按钮单击事件
	void play_clicked_signal(QString path);				//播放按钮单击事件
	void stop_clicked_signal();							//停止按钮单击事件
	void faster_clicked_signal();						//快放按钮单击事件
	void next_clicked_signal(QString path);				//下一首按钮单击事件
	//void setting_clicked_signal();			//设置按钮单击事件
	//void expand_clicked_signal();				//全拼按钮单击事件

public slots:
	//void play_time_slot(QString total, QString now);
	void volume_changed_slot(int);
	void update_time_slot(qint64);
	void show_time_out_slot(qint64);

protected:
	//重绘事件
	void paintEvent(QPaintEvent *);

private:
	QString transform_msec(qint64 mss);

	//音视频地址
	QString m_path;

	//时长
	qint64 duration = 0;

	//布局方式
	QVBoxLayout *v_layout = nullptr;
	QHBoxLayout *h_layout = nullptr;

	//进度条
	GLPlaySlider *progress_bar = nullptr;

	//控件
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

	//对话框
	PlayerDialog *color_dialog = nullptr;
	PlayerDialog *vol_dialog = nullptr;
	PlayerDialog *open_file = nullptr;
	PlayerDialog *list_dialog = nullptr;
};
