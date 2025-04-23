#include "paths.h"

std::string getConfigPath() {
#ifdef _WIN32
    static std::string appdata = std::getenv("APPDATA");
    static auto result = appdata + "\\JBTerminal";
#else
    static std::string appdata = std::getenv("HOME");
    static auto result = appdata + "/.config/JBTerminal";
#endif
    return result;
}

std::string getMacroPath() {
#ifdef _WIN32
    static auto result = getConfigPath() + "\\user.mcr";
#else
    static auto result = getConfigPath() + "/user.mcr";
#endif
    return result;
}
