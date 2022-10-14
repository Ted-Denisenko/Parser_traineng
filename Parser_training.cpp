#include <iostream>
#include <map>

using namespace std;

std::map<string, string> ParseParams1(const string& params)
{
    // на вход дается строка вида "/param value"
    // параметр определяется по слэшу в начале, чтение до первого пробела
    // все после первого пробела считается значением
    if (params[0] != '/')
    {
        std::cout << "WRONG INPUT";
    }
    string param_name;

    string param_value;
    unsigned short int pos{1};
    std::map<string, string> pairs;
    while (pos+1 < params.size())
    {
        unsigned short int name_pos_begin{ pos };
        unsigned short int name_pos_end{ name_pos_begin };

        while (params[pos++] != ' ')
            name_pos_end++;

        for (int i{ name_pos_begin }; i <= name_pos_end; i++)
            param_name.push_back(params[i]);

        unsigned short int value_pos_begin{ pos };
        unsigned short int value_pos_end{ value_pos_begin };
        bool new_pair_incounted{ false };
        bool value_with_spaces{ false };

        if (pos + 1 < params.size())
        {
            // ищем границы второго слова и записываем его
            while (params[pos++] && new_pair_incounted == false)
                if (params[pos] != ' ')
                {
                    // TODO: ЕСЛИ В СТРОКУ МОЖНО ПУШБЭЧИТЬ, ЗАЧЕМ ОПРЕДЕЛЯТЬ ГРАНИЦЫ СЛОВ?
                    value_pos_end++;
                    //pos++;
                }
                else
                    if (params[pos])
                        // это не последняя пара параметр-значение
                        if (params[pos] == ' ' && params[pos + 1] == '/' && isalpha(params[pos + 2]))
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
            {
                param_value.push_back('"');
                for (int i{ value_pos_begin }; i <= value_pos_end; i++)
                    param_value.push_back(params[i]);
                param_value.push_back('"');
            }
            else
                for (int i{ value_pos_begin }; i <= value_pos_end; i++)
                    param_value.push_back(params[i]);
        }
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

// ищем признак имени параметра
// ищем границы имени
// записываем имя
// ищем признак значения параметра
// ищем границы значения
// записываем значение
// записываем пару в мапу
// повторить цикл, если пара не последняя в строке
//

int main()
{
    string str = "/silent /reboot";
    ParseParams1(str);
    return 0;
}

// TODO: выкидывать исключения из проекта тестового задания,    опционально: экранирование пробелов, прямых и обратных слешей, кавычек