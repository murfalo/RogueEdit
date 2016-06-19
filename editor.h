#ifndef EDITOR_H
#define EDITOR_H

#include <QString>
#include <QDebug>

class Editor
{
public:
    Editor();
    ~Editor();

private:
    QString playerDataLocation; // String representing the location of playerData.txt
};

#endif // EDITOR_H
