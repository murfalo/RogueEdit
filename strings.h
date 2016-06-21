#pragma once
#include <string>
#include <QString>

/* Namespace for commonly used strings so I don't have to find and replace a million times
 * Some of these may be pedantic but it is necessary to having to go through and change everything
 * if the Roguelands save format changes slightly. */
namespace Strings
{
    // The location of the save file is different on Windows and Mac
#if defined(Q_OS_WIN)
    static const std::string playerDataPrefix = "C:/Users/";
    static const std::string tmpLocationPrefix = playerDataPrefix;
    static const std::string playerDataSuffix = "/AppData/LocalLow/DefaultCompany/Roguelands/PlayerPrefs.txt";
    static const std::string tmpLocationSuffix = "/AppData/LocalLow/DefaultCompany/Roguelands/tmp.txt";
#elif defined(Q_OS_MAC)
    // Not yet implemented
#endif
    static const QString appTitle = "RogueEdit";

    // Strings for parsing PlayerPrefs.txt
    static const std::string separator = ":";
    static const std::string terminator = ";";
    static const std::string intSpecifier = "System.Int32";
    static const std::string stringSpecifier = "System.String";
    static const std::string nameSpecifier = "name";

    // Strings for UI
    static const QString toolbarObjectName = "mainToolBar";
    static const QString characterMenuObjectName = "menuCharacter";
    static const QString loadCharacterDropdownObjectName = "dropdownLoad_Character";
    static const QString saveCharacterActionText = "Save Character";
}
