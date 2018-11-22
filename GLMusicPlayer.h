#pragma once

#include <QWidget>

class QTimer;
class QHBoxLayout;
class QVBoxLayout;
class GLMusicLogo;
class GLMusicToolBar;
class GLMusicInfo;

class GLMusicPlayer : public QWidget
{
	Q_OBJECT

public:
	GLMusicPlayer(QWidget *parent = nullptr);
	~GLMusicPlayer();

public slots:
	void isPlay(bool);
	void Timeout();

	void music_title_slot(QString title);
	void music_singer_slot(QString singer);
	void music_slider_slot(int value);

signals:
	void music_play_signal();
	void music_next_signal();
	void music_previous_signal();
	void music_list_signal();
	void music_slider_signal(int val);
	
private:
	QHBoxLayout *h_layout = nullptr;
	QVBoxLayout *v_layout = nullptr;
	GLMusicLogo *logo = nullptr;
	GLMusicToolBar *toolbar = nullptr;
	GLMusicInfo *info = nullptr;

	QTimer *timer = nullptr;
	bool b_isplay = false;
	int rotateValue = 0;
	int topValue = 140;	//140Òþ²Ø£¬£¬30ÏÔÊ¾
	QSize logoSize = QSize(120, 120);
};
