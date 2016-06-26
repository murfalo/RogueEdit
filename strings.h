#ifndef STRINGS_H
#define STRINGS_H

#pragma once
#include <string>
#include <QString>

/* Namespace for strings! Some of these may be pedantic but it is necessary to avoid having
 * to go through and change everything if the Roguelands save format changes slightly. */
namespace Strings
{
    // The location of the save file is different on Windows and Mac
#if defined(Q_OS_WIN)
    static const std::string playerDataPrefix = "C:/Users/";
    static const std::string playerDataSuffix = "/AppData/LocalLow/DefaultCompany/Roguelands/PlayerPrefs.txt";
    static const std::string tmpDataSuffix = "/AppData/LocalLow/DefaultCompany/Roguelands/.txt";
#elif defined(Q_OS_MAC)
    // Not yet implemented
#endif

    static const QString appTitle = "RogueEdit";

    // Strings for UI
    static const QString toolbarObjectName = "mainToolBar";
    static const QString characterMenuObjectName = "menuCharacter";
    static const QString loadCharacterDropdownObjectName = "dropdownLoad_Character";
    static const QString saveCharacterActionText = "Save Character";

    /* Strings for parsing PlayerPrefs.txt.
     * Current representation: "specifier : value : type; " */
    static const std::string separator = ":";   // Seperates information for a specifier
    static const std::string terminator = ";";  // Terminates a specifier
    static const std::string paddedSeperator = " : ";
    static const std::string paddedTerminator = " ; ";

    // (Soon to be) Long list of specifiers
    static const std::string intSpecifier = "System.Int32";
    static const std::string stringSpecifier = "System.String";
    static const std::string nameSpecifier = "name";

    static const int NUM_CLASSES = 15;   // Number of character classes
    static const int NUM_STATS = 6;
    static const std::string classes[NUM_STATS][NUM_STATS] = { { NULL, "Enforcer", "Gunner", "Machinist", "Darkmage", "Aethermage" },
                                                               { "Enforcer", NULL, "Blademaster", "Dragoon", "Spellblade", "Aetherknight" },
                                                               { "Gunner", "Blademaster", NULL, "Bounty Hunter", "Gunmage", "Commander" },
                                                               { "Machinist", "Dragoon", "Bounty Hunter", NULL, "Datamancer", "Alchemist" },
                                                               { "Darkmage", "Spellblade", "Gunmage", "Datamancer", NULL, "Arcanist" },
                                                               { "Aethermage", "Aetherknight", "Commander", "Alchemist", "Arcanist", NULL }};
}
#endif
