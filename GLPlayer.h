#pragma once
#include <QWidget>

class QVBoxLayout;
class QHBoxLayout;
class GLPlayerToolBar;


class GLPlayer : public QWidget
{
	Q_OBJECT

public:
	GLPlayer(QWidget *parent = Q_NULLPTR);
	~GLPlayer();
private:
	QVBoxLayout *v_layout = nullptr;
	QHBoxLayout *h_layout = nullptr;
	GLPlayerToolBar *tool_bar = nullptr;
};
