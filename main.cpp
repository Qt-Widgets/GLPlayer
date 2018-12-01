#include <QtWidgets/QApplication>
#include <QtAVWidgets/QtAVWidgets>
#include "GLPlayer.h"
#include "GLMusicPlayer.h"
#include <PlayerListDialog.h>

int main(int argc, char *argv[])
{
	QtAV::Widgets::registerRenderers();

	QApplication a(argc, argv);
	
	//ÊÓÆµ²¥·ÅÆ÷
	GLPlayer video;
	video.show();

	//ÒôÀÖ²¥·ÅÆ÷
	/*GLMusicPlayer music;
	music.show();*/

	/*PlayerListDialog dlg;
	dlg.show();*/

	return a.exec();
}
