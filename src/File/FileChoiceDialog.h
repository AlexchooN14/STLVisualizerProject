#ifndef FILE_CHOICE_DIALOG_H
#define FILE_CHOICE_DIALOG_H

#ifdef PLATFORM_WINDOWS
	#include <windows.h>
	#include <commdlg.h>
	#include <shlobj.h>
#endif

#include <string>


std::string OpenFileDialog();

std::string GetDownloadsFolder();

#endif // !FILE_CHOICE_DIALOG_H
