#include <QtWidgets/QApplication>
#include "GLPlayer.h"
#include "GLMusicPlayer.h"

int main(int argc, char *argv[])
{
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
