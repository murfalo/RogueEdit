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

    static const int NUM_RACES = 24;
    static const int NUM_STATS = 6;       // NUM_STATS is used instead of NUM_CLASSES b/c class depends only on primary stats of a character
    static const int NUM_VARIANTS = 3;
    static const int NUM_UNIFORMS = 24;
    static const int NUM_AUGMENTS = 24;
    static const std::string races[NUM_RACES] = { "Wanderer", "Royalite", "Centurion", "Illuminate", "Shlaami", "Fishfolk", "Gekko",
                                                  "Nomad", "Deathrazor", "Hiveling", "Ancient", "Lightsworn", "Drifter", "Goblin",
                                                  "Swampfolk", "Tiki", "Titan", "Trogon", "Scaled", "Florbgon", "Oompa", "Wizened",
                                                  "Necro", "Golem" };
    static const std::string classes[NUM_STATS][NUM_STATS] = { { "", "Enforcer", "Gunner", "Machinist", "Darkmage", "Aethermage" },
                                                               { "Enforcer", "", "Blademaster", "Dragoon", "Spellblade", "Aetherknight" },
                                                               { "Gunner", "Blademaster", "", "Bounty Hunter", "Gunmage", "Commander" },
                                                               { "Machinist", "Dragoon", "Bounty Hunter", "", "Datamancer", "Alchemist" },
                                                               { "Darkmage", "Spellblade", "Gunmage", "Datamancer", "", "Arcanist" },
                                                               { "Aethermage", "Aetherknight", "Commander", "Alchemist", "Arcanist", "" }};
    static const std::string variants[NUM_VARIANTS] = { "Variant 1", "Variant 2", "Variant 3" };
    static const std::string uniforms[NUM_UNIFORMS] = { "Fleet Cadet", "Hero", "Scholar", "Explorer", "Pyromancer", "Fairy", "Seer",
                                                        "Soldier", "Blacksmith", "President", "Gadget Worker", "Minister", "Antihero",
                                                        "Dirtmage", "Beehive", "Monster Trainer", "Scientist", "Crusader", "Echo",
                                                        "Metalgear", "Phoenix", "Cobalt Mage", "Peasant", "Overworld" };
    static const std::string augments[NUM_AUGMENTS] = { "Crusader Hat", "Rogue Bandana", "Berserker Scarf", "Mage Hat", "Crown", "Shmoo Hat",
                                                        "Glibglob Hat", "Beats by Boizu", "Eyepod Hat", "Slime Hat", "Slime Hat",
                                                        "Mech City Beanie", "Lucky Pumpkin", "Eye Gadget", "Baby Silver", "Oculus Goggles",
                                                        "Chamcham Hat", "Demon Horns", "Forsaker Mask", "Shroom Hat", "Halo", "Creator Mask",
                                                        "Rebellion Headpiece", "Gas Mask" };
}
#endif
