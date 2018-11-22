#pragma once
#include <QObject>
#include <QFont>

class QLabel;

class IconFontHelper : public QObject
{
	Q_OBJECT

private:
	explicit IconFontHelper(QObject*parent = 0);
	explicit IconFontHelper(const IconFontHelper &);
	IconFontHelper& operator=(const IconFontHelper &);
	static IconFontHelper*_instance;
	QFont iconFont;

public:
	static IconFontHelper *Instance();
	QFont& GetFont();
	IconFontHelper *SetFontID(int id);
	void SetIcon(QLabel *ctl, QChar c, int size);
};
