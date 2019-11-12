#include "stdafx.h"
#include "Face_Strech_UI.h"
#include <QtWidgets/QApplication>
#include <io.h>
#include <direct.h>
#include <string>

int main(int argc, char *argv[])
{

	std::string prefix = ".//debug//";
	if (_access(prefix.c_str(), 0) == -1)	//如果文件夹不存在
		_mkdir(prefix.c_str());				//则创建
	QApplication a(argc, argv);
	Face_Strech_UI w;//调用主窗口
	w.show();
	return a.exec();
}
