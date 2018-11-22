#pragma once

#include <QWidget>

class QLabel;
class QVBoxLayout;
class GLPlaySlider;

class GLMusicInfo : public QWidget
{
	Q_OBJECT

public:
	GLMusicInfo(QWidget *parent);
	~GLMusicInfo();

signals:
	void slider_valchang_signal(int val);

public slots:
	void slider_value_slot(int value);
	void tile_slot(QString title);
	void singer_slot(QString singer);

protected:
	void paintEvent(QPaintEvent *event);

private:
	QLabel *title = nullptr;
	QLabel *singer = nullptr;
	GLPlaySlider *slider = nullptr;
	QVBoxLayout *v_layout = nullptr;
};
