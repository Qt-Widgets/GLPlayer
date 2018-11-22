#pragma once

#include <QWidget>

class GLMusicLogo : public QWidget
{
	Q_OBJECT

public:
	GLMusicLogo(QString fileName, QWidget *parent = nullptr);
	~GLMusicLogo();
	void play(bool);

protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);

private:
	QTimer *tim = nullptr;
	QString pixPath;
	QPixmap pixThumb;
};
