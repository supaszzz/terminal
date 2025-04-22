#include "paths.h"

std::string getConfigPath() {
    static std::string appdata = std::getenv("APPDATA");
    static auto result = appdata + "\\JBTerminal";
    return result;
}

std::string getMacroPath() {
    static auto result = getConfigPath() + "\\user.mcr";
    return result;
}
