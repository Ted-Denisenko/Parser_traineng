#include <iostream>
#include <map>

using namespace std;

//map<string, string> ParseParams(const string& params)
//{
//    // на вход дается строка вида "/param value"
//    // параметр определяется по слэшу в начале, чтение до первого пробела
//    // все после первого пробела считается значением
//    // 
//    // Your implementation here
//
//    std::cout << params[1];
//        
//}

void ParseParams1(const string& params)
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
        while (params[pos++] != ' ')
            name_pos_end++;

        for (int i{ name_pos_begin }; i <= name_pos_end; i++)
            param_name.push_back(params[i]);

        short int value_pos_begin{ pos };
        short int value_pos_end{ value_pos_begin };
        bool space_incountered{ false };
        while (params[pos++] && space_incountered==false)
            if (params[pos] != ' ')
                value_pos_end++;
            else
                space_incountered = true;
        for (int i{ value_pos_begin }; i <= value_pos_end; i++)
            param_value.push_back(params[i]);

        pairs.insert({ param_name, param_value });

        param_name.clear();
        param_value.clear();

        if(!space_incountered)
            pos--;
    }
    for (auto itr{ pairs.begin() }; itr != pairs.end(); ++itr) {
        cout << itr->first
            << '\t' << itr->second << '\n';
    }
}

//от начала до первого пробела - имя первой пары
// от первого пробела до второго пробела(или до конца файла) значение первой пары
// с дальнейшими парами аналогично
//

int main()
{
    string str = "/param1 value1 param2 value2 param3 value3 param4 value4";
    ParseParams1(str);
    return 0;
}