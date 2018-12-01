#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "GLPlayer.h"
#include "GLPlaySlider.h"
#include "GLPlayerToolBar.h"

GLPlayer::GLPlayer(QWidget *parent)
	: QWidget(parent)
{
	setAttribute(Qt::WA_TranslucentBackground);
	setAutoFillBackground(true);
	setWindowFlags(Qt::FramelessWindowHint);
	
	this->setMinimumSize(820, 550);

	m_unit = 1000;
	m_player = new QtAV::AVPlayer(this);
	m_vo = new QtAV::VideoOutput(this);
	m_player->setRenderer(m_vo);

	v_layout = new QVBoxLayout(this);
	v_layout->setSpacing(0);
	v_layout->setMargin(0);
	/*add widgets code*/
	/*QLabel *lab = new QLabel(this);
	lab->setStyleSheet("QLabel{border:2px solid #000000;}");*/
	v_layout->addWidget(m_vo->widget());

	h_layout = new QHBoxLayout;
	/*add widgets code*/
	tool_bar = new GLPlayerToolBar(this);
	h_layout->addWidget(tool_bar);

	v_layout->setStretchFactor(m_vo->widget(), 1);
	v_layout->setStretchFactor(tool_bar, 2);
	v_layout->addLayout(h_layout);
	setLayout(v_layout);

	connect(tool_bar, &GLPlayerToolBar::progress_changed_signal, this, &GLPlayer::progress_changed_slot);
	connect(tool_bar, &GLPlayerToolBar::volume_changed_signal, this, &GLPlayer::volume_changed_slot);
	connect(tool_bar, &GLPlayerToolBar::previous_clicked_signal, this, &GLPlayer::previous_clicked_slot);
	connect(tool_bar, &GLPlayerToolBar::slower_clicked_signal, this, &GLPlayer::slower_clicked_slot);
	connect(tool_bar, &GLPlayerToolBar::play_clicked_signal, this, &GLPlayer::play_clicked_slot);
	connect(tool_bar, &GLPlayerToolBar::stop_clicked_signal, this, &GLPlayer::stop_clicked_slot);
	connect(tool_bar, &GLPlayerToolBar::faster_clicked_signal, this, &GLPlayer::faster_clicked_slot);
	connect(tool_bar, &GLPlayerToolBar::next_clicked_signal, this, &GLPlayer::next_clicked_slot);
	connect(m_player, &QtAV::AVPlayer::notifyIntervalChanged,this, &GLPlayer::update_slider_unit);
	connect(m_player, &QtAV::AVPlayer::positionChanged, tool_bar, &GLPlayerToolBar::update_time_slot);
	connect(m_player, &QtAV::AVPlayer::durationChanged, tool_bar, &GLPlayerToolBar::show_time_out_slot);
	connect(this, &GLPlayer::volume_change_signal, tool_bar, &GLPlayerToolBar::volume_changed_slot);
	connect(tool_bar, SIGNAL(progress_move_signal(int)), this, SLOT(progress_move_slot(int)));
	connect(tool_bar, SIGNAL(progress_pressed_signal()), this, SLOT(progress_move_slot()));
	connect(m_player, SIGNAL(positionChanged(qint64)), SLOT(update_slider(qint64)));
	connect(m_player, SIGNAL(started()), SLOT(update_slider()));
}

GLPlayer::~GLPlayer()
{
	if (tool_bar)
	{
		delete tool_bar;
		tool_bar = nullptr;
	}

	if (h_layout)
	{
		delete h_layout;
		h_layout = nullptr;
	}

	if (v_layout)
	{
		delete v_layout;
		v_layout = nullptr;
	}
}

void GLPlayer::volume_changed_slot(int val)
{
	m_player->audio()->setVolume(val);
}

void GLPlayer::previous_clicked_slot(QString path)
{
	m_player->play(path);
}

void GLPlayer::slower_clicked_slot()
{
	if (speed > 0.5)
		speed -= 0.5;
	m_player->setSpeed(speed);
}

void GLPlayer::play_clicked_slot(QString path)
{
	switch (m_player->state())
	{
	case QtAV::AVPlayer::StoppedState:
		m_player->play(path);
		emit volume_change_signal(m_player->audio()->volume());
		break;
	case QtAV::AVPlayer::PlayingState:
			m_player->pause(true);
		break;
	case QtAV::AVPlayer::PausedState:
			m_player->pause(false);
		break;
	}
}

void GLPlayer::stop_clicked_slot()
{
	if (m_player)
		m_player->stop();
}

void GLPlayer::faster_clicked_slot()
{
	speed += 0.5;
	m_player->setSpeed(speed);
}

void GLPlayer::next_clicked_slot(QString path)
{
	m_player->play(path);
}

void GLPlayer::progress_move_slot(int val)
{
	if (!m_player->isPlaying())
		return;
	m_player->seek(qint64(val*m_unit));
}

void GLPlayer::progress_move_slot()
{
	progress_move_slot(m_slider_value);
}

void GLPlayer::progress_changed_slot(int val)
{
	m_slider_value = val;
}

void GLPlayer::update_slider(qint64 value)
{
	tool_bar->getSlider()->setRange(0, int(m_player->duration() / m_unit));
	tool_bar->getSlider()->setValue(int(value / m_unit));
}

void GLPlayer::update_slider()
{
	update_slider(m_player->position());
}

void GLPlayer::update_slider_unit()
{
	m_unit = m_player->notifyInterval();
	update_slider();
}
