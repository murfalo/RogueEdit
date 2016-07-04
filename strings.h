#ifndef STRINGS_H
#define STRINGS_H

#pragma once
#include <string>
#include <QString>

/* Namespace for strings! Some of these may be pedantic but it is necessary to avoid having
 * to go through and change everything if the Roguelands save format changes slightly. */
namespace Strings
{
    /*** Save Location ***/
#if defined(Q_OS_WIN)
    static const std::string playerDataPrefix = "C:/Users/";
    static const std::string playerDataSuffix = "/AppData/LocalLow/DefaultCompany/Roguelands/PlayerPrefs.txt";
    static const std::string tmpDataSuffix = "/AppData/LocalLow/DefaultCompany/Roguelands/.txt";
#elif defined(Q_OS_MAC)
    // Not yet implemented
#endif

    static const QString appTitle = "RogueEdit";

    /*** User Interface ***/

    /* Toolbar and Navigation */
    static const QString toolbarObjectName = "mainToolBar";
    static const QString navigationObjectName = "navigationWidget";
    static const QString characterMenuObjectName = "menuCharacter";
    static const QString loadCharacterDropdownObjectName = "dropdownLoad_Character";
    static const QString saveCharacterActionText = "Save Character";

    /* Item Tab */

    // Object names
    static const QString itemBrowserObjectName = "treeWidgetItemBrowser";
    static const QString itemEditorObjectName = "groupBoxItemEditor";
    static const QString itemNameEditObjectName = "lineEditItemName";

    // Titles for top level items
    static const QString itemBrowserCombatChipsTitle = "Combat Chips";

    // Indexes for top level items
    static const int itemBrowserCombatChipsIndex = 0;
    static const int itemBrowserDronesIndex = 1;
    static const int itemBrowserEquippedIndex = 2;
    static const int itemBrowserInventoryIndex = 3;

    /* Character Tab */

    static const QString nameEditObjectName = "lineEditName";

    // comboBoxes
    static const QString difficultyEditObjectName = "comboBoxDifficultyEdit";
    static const QString raceEditObjectName = "comboBoxRaceEdit";
    static const QString classEditObjectName = "comboBoxClassEdit";
    static const QString variantEditObjectName = "comboBoxVariantEdit";
    static const QString uniformEditObjectName = "comboBoxUniformEdit";
    static const QString augmentEditObjectName = "comboBoxAugmentEdit";
    static const QString allegianceEditObjectName = "comboBoxAllegianceEdit";

    // spinBoxes
    static const QString vitalityEditObjectName = "spinBoxVitVal";
    static const QString dexterityEditObjectName = "spinBoxDexVal";
    static const QString magicEditObjectName = "spinBoxMagVal";
    static const QString strengthEditObjectName = "spinBoxStrVal";
    static const QString techEditObjectName = "spinBoxTecVal";
    static const QString faithEditObjectName = "spinBoxFaiVal";
    static const QString characterLevelObjectName = "spinBoxLevelVal";
    static const QString allegianceLevelObjectName = "spinBoxAllegianceLevelVal";

    /*** Parsing  ***/

    //Current representation: "specifier : value : type; "
    static const std::string separator = ":";              // Seperates information for a specifier
    static const std::string terminator = ";";             // Terminates a specifier
    static const std::string paddedSeperator = " : ";
    static const std::string paddedTerminator = " ; ";

    /*** Specifiers ***/
    static const std::string intSpecifier = "System.Int32";
    static const std::string stringSpecifier = "System.String";
    static const std::string idSpecifier = "id";
    static const std::string nameSpecifier = "name";
    static const std::string difficultySpecifier = "prof";
    static const std::string raceSpecifier = "race";
    static const std::string classSpecifier = "class";
    static const std::string primaryStat1 = "trait0";
    static const std::string primaryStat2 = "trait1";
    static const std::string variantSpecifier = "variant";
    static const std::string uniformSpecifier = "uniform";
    static const std::string augmentSpecifier = "augment";
    static const std::string vitalitySpecifier = "pStat0";
    static const std::string dexteritySpecifier = "pStat1";
    static const std::string magicSpecifier = "pStat2";
    static const std::string strengthSpecifier = "pStat3";
    static const std::string techSpecifier = "pStat4";
    static const std::string faithSpecifier = "pStat5";
    static const std::string characterLevelSpecifier = "level";
    static const std::string characterExperienceSpecifier = "exp";
    static const std::string allegianceLevelSpecifier = "aq";
    static const std::string allegianceSpecifier = "allegiance";
    static const std::string combatChipSpecifier = "cc";


    /*** Stats and Settings */

    // Constant integers used to determine array/map sizes
    static const int NUM_DIFFICULTIES = 2;
    static const int NUM_RACES = 24;
    static const int NUM_STATS = 6;
    static const int NUM_CLASSES = 15;
    static const int NUM_VARIANTS = 3;
    static const int NUM_UNIFORMS = 24;
    static const int NUM_AUGMENTS = 25;
    static const int NUM_ALLEGIANCES = 2;

    /* Difficulty */
    static const std::string difficulties[NUM_DIFFICULTIES] = { "Normal", "Ironman"};

    /* Races */
    static const std::string races[NUM_RACES] = { "Wanderer", "Royalite", "Centurion", "Illuminate", "Shlaami", "Fishfolk", "Gekko",
                                                  "Nomad", "Deathrazor", "Hiveling", "Ancient", "Lightsworn", "Drifter", "Goblin",
                                                  "Swampfolk", "Tiki", "Titan", "Trogon", "Scaled", "Florbgon", "Oompa", "Wizened",
                                                  "Necro", "Golem" };
    /* Classes */
    // Array for retrieving class name by ID
    static const std::string classes[NUM_CLASSES] = { "Enforcer", "Gunner", "Machinist", "Darkmage", "Aethermage", "Blademaster", "Dragoon",
                                                      "Spellblade", "Aetherknight", "Bounty Hunter", "Gunmage", "Commander", "Datamancer",
                                                      "Alchemist", "Arcanist" };
    // Array for finding class name by primary stats
    static const std::string statCombos[NUM_STATS][NUM_STATS] = { { "", "Enforcer", "Gunner", "Machinist", "Darkmage", "Aethermage" },
                                                                  { "Enforcer", "", "Blademaster", "Dragoon", "Spellblade", "Aetherknight" },
                                                                  { "Gunner", "Blademaster", "", "Bounty Hunter", "Gunmage", "Commander" },
                                                                  { "Machinist", "Dragoon", "Bounty Hunter", "", "Datamancer", "Alchemist" },
                                                                  { "Darkmage", "Spellblade", "Gunmage", "Datamancer", "", "Arcanist" },
                                                                  { "Aethermage", "Aetherknight", "Commander", "Alchemist", "Arcanist", "" }};

    /* Variants */
    static const std::string variants[NUM_VARIANTS] = { "Variant 1", "Variant 2", "Variant 3" };

    /* Uniforms */
    static const std::string uniforms[NUM_UNIFORMS] = { "Fleet Cadet", "Hero", "Scholar", "Explorer", "Pyromancer", "Fairy", "Seer",
                                                        "Soldier", "Blacksmith", "President", "Gadget Worker", "Minister", "Antihero",
                                                        "Dirtmage", "Beehive", "Monster Trainer", "Scientist", "Crusader", "Echo",
                                                        "Metalgear", "Phoenix", "Cobalt Mage", "Peasant", "Overworld" };

    /* Augments */
    static const std::string augments[NUM_AUGMENTS] = { "", "Crusader Hat", "Rogue Bandana", "Berserker Scarf", "Mage Hat", "Crown", "Shmoo Hat",
                                                        "Glibglob Hat", "Beats by Boizu", "Eyepod Hat", "Slime Hat", "Slime Hat",
                                                        "Mech City Beanie", "Lucky Pumpkin", "Eye Gadget", "Baby Silver", "Oculus Goggles",
                                                        "Chamcham Hat", "Demon Horns", "Forsaker Mask", "Shroom Hat", "Halo", "Creator Mask",
                                                        "Rebellion Headpiece", "Gas Mask" };

    /* Allegiances */
    static const std::string allegiances[NUM_ALLEGIANCES] = {"Galactic Fleet", "Starlight Rebellion"};

    /*** Arrays for Iteration ***/

    // Total number of spinBoxes and comboBoxes on the character tab
    static const int NUM_SPINBOXES = 8;
    static const int NUM_COMBOBOXES = 7;

    // Arrays for use in spinBox iteration
    static const QString spinBoxObjectNames[NUM_SPINBOXES] = { vitalityEditObjectName, dexterityEditObjectName, magicEditObjectName,
                                                               strengthEditObjectName, techEditObjectName, faithEditObjectName,
                                                               characterLevelObjectName, allegianceLevelObjectName };
    static const std::string spinBoxSpecifiers[NUM_SPINBOXES] = { vitalitySpecifier, dexteritySpecifier, magicSpecifier,
                                                                  strengthSpecifier, techSpecifier, faithSpecifier,
                                                                  characterLevelSpecifier, allegianceLevelSpecifier};

    // Arrays for use in comboBox iteration
    static const QString comboBoxObjectNames[NUM_COMBOBOXES] = { difficultyEditObjectName, raceEditObjectName, classEditObjectName,
                                                                 variantEditObjectName, uniformEditObjectName, augmentEditObjectName,
                                                                 allegianceEditObjectName };
    static const std::string* comboBoxArrays[NUM_COMBOBOXES] = { &difficulties[0], &races[0], &classes[0],
                                                                 &variants[0], &uniforms[0], &augments[0],
                                                                 &allegiances[0] };
    static const std::string comboBoxSpecifiers[NUM_COMBOBOXES] = { difficultySpecifier, raceSpecifier, classSpecifier,
                                                                    variantSpecifier, uniformSpecifier, augmentSpecifier,
                                                                    allegianceSpecifier };
}

#endif
