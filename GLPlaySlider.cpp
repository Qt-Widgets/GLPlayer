#include <QFile>
#include <QLabel>
#include "GLPlaySlider.h"
#include "IconFontHelper.h"

GLPlaySlider::GLPlaySlider(Qt::Orientation orientation,QWidget *parent)
	:_super(orientation,parent)
{
	this->orientation = orientation;

	v_qss << "QSlider::groove:vertical{background:transparent;width:13px;}"
		<< "QSlider::sub-page:vertical{background-color: #57616A;}"
		<< "QSlider::add-page:vertical{background-color: %1;}"
		<< "QSlider::handle:vertical{height:13px;background:qradialgradient(spread : pad, cx : 0.5, cy : 0.5, radius : 0.5, fx : 0.5, fy : 0.5, stop : 0.6#FFFFFF, stop:0.8 #FFFFFF);}";

	h_qss << "QSlider::groove:horizontal,QSlider::add-page:horizontal{height:18px;background:transparent;}"
		<< "QSlider::sub-page:horizontal{background-color:qlineargradient(spread : pad, x1 : 0, y1 : 0, x2 : 1, y2 : 0, stop : 0 %1, stop : 1 %2);height:4px;}"
		<< "QSlider::handle:horizontal{width:13px;background:qradialgradient(spread : pad, cx : 0.5, cy : 0.5, radius : 0.5, fx : 0.5, fy : 0.5, stop : 0.6#FFFFFF, stop:0.8 #FFFFFF);}";

	switch (orientation)
	{
	case Qt::Horizontal:
		setStyleSheet(h_qss.join("").arg("#E750E5").arg("#07D0FF"));
		break;
	case Qt::Vertical:
		setStyleSheet(v_qss.join("").arg("#000000"));
		break;
	}

}

void GLPlaySlider::change_horizontal_color(QString stop0, QString stop1)
{
	switch (this->orientation)
	{
	case Qt::Horizontal:
		setStyleSheet(h_qss.join("").arg(stop0).arg(stop1));
		break;
	}
}

void GLPlaySlider::change_vertical_color(QString add_page)
{
	switch (this->orientation)
	{
	case Qt::Vertical:
		setStyleSheet(v_qss.join("").arg(add_page));
		break;
	}
}

