#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QPaintEvent>
#include "GLPlaySlider.h"
#include "GLLabelButton.h"
#include "PlayerDialog.h"
#include "GLPlayerToolBar.h"
#include "PlayerListDialog.h"
#include "ListItemWidget.h"
#include "GLLabelButton.h"

GLPlayerToolBar::GLPlayerToolBar(QWidget *parent) : QWidget(parent)
{
	v_layout = new QVBoxLayout(this);
	v_layout->setSpacing(0);
	v_layout->setMargin(0);

	/*add widgets code*/
	progress_bar = new GLPlaySlider(Qt::Orientation::Horizontal, this);
	v_layout->addWidget(progress_bar);

	h_layout = new QHBoxLayout;
	
	//按钮控件
	lab_time = new GLLabelButton(LabelButtonType::LABEL, this,12);
	lab_time->setText(QString("%1/%2").arg("00:00:00").arg("00:00:00"));
	lab_time->setMinimumWidth(105);

	btn_list = new GLLabelButton(LabelButtonType::LIST, this);
	btn_open = new GLLabelButton(LabelButtonType::OPEN, this);
	btn_previous = new GLLabelButton(LabelButtonType::PREVIOUS, this);
	btn_slower = new GLLabelButton(LabelButtonType::SLOWER, this);
	btn_play = new GLLabelButton(LabelButtonType::PLAY, this);
	btn_stop = new GLLabelButton(LabelButtonType::STOP, this);
	btn_faster = new GLLabelButton(LabelButtonType::FASTER, this);
	btn_next = new GLLabelButton(LabelButtonType::NETXT, this);
	//btn_setting = new GLLabelButton(LabelButtonType::SETTING, this);
	btn_volume = new GLLabelButton(LabelButtonType::VOL_DOWN, this);
	btn_expand = new GLLabelButton(LabelButtonType::EXPAND, this);
	btn_dropper = new GLLabelButton(LabelButtonType::DROPPER, this);

	h_layout->addWidget(lab_time);
	h_layout->addWidget(btn_list);
	h_layout->addWidget(btn_open);
	h_layout->addStretch();
	h_layout->addWidget(btn_previous);
	h_layout->addWidget(btn_slower);
	h_layout->addWidget(btn_play);
	h_layout->addWidget(btn_stop);
	h_layout->addWidget(btn_faster);
	h_layout->addWidget(btn_next);
	h_layout->addStretch();
	h_layout->addWidget(btn_dropper);
	//h_layout->addWidget(btn_setting);
	h_layout->addWidget(btn_volume);
	h_layout->addWidget(btn_expand);
	h_layout->setContentsMargins(10, 0, 10, 0);
	h_layout->setSpacing(0);

	v_layout->addLayout(h_layout);
	setLayout(v_layout);

	//实例化各种对话框
	color_dialog = new PlayerDialog(DialogType::COLOR, this);
	vol_dialog = new PlayerDialog(DialogType::VOL, this);
	open_file = new PlayerDialog(DialogType::FILE, this);
	list_dialog = new PlayerDialog(DialogType::LIST, this);

	//链接信号和槽
	//列表相关
	connect(btn_next, &GLLabelButton::clicked, list_dialog, &PlayerDialog::next_play_signal);
	connect(btn_previous, &GLLabelButton::clicked, list_dialog, &PlayerDialog::previous_play_signal);
	connect(btn_stop, &GLLabelButton::clicked, list_dialog, &PlayerDialog::stop_signal);
	//播放信号
	connect(btn_next, &GLLabelButton::clicked, this, [=]() { emit next_clicked_signal(m_path); });
	connect(btn_previous, &GLLabelButton::clicked, this, [=]() { emit previous_clicked_signal(m_path); });
	connect(btn_faster, &GLLabelButton::clicked, this, &GLPlayerToolBar::faster_clicked_signal);
	connect(btn_slower, &GLLabelButton::clicked, this, &GLPlayerToolBar::slower_clicked_signal);

	connect(progress_bar, &GLPlaySlider::valueChanged, this, &GLPlayerToolBar::progress_changed_signal);
	connect(progress_bar, &GLPlaySlider::sliderMoved, this, &GLPlayerToolBar::progress_move_signal);
	connect(progress_bar, &GLPlaySlider::sliderPressed, this, &GLPlayerToolBar::progress_pressed_signal);

	connect(btn_expand, &GLLabelButton::clicked, this, &GLPlayerToolBar::expand_clicked_signal);

	connect(open_file, &PlayerDialog::file_select_signal, this, [=](QString path, bool isLoca, bool isVideo)
	{
		if (open_file->isVisible())
			open_file->close();
		
		btn_play->setType(LabelButtonType::PUSE);
		m_path = path;
		emit stop_clicked_signal();
		emit play_clicked_signal(path);
	});

	//当列表双发出播放信号时
	connect(list_dialog, &PlayerDialog::start_signal, this, [=](QString path, PlayList::VideoType type)
	{
		this->m_path = path;
		switch (type)
		{
		case PlayList::VIDEO:
			btn_play->setType(LabelButtonType::PUSE);
			break;
		case PlayList::AUDIO:
			break;
		}

		emit stop_clicked_signal();
		emit play_clicked_signal(m_path);
	});

	//色盘选择器单击事件
	connect(btn_dropper, &GLLabelButton::clicked, this, [=]() 
	{
		if (color_dialog && !color_dialog->isVisible())
		{
			QPoint point = QPoint(this->mapToGlobal(btn_dropper->pos()).x() - color_dialog->width() / 2, this->mapToGlobal(btn_dropper->pos()).y() - color_dialog->height());
			color_dialog->move(point);
			color_dialog->show();
			color_dialog->setFocus();
		}
		else
			color_dialog->hide();
		
		connect(color_dialog, &PlayerDialog::color_changed_signal, lab_time, &GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::color_changed_signal, btn_dropper, &GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::color_changed_signal, btn_expand,&GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::color_changed_signal, btn_volume,&GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::color_changed_signal, btn_setting,&GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::color_changed_signal, btn_next,&GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::color_changed_signal, btn_faster,&GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::color_changed_signal, btn_stop,&GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::color_changed_signal, btn_play,&GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::color_changed_signal, btn_slower,&GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::color_changed_signal, btn_previous,&GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::color_changed_signal, btn_open,&GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::color_changed_signal, btn_list,&GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::color_changed_signal, vol_dialog, &PlayerDialog::volColorChangedSlot);

	});

	//停止按钮
	connect(btn_stop, &GLLabelButton::clicked, this, [=]()
	{
		if (btn_play->getType() == LabelButtonType::PUSE)
			btn_play->setType(LabelButtonType::PLAY);
		progress_bar->setValue(0);
		lab_time->setText(QString("%1/%2").arg("00:00:00").arg("00:00:00"));
		emit stop_clicked_signal();
	});

	//播放按钮单击事件
	connect(btn_play, &GLLabelButton::clicked, this, [=]() 
	{
		switch (btn_play->getType())
		{
		case LabelButtonType::PLAY:
			btn_play->setType(LabelButtonType::PUSE);
			break;
		case LabelButtonType::PUSE:
			btn_play->setType(LabelButtonType::PLAY);
			break;
		}
		emit play_clicked_signal(m_path);
	});

	//当音量改变
	connect(vol_dialog, &PlayerDialog::vol_changed_signal, this, [=](int val) 
	{
		if (val < 200 && val >= 150)
			btn_volume->setType(LabelButtonType::VOL);
		else if (val < 150 && val >= 50)
			btn_volume->setType(LabelButtonType::VOL_DOWN);
		else if (val < 50 && val > 1)
			btn_volume->setType(LabelButtonType::VOL_OFF);

		if (val == 0)
			btn_volume->setType(LabelButtonType::VOL_MUTE);

		emit volume_changed_signal(val);
	});

	//音量按钮点击事件
	connect(btn_volume, &GLLabelButton::clicked, this, [=]() 
	{
	
		if (vol_dialog && !vol_dialog->isVisible())
		{
			QPoint point = QPoint(this->mapToGlobal(btn_volume->pos()).x(), this->mapToGlobal(btn_volume->pos()).y() - vol_dialog->height());
			vol_dialog->move(point);
			vol_dialog->show();
			vol_dialog->setFocus();
		}
		else
			vol_dialog->hide();

	});

	//打开文件按钮点击事件
	connect(btn_open, &GLLabelButton::clicked, this, [=]() {
		if (open_file && !open_file->isVisible())
			open_file->show();
		else
			open_file->hide();
	});

	//列表按钮单击事件
	connect(btn_list, &GLLabelButton::clicked, this, [=]() 
	{
		if (list_dialog && !list_dialog->isVisible())
		{
			QPoint point = QPoint(this->mapToGlobal(btn_list->pos()).x() - list_dialog->width() / 4, this->mapToGlobal(btn_list->pos()).y() - list_dialog->height());
			list_dialog->move(point);
			list_dialog->show();
		}
		else
			list_dialog->hide();

	});
}

GLPlayerToolBar::~GLPlayerToolBar()
{
	if (progress_bar)
	{
		delete progress_bar;
		progress_bar = nullptr;
	}
	if (lab_time)
	{
		delete lab_time;
		lab_time = nullptr;
	}
	if (btn_list)
	{
		delete btn_list;
		btn_list = nullptr;
	}
	if (btn_open)
	{
		delete btn_open;
		btn_open = nullptr;
	}
	if (btn_previous)
	{
		delete btn_previous;
		btn_previous = nullptr;
	}
	if (btn_slower)
	{
		delete btn_slower;
		btn_slower = nullptr;
	}
	if (btn_play)
	{
		delete btn_play;
		btn_play = nullptr;
	}
	if (btn_stop)
	{
		delete btn_stop;
		btn_stop = nullptr;
	}
	if (btn_faster)
	{
		delete btn_faster;
		btn_faster = nullptr;
	}
	if (btn_next)
	{
		delete btn_next;
		btn_next = nullptr;
	}
	if (btn_setting)
	{
		delete btn_setting;
		btn_setting = nullptr;
	}
	if (btn_volume)
	{
		delete btn_volume;
		btn_volume = nullptr;
	}
	if (btn_expand)
	{
		delete btn_expand;
		btn_expand = nullptr;
	}
	if (btn_dropper)
	{
		delete btn_dropper;
		btn_dropper = nullptr;
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
	if (color_dialog)
	{
		delete color_dialog;
		color_dialog = nullptr;
	}
	if (vol_dialog)
	{
		delete vol_dialog;
		vol_dialog = nullptr;
	}
	if (open_file)
	{
		delete open_file;
		open_file = nullptr;
	}
}

void GLPlayerToolBar::volume_changed_slot(int vol)
{
	vol_dialog->volume_changed_slot(vol);
}

void GLPlayerToolBar::update_time_slot(qint64 mss)
{
	lab_time->setText(QString("%1/%2")
		.arg(transform_msec(mss))
		.arg(transform_msec(duration)));
}

void GLPlayerToolBar::show_time_out_slot(qint64 mss)
{
	duration = mss;
}

void GLPlayerToolBar::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.fillRect(event->rect(), QBrush(QColor(255,255,255,100)));//0, 0, 0
	update();
}

QString GLPlayerToolBar::transform_msec(qint64 mss)
{
	long hours = (mss % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60);
	long minutes = (mss % (1000 * 60 * 60)) / (1000 * 60);
	long seconds = (mss % (1000 * 60)) / 1000;
	return QString("%1:%2:%3").arg(hours, 2, 10, QLatin1Char('0'))
		.arg(minutes, 2, 10, QLatin1Char('0'))
		.arg(seconds, 2, 10, QLatin1Char('0'));
}
