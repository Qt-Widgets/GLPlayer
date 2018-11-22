#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QBitmap>
#include "GLMusicLogo.h"

GLMusicLogo::GLMusicLogo(QString fileName, QWidget *parent) : QWidget(parent)
{
	tim = new QTimer(this);
	connect(tim, &QTimer::timeout, this, [=]() { update(); });

	resize(120, 120);
	pixPath = fileName;
	pixThumb = QPixmap(pixPath);
	pixThumb = pixThumb.scaled(this->width(), this->height(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
}

GLMusicLogo::~GLMusicLogo()
{
	if (tim)
		delete tim;
}

void GLMusicLogo::play(bool isplay)
{
	if (isplay)
	{
		if (!tim->isActive())
			tim->start(30);
	}
	else
	{
		if (tim->isActive())
			tim->stop();
	}
}

void GLMusicLogo::paintEvent(QPaintEvent *event)
{
	static int i = 0;
	i++;

	QRect drawRect = event->rect();

	//设置遮罩
	QBitmap mask(drawRect.width(), drawRect.height());
	QPainter painter2(&mask);
	painter2.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	painter2.fillRect(drawRect, Qt::white);
	painter2.setBrush(Qt::black);
	painter2.drawEllipse(drawRect);
	pixThumb.setMask(mask);

	//准备绘制
	QPainter painter(this);
	painter.setPen(QColor(255,255,255,0));
	painter.save();
	painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	
	//计算旋转中心轴
	painter.translate(drawRect.width() / 2, drawRect.height() / 2);
	painter.rotate(i);
	//绘制带遮罩的封面
	painter.drawPixmap(-pixThumb.width() / 2, -pixThumb.height() / 2, pixThumb);

	//绘制中心小圆点
	painter.setBrush(painter.background());
	QRect drawRect2 = QRect(-drawRect.adjusted(drawRect.width() / 3 + 10, drawRect.height() / 3 + 10, -drawRect.width() / 3 - 10, -drawRect.height() / 3 - 10).width()/2,
		- drawRect.adjusted(drawRect.width() / 3 + 10, drawRect.height() / 3 + 10, -drawRect.width() / 3 - 10, -drawRect.height() / 3 - 10).height() / 2,
		drawRect.adjusted(drawRect.width() / 3 + 10, drawRect.height() / 3 + 10, -drawRect.width() / 3 - 10, -drawRect.height() / 3 - 10).width(),
		drawRect.adjusted(drawRect.width() / 3 + 10, drawRect.height() / 3 + 10, -drawRect.width() / 3 - 10, -drawRect.height() / 3 - 10).height());
	painter.drawEllipse(drawRect2);

	event->accept();
	painter.restore();

	if (i == 360)
		i = 0;
}

void GLMusicLogo::resizeEvent(QResizeEvent *event)
{
	pixThumb = QPixmap(pixPath);
	pixThumb = pixThumb.scaled(this->width(), this->height(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
	update();
}
