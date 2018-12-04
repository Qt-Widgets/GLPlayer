#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QFileInfo>
#include "GLPlayer.h"
#include "GLPlaySlider.h"
#include "GLPlayerToolBar.h"

GLPlayer::GLPlayer(QWidget *parent)
	: QWidget(parent)
{
	setAttribute(Qt::WA_TranslucentBackground);
	setAutoFillBackground(true);
	//setWindowFlags(Qt::FramelessWindowHint);

	this->setWindowTitle(u8"GL Player - 呐，做人呢，最重要的就是开心。");
	this->setMinimumSize(820, 550);
	setAcceptDrops(true);

	m_unit = 1000;
	m_player = new QtAV::AVPlayer(this);
	m_vo = new QtAV::GLWidgetRenderer2(this);
	m_player->setRenderer(m_vo);
	
	v_layout = new QVBoxLayout(this);
	v_layout->setSpacing(0);
	v_layout->setMargin(0);
	/*add widgets code*/
	v_layout->addWidget(m_vo->widget());

	h_layout = new QHBoxLayout;
	tool_bar = new GLPlayerToolBar(this);
	h_layout->addWidget(tool_bar);

	v_layout->setStretchFactor(h_layout, 1);
	v_layout->setStretchFactor(m_vo->widget(), 2);
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
	connect(tool_bar, &GLPlayerToolBar::expand_clicked_signal, this, &GLPlayer::expand_clicked_slot);
}

GLPlayer::~GLPlayer()
{
	if (m_player)
	{
		delete m_player;
		m_player = nullptr;
	}
	if (m_vo)
	{
		delete m_vo;
		m_vo = nullptr;
	}
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

void GLPlayer::next_clicked_slot(QString path)
{
	m_player->play(path);
}

void GLPlayer::slower_clicked_slot()
{
	speed -= 0.5;
	m_player->setSpeed(speed);
}

void GLPlayer::faster_clicked_slot()
{
	speed += 0.5;
	m_player->setSpeed(speed);
}

void GLPlayer::play_clicked_slot(QString path)
{
	QFileInfo info(path);

	switch (m_player->state())
	{
	case QtAV::AVPlayer::StoppedState:
		m_player->play(path);
		this->setWindowTitle(info.fileName());
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
	this->setWindowTitle(u8"GL Player - 呐，做人呢，最重要的就是开心。");
}

void GLPlayer::expand_clicked_slot()
{
	if (!this->isFullScreen())
	{
		size.setWidth(this->width());
		size.setHeight(this->height());
		this->showFullScreen();
		tool_bar->setFullScreen(true);
		h_layout->removeWidget(tool_bar);
		tool_bar->setParent(m_vo->widget());
		tool_bar->show();
	}
	else
	{
		tool_bar->setFullScreen(false);
		h_layout->addWidget(tool_bar);
		tool_bar->setParent(this);
		tool_bar->show();
		this->showNormal();
		this->resize(size);
	}
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

void GLPlayer::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasUrls())
		event->acceptProposedAction();
	else
		event->ignore();
}

void GLPlayer::dropEvent(QDropEvent *event)
{
	const QMimeData *mimeData = event->mimeData();
	if (mimeData->hasUrls())
	{
		QList<QUrl> urlList = mimeData->urls();
		tool_bar->played_slot(urlList.at(0).toLocalFile());
	}
}