#include "FileChoiceDialog.h"


#ifdef PLATFORM_WINDOWS
std::string OpenFileDialog() {
    OPENFILENAME ofn;
    char szFile[260] = { 0 };

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "STL Files\0*.STL\0\0";
    CoInitialize(NULL);
    std::string initialDir = GetDownloadsFolder();
    ofn.lpstrInitialDir = initialDir.empty() ? nullptr : initialDir.c_str();
    CoUninitialize();
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn) == TRUE) {
        return std::string(ofn.lpstrFile);
    }
    return "";
}

static std::string GetDownloadsFolder() {
    PWSTR path = nullptr;
    std::string result;

    if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Downloads, 0, NULL, &path))) {
        // Convert UTF-16 (PWSTR) to UTF-8 std::string
        int size_needed = WideCharToMultiByte(CP_UTF8, 0, path, -1, nullptr, 0, nullptr, nullptr);
        if (size_needed > 0) {
            result.resize(size_needed - 1); // exclude null terminator
            WideCharToMultiByte(CP_UTF8, 0, path, -1, result.data(), size_needed, nullptr, nullptr);
        }

        CoTaskMemFree(path);
    }

    return result;
}
#endif

#ifdef PLATFORM_MAC
std::string OpenFileDialog();
std::char* GetDownloadsFolder();
#endif

#ifdef PLATFORM_LINUX
std::string OpenFileDialog();
std::char* GetDownloadsFolder();
#endif

