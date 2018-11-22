#include <QMutex>
#include <QMutexLocker>
#include <QtGui>
#include <QtWidgets>
#include "IconFontHelper.h"

IconFontHelper::IconFontHelper(QObject*) : QObject(qApp)
{
	int fontId = QFontDatabase::addApplicationFont(":/fonts/Resources/Font Awesome 5 Free-Solid-900.otf");
	fontId = QFontDatabase::addApplicationFont(":/fonts/Resources/Font Awesome 5 Free-Regular-400.otf");
	fontId = QFontDatabase::addApplicationFont(":/fonts/Resources/Font Awesome 5 Brands-Regular-400.otf");
	fontId = QFontDatabase::addApplicationFont(":/fonts/Resources/Federant-Regular.ttf");
}

IconFontHelper*IconFontHelper::_instance = nullptr;
IconFontHelper * IconFontHelper::Instance()
{
	static QMutex mutex;
	if (!_instance)
	{
		QMutexLocker locker(&mutex);
		if (!_instance)
			_instance = new IconFontHelper;
	}
	return _instance;
}

QFont& IconFontHelper::GetFont()
{
	return iconFont;
}

IconFontHelper * IconFontHelper::SetFontID(int id)
{
	QString fontName = QFontDatabase::applicationFontFamilies(id).at(0);
	iconFont = QFont(fontName);
	return _instance;
}

void IconFontHelper::SetIcon(QLabel *ctl, QChar c, int size)
{
	iconFont.setPointSize(size);
	ctl->setFont(iconFont);
	ctl->setText(QChar(c));
	ctl->setAlignment(Qt::AlignCenter);
}
