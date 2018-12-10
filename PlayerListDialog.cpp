#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QFileInfo>
#include <QFileInfoList>
#include <QFile>
#include <QDir>
#include <QFileDialog>

#include "GLLabelButton.h"
#include "PlayerListDialog.h"

PlayerListDialog::PlayerListDialog(QWidget *parent) : QWidget(parent)
{
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_AlwaysShowToolTips);
	
	setAcceptDrops(true);

	video = ".3g2.3gp.3gp2.3gpp.amv.asf.asx.avi.bik.bup.divx.dmskm.dpg.dv.dvr-ms.evo.f4v.flv.h264.idx.ifo.k3g.m1v.m2p.m2t.m2ts.m2v.m4v.mkv.mod.mov.mp2v.mp4.mp4v.mpa.mpe.mpeg.mpeg1.mpeg2.mpeg4.mpg.mpv2.mqv.mts.mxf.nsv.ogm.ogv.ogx.qt.rec.rm.rmvb.rpm.rv.skm.smi.srt.sub.swf.tod.tp.trp.ts.tts.vob.vro.webm.wm.wmv.wtv";
	audio = ".aac.ac3.adts.aifc.aiff.amr.aob.ape.au.cda.dts.flac.it.m1a.m2a.m4a.m4b.m4p.m4r.mid.mka.mp1.mp2.mp3.mpc.oga.ogg.oma.ra.ram.rmi.s3m.spx.tak.tta.voc.vqf.w64.wav.wax.wma.wv.xm.xspf";
	video.replace(QRegExp("\\."), " *.");
	audio.replace(QRegExp("\\."), " *.");

	v_layout = new QVBoxLayout(this);
	h_layout = new QHBoxLayout;

	btn_layout2 = new QHBoxLayout;
	QLineEdit *edit = new QLineEdit(this);		//未释放
	
	edit->setPlaceholderText(u8"输入文件名称筛选");
	edit->setStyleSheet("QLineEdit{ background-color: rgba(255,240,255,120); }QLineEdit:focus{background-color: rgb(255,255,255)}");
	
	loca = new GLLabelButton(LabelButtonType::LOCAL, this);
	//loca->setToolTip(u8"快速定位到当前播放项");

	btn_layout2->addWidget(edit);
	btn_layout2->addWidget(loca);
	btn_layout2->setSpacing(0);
	btn_layout2->setContentsMargins(0, 0, 0, 10);

	list_widget = new QListWidget(this);
	list_widget->setFocusProxy(parent);
	list_widget->setAcceptDrops(true);
	list_widget->setSelectionMode(QAbstractItemView::ExtendedSelection);
	h_layout->addWidget(list_widget);

	btn_layout = new QHBoxLayout;
	add_item = new GLLabelButton(LabelButtonType::ADD, this);
	
	del_item = new GLLabelButton(LabelButtonType::DEL, this);
	
	btn_layout->addStretch();
	btn_layout->addWidget(add_item);
	btn_layout->addWidget(del_item);
	btn_layout->setSpacing(0);
	btn_layout->setMargin(0);

	h_layout->setSpacing(0);
	h_layout->setMargin(0);
	v_layout->setSpacing(0);
	v_layout->setMargin(0);
	v_layout->addLayout(btn_layout2);
	v_layout->addLayout(h_layout);
	v_layout->addLayout(btn_layout);
	this->setLayout(v_layout);

	list_widget->setFocusProxy(parent);
	loca->setFocusProxy(parent);
	add_item->setFocusProxy(parent);
	del_item->setFocusProxy(parent);

	connect(add_item, &GLLabelButton::clicked, this, &PlayerListDialog::add_item_slot);
	connect(del_item, &GLLabelButton::clicked, this, &PlayerListDialog::del_item_slot);
	connect(loca, &GLLabelButton::clicked, this, [=]()
	{
		list_widget->scrollToItem(m_current);
	});

	connect(list_widget, &QListWidget::itemDoubleClicked, this, &PlayerListDialog::item_double_clicked);

	connect(list_widget, &QListWidget::itemPressed, this, [=](QListWidgetItem *item) 
	{
		m_current = item;
		//item_double_clicked(item);
	});

	//void itemChanged(QListWidgetItem *item);
	connect(list_widget, &QListWidget::itemChanged, this, [=](QListWidgetItem *item)
	{
		items.insert(item, static_cast<ListItemWidget*>(list_widget->itemWidget(item)));
	});

	//筛选器
	connect(edit, &QLineEdit::textChanged, [=](const QString &text)
	{
		auto i = items.constBegin();
		while (i != items.constEnd())
		{
			QString item_path = i.value()->path();
			bool is_hidden = item_path.indexOf(text) == -1;
			list_widget->setItemHidden(static_cast<QListWidgetItem*>(i.key()), is_hidden);
			i++;
		}
	});
}

void PlayerListDialog::add_item_slot()
{
	QString filter = QString(u8"所有文件(%1);;视频文件(%2);;音频文件(%3)")
		.arg(video + audio)
		.arg(video)
		.arg(audio);
	
	QStringList path_list = QFileDialog::getOpenFileNames(this, u8"添加文件", "/",filter);

	for each (QString path in path_list)
		add_list_item(path);

}

void PlayerListDialog::del_item_slot()
{
	for each (auto item in list_widget->selectedItems())
	{
		items.remove(item);
		list_widget->removeItemWidget(item);
		delete item;
	}
}

void PlayerListDialog::next_play_slot()
{
	int current_row = list_widget->currentRow();
	if (current_row != -1)
	{
		for (int i = 0; i < list_widget->count(); i++)
			list_widget->item(i)->setSizeHint(QSize(0, 30));
		
		current_row++;
		if (current_row > list_widget->count() - 1)
			current_row = 0;
		
		QListWidgetItem *item = list_widget->item(current_row);
		ListItemWidget *list_item = (ListItemWidget*)list_widget->itemWidget(item);
		list_widget->setCurrentRow(current_row);
		item->setSizeHint(QSize(0, 45));

		emit start_play_signals(list_item->path(), list_item->type());
	}
}

void PlayerListDialog::previous_play_slot()
{
	int current_row = list_widget->currentRow();
	if (current_row != -1)
	{
		for (int i = 0; i < list_widget->count(); i++)
			list_widget->item(i)->setSizeHint(QSize(0, 30));

		current_row--;
		if (current_row < 0)
			current_row = list_widget->count() - 1;

		QListWidgetItem *item = list_widget->item(current_row);
		ListItemWidget *list_item = (ListItemWidget*)list_widget->itemWidget(item);
		list_widget->setCurrentRow(current_row);
		item->setSizeHint(QSize(0, 45));

		emit start_play_signals(list_item->path(), list_item->type());
	}
}

void PlayerListDialog::stop_slot()
{
	for (int i = 0; i < list_widget->count(); i++)
		list_widget->item(i)->setSizeHint(QSize(0, 30));
}

void PlayerListDialog::add_list_item(QString path)
{
	QFileInfo file(path);

	//去重
	auto i = items.constBegin();
	while (i != items.constEnd())
	{
		if (path == i.value()->path())
			return;
		i++;
	}

	ListItemWidget *widget = nullptr;
	if (audio.indexOf(file.suffix()) != -1)
		widget = new ListItemWidget(path, PlayList::AUDIO, list_widget);

	if (video.indexOf(file.suffix()) != -1)
		widget = new ListItemWidget(path, PlayList::VIDEO, list_widget);

	if (widget)
	{
		QListWidgetItem *listitem = new QListWidgetItem(list_widget);
		list_widget->addItem(listitem);
		list_widget->setItemWidget(listitem, widget);
		listitem->setSizeHint(QSize(0, 30));
		list_widget->setItemSelected(listitem, true);
	}
}

void PlayerListDialog::item_double_clicked(QListWidgetItem *item)
{
	m_current = item;

	for (int i = 0; i < list_widget->count(); i++)
		list_widget->item(i)->setSizeHint(QSize(0, 30));

	ListItemWidget *list_item = (ListItemWidget*)list_widget->itemWidget(item);
	item->setSizeHint(QSize(0, 45));

	emit start_play_signals(list_item->path(), list_item->type());
}

QFileInfoList PlayerListDialog::GetFileList(QString path)
{
	QDir dir(path);
	QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
	for (int i = 0; i != folder_list.size(); i++)
	{
		QString name = folder_list.at(i).absoluteFilePath();
		QFileInfoList child_file_list = GetFileList(name);
		file_list.append(child_file_list);
	}
	return file_list;
}

PlayerListDialog::~PlayerListDialog()
{
	if (items.count() != 0)
		items.clear();

	if (loca)
	{
		delete loca;
		loca = nullptr;
	}

	if (add_item)
	{
		delete add_item;
		add_item = nullptr;
	}
	if (del_item)
	{
		delete del_item;
		del_item = nullptr;
	}
	if (list_widget)
	{
		delete list_widget;
		list_widget = nullptr;
	}
	if (btn_layout)
	{
		delete btn_layout;
		btn_layout = nullptr;
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

void PlayerListDialog::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasUrls())
		event->acceptProposedAction();
	else
		event->ignore();
}

void PlayerListDialog::dropEvent(QDropEvent *event)
{
	const QMimeData *mimeData = event->mimeData();
	if (mimeData->hasUrls())
	{
		QList<QUrl> urlList = mimeData->urls();
		for each (QUrl url in urlList)
		{
			QFileInfo file_info(url.toLocalFile());
			if (file_info.isDir())
			{
				QFileInfoList file_list = GetFileList(url.toLocalFile());
				for each (QFileInfo file in file_list)
					add_list_item(file.absoluteFilePath());
			}
			else
				add_list_item(file_info.absoluteFilePath());
		}
	}
}

