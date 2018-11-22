#include <QPainter>
#include <QHBoxLayout>
#include "GLLabelButton.h"
#include "GLMusicToolBar.h"


GLMusicToolBar::GLMusicToolBar(QWidget *parent) : QWidget(parent)
{
	resize(parent->width(), 0);

	h_layout = new QHBoxLayout(this);

	btn_previous = new GLLabelButton(LabelButtonType::PREVIOUS, this, 25);
	btn_play = new GLLabelButton(LabelButtonType::PLAY, this, 25);
	btn_next = new GLLabelButton(LabelButtonType::NETXT, this, 25);
	btn_list = new GLLabelButton(LabelButtonType::LIST, this, 25);

	h_layout->addStretch();
	h_layout->addWidget(btn_previous);
	h_layout->addWidget(btn_play);
	h_layout->addWidget(btn_next);
	h_layout->addStretch();
	h_layout->addWidget(btn_list);

	h_layout->setContentsMargins(100, 20, 40, 20);
	this->setLayout(h_layout);

	connect(btn_play, &GLLabelButton::clicked, this, [=]() { 
		bool bplay = false;
		switch (btn_play->getType())
		{
		case LabelButtonType::PLAY:
			bplay = true;
			btn_play->setType(LabelButtonType::PUSE,25);
			break;
		case LabelButtonType::PUSE:
			bplay = false;
			btn_play->setType(LabelButtonType::PLAY,25);
			break;
		}
		emit isPlay(bplay);

	});

	connect(btn_play, &GLLabelButton::clicked, this, &GLMusicToolBar::play_signal);
	connect(btn_list, &GLLabelButton::clicked, this, &GLMusicToolBar::list_signal);
	connect(btn_next, &GLLabelButton::clicked, this, &GLMusicToolBar::next_signal);
	connect(btn_previous, &GLLabelButton::clicked, this, &GLMusicToolBar::previous_signal);
}

GLMusicToolBar::~GLMusicToolBar()
{
	if (btn_previous)
		delete btn_previous;

	if (btn_play)
		delete btn_play;

	if (btn_next)
		delete btn_next;

	if (btn_list)
		delete btn_list;

	if (h_layout)
		delete h_layout;
}

void GLMusicToolBar::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);  // ·´¾â³Ý;
	painter.setBrush(QColor(254, 253, 253));
	painter.setPen(Qt::transparent);
	QRect rect = this->rect();
	rect.setWidth(rect.width() - 1);
	rect.setHeight(rect.height() - 1);
	painter.drawRoundedRect(rect, 15, 15);
	QWidget::paintEvent(event);
}