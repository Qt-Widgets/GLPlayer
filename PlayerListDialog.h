#pragma once

#include <QWidget>

class PlayerListDialog : public QWidget
{
	Q_OBJECT

public:
	PlayerListDialog(QWidget *parent = nullptr);
	~PlayerListDialog();

protected:
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);

};
