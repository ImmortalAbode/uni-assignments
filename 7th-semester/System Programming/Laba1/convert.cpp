#include "convert.h"

#include <vector>
#include <QString>
#include <QChar>

//Перевод из 10-чной СИ в 16-ричную СИ.
QString Convert::DecToHex(int dec_number)
{
    QString hex_number = "";
    QChar hex_chars[16]{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    int temp_number{dec_number};
    std::vector<int> mods;

    if (temp_number < 16)
    {
        hex_number += hex_chars[temp_number];
    }
    else
    {
        while (temp_number > 0)
        {
            mods.push_back(temp_number % 16);
            temp_number = temp_number / 16;
        }

        for (int i = mods.size() - 1; i >= 0; i--)
        {
            hex_number += hex_chars[mods[i]];
        }
    }
    mods.clear();
    return hex_number;
}
//Перевод из 16-ричной СИ в 10-чную СИ.
int Convert::HexToDec(QString hex_number)
{
    int dec_number = 0;
    hex_number = hex_number.toUpper();
    QString hex_numbers = "0123456789ABCDEF";

    int length = hex_number.length();
    int k = 0;

    for (int i = length - 1; i >= 0; i--)
    {
        QChar current_char = hex_number[i];
        int index = hex_numbers.indexOf(current_char);
        dec_number += index * pow(16, k);
        k++;
    }

    return dec_number;
}


