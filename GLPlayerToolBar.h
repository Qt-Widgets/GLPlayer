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
	void progress_changed_signal(int val);	//进度条改变信号
	void volume_changed_signal(int val);	//音量条改变信号
	void list_clicked_signal();				//列表按钮单击事件
	void open_clicked_signal();				//打开文件按钮单击事件
	void previous_clicked_signal();			//上一曲按钮单击事件
	void slower_clicked_signal();			//慢放按钮单击事件
	void play_clicked_signal();				//播放按钮单击事件
	void stop_clicked_signal();				//停止按钮单击事件
	void faster_clicked_signal();			//快放按钮单击事件
	void next_clicked_signal();				//下一首按钮单击事件
	void setting_clicked_signal();			//设置按钮单击事件
	void expand_clicked_signal();			//全拼按钮单击事件

public slots:
	//void play_time_slot(QString total, QString now);

private:
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

};
