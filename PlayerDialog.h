#pragma once
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

class GLLabelButton;
class SVColorArea;
class HColorArea;
class GLPlaySlider;
class OpenFileDialog;

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
	//��ɫѡ�����Ի���
	void ColorDialog();
	//����ѡ��Ի���
	void VolDialog();
	//�ļ�ѡ�����Ի���
	void FileDialog();
	//�����б�Ի���
	void ListDialog();

protected:
	//�Ի���ʧȥ�����¼�
	void focusOutEvent(QFocusEvent *event);
	void paintEvent(QPaintEvent *event);

signals:
	//��ɫѡ������ɫ�ı䷢�����ź�
	void color_changed_signal(QString colorName);
	//�����ı��ź�
	void vol_changed_signal(int val);
	//�ļ�ѡ����
	void file_select_signal(QString path, bool isLoca, bool isVideo);

public slots:
	//�ı���������slider��ɫ
	void volColorChangedSlot(QString color);

private:
	DialogType::Type m_type;

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

	//�ļ�ѡ����
	OpenFileDialog *file_dialog = nullptr;

};
