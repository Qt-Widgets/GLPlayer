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
	//��ɫѡ�����Ի���
	void ColorDialog();
	//����ѡ��Ի���
	void VolDialog();

protected:
	//�Ի���ʧȥ�����¼�
	void focusOutEvent(QFocusEvent *event);
	void paintEvent(QPaintEvent *event);

signals:
	//��ɫѡ������ɫ�ı䷢�����ź�
	void colorChangedSignal(QString colorName);
	//�����ı��ź�
	void vol_changed_signal(int val);

public slots:
	//�ı���������slider��ɫ
	void volColorChangedSlot(QString color);

private:
	//����
	QHBoxLayout *h_layout = nullptr;
	QVBoxLayout *v_layout = nullptr;
	QGridLayout *g_layout = nullptr;

	//��ɫѡ����
	HColorArea *h_color = nullptr;
	SVColorArea *sv_color = nullptr;

	//����ѡ����
	GLPlaySlider *slider = nullptr;
	GLLabelButton *lab_vol = nullptr;

};
