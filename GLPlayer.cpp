#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "GLPlayer.h"
#include "GLPlayerToolBar.h"

GLPlayer::GLPlayer(QWidget *parent)
	: QWidget(parent)
{
	//setAttribute(Qt::WA_TranslucentBackground);
	//setAutoFillBackground(true);
	//setWindowFlags(Qt::FramelessWindowHint);
	
	this->setMinimumSize(800, 400);

	v_layout = new QVBoxLayout(this);
	v_layout->setSpacing(0);
	v_layout->setMargin(0);
	/*add widgets code*/
	QLabel *lab = new QLabel(this);
	lab->setStyleSheet("QLabel{border:2px solid #000000;}");
	v_layout->addWidget(lab);

	h_layout = new QHBoxLayout;
	/*add widgets code*/
	tool_bar = new GLPlayerToolBar(this);
	h_layout->addWidget(tool_bar);

	v_layout->setStretchFactor(lab, 1);
	v_layout->setStretchFactor(tool_bar, 2);
	v_layout->addLayout(h_layout);
	setLayout(v_layout);
}

GLPlayer::~GLPlayer()
{
	if (tool_bar)
	{
		delete tool_bar;
		tool_bar = nullptr;
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

