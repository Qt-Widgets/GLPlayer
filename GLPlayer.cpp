#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QFileInfo>
#include <QFileDialog>
#include <QTimer>
#include <QMouseEvent>
#include <QMoveEvent>
#include <QKeyEvent>
#include "GLPlayer.h"
#include "GLPlaySlider.h"
#include "GLPlayerToolBar.h"

#include <QDebug>

GLPlayer::GLPlayer(QWidget *parent) : QWidget(parent)
{
	setAttribute(Qt::WA_TranslucentBackground);
	setAutoFillBackground(true);
	//setWindowFlags(Qt::FramelessWindowHint);

	this->setWindowTitle(u8"GL Player - 呐，做人呢，最重要的就是开心。");
	this->setMinimumSize(1100, 620);
	setAcceptDrops(true);
	setMouseTracking(true);

	m_unit = 1000;
	m_player = new QtAV::AVPlayer(this);
	m_vo = new QtAV::GLWidgetRenderer2(this);
	//play_subtitle = new QtAV::PlayerSubtitle(this);
	///play_subtitle->setPlayer(m_player);
	m_player->setRenderer(m_vo);
	m_vo->setMouseTracking(true);

	v_layout = new QVBoxLayout(this);
	v_layout->setSpacing(0);
	v_layout->setMargin(0);
	/*add widgets code*/
	v_layout->addWidget(m_vo->widget());

	h_layout = new QHBoxLayout;
	tool_bar = new GLPlayerToolBar(this);
	tool_bar->setMouseTracking(true);
	h_layout->addWidget(tool_bar);

	v_layout->setStretchFactor(h_layout, 1);
	v_layout->setStretchFactor(m_vo->widget(), 2);
	v_layout->addLayout(h_layout);
	setLayout(v_layout);

	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &GLPlayer::time_out);
	timer->setInterval(3000);

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

	connect(tool_bar, &GLPlayerToolBar::setting_clicked_signal, this, [=]() 
	{
		//QString subtitle_file = QFileDialog::getOpenFileName(this, u8"选择字幕文件", "/");
		//if (m_player->isPlaying())
			//play_subtitle->setFile(subtitle_file);
	});

	connect(tool_bar, &GLPlayerToolBar::progress_clicked_signal, this, [=](int val) 
	{
		if (m_player->isPlaying())
			m_player->seek(qint64(val*m_unit));
	});
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
	if (timer)
	{
		delete timer;
		timer = nullptr;
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
	if (m_player->isPlaying())
		m_player->seek(m_player->position() - 10000);
}

void GLPlayer::faster_clicked_slot()
{
	if (m_player->isPlaying())
		m_player->seek(m_player->position() + 10000);
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
		if (!timer->isActive())
			timer->start();
	}
	else
	{
		tool_bar->setFullScreen(false);
		h_layout->addWidget(tool_bar);
		tool_bar->setParent(this);
		tool_bar->show();
		this->showNormal();
		this->resize(size);
		if (timer->isActive())
			timer->stop();
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

void GLPlayer::time_out()
{
	if (this->isFullScreen())
	{
		this->setCursor(Qt::BlankCursor);
		if (tool_bar->isVisible())
			tool_bar->hide();
	}
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

void GLPlayer::mouseMoveEvent(QMouseEvent *event)
{
	this->setCursor(Qt::ArrowCursor);
	QPoint point = event->pos();

	if (point.y() > tool_bar->y())
	{
		if (!tool_bar->isVisible())
			tool_bar->show();
		if (timer->isActive())
			timer->stop();
	}
	else
	{
		if (!timer->isActive())
			timer->start();
	}
}

void GLPlayer::moveEvent(QMoveEvent *event)
{
	tool_bar->move_event(event);
}

void GLPlayer::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key::Key_Escape:
		if (this->isFullScreen())
			expand_clicked_slot();
		else
		{
			this->showMinimized();
			switch (m_player->state())
			{
			case QtAV::AVPlayer::PlayingState:
				m_player->pause(true);
				tool_bar->toggle_pause();
				break;
			}
		}
		break;
	case Qt::Key::Key_Space:
		if (m_player->isPaused())
		{
			m_player->pause(false);
			tool_bar->toggle_pause();
		}
		else
		{
			m_player->pause();
			tool_bar->toggle_pause();
		}
		break;
	case Qt::Key::Key_Left:
		slower_clicked_slot();
		break;
	case Qt::Key::Key_Right:
		faster_clicked_slot();
		break;
	case Qt::Key::Key_Up:
		break;
	case Qt::Key::Key_Down:
		break;
	}

	QWidget::keyPressEvent(event);
	event->accept();
}

void GLPlayer::mouseDoubleClickEvent(QMouseEvent *event)
{
	expand_clicked_slot();
}

