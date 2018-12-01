#pragma once
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include "ListItemWidget.h"

class GLLabelButton;
class SVColorArea;
class HColorArea;
class GLPlaySlider;
class OpenFileDialog;
class PlayerListDialog;

namespace DialogType 
{
	enum Type
	{
		COLOR,
		VOL,
		FILE,
		LIST
	};
}

class PlayerDialog : public QDialog
{
	Q_OBJECT

public:
	PlayerDialog(DialogType::Type type, QWidget *parent = 0);
	~PlayerDialog();

private:
	//颜色选择器对话框
	void ColorDialog();
	//声音选择对话框
	void VolDialog();
	//文件选择器对话框
	void FileDialog();
	//播放列表对话框
	void ListDialog();

protected:
	//对话框失去焦点事件
	void focusOutEvent(QFocusEvent *event);
	void paintEvent(QPaintEvent *event);

signals:
	//颜色选择器颜色改变发出该信号
	void color_changed_signal(QString colorName);
	//声音改变信号
	void vol_changed_signal(int val);
	//文件选择器
	void file_select_signal(QString path, bool isLoca, bool isVideo);

	//列表控制信号
	void next_play_signal();		//下一首
	void previous_play_signal();	//上一首
	void stop_signal();				//停止
	void start_signal(QString path, PlayList::VideoType type);			//开始信号

public slots:
	//改变声音控制slider颜色
	void volColorChangedSlot(QString color);
	void volume_changed_slot(int);

private:
	DialogType::Type m_type;

	//布局
	QHBoxLayout *h_layout = nullptr;
	QVBoxLayout *v_layout = nullptr;
	QGridLayout *g_layout = nullptr;

	//颜色选择器
	HColorArea *h_color = nullptr;
	SVColorArea *sv_color = nullptr;

	//声音选择器
	GLPlaySlider *slider = nullptr;
	GLLabelButton *lab_vol = nullptr;

	//文件选择器
	OpenFileDialog *file_dialog = nullptr;

	//列表对话框
	PlayerListDialog *play_list = nullptr;
};
