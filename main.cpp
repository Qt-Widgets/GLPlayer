#include <QtWidgets/QApplication>
#include "GLPlayer.h"
#include "GLMusicPlayer.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//��Ƶ������
	GLPlayer video;
	video.show();

	//���ֲ�����
	/*GLMusicPlayer music;
	music.show();*/

	/*PlayerListDialog dlg;
	dlg.show();*/

	return a.exec();
}
