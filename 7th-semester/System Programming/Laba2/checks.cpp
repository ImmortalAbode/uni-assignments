#include "checks.h"

#include "codeoperationtable.h"
#include "convert.h"

#include <QTextEdit>
#include <QChar>
#include <QStringList>

#include "array"

//Проверка длины символического имени (СИ).
bool Checks::CheckLengthSymbolicName(const QString &symbolic_name)
{
    if (!symbolic_name.isEmpty() && symbolic_name.length() > 6)
        return false;
    return true;
}
//Посимвольная проверка корректности СИ.
bool Checks::CheckCharsSymbolicName(const QString &symbolic_name)
{
    //Пустая метка - это нормально.
    if (symbolic_name.isEmpty())
        return true;
    //Должна начинаться с латинской буквы.
    if (!(symbolic_name[0].toUpper() >= 'A' && symbolic_name[0].toUpper() <= 'Z'))
    {
        return false;
    }
    //Остальные символы могут быть цифрами/латинскими буквами.
    for (int i{ 1 }; i < symbolic_name.length(); ++i)
    {
        QChar currentChar = symbolic_name[i];
        if (!((currentChar >= '0' && currentChar <= '9') || (currentChar.toUpper() >= 'A' && currentChar.toUpper() <= 'Z')))
        {
            return false;
        }
    }
    return true;
}
//Проверка совпадения метки с названием директивы или регистром (аналогично для МКОП в ТКО).
bool Checks::CheckIncorrectName(const QString &name)
{
    if (!CheckDirective(name.toUpper()).isEmpty() || !CheckRegister(name.toUpper()).isEmpty())
        return false;
    return true;
}
//Посимвольная проверка корректности МКОП.
bool Checks::CheckCharsMCOP(const QString& mnemonic_code)
{
    //Пустой МКОП не проверяется в данной проверке.
    if (mnemonic_code.isEmpty())
        return true;
    //Cимволы могут быть цифрами и латинскими буквами (любого регистра).
    for (int i{ 1 }; i < mnemonic_code.length(); ++i)
    {
        QChar currentChar = mnemonic_code[i];
        if (!((currentChar >= '0' && currentChar <= '9') || (currentChar >= 'A' && currentChar <= 'Z') || (currentChar >= 'a' && currentChar <= 'z')))
        {
            return false;
        }
    }
    if (!((mnemonic_code[0] >= 'A' && mnemonic_code[0] <= 'Z') || (mnemonic_code[0] >= 'a' && mnemonic_code[0] <= 'z')))
        return false;
    return true;
}

//Проверка на регистр (поле Операндная часть).
QString Checks::CheckRegister(const QString& reg){
    std::array<QString, 16> regs = {"R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15"};
    for (size_t i{}; i < regs.size(); ++i){
        if (reg == regs[i])
            return reg;
    }
    return "";
}

//Проверка ТКО.
bool Checks::CorrectTableCodeOperation(const CodeOperationTable& opCodeTable, QTextEdit* fpe_text)
{
    //Вынимаем структуру реализации хеш-таблицы, чтобы итерироваться по ней.
    const CodeOperation* opCode_Table{opCodeTable.getOpCodeTable()};
    for (size_t row{}; row < opCodeTable.getOpCodeTableSize() - 1; ++row)
    {
        //Проверка ячеек на пустоту.
        if (!opCode_Table[row].mnemonic_code.isEmpty() && (opCode_Table[row].binary_code.isEmpty() || opCode_Table[row].size.isEmpty()))
        {
            fpe_text->append("Строка " + QString::number(row + 1) + ": Пустая ячейка в ТКО не допустима.\n");
            return false;
        }
        if (opCode_Table[row].mnemonic_code.isEmpty() && (!opCode_Table[row].binary_code.isEmpty() || !opCode_Table[row].size.isEmpty()))
        {
            fpe_text->append("Строка " + QString::number(row + 1) + ": Пустая ячейка в ТКО не допустима.\n");
            return false;
        }
        //Остальные проверки уже по полностью заполненным строкам.
        if (!opCode_Table[row].mnemonic_code.isEmpty())
        {
            //Проверка ячеек на длину.
            if (opCode_Table[row].mnemonic_code.length() > 6 || opCode_Table[row].binary_code.length() > 2 || opCode_Table[row].size.length() > 1)
            {
                fpe_text->append("Строка " + QString::number(row + 1) + ": МКОП в ТКО должен быть от 1 до 6 символов, двоичный код МКОП - от 1 до 2 символов, длина МКОП в байтах - не более одного символа.\n");
                return false;
            }
            //Проверка посимвольно МКОП.
            if (!CheckCharsMCOP(opCode_Table[row].mnemonic_code))
            {
                fpe_text->append("Строка " + QString::number(row + 1) + ": МКОП в ТКО должен начинаться с буквы и не содержать некорректных символов, отличных от цифр и букв латинского алфавита.\n");
                return false;
            }
            //Проверка МКОП на зарезервированное слово.
            if (!CheckIncorrectName(opCode_Table[row].mnemonic_code))
            {
                fpe_text->append("Строка " + QString::number(row + 1) + ": МКОП в ТКО не может совпадать с директивой или регистром.\n");
                return false;
            }
            //Проверка двоичного кода МКОП.
            if (CheckAmountMemoryForAddress(opCode_Table[row].binary_code)){
                int dec_BinCode = Convert::HexToDec(opCode_Table[row].binary_code);
                const int MAX_BINARY_CODE{63};//0x3F
                if (dec_BinCode == 0)
                {
                    fpe_text->append("Строка " + QString::number(row + 1) + ": Двоичный код МКОП в 16-ричной СИ в ТКО не может быть равен 0.\n");
                    return false;
                }
                if (dec_BinCode > MAX_BINARY_CODE)
                {
                    fpe_text->append("Строка " + QString::number(row + 1) + ": Двоичный код МКОП в 16-ричной СИ в ТКО не должен превышать " + Convert::DecToHex(MAX_BINARY_CODE) + ".\n");
                    return false;
                }
            }
            else
            {
                fpe_text->append("Строка " + QString::number(row + 1) + ": Двоичный код МКОП в ТКО должен быть представлен из символов 16-ричной СИ.\n");
                return false;
            }
            //Проверка длины команды МКОП в байтах.
            if (!CheckCorrectAmountMemoryForCodeOperation(opCode_Table[row].size))
            {
                fpe_text->append("Строка " + QString::number(row + 1) + ": Допустимы команды от 1 до 4 байт (указываются в 10-чной СИ).\n");
                return false;
            }
            //Проверка уникальности МКОП в ТКО (осуществляется во время парсинга с интерфейса).
            //Проверка уникальности двоичного кода МКОП в ТКО.
            for (size_t k = row + 1; k < opCodeTable.getOpCodeTableSize() - 1; ++k)
            {
                QString first_binCode = opCode_Table[row].binary_code.rightJustified(2, '0');
                QString second_binCode = opCode_Table[k].binary_code.rightJustified(2, '0');
                if (first_binCode == second_binCode)
                {
                    fpe_text->append("Строка " + QString::number(row + 1) + ": Найдены совпадения в двоичных кодах МКОП!\nСовпадающий двоичный код МКОП: " + first_binCode + ".\n");
                    return false;
                }
            }
        }
    }
    return true;
}
//Проверка корректности указания объема памяти посимвольно.
bool Checks::CheckAmountMemoryForAddress(const QString &amountMemory)
{
    std::array<char,16> allowed_chars = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    for (auto const& chr : amountMemory)
    {
        if (std::find(allowed_chars.begin(), allowed_chars.end(), chr) == allowed_chars.end())
            return false;
    }
    return true;
}
//Проверка, что СА <= допустимого объема памяти.
bool Checks::CheckAddressCounterAvailable(QTextEdit* fpe_text, const int& row, const int &address_counter)
{
    const int MAX_AMOUNT_ALLOC_MEMORY{16777215}; //0xFFFFFF
    if (address_counter > MAX_AMOUNT_ALLOC_MEMORY)
    {
        //Если переполнение зафиксировано на текущей строке, то возникло оно на предыдущей.
        fpe_text->append("Строка " + QString::number(row) + ": Произошло переполнение СА! СА = " + Convert::DecToHex(address_counter).rightJustified(6, '0') + "\n");
        return false;
    }
    return true;
}
//Проверка каждой строки исходного кода ассмеблирующей программы.
bool Checks::CheckRowSourceCode(QTextEdit *fpe_text, const int &row, QString& prog_name, const QString &label, const QString &mnemonic_code)
{
    /*ПРОВЕРКА МЕТКИ*/
    //Длина метки.
    if (row != 0 && !CheckLengthSymbolicName(label))
    {
        fpe_text->append("Строка " + QString::number(row + 1) + ": Длина СИ должна быть не более 6 символов!\n");
        return false;
    }
    //Если метка не пустая.
    if (!label.isEmpty())
    {
        //Символы метки.
        if (row != 0 && !CheckCharsSymbolicName(label))
        {
            fpe_text->append( "Строка " + QString::number(row + 1) + ": Символическое имя содержит недопустимые символы или начинается не с буквы!\n");
            return false;
        }
        //Совпадение метки по названию.
        if (!CheckIncorrectName(label))
        {
            fpe_text->append("Строка " + QString::number(row + 1) + (row == 0 ? (": Название программы") : (": Символическое имя")) + " совпадает с директивой или регистром.\n");
            return false;
        }
        if (row != 0 && label == prog_name)
        {
            fpe_text->append("Строка " + QString::number(row + 1) + ": Символическое имя совпадает с названием программы. Измените название программы или символическое имя!\n");
            return false;
        }
        //Отсутствие директивы START на первой строке.
        if (row == 0 && mnemonic_code != "START")
        {
            fpe_text->append("Строка " + QString::number(row + 1) + ": Директива START не найдена.\n");
            return false;
        }
    }
    /*ПРОВЕРКА МКОП*/
    //Символы МКОП.
    if (!CheckCharsMCOP(mnemonic_code))
    {
        fpe_text->append("Строка " + QString::number(row + 1) + ": МКОП содержит недопустимые символы!\n");
        return false;
    }
    //Иначе все корректно.
    return true;
}
//Проверка имени программы.
QString Checks::CheckProgramName(const QString &prog_name)
{
    if (prog_name.isEmpty()) return "Имя программы не задано!\n";
    if (prog_name.length() > 6) return "Имя программы слишком длинное! Ограничение на длину: 6 символов.\n";
    for (const auto& symbol : prog_name)
    {
        int code = symbol.unicode();
        if (!((code >= 48 && code <= 57) ||   // Цифры: '0'-'9'
              (code >= 65 && code <= 90) ||   // Заглавные буквы: 'A'-'Z'
              (code >= 97 && code <= 122) ||  // Строчные буквы: 'a'-'z'
              code == 95)){                   // Подчеркивание: '_'
            return "Имя программы содержит недопустимые символы! Разрешены только цифры, буквы латинского алфавита и символ подчеркивания.\n";
        }
    }
    if (prog_name[0] >= '0' && prog_name[0] <= '9')
        return "Имя программы не может начинаться с цифры.\n";
    if (!CheckDirective(prog_name).isEmpty() || !CheckRegister(prog_name).isEmpty())
        return "Имя программы не может совпадать с директивой или регистром.\n";
    //Проверка на совпадение метки и имени программы осуществляется в проверке строк относительно меток.
    return "";
}
//Проверка адреса загрузки программы.
QString Checks::CheckProgramDownloadAddress(const QString& download_address)
{
    if (!CheckAmountMemoryForAddress(download_address))
        return "Адрес загрузки программы содержит недопустимые символы! Текущий адрес загрузки: " + download_address + ".";
    const int MAX_LENGTH_HEX_LOAD_ADDRESS{6};
    QString load_address = download_address.rightJustified(6, '0');
    if (load_address.length() > MAX_LENGTH_HEX_LOAD_ADDRESS)
        return "Строка 1: Переполнение счетчика адреса! СА = " + load_address + ".\n";
    if (Convert::HexToDec(load_address) != 0)
        return "Адрес загрузки программы неизвестен! Он должен быть равен 0 или отсутствовать.\n";

    return "";
}
//Проверка наличия операндной части после директивы..
QString Checks::CheckOtherOperandPart(const QString &second_operand, const QString& mnemonic_code, const int& row)
{
    if (!second_operand.isEmpty()){
        return "Предупреждение: Строка " + QString::number(row + 1) + ": Второй операнд после директивы " + mnemonic_code + " рассматриваться не будет!\n"
                                                                                                                            "Операнд: " + second_operand + ".\n";
    }
    return "";
}
//Проверка на директиву (поле МКОП).
QString Checks::CheckDirective(const QString &mnemonic_code)
{
    if (mnemonic_code == "START") return "START";
    if (mnemonic_code == "END") return "END";
    if (mnemonic_code == "BYTE") return "BYTE";
    if (mnemonic_code == "WORD") return "WORD";
    if (mnemonic_code == "RESB") return "RESB";
    if (mnemonic_code == "RESW") return "RESW";
    return "";
}
//Проверка корректности указания объема выделения памяти для кодов операций.
bool Checks::CheckCorrectAmountMemoryForCodeOperation(const QString &amount_memory)
{
    std::array<char,4> allowed_amount_memory = {'1','2','3','4'};
    for (auto const& chr : amount_memory)
    {
        if (std::find(allowed_amount_memory.begin(), allowed_amount_memory.end(), chr) == allowed_amount_memory.end())
        {
            return false;
        }
    }
    return true;
}
//Проверка корректности указания объема выделения памяти для директив BYTE, WORD, RESB, RESW.
bool Checks::CheckCorrectAmountMemoryForDecNumber(const QString &amount_memory)
{
    std::array<char,10> decMass = {'0','1','2','3','4','5','6','7','8','9'};
    for (auto const& chr : amount_memory){
        if (std::find(decMass.begin(), decMass.end(), chr) == decMass.end()){
            return false;
        }
    }
    return true;
}
//Проверка корректно указанного объема выделения памяти на доступность для BYTE (или в целом под байт).
bool Checks::CheckAllocAmountMemoryForByte(const QString &alloc_memory_byte){
    bool ok{};
    const int max_byte_memory{255};
    int alloc_memory_byte_int = alloc_memory_byte.toInt(&ok);
    if (!ok || alloc_memory_byte_int > max_byte_memory){
        return false;
    }
    return true;
}
//Проверка на то, что операнд после директивы BYTE начинается на 'X' и корректно задан.
bool Checks::CheckCorrectAmountMemoryForHexNumber(const QString &amount_memory)
{
    if (amount_memory.startsWith('X'))
    {
        QStringList parts = amount_memory.split('\'');
        if (parts.size() == 3 && parts[2].isEmpty() && parts[0].length() == 1 && !parts[1].isEmpty() && parts[1].length() % 2 == 0)
        {
            return true;
        }
    }
    return false;
}
//Проверка на то, что операнд после директивы BYTE начинается на 'C' и корректно задан.
bool Checks::CheckCorrectAmountMemoryForUnicodeString(const QString &amount_memory) {
    if (amount_memory.startsWith('C') &&
        amount_memory.endsWith("'") &&
        amount_memory.indexOf("'") == 1 &&
        amount_memory.lastIndexOf("'") == amount_memory.length() - 1)
    {
        return true;
    }
    return false;
}
//Проверка корректно указанного объема выделения памяти на доступность для WORD.
bool Checks::CheckAllocAmountMemoryForWord(const QString &alloc_memory)
{
    bool ok{};
    const int max_word_memory{16777215};
    int alloc_memory_word_int = alloc_memory.toInt(&ok);
    if (!ok || alloc_memory_word_int > max_word_memory)
    {
        return false;
    }
    return true;
}
//Проверка корректно указанного объема выделения памяти на доступность для RESB или RESW.
bool Checks::CheckAllocAmountMemoryForRES(const QString &alloc_memory){
    bool ok{};
    alloc_memory.toInt(&ok);
    return ok;
}
//Получение реального двоичного кода адресации со всеми проверками.
int Checks::GetDecOpcode(const QString &command_binary_code, const int &type_addressing)
{
    int opcode{};
    //Cдвиг на 2 влево.
    const int SHIFT{4};
    const int MAX_BYTE_MEMORY{255};
    //Если КОП пустой - это ошибка.
    if (command_binary_code.isEmpty())
    {
        return -1;
    }
    //Получаем десятичное представление шестнадцатиричного КОП.
    opcode = Convert::HexToDec(command_binary_code);
    //Получаем реальный двоичный код.
    opcode = opcode * SHIFT + type_addressing;
    //Если резервируемая память > байта, т.е. значения 255, то ошибка.
    if (opcode > MAX_BYTE_MEMORY)
    {
        return -1;
    }
    return opcode;
}




