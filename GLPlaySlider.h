#pragma once
#include <QSlider>
#include <QStringList>

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

private:
	Qt::Orientation orientation;
	QStringList v_qss;
	QStringList h_qss;
};

