#pragma once
#include <QLabel>

namespace LabelButtonType
{
	enum Type
	{
		LABEL,
		OPEN,
		PREVIOUS,
		SLOWER,
		STOP,
		PLAY,
		PUSE,
		FASTER,
		NETXT,
		SETTING,
		VOL,
		VOL_DOWN,
		VOL_MUTE,
		VOL_OFF,
		CLOSE,
		LIST,
		REPEAT,
		TAKEPHON,
		SHARE,
		EXPAND,
		DROPPER,
		OPENFILE
	};
}

class GLLabelButton : public QLabel
{
	Q_OBJECT

public:
	explicit GLLabelButton(LabelButtonType::Type, QWidget *parent = nullptr, int size = 16);
	//设置按钮类型
	void setType(LabelButtonType::Type, int size = 16);
	//获取按钮类型
	LabelButtonType::Type& getType();

protected:
	//鼠标按下事件
	void mousePressEvent(QMouseEvent *ev);
	//鼠标移入事件
	void enterEvent(QEvent *event);
	//鼠标移出事件
	void leaveEvent(QEvent *event);

signals:
	//单击事件信号
	void clicked();

public slots:
	//接收颜色槽，改变icon颜色
	void colorChangedSlot(QString colorName);

private:
	LabelButtonType::Type m_type;
};
