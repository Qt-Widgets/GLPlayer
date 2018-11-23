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
	//���ð�ť����
	void setType(LabelButtonType::Type, int size = 16);
	//��ȡ��ť����
	LabelButtonType::Type& getType();

protected:
	//��갴���¼�
	void mousePressEvent(QMouseEvent *ev);
	//��������¼�
	void enterEvent(QEvent *event);
	//����Ƴ��¼�
	void leaveEvent(QEvent *event);

signals:
	//�����¼��ź�
	void clicked();

public slots:
	//������ɫ�ۣ��ı�icon��ɫ
	void colorChangedSlot(QString colorName);

private:
	LabelButtonType::Type m_type;
};
