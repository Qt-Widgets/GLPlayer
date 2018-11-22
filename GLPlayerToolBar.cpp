#include <QVBoxLayout>
#include <QHBoxLayout>
#include "GLPlaySlider.h"
#include "GLLabelButton.h"
#include "PlayerDialog.h"
#include "GLPlayerToolBar.h"

GLPlayerToolBar::GLPlayerToolBar(QWidget *parent) : QWidget(parent)
{
	setWindowFlag(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);

	v_layout = new QVBoxLayout(this);
	v_layout->setSpacing(0);
	v_layout->setMargin(0);

	/*add widgets code*/
	progress_bar = new GLPlaySlider(Qt::Orientation::Horizontal, this);
	v_layout->addWidget(progress_bar);

	h_layout = new QHBoxLayout(this);
	
	//控件
	lab_time = new GLLabelButton(LabelButtonType::LABEL, this,12);
	lab_time->setText(QString("%1/%2").arg("00:00:00").arg("00:00:00"));
	btn_list = new GLLabelButton(LabelButtonType::LIST, this);
	btn_open = new GLLabelButton(LabelButtonType::OPEN, this);
	btn_previous = new GLLabelButton(LabelButtonType::PREVIOUS, this);
	btn_slower = new GLLabelButton(LabelButtonType::SLOWER, this);
	btn_play = new GLLabelButton(LabelButtonType::PLAY, this);
	btn_stop = new GLLabelButton(LabelButtonType::STOP, this);
	btn_faster = new GLLabelButton(LabelButtonType::FASTER, this);
	btn_next = new GLLabelButton(LabelButtonType::NETXT, this);
	btn_setting = new GLLabelButton(LabelButtonType::SETTING, this);
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
	h_layout->addWidget(btn_setting);
	h_layout->addWidget(btn_volume);
	h_layout->addWidget(btn_expand);
	h_layout->setContentsMargins(10, 0, 10, 0);
	h_layout->setSpacing(0);

	v_layout->addLayout(h_layout);
	setLayout(v_layout);

	color_dialog = new PlayerDialog(DialogType::COLOR, this);
	vol_dialog = new PlayerDialog(DialogType::VOL, this);

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
		
		connect(color_dialog, &PlayerDialog::colorChangedSignal, lab_time, &GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::colorChangedSignal, btn_dropper, &GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::colorChangedSignal, btn_expand,&GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::colorChangedSignal, btn_volume,&GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::colorChangedSignal, btn_setting,&GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::colorChangedSignal, btn_next,&GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::colorChangedSignal, btn_faster,&GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::colorChangedSignal, btn_stop,&GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::colorChangedSignal, btn_play,&GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::colorChangedSignal, btn_slower,&GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::colorChangedSignal, btn_previous,&GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::colorChangedSignal, btn_open,&GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::colorChangedSignal, btn_list,&GLLabelButton::colorChangedSlot);
		connect(color_dialog, &PlayerDialog::colorChangedSignal, vol_dialog, &PlayerDialog::volColorChangedSlot);

	});

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

	});

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
		btn_expand = nullptr;
	}
	if (v_layout)
	{
		delete v_layout;
		btn_expand = nullptr;
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
}
