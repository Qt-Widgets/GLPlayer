#pragma once

#include <QWidget>

class QHBoxLayout;
class GLLabelButton;

class GLMusicToolBar : public QWidget
{
	Q_OBJECT

public:
	GLMusicToolBar(QWidget *parent);
	~GLMusicToolBar();

signals:
	void isPlay(bool);
	void play_signal();
	void next_signal();
	void previous_signal();
	void list_signal();

protected:
	void paintEvent(QPaintEvent *event);

private:
	QHBoxLayout *h_layout = nullptr;
	GLLabelButton *btn_previous = nullptr;
	GLLabelButton *btn_play = nullptr;
	GLLabelButton *btn_next = nullptr;
	GLLabelButton *btn_list = nullptr;
};
