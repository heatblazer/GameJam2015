#ifndef TEXTNODES_H
#define TEXTNODES_H
#include <QStringList>
class TextNodes {
private:
    static char digits[10];//deprecate
    static QStringList digitz;
    static int index;
    static int size;
   public:
    static QString readFromFile(QString fname);
    static char getNextDigit();
    static QString getNextDigit2();
    static void setDigits(int);

};

#endif // TEXTNODES_H
