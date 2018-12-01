#pragma once
#include <QWidget>
#include <MediaInfoDLL/MediaInfoDLL.h>

class QLabel;
class QHBoxLayout;
class QFileInfo;
class GLLabelButton;

namespace PlayList
{
	enum VideoType
	{
		VIDEO,
		AUDIO,
	};
}

class ListItemWidget : public QWidget
{
	Q_OBJECT

public:
	ListItemWidget(QString path , PlayList::VideoType type, QWidget *parent = nullptr);
	~ListItemWidget();
	inline QString path()
	{
		return m_path;
	}
	inline PlayList::VideoType type()
	{
		return m_type;
	}
	QString transform_msec(long mss);
private:
	QString m_path;
	PlayList::VideoType m_type;
	QTimer *m_timer = nullptr;
	QFileInfo *file_info = nullptr;
	QLabel *lab_text = nullptr;
	QLabel *lab_time = nullptr;
	QHBoxLayout *h_layout = nullptr;
	MediaInfoDLL::MediaInfo *medioa_info = nullptr;

	long duration = 0;
};
