#include <QPainter>
#include <QFont>
#include "IconFontHelper.h"
#include "SVColorArea.h"
#include "HColorArea.h"
#include "PlayerDialog.h"
#include "GLPlaySlider.h"
#include "GLLabelButton.h"

PlayerDialog::PlayerDialog(DialogType::Type type, QWidget *parent) : QDialog(parent)
{
	setWindowFlag(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);

	setFocusPolicy(Qt::FocusPolicy::StrongFocus);

	switch (type)
	{
	case DialogType::COLOR:
		this->ColorDialog();
		break;
	case DialogType::VOL:
		this->VolDialog();
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
}

void PlayerDialog::ColorDialog()
{
	this->resize(303, 270);

	h_layout = new QHBoxLayout(this);
	h_layout->setContentsMargins(7, 0, 0, 0);

	sv_color = new SVColorArea;
	h_color = new HColorArea;

	h_layout->addWidget(sv_color);
	h_layout->addWidget(h_color);

	this->setLayout(h_layout);

	connect(h_color, &HColorArea::hueChangedSignal, sv_color, &SVColorArea::hueChangedSlot);
	connect(sv_color, &SVColorArea::svChangedSignal, this, [=](int h, int s, int v) {
		QColor color = QColor::fromHsv(h, s, v);
		emit colorChangedSignal(color.name());
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
	slider->setMaximum(200);
	

	lab_vol = new GLLabelButton(LabelButtonType::LABEL,this);
	lab_vol->setText("000");
	lab_vol->setFont(font);
	lab_vol->setMinimumSize(38, 30);

	g_layout->addWidget(slider, 0, 0, 3, 1, Qt::AlignHCenter | Qt::AlignVCenter);
	g_layout->addWidget(lab_vol, 4, 0, 2, 1, Qt::AlignHCenter | Qt::AlignVCenter);

	this->setLayout(g_layout);

	//设置焦点
	lab_vol->setFocusProxy(this);
	slider->setFocusProxy(this);

	connect(slider, &GLPlaySlider::valueChanged, this, [=](int val) { lab_vol->setText(QString("%1").arg(val, 3, 10, QLatin1Char('0'))); });
	connect(slider, &GLPlaySlider::valueChanged, this, &PlayerDialog::vol_changed_signal);
	connect(lab_vol, &GLLabelButton::clicked, this, [=]() { lab_vol->setText("000"); slider->setValue(0); });
}

void PlayerDialog::focusOutEvent(QFocusEvent *event)
{
	if (isVisible())
		this->hide();
}

void PlayerDialog::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.fillRect(rect(), QColor(255, 255, 255, 150));
}

void PlayerDialog::volColorChangedSlot(QString color)
{
	if (slider)
		slider->change_vertical_color(color);
	if (lab_vol)
		lab_vol->setStyleSheet(QString("color:%1").arg(color));
}
