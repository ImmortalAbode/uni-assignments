#ifndef CONVERT_H
#define CONVERT_H

#include <QString>

class Convert
{
public:
    Convert() = default;

    static QString DecToHex(int dec_number);
    static int HexToDec(QString hex_number);
    static QString SubTwoHexNumbers(const QString &hexNumber1, const QString &hexNumber2);
};

#endif // CONVERT_H
