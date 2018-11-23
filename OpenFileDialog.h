#pragma once
#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;
class QTabWidget;
class QVBoxLayout;
class QHBoxLayout;
class GLLabelButton;

class OpenFileDialog : public QWidget
{
	Q_OBJECT

public:
	OpenFileDialog(QWidget *parent = nullptr);
	~OpenFileDialog();

public slots:
	void TabIndex(int index);
	void Open_Btn_Clicked();
	void File_Select_Slots();

signals:
	void OpenFile_Signal(QString path, bool loca, bool isVideo);

private:
	//构建打开本地文件的Tab
	void BulidLocaTab();
	//构建打开流媒体的Tab
	void BulidRemoTab();

private:
	bool isLoca = true;
	QFont font;
	QString video;
	QString audio;

	QVBoxLayout *v_layout = nullptr;
	QHBoxLayout *h_layout = nullptr;
	QTabWidget *tab = nullptr;
	QLabel *label = nullptr;
	QPushButton *btn_ok = nullptr;
	QPushButton *btn_cancel = nullptr;

	//打开本地文件的tab
	QWidget *loca_widget = nullptr;
	QHBoxLayout *loca_h_layout = nullptr;
	QLabel *loca_label = nullptr;
	QLineEdit *loca_lineedit = nullptr;
	GLLabelButton *btn_openfile = nullptr;

	//打开远程文件的tab
	QWidget *remo_widget = nullptr;
	QHBoxLayout *remo_h_layout = nullptr;
	QLabel *remo_label = nullptr;
	QLineEdit *remo_lineedit = nullptr;

};
