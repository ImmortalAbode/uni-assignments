#ifndef CONVERT_H
#define CONVERT_H

#include <QString>

class Convert
{
public:
    Convert() = default;

    static QString DecToHex(int dec_number);
    static int HexToDec(QString hex_number);
};

#endif // CONVERT_H
