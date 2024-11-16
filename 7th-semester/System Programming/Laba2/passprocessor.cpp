#include "passprocessor.h"

#include "StructAssemblerLine.h"
#include "codeoperationtable.h"
#include "symbolicnamestable.h"
#include "StructSupportTable.h"
#include "checks.h"
#include "convert.h"

#include <vector>
#include <QTableWidget>
#include <QTextEdit>
#include <QString>

bool PassProcessor::LoadSymbolicNamesTable(QTextEdit* fpe_text, const std::vector<AssemblerInstruction>& sourceText_code, const CodeOperationTable& opCode_table,
                                                QTableWidget* aux_table, std::vector<SupportTable>& sup_table,
                                                QTableWidget* table_symbolic_names, SymbolicNamesTable& symb_table)
{
    //Очищаем таблицы и устанавливаем 4 столбца во вспомогательной таблице и 2 столбца в ТСИ.
    aux_table->clear();
    aux_table->setColumnCount(4);
    aux_table->setRowCount(1);

    table_symbolic_names->clear();
    table_symbolic_names->setColumnCount(2);
    table_symbolic_names->setRowCount(1);

    //Очищаем поле с ошибками.
    fpe_text->clear();

    /*Адреса (хранятся в 10-ичной системе).*/
    //Счетчик адреса (СА).
    this->addressCounter = 0;
    //Адрес загрузки программы.
    this->start_prog_address = 0;
    //Адрес точки входа в программу.
    this->end_prog_address = 0;

    //Название программы.
    QString prog_name{};

    //Флаги для учета найденных директив START и END.
    bool start_dir_flag{false};
    bool end_dir_flag{false};

    //Проверка ТКО.
    if (!check.CorrectTableCodeOperation(opCode_table, fpe_text))
        return false;

    //Построчно обрабатываем каждую строку исходной программы.
    for (size_t i{}; i < sourceText_code.size(); ++i)
    {
        //Извлекаем текущую инструкцию.
        const AssemblerInstruction &instruction = sourceText_code[i];
        /*-------------------------------------------------------------------------------------------------------------
         * 1. Разбиваем строку на составляющие: Метка | МКОП | Операндная часть (операнд 1 | операнд 2 (опционально)).|
         -------------------------------------------------------------------------------------------------------------*/
        QString label = instruction.label.value_or("");
        QString mnemonic = instruction.mnemonic.toUpper();
        QString operand1 = instruction.operand1;
        QString operand2 = instruction.operand2.value_or("");
        //Наличие метки.
        bool label_flag{false};

        //Если найдена директива START, то имеет смысл проверять СА на допустимость.
        if (start_dir_flag)
        {
            //Адрес загрузки программы записан в СА и необходимо проверить, чтобы СА не выходил за максимальный допустимый объем памяти (0xFFFFFF).
            if (!check.CheckAddressCounterAvailable(fpe_text, i, this->addressCounter))
                return false;
        }
        //Если найдена директива END - выход.
        if (end_dir_flag)
            break;

        //Проверка строки исходного текста программы на корректность.
        if (!check.CheckRowSourceCode(fpe_text, i, prog_name, label, mnemonic))
        {
            return false;
        }
        /*------------------------
         * 2. Поиск метки в ТСИ. |
         ------------------------*/
        //Название программы опускается за счет флага start_flag далее.
        //Найдена существующая метка.
        QString address{};
        if (symb_table.find(label, address))
        {
            fpe_text->append("Строка ТСИ " + QString::number(i + 1) + ": Дважды определенное символическое имя " + label + ".\n");
            return false;
        }
        else
        {
            //Если метка не пустая и встречена после нахождения директивы START, то добавляем в ТСИ.
            //Метка корректная.
            if (!label.isEmpty() && start_dir_flag)
            {
                symb_table.insert(label, Convert::DecToHex(addressCounter).rightJustified(6, '0'));
                this->TManager.LoadOneLineToSymbolicNamesTable(table_symbolic_names, symb_table, label);
                label_flag = true;
            }
            /*---------------------------
             * 3. Анализируем поле МКОП |
             ---------------------------*/
            //Если поле МКОП пустое, то ошибка. Иначе продолжаем...
            if (!mnemonic.isEmpty())
            {
                //Проверяем - это директива?
                QString current_mnemonic_code = check.CheckDirective(mnemonic);
                if (current_mnemonic_code != "")
                {
                    if (current_mnemonic_code == "START"){
                        //Если START не в начале исходного текста ассемблирующей программы и встречен еще раз - это ошибка.
                        if (i == 0 && !start_dir_flag)
                        {
                            start_dir_flag = true;

                            QString error{};
                            //Имя программы.
                            error = check.CheckProgramName(label);
                            if (error != ""){
                                fpe_text->append(error);
                                return false;
                            }
                            else
                                prog_name = label;

                            //Проверка адреса загрузки программы.
                            error = check.CheckProgramDownloadAddress(operand1);
                            if (error != ""){
                                fpe_text->append(error);
                                return false;
                            }

                            //Проверка оставшейся операндной части.
                            error = check.CheckOtherOperandPart(operand2, mnemonic, i);
                            if (error != ""){
                                fpe_text->append(error);
                            }

                            //Устанавливаем Адрес загрузки программы и увеличиваем СА = СА + Адрес загрузки программы (СА = Адрес загрузки программы).
                            if (operand1.isEmpty())
                            {
                                this->start_prog_address = 0;
                                fpe_text->append("Предупреждение: Строка " + QString::number(i + 1) + ": АЗ программы был установлен равным 0. Ассемблирующая программа в перемещаемом формате.\n");
                            }
                            else
                                this->start_prog_address = Convert::HexToDec(operand1);
                            this->addressCounter = Convert::HexToDec(operand1);
                            //Выводим в вспомогательную таблицу строчку.
                            sup_table.push_back({label, mnemonic, operand1, ""});
                            this->TManager.LoadOneLineToSupportTable(aux_table, sup_table[i]);
                        }
                        else
                        {
                            fpe_text->append("Строка " + QString::number(i + 1) + ": Директива START найдена повторно.\n");
                            return false;
                        }
                    }
                    if (current_mnemonic_code == "END"){
                        if (start_dir_flag && !end_dir_flag)
                        {
                            if (!label_flag)
                            {
                                end_dir_flag = true;
                                if (operand1.isEmpty())
                                {
                                    this->end_prog_address = this->start_prog_address;
                                    fpe_text->append("Предупреждение: Строка " + QString::number(i + 1) + ": Адрес точки входа в программу установлен таким же, как адрес загрузки программы.\n");
                                }
                                else
                                {
                                    if (!check.CheckAmountMemoryForAddress(operand1))
                                    {
                                        fpe_text->append("Строка " + QString::number(i + 1) + ": Адрес точки входа программы содержит недопустимые символы!\n");
                                        return false;
                                    }
                                    else
                                    {
                                        //Устанавливаем адрес точки входа.
                                        this->end_prog_address = Convert::HexToDec(operand1);
                                    }
                                }
                                //Директива END встречена не в конце программы.
                                if (i != sourceText_code.size() - 1)
                                {
                                    fpe_text->append("Предупреждение: Строка " + QString::number(i + 1) + ": Весь следующий текст программы после строки с директивой END учитываться не будет.\n");
                                }
                                //Если Точка входа программы не укладывается в адресное пространство.
                                if (end_prog_address < start_prog_address || end_prog_address > this->addressCounter)
                                {
                                    fpe_text->append("Строка " + QString::number(i + 1) + ": Точка входа программы не укладывается в адресное пространство (Директива END)!");
                                    return false;
                                }
                                //Второй операнд не учитывается.
                                QString error = check.CheckOtherOperandPart(operand2, mnemonic, i);
                                if (error != ""){
                                    fpe_text->append(error);
                                }
                                //Выводим в вспомогательную таблицу строчку.
                                QString str_AC = Convert::DecToHex(addressCounter).rightJustified(6, '0');
                                sup_table.push_back({str_AC, mnemonic, operand1, ""});
                                this->TManager.LoadOneLineToSupportTable(aux_table, sup_table[i]);
                            }
                            else
                            {
                                fpe_text->append("Строка " + QString::number(i + 1) + ": Обнаружена метка перед директивой END.\nМетка = " + label + ".\n");
                                return false;
                            }
                        }
                        else
                        {
                            fpe_text->append("Строка " + QString::number(i + 1) + ": Директива END обнаружена без директивы START.");
                            return false;
                        }
                    }
                    if (current_mnemonic_code == "BYTE")
                    {
                        if (!start_dir_flag)
                        {
                            fpe_text->append("Строка " + QString::number(i + 1) + ": Отсутствует директива START!\n");
                            return false;
                        }
                        if (label_flag)
                        {
                            //Если операнд не пуст.
                            if (!operand1.isEmpty())
                            {
                                //Значит под выделенный байт записывается десятичное число.
                                if (check.CheckCorrectAmountMemoryForDecNumber(operand1))
                                {
                                    //Если десятичное число умещается в байт.
                                    if (check.CheckAllocAmountMemoryForByte(operand1))
                                    {
                                        //Выводим в вспомогательную таблицу строчку.
                                        QString str_AC = Convert::DecToHex(addressCounter).rightJustified(6, '0');
                                        sup_table.push_back({str_AC, mnemonic, operand1, ""});
                                        this->TManager.LoadOneLineToSupportTable(aux_table, sup_table[i]);
                                        //Увеличиваем СА = СА + кол-во рез. памяти.
                                        //СА = СА + 1
                                        addressCounter += 1;
                                    }
                                    else
                                    {
                                        fpe_text->append("Строка " + QString::number(i + 1) + ": Переполнение допустимого выделения памяти для BYTE.\n");
                                        return false;
                                    }
                                }
                                //или 16-ричное число или юникодная строка - неважно, главное, чтобы СА не переполнился, а число уместилось  в байт.
                                else
                                {
                                    //Выделение под 16-ричное число.
                                    if (check.CheckCorrectAmountMemoryForHexNumber(operand1) && check.CheckAmountMemoryForAddress(operand1.split('\'')[1]))
                                    {
                                        //Выводим в вспомогательную таблицу строчку.
                                        QString str_AC = Convert::DecToHex(addressCounter).rightJustified(6, '0');
                                        sup_table.push_back({str_AC, mnemonic, operand1, ""});
                                        this->TManager.LoadOneLineToSupportTable(aux_table, sup_table[i]);
                                        //Увеличваем СА = СА + кол-во рез. памяти (длина числа / 2, 2 символа = 1 байт).
                                        int operand_length = operand1.split('\'')[1].length();
                                        addressCounter += operand_length / 2;
                                    }
                                    //Иначе под ASCII строку или ошибка.
                                    else
                                    {
                                        //Выделение под юникодную строку.
                                        if (check.CheckCorrectAmountMemoryForUnicodeString(operand1))
                                        {
                                            //Выводим в вспомогательную таблицу строчку.
                                            QString str_AC = Convert::DecToHex(addressCounter).rightJustified(6, '0');
                                            sup_table.push_back({str_AC, mnemonic, operand1, ""});
                                            this->TManager.LoadOneLineToSupportTable(aux_table, sup_table[i]);
                                            //Увеливаем СА = СА + кол-во рез. памяти (длина юникодной строки, каждый символ = 1 байт).
                                            int operand_length = operand1.mid(2, sup_table[i].operand1.length() - 3).trimmed().length();
                                            addressCounter += operand_length;
                                        }
                                        //Иначе неизвестно, что задано.
                                        else
                                        {
                                            fpe_text->append("Строка " + QString::number(i + 1) + ": Неверно задан операнд для BYTE!\n");
                                            return false;
                                        }
                                    }
                                }
                                //Если был задан второй операнд, то от игнорируется.
                                QString error = check.CheckOtherOperandPart(operand2, mnemonic, i);
                                if (error != ""){
                                    fpe_text->append(error);
                                }
                            }
                            //Иначе ошибка в задании операнда - его нет.
                            else
                            {
                                fpe_text->append("Строка " + QString::number(i + 1) + ": Значение операнда не может быть пустым (BYTE)!\n");
                                return false;
                            }
                        }
                        //Директива должна содержать метку.
                        else
                        {
                            fpe_text->append("Строка " + QString::number(i + 1) + ": Отсутствует метка перед директивой BYTE.");
                            return false;
                        }
                    }
                    if (current_mnemonic_code == "WORD")
                    {
                        if (!start_dir_flag)
                        {
                            fpe_text->append("Строка " + QString::number(i+1) + ": Отсутствует директива START!\n");
                            return false;
                        }
                        if (label_flag)
                        {
                            //Если операнд не пуст.
                            if (!operand1.isEmpty())
                            {
                                //Проверка операнда на десятичное число.
                                if (check.CheckCorrectAmountMemoryForDecNumber(operand1))
                                {
                                    //Максимум на значение выделяется 3 байта (как и на значение СА).
                                    if (check.CheckAllocAmountMemoryForWord(operand1))
                                    {
                                        //Выводим в вспомогательную таблицу строчку.
                                        QString str_AC = Convert::DecToHex(addressCounter).rightJustified(6, '0');
                                        sup_table.push_back({str_AC, mnemonic, operand1, ""});
                                        this->TManager.LoadOneLineToSupportTable(aux_table, sup_table[i]);
                                        //Увеличиваем СА = СА + кол-во рез. памяти (3 байт).
                                        addressCounter += 3;
                                    }
                                    else
                                    {
                                        fpe_text->append("Строка " + QString::number(i + 1) + ": Переполнение допустимого выделения памяти для WORD.\n");
                                        return false;
                                    }
                                }
                                //Иначе ошибка.
                                else
                                {
                                    fpe_text->append("Строка " + QString::number(i + 1) + ": Неверно задан операнд для WORD!\n");
                                    return false;
                                }
                                //Второй операнд игнорируется.
                                QString error = check.CheckOtherOperandPart(operand2, mnemonic, i);
                                if (error != ""){
                                    fpe_text->append(error);
                                }
                            }
                            //Операнд не может быть пустым.
                            else
                            {
                                fpe_text->append("Строка " + QString::number(i + 1) + ": Значение операнда не может быть пустым (WORD)!\n");
                                return false;
                            }
                        }
                        //Метка обязана быть.
                        else
                        {
                            fpe_text->append("Строка " + QString::number(i + 1) + ": Отсутствует метка перед директивой WORD.");
                            return false;
                        }
                    }
                    if (current_mnemonic_code == "RESB")
                    {
                        if (!start_dir_flag)
                        {
                            fpe_text->append("Строка " + QString::number(i+1) + ": Отсутствует директива START!\n");
                            return false;
                        }
                        if (label_flag){
                            if (!operand1.isEmpty())
                            {
                                //Если можно преобразовать в число.
                                if (check.CheckCorrectAmountMemoryForDecNumber(operand1))
                                {
                                    //В пределах логичного (размерность Int - 4 байт: по 2 байта в обе стороны).
                                    if (check.CheckAllocAmountMemoryForRES(operand1))
                                    {
                                        //Выводим в вспомогательную таблицу строчку.
                                        QString str_AC = Convert::DecToHex(addressCounter).rightJustified(6, '0');
                                        sup_table.push_back({str_AC, mnemonic, operand1, ""});
                                        this->TManager.LoadOneLineToSupportTable(aux_table, sup_table[i]);
                                        //СА = СА + кол-во рез. памяти (т.е. кол-во байт * 1, т.к. подсчет СА в байтах).
                                        int reserve_byte_memory = operand1.toInt(nullptr, 10) * 1;
                                        addressCounter += reserve_byte_memory;
                                    }
                                    else
                                    {
                                        fpe_text->append("Строка " + QString::number(i + 1) + ": Переполнение допустимого выделения памяти для RESB!\n");
                                        return false;
                                    }
                                }
                                else
                                {
                                    fpe_text->append("Строка " + QString::number(i + 1) + ": Неверно задан операнд для RESB!\n");
                                    return false;
                                }
                                //Второй операнд игнорируется.
                                QString error = check.CheckOtherOperandPart(operand2, mnemonic, i);
                                if (error != "")
                                {
                                    fpe_text->append(error);
                                }
                            }
                            //Операнд не может быть пустым.
                            else
                            {
                                fpe_text->append("Строка " + QString::number(i + 1) + ": Значение операнда не может быть пустым (RESB)!\n");
                                return false;
                            }
                        }
                        //Метка обязана быть.
                        else
                        {
                            fpe_text->append("Строка " + QString::number(i + 1) + ": Отсутствует метка перед директивой RESB.");
                            return false;
                        }
                    }
                    if (current_mnemonic_code == "RESW")
                    {
                        if (!start_dir_flag)
                        {
                            fpe_text->append("Строка " + QString::number(i+1) + ": Отсутствует директива START!\n");
                            return false;
                        }
                        if (label_flag)
                        {
                            if (!operand1.isEmpty())
                            {
                                //Можно преобразовать в число.
                                if (check.CheckCorrectAmountMemoryForDecNumber(operand1))
                                {
                                    //Как и для RESB - в пределах логичного.
                                    if (check.CheckAllocAmountMemoryForRES(operand1))
                                    {
                                        //Выводим в вспомогательную таблицу строчку.
                                        QString str_AC = Convert::DecToHex(addressCounter).rightJustified(6, '0');
                                        sup_table.push_back({str_AC, mnemonic, operand1, ""});
                                        this->TManager.LoadOneLineToSupportTable(aux_table, sup_table[i]);
                                        //СА = СА + кол-во рез. памяти (число * 3 байт).
                                        int reserve_word_memory = operand1.toInt(nullptr, 10) * 3;
                                        addressCounter += reserve_word_memory;
                                    }
                                    else
                                    {
                                        fpe_text->append("Строка " + QString::number(i + 1) + ": Переполнение допустимого выделения памяти для RESW!\n");
                                        return false;
                                    }
                                }
                                else
                                {
                                    fpe_text->append("Строка " + QString::number(i + 1) + ": Неверно задан операнд для RESW!\n");
                                    return false;
                                }
                                //Второй операнд игнорируется.
                                QString error = check.CheckOtherOperandPart(operand2, mnemonic, i);
                                if (error != "")
                                {
                                    fpe_text->append(error);
                                }
                            }
                            //Операнд не может быть пустым.
                            else
                            {
                                fpe_text->append("Строка " + QString::number(i + 1) + ": Значение операнда не может быть пустым (RESW)!\n");
                                return false;
                            }
                        }
                        //Метка обязана быть.
                        else
                        {
                            fpe_text->append("Строка " + QString::number(i + 1) + ": Отсутствует метка перед директивой RESW.");
                            return false;
                        }
                    }
                }
                //Проверяем - это команда?
                else
                {
                    //Получение команды из ТКО.
                    CodeOperation opCode{};
                    //Если оманда найдена.
                    if (opCode_table.find(mnemonic.toUpper(), opCode))
                    {
                        if (!start_dir_flag)
                        {
                            fpe_text->append("Строка " + QString::number(i+1) + ": Отсутствует директива START!\n");
                            return false;
                        }
                        //Различная обработка в зависимости от байт команды - обработка общая, не специализрованная на определенные команды.
                        //Однобайтная команда.
                        if (opCode.size == "1")
                        {
                            //Один байт выделяется под МКОП, на операнды памяти не выделяется - они не рассматриваются. Например, NOP.
                            //Тип адресации считается никаким, т.е прибавляется 0.
                            //Реальный дв.код = дв.код * 4 + тип адр.
                            int opcode = check.GetDecOpcode(opCode.binary_code, 0);
                            if (opcode != -1)
                            {
                                //Выводим в вспомогательную таблицу строчку.
                                QString str_AC = Convert::DecToHex(addressCounter).rightJustified(6, '0');
                                sup_table.push_back({str_AC, Convert::DecToHex(opcode).rightJustified(2, '0'), "", ""});
                                this->TManager.LoadOneLineToSupportTable(aux_table, sup_table[i]);
                                //Увеличиваем СА = СА + длина команды.
                                addressCounter += 1;
                                //Операнды не учитываются.
                                if (!operand1.isEmpty() || !operand2.isEmpty())
                                {
                                    fpe_text->append("Предупреждение: Строка " + QString::number(i + 1) + ": Операнды учитываться не будут в команде " +
                                                         opCode.mnemonic_code + "!\n");
                                }
                            }
                        }
                        //Двухбайтная команда.
                        if (opCode.size == "2")
                        {
                            //Один байт выделяется под МКОП, на операнды выделяется либо по 4 бита (регистры), либо 1 байт (целое число).
                            //Если первый операнд - число, то это непосредственная адресация.
                            //Если можно преобразовать в десятичное число.
                            if (check.CheckCorrectAmountMemoryForDecNumber(operand1))
                            {
                                //Если умещается в байт.
                                if (check.CheckAllocAmountMemoryForByte(operand1))
                                {
                                    //Реальный дв.код = дв.код * 4 + тип адр.
                                    int opcode = check.GetDecOpcode(opCode.binary_code, 0);
                                    if (opcode != -1)
                                    {
                                        //Выводим в вспомогательную таблицу строчку.
                                        QString str_AC = Convert::DecToHex(addressCounter).rightJustified(6, '0');
                                        sup_table.push_back({str_AC, Convert::DecToHex(opcode).rightJustified(2, '0'), operand1, ""});
                                        this->TManager.LoadOneLineToSupportTable(aux_table, sup_table[i]);
                                        //Увеличиваем СА = СА + длина команды.
                                        addressCounter += 2;
                                        //Второй операнд не учитывается.
                                        if (!operand2.isEmpty())
                                        {
                                            fpe_text->append("Предупреждение: Строка " + QString::number(i + 1) + ": Второй операнд учитываться не будет в команде " +
                                                                 opCode.mnemonic_code + "!\nОперанд: " + operand2 + ".\n");
                                        }
                                    }
                                }
                                else
                                {
                                    fpe_text->append("Строка " + QString::number(i + 1) + ": Переполнение допустимого выделения памяти для операнда.\n");
                                    return false;
                                }
                            }
                            //Иначе это регистровая адресация == непосредственная (по абстрактному ассемблеру) или относительная.
                            else
                            {
                                //Если регистры.
                                if (!check.CheckRegister(operand1).isEmpty() && !check.CheckRegister(operand2).isEmpty())
                                {
                                    //Реальный дв.код = дв.код * 4 + тип адр.
                                    int opcode = check.GetDecOpcode(opCode.binary_code, 0);
                                    if (opcode != -1)
                                    {
                                        //Выводим в вспомогательную таблицу строчку.
                                        QString str_AC = Convert::DecToHex(addressCounter).rightJustified(6, '0');
                                        sup_table.push_back({str_AC, Convert::DecToHex(opcode).rightJustified(2, '0'), operand1, operand2});
                                        this->TManager.LoadOneLineToSupportTable(aux_table, sup_table[i]);
                                        //Увеличиваем СА = СА + длина команды.
                                        addressCounter += 2;
                                    }
                                }
                                else
                                {
                                    fpe_text->append("Строка " + QString::number(i + 1) + ": Операнды должны представлять собой регистры в команде " +
                                                         opCode.mnemonic_code + "!\n");
                                    return false;
                                }
                            }
                        }
                        //Трехбайтная команда.
                        if (opCode.size == "3")
                        {
                            //Один байт выделяется под МКОП, на операнды выделяется 2 байта.
                            //Тип адресации прямая или относительная (зависит от модификаторов операндной части []).
                            if (operand1.isEmpty())
                            {
                                fpe_text->append("Строка " + QString::number(i + 1) + ": Не обнаружена операндная часть в команде " + opCode.mnemonic_code + "!\n");
                                return false;
                            }
                            int opcode = 0;
                            //Относительная адресация = 2б.
                            if ((operand1[0] == '[') && (operand1[operand1.length() - 1] == ']') && (this->start_prog_address == 0))
                                opcode = check.GetDecOpcode(opCode.binary_code, 2);
                            //Прямая адресация = 1б.
                            else
                                opcode = check.GetDecOpcode(opCode.binary_code, 1);
                            if (opcode != -1)
                            {
                                //Выводим в вспомогательную таблицу строчку.
                                QString str_AC = Convert::DecToHex(addressCounter).rightJustified(6, '0');
                                sup_table.push_back({str_AC, Convert::DecToHex(opcode).rightJustified(2, '0'), operand1, ""});
                                this->TManager.LoadOneLineToSupportTable(aux_table, sup_table[i]);
                                //Увеличиваем СА = СА + длина команды.
                                addressCounter += 3;
                                //Второй операнд не учитывается.
                                if (!operand2.isEmpty())
                                {
                                    fpe_text->append("Предупреждение: Строка " + QString::number(i + 1) + ": Второй операнд учитываться не будет в команде " +
                                                         opCode.mnemonic_code + "!\nОперанд: " + operand2 + ".\n");
                                }
                            }
                        }
                        //Четырехбайтная команда.
                        if (opCode.size == "4")
                        {
                            //Один байт выделяется под МКОП, на операнды выделяется 3 байта.
                            //Тип адресации прямая или относительная (зависит от модификаторов операндной части []).
                            if (operand1.isEmpty())
                            {
                                fpe_text->append("Строка " + QString::number(i + 1) + ": Не обнаружена операндная часть в команде " + opCode.mnemonic_code + "!\n");
                                return false;
                            }
                            int opcode = 0;
                            //Относительная адресация = 2б.
                            if ((operand1[0] == '[') && (operand1[operand1.length() - 1] == ']') && (this->start_prog_address == 0))
                                opcode = check.GetDecOpcode(opCode.binary_code, 2);
                            //Прямая адресация = 1б.
                            else
                                opcode = check.GetDecOpcode(opCode.binary_code, 1);
                            if (opcode != -1)
                            {
                                //Выводим в вспомогательную таблицу строчку.
                                QString str_AC = Convert::DecToHex(addressCounter).rightJustified(6, '0');
                                sup_table.push_back({str_AC, Convert::DecToHex(opcode).rightJustified(2, '0'), operand1, ""});
                                this->TManager.LoadOneLineToSupportTable(aux_table, sup_table[i]);
                                //Увеличиваем СА = СА + длина команды.
                                addressCounter += 4;
                                //Второй операнд не учитывается.
                                if (!operand2.isEmpty())
                                {
                                    fpe_text->append("Предупреждение: Строка " + QString::number(i+1) + ": Второй операнд учитываться не будет в команде " +
                                                         opCode.mnemonic_code + "!\nОперанд: " + operand2 + ".\n");
                                }
                            }
                        }
                    }
                    //Значит - что-то непонятное.
                    else
                    {
                        fpe_text->append("Строка " + QString::number(i+1) + ": МКОП не найден в ТКО.");
                        return false;
                    }
                }
            }
            else
            {
                fpe_text->append("Строка " + QString::number(i + 1) + ": Поле МКОП не может быть пустым.");
                return false;
            }
        }
    }
    if (!end_dir_flag)
    {
        fpe_text->append("Не найдена точка входа в программу (END)!");
        return false;
    }
    //Если все хорошо - выход.
    return true;
}

bool PassProcessor::LoadBinaryCodeText(QTableWidget *omh_table, QTableWidget *settings_table, QTextEdit *spe_text, QTextEdit *binaryCode_text,
                                       const std::vector<SupportTable> &sup_table, const SymbolicNamesTable &symb_table)
{
    //Очищаем таблицу заголовка объектного модуля.
    omh_table->clear();
    omh_table->setColumnCount(3);
    omh_table->setRowCount(1);

    //Очищаем таблицу настроек (или перемещений).
    settings_table->clear();
    settings_table->setColumnCount(1);
    settings_table->setRowCount(1);

    //Очищаем поле с ошибками.
    spe_text->clear();

    //Вычисляем длину программы: СА = СА - АЗ.
    int length_programm{this->addressCounter - this->start_prog_address};
    /*-------------------------------------------------------------------------------------------------------------
     | 1. Считываем первую строку вспомогательной таблицы и формируем запись-заголовок.                           |
     -------------------------------------------------------------------------------------------------------------*/
    //Для заголовка объектного модуля.
    omh_table->setItem(0, 0, new QTableWidgetItem(sup_table[0].machine_code));
    omh_table->setItem(0, 1, new QTableWidgetItem(Convert::DecToHex(this->start_prog_address).rightJustified(6, '0')));
    omh_table->setItem(0, 2, new QTableWidgetItem(Convert::DecToHex(length_programm).rightJustified(6, '0')));
    //Для двоичного кода.
    binaryCode_text->append("H  " + sup_table[0].machine_code + "\t" +
                                 Convert::DecToHex(this->start_prog_address).rightJustified(6, '0') + "\t" +
                                 Convert::DecToHex(this->addressCounter - this->start_prog_address).rightJustified(6, '0'));

    /*------------------------------------------------------------------
     | 2. Цикл строки исходного текста (через вспомогательную таблицу).|
     ------------------------------------------------------------------*/
    for (size_t i{ 1 }; i < sup_table.size(); i++){
        /*----------------------------
         | 3. Обработка записи-конец.|
         ----------------------------*/
        //Если найдена директива END, то выгружается ТМ, формируется запись-конец и запись двоичного кода завершается.
        if (sup_table[i].operation_code == "END")
        {
            //Формируем записи-модификаций.
            for (int row = 0; row < settings_table->rowCount() - 1; ++row)
            {
                QTableWidgetItem* item = settings_table->item(row, 0);
                if (item)
                {
                    QString OAMK = item->text();
                    binaryCode_text->append("M  " + OAMK.rightJustified(6, '0'));
                }
            }
            //Формируем запись-конец.
            binaryCode_text->append("E  " + Convert::DecToHex(this->end_prog_address).rightJustified(6,'0'));
            break;
        }
        //Переменные для записи двоичного представления команд и данных (адрес метки, число, строка и тд.).
        QString binary_opCode{};
        QString data{};
        //Директивы START и END встречены быть не могут, т.к. обработаны выше.
        //Директивы BYTE, WORD, RESB, RESW.
        if (check.CheckDirective(sup_table[i].operation_code) != "")
        {
            //Операнд является числом в 10-тичной СИ.
            if (check.CheckCorrectAmountMemoryForDecNumber(sup_table[i].operand1))
            {
                //Директивы резервирования памяти.
                if (sup_table[i].operation_code=="RESB" || sup_table[i].operation_code=="RESW")
                {
                    binary_opCode = "";
                    data = "";
                }
                //Директивы выделения памяти под 1b (BYTE) или 3b (WORD).
                else
                {
                    binary_opCode = "";
                    data = Convert::DecToHex(sup_table[i].operand1.toInt());
                    sup_table[i].operation_code == "BYTE" ? (data = data.rightJustified(2, '0')) : (data = data.rightJustified(6, '0'));
                }
            }
            //Это либо ASCII-строка, либо число в 16 СИ.
            else
            {
                //Это число в 16 СИ.
                if (check.CheckCorrectAmountMemoryForHexNumber(sup_table[i].operand1))
                {
                    binary_opCode = "";
                    data = sup_table[i].operand1.split('\'')[1];
                }
                //Это ASCII-строка.
                else
                {
                    binary_opCode = "";
                    QString unicode_string{sup_table[i].operand1.mid(2, sup_table[i].operand1.length() - 3)};
                    for (QChar chr : unicode_string){
                        int ASCII_code = chr.unicode();
                        data.append(Convert::DecToHex(ASCII_code));
                    }
                }
            }
        }
        //Иначе это может быть только реальный двоичный КОП.
        else
        {
            int type_addr{Convert::HexToDec(sup_table[i].operation_code) & 0x03}; //Если = 0, то непосредственная/регистровая адресация; = 1 - прямая, иначе - относительная.
            //Операнды могут не быть, а могут быть.
            if (type_addr == 0)
            {
                //Два операнда-регистра (проверка регистровой адресации в первом проходе).
                if (!sup_table[i].operand1.isEmpty() && !sup_table[i].operand2.isEmpty())
                {
                    binary_opCode = sup_table[i].operation_code;
                    data = Convert::DecToHex(sup_table[i].operand1.split('R')[1].toInt()) +
                           Convert::DecToHex(sup_table[i].operand2.split('R')[1].toInt());
                }
                //Один операнд-число (проверка непосредственной адресации в первом проходе).
                else if (!sup_table[i].operand1.isEmpty() && sup_table[i].operand2.isEmpty())
                {
                    binary_opCode = sup_table[i].operation_code;
                    data = Convert::DecToHex(sup_table[i].operand1.toInt()).rightJustified(2,'0');
                }
                //Нет операндов.
                else
                {
                    binary_opCode = sup_table[i].operation_code;
                    data = "";
                }
            }
            //Операндная часть обязана быть - прямая адресация (обработано на первом проходе).
            else if (type_addr == 1)
            {
                QString address{};
                //Поиск СИ в ТСИ (операнд точно должен быть СИ).
                if (symb_table.find(sup_table[i].operand1, address))
                {
                    binary_opCode = sup_table[i].operation_code;
                    //Необходимо занести в ТМ ОАМК.
                    this->TManager.LoadOneLineToSettingsTable(settings_table, sup_table[i].machine_code);
                    data = address;
                }
                else{
                    spe_text->append("Строка " + QString::number(i+1) + ": Неверно задан операнд, т.к. тип адресации (прямая) подразумевает, "
                                                                              "что операнд является меткой. Метка: " + sup_table[i].operand1 + " не найдена в ТСИ.");
                    return false;
                }
            }
            //Операндная часть обязана быть - относительная адресация (обработано на первом проходе).
            else
            {
                QString address{};
                QString operand = sup_table[i].operand1;
                //Относительная адресация в случае программы в перемещаемом формате (ПвПФ).
                operand = sup_table[i].operand1.mid(1, sup_table[i].operand1.length() - 2);
                //Поиск СИ в ТСИ (операнд точно должен быть СИ).
                if (symb_table.find(operand, address))
                {
                    binary_opCode = sup_table[i].operation_code;
                    data = Convert::SubTwoHexNumbers(address, sup_table[i + 1].machine_code);
                }
                else
                {
                    spe_text->append("Строка " + QString::number(i+1) + ": Неверно задан операнд, т.к. тип адресации (относительная) подразумевает, "
                                                                              "что операнд является меткой. Метка: " + operand + " не найдена в ТСИ.");
                    return false;
                }
            }
        }
        //Вывод результатов в поле Двоичного кода.
        binaryCode_text->append("T  " + sup_table[i].machine_code + "\t" +
                                     Convert::DecToHex(binary_opCode.length() + data.length()).rightJustified(2, '0') +
                                     (binary_opCode.isEmpty() ? "" : "\t") + binary_opCode +
                                     (data.isEmpty() ? "" : "\t") + data);
    }
    return true;
}
