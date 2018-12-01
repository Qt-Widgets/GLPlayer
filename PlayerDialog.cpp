#include <QPainter>
#include <QFont>
#include <QPaintEvent>
#include "IconFontHelper.h"
#include "SVColorArea.h"
#include "HColorArea.h"
#include "PlayerDialog.h"
#include "GLPlaySlider.h"
#include "GLLabelButton.h"
#include "OpenFileDialog.h"
#include "PlayerListDialog.h"

PlayerDialog::PlayerDialog(DialogType::Type type, QWidget *parent) : QDialog(parent)
{
	setWindowFlag(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setFocusPolicy(Qt::FocusPolicy::StrongFocus);

	m_type = type;
	switch (m_type)
	{
	case DialogType::COLOR:
		this->ColorDialog();
		break;
	case DialogType::VOL:
		this->VolDialog();
		break;
	case DialogType::LIST:
		this->ListDialog();
		break;
	case DialogType::FILE:
		this->FileDialog();
		break;
	}
}

PlayerDialog::~PlayerDialog()
{
	//释放资源
	//布局
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
	if (g_layout)
	{
		delete g_layout;
		g_layout = nullptr;
	}

	//颜色选择器
	if (h_color)
	{
		delete h_color;
		h_color = nullptr;
	}
	if (sv_color)
	{
		delete sv_color;
		sv_color = nullptr;
	}

	//声音选择器
	if (slider)
	{
		delete slider;
		slider = nullptr;
	}
	if (lab_vol)
	{
		delete lab_vol;
		lab_vol = nullptr;
	}

	//文件选择器
	if (file_dialog)
	{
		delete file_dialog;
		file_dialog = nullptr;
	}

	//列表对话框
	if (play_list)
	{
		delete play_list;
		play_list = nullptr;
	}
}

void PlayerDialog::ColorDialog()
{
	this->resize(303, 270);

	h_layout = new QHBoxLayout(this);
	h_layout->setMargin(0);
	h_layout->setSpacing(0);

	sv_color = new SVColorArea;
	h_color = new HColorArea;

	h_layout->addWidget(sv_color);
	h_layout->addWidget(h_color);

	this->setLayout(h_layout);

	connect(h_color, &HColorArea::hueChangedSignal, sv_color, &SVColorArea::hueChangedSlot);
	connect(sv_color, &SVColorArea::svChangedSignal, this, [=](int h, int s, int v) {
		QColor color = QColor::fromHsv(h, s, v);
		emit color_changed_signal(color.name());
	});

}

void PlayerDialog::VolDialog()
{
	this->resize(48, 130);

	QFont font = IconFontHelper::Instance()->SetFontID(3)->GetFont();
	font.setPointSize(16);

	g_layout = new QGridLayout(this);
	g_layout->setMargin(5);

	slider = new GLPlaySlider(Qt::Orientation::Vertical, this);
	slider->setMaximum(100);

	lab_vol = new GLLabelButton(LabelButtonType::LABEL,this);
	lab_vol->setText("000");
	lab_vol->setFont(font);
	lab_vol->setMinimumSize(38, 30);

	g_layout->addWidget(slider, 0, 0, 3, 1, Qt::AlignHCenter | Qt::AlignVCenter);
	g_layout->addWidget(lab_vol, 4, 0, 2, 1, Qt::AlignHCenter | Qt::AlignVCenter);

	this->setLayout(g_layout);

	//设置焦点代理
	lab_vol->setFocusProxy(this);
	slider->setFocusProxy(this);

	connect(slider, &GLPlaySlider::valueChanged, this, [=](int val) { lab_vol->setText(QString("%1").arg(val, 3, 10, QLatin1Char('0'))); });
	connect(slider, &GLPlaySlider::valueChanged, this, &PlayerDialog::vol_changed_signal);
	connect(lab_vol, &GLLabelButton::clicked, this, [=]() { lab_vol->setText("000"); slider->setValue(0); });
}

void PlayerDialog::FileDialog()
{
	h_layout = new QHBoxLayout(this);
	file_dialog = new OpenFileDialog(this);
	h_layout->addWidget(file_dialog);
	this->setLayout(h_layout);

	connect(file_dialog, &OpenFileDialog::OpenFile_Signal, this, &PlayerDialog::file_select_signal);
}

void PlayerDialog::ListDialog()
{
	this->resize(QSize(376, 500));

	h_layout = new QHBoxLayout(this);
	play_list = new PlayerListDialog(this);
	h_layout->addWidget(play_list);
	h_layout->setSpacing(0);
	this->setLayout(h_layout);

	connect(this, &PlayerDialog::next_play_signal, play_list, &PlayerListDialog::next_play_slot);
	connect(this, &PlayerDialog::previous_play_signal, play_list, &PlayerListDialog::previous_play_slot);
	connect(this, &PlayerDialog::stop_signal, play_list, &PlayerListDialog::stop_slot);
	connect(play_list, &PlayerListDialog::start_play_signals, this, &PlayerDialog::start_signal);
}

void PlayerDialog::focusOutEvent(QFocusEvent *event)
{
	if (m_type != DialogType::FILE && m_type != DialogType::LIST)
	{
		if (isVisible())
			this->hide();
	}
}

void PlayerDialog::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.fillRect(rect(), QColor(255, 255, 255, 100));
	event->accept();
}

void PlayerDialog::volColorChangedSlot(QString color)
{
	if (slider)
		slider->change_vertical_color(color);
	if (lab_vol)
		lab_vol->setStyleSheet(QString("color:%1").arg(color));
}

void PlayerDialog::volume_changed_slot(int val)
{
	slider->setValue(val);
}
