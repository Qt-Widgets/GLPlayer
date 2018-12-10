#pragma once
#include <QSlider>
#include <QStringList>
#include <QCoreApplication>

using _super = QSlider;

class GLPlaySlider : public _super
{
	Q_OBJECT

public:
	GLPlaySlider(Qt::Orientation, QWidget *parent = Q_NULLPTR);

	//�ı����slider��ɫ
	void change_horizontal_color(QString stop0 = "E750E5", QString stop1 = "07D0FF");
	//�ı�����slider��ɫ
	void change_vertical_color(QString add_page = "FF4500");

protected:
	void mousePressEvent(QMouseEvent *ev);

signals:
	void progress_clicked_signal(int value);

private:
	Qt::Orientation orientation;
	QStringList v_qss;
	QStringList h_qss;
};

