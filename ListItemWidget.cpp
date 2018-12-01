#include <QHBoxLayout>
#include <QFileInfo>
#include <QLabel>
#include <QTimer>
#include <QDebug>
#include "ListItemWidget.h"
#include "GLLabelButton.h"

ListItemWidget::ListItemWidget(QString path, PlayList::VideoType type, QWidget *parent) : QWidget(parent),m_path(path)
{
	medioa_info = new MediaInfoDLL::MediaInfo;
	medioa_info->Open(path.toLocal8Bit().toStdString().c_str());
	QString time;
	switch (type)
	{
	case PlayList::VIDEO:
		time = QString::fromStdString(medioa_info->Get(MediaInfoDLL::Stream_Video, 0, "Duration").c_str());
		break;
	case PlayList::AUDIO:
		time = QString::fromStdString(medioa_info->Get(MediaInfoDLL::Stream_Audio, 0, "Duration").c_str());
		break;
	}

	file_info = new QFileInfo(m_path);
	h_layout = new QHBoxLayout(this);
	this->m_type = type;

	lab_text = new QLabel(this);
	lab_text->setMinimumWidth(100);
	QFontMetrics fontWidth(lab_text->font());
	QString elideNote = fontWidth.elidedText(file_info->fileName(), Qt::ElideRight, 230);
	lab_text->setText(elideNote);

	lab_time = new QLabel(transform_msec(time.toLong()), this);
	
	h_layout->addWidget(lab_text, 0, Qt::AlignLeft);
	h_layout->addWidget(lab_time, 0, Qt::AlignRight);

	h_layout->setSpacing(3);
	setLayout(h_layout);
	this->setToolTip(file_info->fileName());
}

ListItemWidget::~ListItemWidget()
{
	if (file_info)
	{
		delete file_info;
		file_info = nullptr;
	}
	if (lab_text)
	{
		delete lab_text;
		lab_text = nullptr;
	}
	if (lab_time)
	{
		delete lab_time;
		lab_time = nullptr;
	}
	if (h_layout)
	{
		delete h_layout;
		h_layout = nullptr;
	}
	if (medioa_info)
	{
		delete medioa_info;
		medioa_info = nullptr;
	}
}

QString ListItemWidget::transform_msec(long mss)
{
	long hours = (mss % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60);
	long minutes = (mss % (1000 * 60 * 60)) / (1000 * 60);
	long seconds = (mss % (1000 * 60)) / 1000;
	return QString("%1:%2:%3").arg(hours, 2, 10, QLatin1Char('0'))
							.arg(minutes, 2, 10, QLatin1Char('0'))
							.arg(seconds, 2, 10, QLatin1Char('0'));
}

