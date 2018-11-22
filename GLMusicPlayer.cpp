#include <QVBoxLayout>
#include <QTimer>

#include "GLMusicLogo.h"
#include "GLMusicToolBar.h"
#include "GLMusicInfo.h"
#include "GLMusicPlayer.h"

GLMusicPlayer::GLMusicPlayer(QWidget *parent) : QWidget(parent)
{
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlags(Qt::FramelessWindowHint);

	resize(513, 200);
	setMinimumSize(size());
	setMaximumSize(size());

	timer = new QTimer(this);
	timer->setInterval(100);
	connect(timer, &QTimer::timeout, this, &GLMusicPlayer::Timeout);

	h_layout = new QHBoxLayout;
	info = new GLMusicInfo(this);
	h_layout->addWidget(info);
	h_layout->setSpacing(0);
	h_layout->setContentsMargins(25, topValue, 25, 0);

	v_layout = new QVBoxLayout(this);
	v_layout->setMargin(0);
	v_layout->setSpacing(0);
	v_layout->addLayout(h_layout);

	toolbar = new GLMusicToolBar(this);
	v_layout->addWidget(toolbar);

	setLayout(v_layout);

	logo = new GLMusicLogo(":/images/Resources/music.jpg", this);
	logo->move(40, 50);


	connect(info, &GLMusicInfo::slider_valchang_signal, this, &GLMusicPlayer::music_slider_slot);
	connect(info, &GLMusicInfo::slider_valchang_signal, this, &GLMusicPlayer::music_slider_signal);
	connect(toolbar, &GLMusicToolBar::isPlay, this, &GLMusicPlayer::isPlay);
	connect(toolbar, &GLMusicToolBar::play_signal, this, &GLMusicPlayer::music_play_signal);
	connect(toolbar, &GLMusicToolBar::next_signal, this, &GLMusicPlayer::music_next_signal);
	connect(toolbar, &GLMusicToolBar::previous_signal, this, &GLMusicPlayer::music_previous_signal);
	connect(toolbar, &GLMusicToolBar::list_signal, this, &GLMusicPlayer::music_list_signal);
}

GLMusicPlayer::~GLMusicPlayer()
{
	if (timer)
		delete timer;

	if (info)
		delete info;

	if (toolbar)
		delete toolbar;

	if (logo)
		delete logo;

	if (h_layout)
		delete h_layout; 

	if (v_layout)
		delete v_layout;
}

void GLMusicPlayer::isPlay(bool play)
{
	this->b_isplay = play;
	logo->play(b_isplay);
	if (b_isplay)
	{
		//²¥·Å
		if (!timer->isActive())
			timer->start();
	}
	else
	{
		//ÔÝÍ£
		if (!timer->isActive())
			timer->start();
	}
}

void GLMusicPlayer::Timeout()
{
	if (b_isplay)
	{
		topValue -= 20;
		logoSize += QSize(1, 1);
		if (topValue > 30 )
		{
			h_layout->setContentsMargins(25, topValue, 25, 0);
			logo->update();

			if (logo->width() != 130)
			{
				logo->resize(logoSize);
				logoSize = QSize(130, 130);
			}
		}
		else
		{
			if (timer->isActive())
				timer->stop();
			topValue = 30;
		}
	}
	else
	{
		topValue += 20;
		logoSize -= QSize(1, 1);
		if (topValue < 140)
		{
			h_layout->setContentsMargins(25, topValue, 25, 0);
			logo->update();

			if (logo->width() != 120)
			{
				logo->resize(logoSize);
				logoSize = QSize(120, 120);
			}
		}
		else
		{
			if (timer->isActive())
				timer->stop();
			topValue = 140;
		}
	}
}

void GLMusicPlayer::music_title_slot(QString title)
{
	info->tile_slot(title);
}

void GLMusicPlayer::music_singer_slot(QString singer)
{
	info->singer_slot(singer);
}

void GLMusicPlayer::music_slider_slot(int value)
{
	info->slider_value_slot(value);
}

