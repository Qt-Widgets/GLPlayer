#include <QtWidgets/QApplication>
#include "GLPlayer.h"
#include "GLMusicPlayer.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	a.setWindowIcon(QIcon(":/images/Resources/favicon.ico"));

	//��Ƶ������
	GLPlayer video;
	video.show();

	//���ֲ�����
	/*GLMusicPlayer music;
	music.show();*/

	return a.exec();
}
