#include <QLabel>
#include <QVBoxLayout>
#include <QPainter>
#include "GLPlaySlider.h"
#include "GLMusicInfo.h"

GLMusicInfo::GLMusicInfo(QWidget *parent) : QWidget(parent)
{
	resize(parent->width(), 0);
	setMaximumHeight(80);

	v_layout = new QVBoxLayout(this);
	v_layout->setContentsMargins(158, 0, 20, 0);
	v_layout->setSpacing(0);

	title = new QLabel(this);
	title->setText("Flume");
	singer = new QLabel(this);
	singer->setText("Say it");
	slider = new GLPlaySlider(Qt::Horizontal, this);
	slider->resize(slider->width(), 20);

	v_layout->addStretch();
	v_layout->addWidget(title);
	v_layout->addWidget(singer);
	v_layout->addStretch();
	v_layout->addWidget(slider);

	setLayout(v_layout);

	connect(slider, &GLPlaySlider::valueChanged, this, &GLMusicInfo::slider_value_slot);
	connect(slider, &GLPlaySlider::valueChanged, this, &GLMusicInfo::slider_valchang_signal);
}

GLMusicInfo::~GLMusicInfo()
{
	if (title)
		delete title;

	if (singer)
		delete singer;

	if (slider)
		delete slider;

	if (v_layout)
		delete v_layout;
}

void GLMusicInfo::slider_value_slot(int value)
{
	slider->setValue(value);
}

void GLMusicInfo::tile_slot(QString title)
{
	this->title->setText(title);
}

void GLMusicInfo::singer_slot(QString singer)
{
	this->singer->setText(singer);
}

void GLMusicInfo::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(QColor(216, 234, 244, 200));
	painter.setPen(Qt::transparent);
	QRect rect = this->rect();
	rect.setWidth(rect.width() - 1);
	rect.setHeight(rect.height() - 1);
	painter.drawRoundedRect(rect, 7, 7);
	QWidget::paintEvent(event);
}

