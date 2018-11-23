#include <QVBoxLayout>
#include <QTabWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QFileDialog>
#include <QFileInfo>

#include "IconFontHelper.h"
#include "GLLabelButton.h"
#include "OpenFileDialog.h"

OpenFileDialog::OpenFileDialog(QWidget *parent) : QWidget(parent)
{
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlags(Qt::FramelessWindowHint);
	setMaximumSize(400, 200);
	setMinimumSize(400, 200);

	font = IconFontHelper::Instance()->SetFontID(4)->GetFont();
	font.setPointSize(10);

	v_layout = new QVBoxLayout(this);
	label = new QLabel(u8"播放文件或流媒体", this);
	tab = new QTabWidget(this);
	tab->setFont(font);
	font.setPointSize(13);
	label->setFont(font);

	v_layout->addWidget(label);
	v_layout->addStretch();
	v_layout->addWidget(tab);
	v_layout->addStretch();

	h_layout = new QHBoxLayout;
	btn_ok = new QPushButton(u8"确定", this);
	btn_cancel = new QPushButton(u8"取消", this);
	font.setPointSize(8);
	btn_ok->setFont(font);
	btn_cancel->setFont(font);
	
	h_layout->addStretch();
	h_layout->addWidget(btn_ok);
	h_layout->addWidget(btn_cancel);

	v_layout->addLayout(h_layout);
	v_layout->setStretchFactor(tab, 2);
	v_layout->setStretchFactor(label, 1);
	v_layout->setStretchFactor(h_layout, 1);
	this->setLayout(v_layout);

	this->BulidLocaTab();
	this->BulidRemoTab();

	video = ".3g2.3gp.3gp2.3gpp.amv.asf.asx.avi.bik.bup.divx.dmskm.dpg.dv.dvr-ms.evo.f4v.flv.h264.idx.ifo.k3g.m1v.m2p.m2t.m2ts.m2v.m4v.mkv.mod.mov.mp2v.mp4.mp4v.mpa.mpe.mpeg.mpeg1.mpeg2.mpeg4.mpg.mpv2.mqv.mts.mxf.nsv.ogm.ogv.ogx.qt.rec.rm.rmvb.rpm.rv.skm.smi.srt.sub.swf.tod.tp.trp.ts.tts.vob.vro.webm.wm.wmv.wtv";
	audio = ".aac.ac3.adts.aifc.aiff.amr.aob.ape.au.cda.dts.flac.it.m1a.m2a.m4a.m4b.m4p.m4r.mid.mka.mp1.mp2.mp3.mpc.oga.ogg.oma.ra.ram.rmi.s3m.spx.tak.tta.voc.vqf.w64.wav.wax.wma.wv.xm.xspf";
	video.replace(QRegExp("\\."), " *.");
	audio.replace(QRegExp("\\."), " *.");

	connect(tab, &QTabWidget::currentChanged, this, &OpenFileDialog::TabIndex);
	connect(btn_cancel, &QPushButton::clicked, parent, &QWidget::hide);
	connect(btn_ok, &QPushButton::clicked, this, &OpenFileDialog::Open_Btn_Clicked);
	connect(btn_openfile, &GLLabelButton::clicked, this, &OpenFileDialog::File_Select_Slots);
}

OpenFileDialog::~OpenFileDialog()
{
	if (label)
	{
		delete label;
		label = nullptr;
	}
	if (btn_ok)
	{
		delete btn_ok;
		btn_ok = nullptr;
	}
	if (btn_cancel)
	{
		delete btn_cancel;
		btn_cancel = nullptr;
	}

	//打开本地文件的tab
	if (loca_label)
	{
		delete loca_label;
		loca_label = nullptr;
	}
	if (loca_lineedit)
	{
		delete loca_lineedit;
		loca_lineedit = nullptr;
	}
	if (btn_openfile)
	{
		delete btn_openfile;
		btn_openfile = nullptr;
	}
	if (loca_h_layout)
	{
		delete loca_h_layout;
		loca_h_layout = nullptr;
	}
	if (loca_widget)
	{
		delete loca_widget;
		loca_widget = nullptr;
	}

	//打开远程文件的tab
	if (remo_label)
	{
		delete remo_label;
		remo_label = nullptr;
	}
	if (remo_lineedit)
	{
		delete remo_lineedit;
		remo_lineedit = nullptr;
	}
	if (remo_h_layout)
	{
		delete remo_h_layout;
		remo_h_layout = nullptr;
	}
	if (remo_widget)
	{
		delete remo_widget;
		remo_widget = nullptr;
	}

	if (tab)
	{
		delete tab;
		tab = nullptr;
	}
	if (h_layout)
	{
		delete h_layout;
		h_layout = nullptr;
	}
	if (v_layout)
	{
		delete v_layout;
		v_layout = nullptr;
	}
}

void OpenFileDialog::TabIndex(int index)
{
	if (index != 0)
		isLoca = false;
	else
		isLoca = true;
}

void OpenFileDialog::Open_Btn_Clicked()
{
	bool isVideo = true;
	QString path;
	if (isLoca)
		path = loca_lineedit->text();
	else
		path = remo_lineedit->text();
	
	QFileInfo fileInfo(path);

	if (video.indexOf(fileInfo.suffix()) != -1)
		isVideo = true;

	if (audio.indexOf(fileInfo.suffix()) != -1)
		isVideo = false;

	if (!path.isEmpty())
		emit OpenFile_Signal(path, isLoca, isVideo);
}

void OpenFileDialog::File_Select_Slots()
{
	QString filter = QString(u8"所有文件(%1);;视频文件(%2);;音频文件(%3)")
		.arg(video + audio)
		.arg(video)
		.arg(audio);
	QString path = QFileDialog::getOpenFileName(this, u8"打开文件", "/", filter);
	loca_lineedit->setText(path);
}

void OpenFileDialog::BulidLocaTab()
{
	loca_widget = new QWidget(this);
	loca_h_layout = new QHBoxLayout(loca_widget);
	loca_label = new QLabel(u8"打开文件", loca_widget);
	loca_lineedit = new QLineEdit(loca_widget);
	btn_openfile = new GLLabelButton(LabelButtonType::OPENFILE, this, 18);
	loca_h_layout->addWidget(loca_label);
	loca_h_layout->addWidget(loca_lineedit);
	loca_h_layout->addWidget(btn_openfile);

	loca_widget->setLayout(loca_h_layout);

	this->tab->addTab(loca_widget, u8"本地文件");
}

void OpenFileDialog::BulidRemoTab()
{
	remo_widget = new QWidget(this);
	remo_h_layout = new QHBoxLayout(remo_widget);
	remo_label = new QLabel(u8"打开网络流媒体",remo_widget);
	remo_lineedit = new QLineEdit(remo_widget);
	remo_h_layout->addWidget(remo_label);
	remo_h_layout->addWidget(remo_lineedit);

	remo_widget->setLayout(remo_h_layout);

	this->tab->addTab(remo_widget, u8"网络流媒体");
}

