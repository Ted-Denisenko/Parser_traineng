#include <iostream>
#include <map>

using namespace std;

std::map<string, string> ParseParams1(const string& params)
{
    // на вход дается строка вида "/param value"
    // параметр определяется по слэшу в начале, чтение до первого пробела
    // все после первого пробела считается значением
    // 
    // Your implementation here
    if (params[0] != '/')
    {
        std::cout << "WRONG INPUT";
    }
    string param_name;

    string param_value;
    short int pos{1};
    std::map<string, string> pairs;
    while (params[pos])
    {
        short int name_pos_begin{ pos };
        short int name_pos_end{ name_pos_begin };

        // ищем границы первого слова и записываем его
        while (params[pos++] != ' ')
            name_pos_end++;
        for (int i{ name_pos_begin }; i <= name_pos_end; i++)
            param_name.push_back(params[i]);

        short int value_pos_begin{ pos };
        short int value_pos_end{ value_pos_begin };
        bool new_pair_incounted{ false };
        bool value_with_spaces{ false };

        // ищем границы второго слова и записываем его
        while (params[pos++] && new_pair_incounted==false)
            if (params[pos] != ' ')
                value_pos_end++;
            else
                if(params[pos])
                    // это не последняя пара параметр-значение
                    if (params[pos] == ' ' && params[pos + 1] == '/' && isalpha(params[pos+2]) )
                    {
                        new_pair_incounted = true;
                        pos++;
                    }
                    // пробел относился к значению текущей пары
                    else
                    {
                        value_with_spaces = true;
                        value_pos_end++;
                    }

        // значения с пробелами должны быть в кавычках
        if (value_with_spaces)
            param_value.push_back('"');
        for (int i{ value_pos_begin }; i <= value_pos_end; i++)
            param_value.push_back(params[i]);
        if (value_with_spaces)
            param_value.push_back('"');

        pairs.insert({ param_name, param_value });

        param_name.clear();
        param_value.clear();

        if(!new_pair_incounted)
            pos--;
    }
    for (auto itr{ pairs.begin() }; itr != pairs.end(); ++itr) {
        cout << itr->first
            << '\t' << itr->second << '\n';
    }
    return pairs;
}

//от начала до первого пробела - имя первой пары
// от первого пробела до второго пробела(или до конца файла) значение первой пары
// с дальнейшими парами аналогично
//

int main()
{
    string str = "/param1 value  /  1 /param2 value2 /param3 value3 /param4 value4";
    // Значения параметров, содержащие пробелы, необходимо заключать в кавычки или экранировать с помощью обратного слеша:
    // value   1 -> "value   1" || value\\\1
    //value    1

    //
    ParseParams1(str);
    return 0;
}

// TODO: выкидывать исключения из проекта тестового задания,    опционально: экранирование пробелов, прямых и обратных слешей, кавычек