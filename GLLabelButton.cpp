#include "GLLabelButton.h"
#include "IconFontHelper.h"

GLLabelButton::GLLabelButton(LabelButtonType::Type type, QWidget *parent, int size) : QLabel(parent)
{
	this->m_type = type;
	setType(m_type, size);

	if (type != LabelButtonType::LABEL && 
		type != LabelButtonType::AUDIO && 
		type != LabelButtonType::VIDEO &&
		type != LabelButtonType::LOCAL)
	{
		setMinimumSize(50, 50);
		setMaximumSize(50, 50);
	}
	if (type != LabelButtonType::OPENFILE)
		setStyleSheet("color:#ffffff;");

}

void GLLabelButton::setType(LabelButtonType::Type type, int size)
{
	this->m_type = type;
	switch (m_type)
	{
	case LabelButtonType::LABEL:
		IconFontHelper::Instance()->GetFont().setPointSize(size);
		setFont(IconFontHelper::Instance()->SetFontID(3)->GetFont());
		setAlignment(Qt::AlignCenter);
		break;
	case LabelButtonType::PREVIOUS:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf048), size);
		break;
	case LabelButtonType::SLOWER:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf04a), size);
		break;
	case LabelButtonType::STOP:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf04d), size);
		break;
	case LabelButtonType::PLAY:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf04b), size);
		break;
	case LabelButtonType::PUSE:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf04c), size);
		break;
	case LabelButtonType::FASTER:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf04e), size);
		break;
	case LabelButtonType::NETXT:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf051), size);
		break;
	case LabelButtonType::SETTING:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf013), size);
		break;
	case LabelButtonType::VOL:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf028), size);
		break;
	case LabelButtonType::VOL_DOWN:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf027), size);
		break;
	case LabelButtonType::VOL_MUTE:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf6a9), size);
		break;
	case LabelButtonType::VOL_OFF:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf026), size);
		break;
	case LabelButtonType::CLOSE:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf04b), size);
		break;
	case LabelButtonType::LIST:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf00b), size);
		break;
	case LabelButtonType::REPEAT:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf2ea), size);
		break;
	case LabelButtonType::TAKEPHON:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf04b), size);
		break;
	case LabelButtonType::SHARE:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf04b), size);
		break;
	case LabelButtonType::OPEN:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf052), size);
		break;
	case LabelButtonType::EXPAND:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf065), size);
		break;
	case LabelButtonType::DROPPER:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf53f), size);
		break;
	case LabelButtonType::OPENFILE:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf07c), size);
		break;
	case LabelButtonType::AUDIO:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf3b5), size);
		break;
	case LabelButtonType::VIDEO:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf1c8), size);
		break;
	case LabelButtonType::DEL:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf2ed), size);
		break;
	case LabelButtonType::ADD:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf067), size);
		break;
	case LabelButtonType::LOCAL:
		IconFontHelper::Instance()->SetFontID(0)->SetIcon(this, QChar(0xf192), size);
		break;
	}
}

LabelButtonType::Type& GLLabelButton::getType()
{
	return this->m_type;
}

void GLLabelButton::mousePressEvent(QMouseEvent *ev)
{
	emit clicked();
}

void GLLabelButton::enterEvent(QEvent *event)
{
	setCursor(Qt::PointingHandCursor);
	QPalette palette;
	palette.setColor(QPalette::Background, QColor(227, 225, 225));
	setAutoFillBackground(true);
	setPalette(palette);
}

void GLLabelButton::leaveEvent(QEvent *event)
{
	QPalette palette;
	palette.setColor(QPalette::Background, QColor(0, 0, 0,0));
	setAutoFillBackground(true);
	setPalette(palette);
}

void GLLabelButton::colorChangedSlot(QString colorName)
{
	this->setStyleSheet(QString("color:%1").arg(colorName));
}
