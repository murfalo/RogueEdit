# RogueEdit

## Description
RogueEdit is an entirely free and open-source tool that allows [Roguelands][Steam] players to edit attributes of their characters.

## Installation
To download RogueEdit, check out the [releases page][releases] and download the latest release for your platform.  Compiling the project from source is also a relatively simple process:

1. Download [Qt Open Source][Qt]
2. Clone this repository
3. Open RogueEdit.pro with Qt Creator
4. Click on Projects
5. Configure the project to use your desired compiler
  * I would recommend using the "Shadow Build" option so that build files don't clutter up the source files
6. Click the green arrow in the bottom left of Qt Creator to build and run the project

## Contributing
1. **Fork** the repo on GitHub
2. **Clone** the project to your own machine
3. **Commit** changes to your own branch
4. **Push** your work back up to your fork
5. Submit a **pull request** so that I can review your changes

Note that there are some resources available for updating things such as items and combat chips [here][utilities].  These can be used to convert the [item spreadsheets][items] into the format needed by [Items.h][items.h].

## Dependencies
* [Qt Open Source][Qt]
* [Roguelands][Steam]

[Steam]: http://store.steampowered.com/app/364420/
[releases]: https://github.com/Murfalo/RogueEdit/releases
[Qt]: https://www.qt.io/download-open-source/
[utilities]: https://github.com/Murfalo/RogueEdit/tree/master/src/resources/utilities
[items]: https://github.com/Murfalo/RogueEdit/tree/master/src/resources/items
[items.h]: https://github.com/Murfalo/RogueEdit/blob/master/src/headers/items.h
