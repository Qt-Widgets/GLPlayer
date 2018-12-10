#include <QtWidgets/QApplication>
#include "GLPlayer.h"
#include "GLMusicPlayer.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	a.setWindowIcon(QIcon(":/images/Resources/favicon.ico"));

	//ÊÓÆµ²¥·ÅÆ÷
	GLPlayer video;
	video.show();

	//ÒôÀÖ²¥·ÅÆ÷
	/*GLMusicPlayer music;
	music.show();*/

	return a.exec();
}
