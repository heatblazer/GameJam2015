#include "TextNodes.h"
/* optional utility class */
#include <QFile>
#include <QDebug>
//#define DEBG
#include <stdlib.h>
#include <stdio.h>
/*************************************************************************
 * TODO add description
 *Optional for tests
 *
 *
 * ************************************************************************/
int TextNodes::index = 0;
char TextNodes::digits[10] = {'0','1','2','3','4','5',
                              '6','7','8','9'};
QStringList TextNodes::digitz;
int TextNodes::size = 0;
QString TextNodes::readFromFile(QString fname)
{
#ifdef DEBG
    /* C based code goes here */
#else
     QFile f(fname);
     QTextStream in(&f);
     QString retstr;
    if ( f.exists() && f.open(QIODevice::ReadOnly) ) {
        qDebug() << "OK - I`ll read the file";
        retstr.append(in.readAll());
        retstr = retstr.toLocal8Bit(); /* fixes unicoding for Windows */
        return retstr;
    } else {
        return NULL;
    }
#endif
}

char TextNodes::getNextDigit() {
    index = index > 9 ? 0 : index++;
    return digits[index++];
}
QString TextNodes::getNextDigit2() {
    index = index > size ? 0 : index;
    return digitz.at(index++);
}

void TextNodes::setDigits(int size) {
    int i=0;
    TextNodes::size = size;
    for (;  i < size; i++ ) {
        TextNodes::digitz.append(QString::number(i+1));
    }
}


