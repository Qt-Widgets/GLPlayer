#pragma once
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

class GLLabelButton;
class SVColorArea;
class HColorArea;
class GLPlaySlider;

namespace DialogType 
{
	enum Type
	{
		COLOR,
		VOL
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

protected:
	//对话框失去焦点事件
	void focusOutEvent(QFocusEvent *event);
	void paintEvent(QPaintEvent *event);

signals:
	//颜色选择器颜色改变发出该信号
	void colorChangedSignal(QString colorName);
	//声音改变信号
	void vol_changed_signal(int val);

public slots:
	//改变声音控制slider颜色
	void volColorChangedSlot(QString color);

private:
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

};
