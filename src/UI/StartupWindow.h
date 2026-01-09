#ifndef STARTUP_WINDOW_H
#define STARTUP_WINDOW_H

#include "ImGuiWindowBase.h"
#include <string>


class StartupWindow : public ImGuiWindowBase {
private:
	std::string selectedFilePath;

public:
	StartupWindow(std::string name, int width, int height);

	void setFilePath(std::string path);
	std::string getFilePath();

	void draw() override;
};

#endif // !STARTUP_WINDOW_H
