#pragma once
#include <QWidget>
#include <QtAV/QtAV>

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
	void volume_changed_slot(int val);			//音量条改变信号
	void previous_clicked_slot(QString path);	//上一曲按钮单击事件
	void slower_clicked_slot();					//慢放按钮单击事件
	void play_clicked_slot(QString path);		//播放按钮单击事件
	void stop_clicked_slot();					//停止按钮单击事件
	void faster_clicked_slot();					//快放按钮单击事件
	void next_clicked_slot(QString path);		//下一首按钮单击事件
	//控制进度条
	void progress_move_slot(int val);			//拖动进度条
	void progress_move_slot();					//拖动进度条
	void progress_changed_slot(int val);		//进度条改变信号
	//更新进度条
	void update_slider(qint64 value);
	void update_slider();
	void update_slider_unit();

private:
	QVBoxLayout *v_layout = nullptr;
	QHBoxLayout *h_layout = nullptr;
	GLPlayerToolBar *tool_bar = nullptr;

	QtAV::VideoOutput *m_vo;
	QtAV::AVPlayer *m_player;
	int m_unit;
	int m_slider_value;
	double speed = 0;
};
