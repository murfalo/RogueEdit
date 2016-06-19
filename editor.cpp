#include "editor.h"

Editor::Editor()
{
    // Determine the username
    QString username = qgetenv("USER");
    if (username.isEmpty())
        username = qgetenv("USERNAME");

    // The location of the save file is different on Windows and Mac
#if defined(Q_OS_WIN)
    this->playerDataLocation = "C:/Users/" + username + "/AppData/LocalLow/DefaultCompany/Roguelands/PlayerPrefs.txt";
#elif defined(Q_OS_MAC)
    this->playerDataLocation = "not yet implemented";
#endif
}

Editor::~Editor() {}
