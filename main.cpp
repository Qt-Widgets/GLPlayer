#include <QtWidgets/QApplication>
#include <QtAVWidgets/QtAVWidgets>
#include "GLPlayer.h"
#include "GLMusicPlayer.h"

int main(int argc, char *argv[])
{
	//QtAV::Widgets::registerRenderers();

	QApplication a(argc, argv);
	
	//��Ƶ������
	GLPlayer video;
	video.show();

	//���ֲ�����
	/*GLMusicPlayer music;
	music.show();*/

	return a.exec();
}
