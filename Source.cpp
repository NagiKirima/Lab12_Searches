#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
using namespace std;

struct Date
{
    int Day, Month, Year;
    void Get_date() 
    {
        cout << "Введите день:\t";
        cin >> Day;
        cout << "Введите месяц:\t";
        cin >> Month;
        cout << "Введите год:\t";
        cin >> Year;
    }
};
struct Human
{
    string FIO;
    Date DateOfBirth;
    unsigned int passportNumber;
    void Fill() 
    {
        srand(time(0));
        vector <string> names = { "Nikolay", "Oleg", "Vadim", "Alexander", "Artem" }; //заранее подготовленные массивы фамилий
        vector <string> surnames = { "Tedeev" , "Karelov", "Kuznetsov", "Galinov", "Chernykh" };
        vector <string> patronymic = { "Andreevich","Alexandrovich", "Mikhailovich", "Petrovich","Dmitryevich" };
    
        FIO = surnames[rand() % surnames.size()] + " " + names[rand() % names.size()] + " " + patronymic[rand() % patronymic.size()];
        DateOfBirth.Day = rand() % 28 + 1;
        DateOfBirth.Month = rand() % 12 + 1;
        DateOfBirth.Year = rand() % 100 + 1921;
        passportNumber = rand() % 6000 + 1;
    }
};

int GetSize()
{
    int size;
    while (!(cin >> size) || (cin.peek() != '\n') || (size < 1))
    {
        cin.clear();
        while (cin.get() != '\n')
        {
            cout << "Введите корректный размер списка:\t";
        }
    }
    return size;
}
int GetMenu()
{
    int menu;
    cout << "Выберете действие:" << endl;
    cout << "1. Создать список." << endl;
    cout << "2. Вывести список." << endl;
    cout << "3. Поиск элемента в списке." << endl;
    cout << "4. Удалить элемент из списка." << endl;
    cout << "5. Отменить удаление." << endl;
    cout << "6. Сохранить изменения в файл." << endl;
    cout << "7. Добавить элемент в список." << endl;
    cout << "0. Выход." << endl;
    cout << "Поле ввода:\t";
    while (!(cin >> menu) || (cin.peek() != '\n') || (menu < 0) || (menu > 7))
    {
        cin.clear();
        while (cin.get() != '\n')
        {
            cout << "Введите корректный номер функции:\t";
        }
    }
    cout << endl;
    return menu;
}

void Print_list(vector <Human> list)
{
    for (int i = 0; i < list.size(); i++)
    {
        cout << "===============================================================" << endl;
        cout << i + 1 << "-й человек в списке:" << endl;
        cout << "ФИО:\t" << list[i].FIO << endl;
        cout << "Дата рождения:\t" << list[i].DateOfBirth.Day << "." << list[i].DateOfBirth.Month << "." << list[i].DateOfBirth.Year << endl;
        cout << "Номер паспорта:\t" << list[i].passportNumber << endl;

    }
}
vector<Human> CreateArray(int size)
{
    srand(time(0));
    vector<Human> result;
    vector <string> names = { "Nikolay", "Oleg", "Vadim", "Alexander", "Artem" }; //заранее подготовленные массивы фамилий
    vector <string> surnames = { "Tedeev" , "Karelov", "Kuznetsov", "Galinov", "Chernykh" };
    vector <string> patronymic = { "Andreevich","Alexandrovich", "Mikhailovich", "Petrovich","Dmitryevich" };
    for (int i = 0; i < size; i++)
    {
        Human NewPerson;
        NewPerson.FIO = surnames[rand() % surnames.size()] + " " + names[rand() % names.size()] +  " " + patronymic[rand() % patronymic.size()];
        NewPerson.DateOfBirth.Day = rand() % 28 + 1;
        NewPerson.DateOfBirth.Month = rand() % 12 + 1;
        NewPerson.DateOfBirth.Year = rand() % 100 + 1921;
        NewPerson.passportNumber = rand() % 6000 + 1;
        result.push_back(NewPerson);
    }

    return result;
}

int Substring_search(vector<Human> humans, Date key)
{
    string listOfDates;
    string substring;
    ////////////////////////////////////////
    if (key.Day < 10) substring += "0";
    substring += to_string(key.Day);
    /////////////////////////////////////// 
    if (key.Month < 10) substring += "0";
    substring += to_string(key.Month);
    ///////////////////////////////////////
    if (key.Year < 10) substring += "0";
    substring += to_string(key.Year);
    ///////////////////////////////////////
   
    for (int i = 0; i < humans.size(); i++)
    {
        string newLine = "";
        if (humans[i].DateOfBirth.Day < 10) newLine += "0";
        newLine += to_string(humans[i].DateOfBirth.Day);
        if (humans[i].DateOfBirth.Month < 10) newLine += "0";
        newLine += to_string(humans[i].DateOfBirth.Month);
        if (humans[i].DateOfBirth.Year < 10) newLine += "0";
        newLine += to_string(humans[i].DateOfBirth.Year);
        listOfDates += newLine;
    }

    for (int i = 0; i < listOfDates.size() - substring.size(); i++)
    {
        int j = 0;
        while (listOfDates[i + j] == substring[j] && j < substring.size())
        {
            j++;
        }
        if (j == substring.size())
        {
            return i / 8;
        }
    }

    return -1;
}
int Line_search(vector<Human> humans, Date key) 
{
    vector<int> date_list;
    int tmp_key = key.Day * 1000000 + key.Month * 10000 + key.Year;
    for (int i = 0; i < humans.size(); i++)
    {
        date_list.push_back(humans[i].DateOfBirth.Day*1000000 + humans[i].DateOfBirth.Month*10000 + humans[i].DateOfBirth.Year);
    }
    for (int i = 0; i < date_list.size(); i++) 
    {
        if (date_list[i] == tmp_key) 
        {
            return i;
        }
    }
    return -1;
}
void Shell_sort(vector<int>& humans) 
{
    int size = humans.size();
    for (int step = size / 2; size > 0; size /= 2) 
    {
        for (int i = step; i < size; i++) 
        {
            for (int j = i; j >= step; j -= step) 
            {
                if (humans[j] < humans[j - step]) 
                {
                    int tmp = humans[j];
                    humans[j] = humans[j - step];
                    humans[j - step] = tmp;
                }
            }
        }
    }
}
bool Interpol_search(vector<Human>& humans, Date key) 
{
    bool check = false;
    vector<int> date_list;
    int tmp_key = key.Day * 1000000 + key.Month * 10000 + key.Year;
    for (int i = 0; i < humans.size(); i++)
    {
        date_list.push_back(humans[i].DateOfBirth.Day * 1000000 + humans[i].DateOfBirth.Month * 10000 + humans[i].DateOfBirth.Year);
    }
    Shell_sort(date_list); // сортировка по возрастанию
    
    int mid = 0, left = 0, right = date_list.size() - 1;
    while (date_list[left] <= tmp_key && date_list[right] >= tmp_key) 
    {
        mid = left + ((tmp_key - date_list[left]) * (right - left)) / (date_list[right] - date_list[left]);
        if (date_list[mid] < tmp_key)
        {
            left = ++mid;
        }
        else if (date_list[mid] > tmp_key)
        {
            right = --mid;
        }
        else 
        {
            check = true;
            return check;
        }
    }
    return check;
}

bool DeleteHuman(vector <Human>& list, string value) 
{
    bool check = false;
    for (int i = 0; i < list.size(); i++) 
    {
        if (list[i].FIO == value) 
        {
            list.erase(list.begin() + i);
            check = true;
        }
    }
    if (check) 
    {
        cout << "Человек успешно удален из списка!" << endl;
    }
    else 
    {
        cout << "Такого человека в списке нет!" << endl;
    }
    return check;
}

string Reverse_str(string str) 
{
    string result;
    for (int i = str.size() - 1; i >= 0; i--) 
    {
        result.push_back(str[i]);
    }
    return result;
}
int Boyer_Moor(vector<Human> humans, Date key) 
{
    string listOfDates;
    string substring;
    ////////////////////////////////////////
    if (key.Day < 10) substring += "0";
    substring += to_string(key.Day);
    /////////////////////////////////////// 
    if (key.Month < 10) substring += "0";
    substring += to_string(key.Month);
    ///////////////////////////////////////
    if (key.Year < 10) substring += "0";
    substring += to_string(key.Year);
    ///////////////////////////////////////
    for (int i = 0; i < humans.size(); i++)
    {
        string newLine = "";
        if (humans[i].DateOfBirth.Day < 10) newLine += "0";
        newLine += to_string(humans[i].DateOfBirth.Day);
        if (humans[i].DateOfBirth.Month < 10) newLine += "0";
        newLine += to_string(humans[i].DateOfBirth.Month);
        if (humans[i].DateOfBirth.Year < 10) newLine += "0";
        newLine += to_string(humans[i].DateOfBirth.Year);
        listOfDates += newLine;
    }

    vector<int> shiftarray(substring.size());
    string substring_reverse_copy = Reverse_str(substring); //перевернутая строка
    for (int i = 0; i < substring.size(); i++) //получение массива сдвигов
    {
        shiftarray[i] = substring_reverse_copy.find(substring[i]) + 1;
    }
    
    cout << "Массив сдвигов:" << endl;
    cout << substring << endl;
    for (int i = 0; i < shiftarray.size(); i++)  //проверка массива сдвигов
    {
        cout << shiftarray[i] << " ";
    }
    cout << endl << "==============================================================" << endl;


    int current_char = substring.size() - 1;
    while (current_char < listOfDates.size()) 
    {
        int i = substring.size() - 1;
        if (listOfDates[current_char] == substring[i]) 
        {
            int j = current_char;
            while (listOfDates[j] == substring[i] && i != 0) 
            {
                i--;
                j--;
            }
        }
        if (i == 0)
        {
            return current_char / 8 + 1;
        }
        else 
        {
            if (substring.find(listOfDates[i]) == -1) 
            {
                current_char += substring.size();
            }
            else 
            {
                current_char += shiftarray[substring.find(listOfDates[i])];
            }
        }
    }
    return -1;
}

vector<int> Prefix_func(string substring) 
{
    vector<int> result(substring.size());
    result[0] = 0;
    for (int i = 1; i < result.size(); i++)
    {
        int pre_pos = result[i - 1];
        while (pre_pos > 0 && substring[pre_pos] != substring[i])
        {
            pre_pos = result[pre_pos - 1];
        }
        result[i] = pre_pos + (substring[pre_pos] == substring[i] ? 1 : 0);
    }
    return result;
}
int KMP(vector<Human> humans, Date key)
{
    string listOfDates; //строка
    string substring; //подстрока
    ////////////////////////////////////////
    if (key.Day < 10) substring += "0";
    substring += to_string(key.Day);
    /////////////////////////////////////// 
    if (key.Month < 10) substring += "0";
    substring += to_string(key.Month);
    ///////////////////////////////////////
    if (key.Year < 10) substring += "0";
    substring += to_string(key.Year);
    ///////////////////////////////////////
    for (int i = 0; i < humans.size(); i++)
    {
        string newLine = "";
        if (humans[i].DateOfBirth.Day < 10) newLine += "0";
        newLine += to_string(humans[i].DateOfBirth.Day);
        if (humans[i].DateOfBirth.Month < 10) newLine += "0";
        newLine += to_string(humans[i].DateOfBirth.Month);
        if (humans[i].DateOfBirth.Year < 10) newLine += "0";
        newLine += to_string(humans[i].DateOfBirth.Year);
        listOfDates += newLine;
    }


    vector <int> pi = Prefix_func(substring); //получение pi массива (префиксов)
    int k = 0, l = 0; //l - указатель на подстроку, k - на строку
    while (k < listOfDates.size()) 
    {
        if (substring[l] == listOfDates[k])
        {
            k++;
            l++;
            if (l == substring.size()) return k / 8;
        }
        else if (l == 0)
        {
            k++;
        }
        else if (l != 0) l = pi[l - 1];
    }
    return -1;
}

void Save_list(vector<Human> list) 
{
    ofstream output("Saved.txt");
    for (int i = 0; i < list.size(); i++)
    {
        output << "===========================================================" << endl;
        output << i + 1 << "-й пользователь" << endl;
        output << "ФИО:\t" << list[i].FIO << endl;
        string pasport = to_string(list[i].passportNumber);
        output << "Номер паспорта:\t" << pasport << endl;
        string date = to_string(list[i].DateOfBirth.Day) + "." + to_string(list[i].DateOfBirth.Month) + "." + to_string(list[i].DateOfBirth.Year);
        output << "Дата рождения:\t" << date << endl;
    }
    output << "===========================================================" << endl;
    output.close();
}
int main()
{
    setlocale(LC_ALL, "ru");
    vector <Human> Humans;
    vector <Human> reserveHumans = Humans;
    bool check_delete = false;
    int menu = -1;
    while (menu == -1)
    {
        menu = GetMenu();
        switch (menu)
        {
            case 1: //заполнение списка
            {
                cout << "===============================================================" << endl;
                cout << "Введите размер списка:\t";
                int size = GetSize();
                Humans = CreateArray(size);
                cout << "Список успешно создан!" << endl;
                cout << "===============================================================" << endl;
                menu = -1;
                break;
            }
            case 2://вывод списка
            {
                if (Humans.size() != 0)
                {
                    cout << "Список с людьми:" << endl;
                    Print_list(Humans);
                    cout << "===============================================================" << endl << endl;
                }
                else
                {
                    cout << "Список пуст!" << endl;
                    cout << "===============================================================" << endl << endl;
                }
                menu = -1;
                break;
            }
            case 3: // поиск элемента в списке по ключу
            {
                if (Humans.size() == 0) 
                {
                    cout << "Список пуст!" << endl;
                    cout << "===============================================================" << endl << endl;
                    menu = -1;
                    break;
                }
                cout << "Выберете способ поиска!" << endl;
                cout << "1. Подстроки в строке." << endl;
                cout << "2. Линейный." << endl;
                cout << "3. Интерполяционный." << endl;
                cout << "4. Бойера-Мура." << endl;
                cout << "5. K-M-P method." << endl;
                cout << "0. Вернуться в меню." << endl;
                int search;
                cout << "Поле ввода:\t";
                while (!(cin >> search) || (cin.peek() != '\n') || (search < 0) || (search > 5)) 
                {
                    cin.clear();
                    while (cin.get() != '\n') 
                    {
                        cout << "Введите корректное число:\t";
                    }
                }
                switch (search) 
                {
                    case 1: 
                    {
                        Date key;
                        key.Get_date();
                        int pos = Substring_search(Humans, key);
                        if (pos != -1) 
                        {
                            cout << "Элемент с такой датой рождения найден. Он находится в списке под номером: " << pos + 1 << endl;
                            cout << "===============================================================" << endl << endl;
                        }
                        else 
                        {
                            cout << "Элемента с такой датой рождения нет!" << endl;
                            cout << "===============================================================" << endl << endl;
                        }
                        break;
                    }
                    case 2: 
                    {
                        Date key;
                        key.Get_date();
                        int pos = Line_search(Humans, key);
                        if (pos != -1)
                        {
                            cout << "Элемент с такой датой рождения найден. Он находится в списке под номером: " << pos + 1 << endl;
                            cout << "===============================================================" << endl << endl;
                        }
                        else
                        {
                            cout << "Элемента с такой датой рождения нет!" << endl;
                            cout << "===============================================================" << endl << endl;
                        }
                        break;
                    }
                    case 3: 
                    {
                        Date key;
                        key.Get_date();
                        if (Interpol_search(Humans, key) == true)
                        {
                            cout << "Элемент с такой датой рождения найден." << endl;
                            cout << "===============================================================" << endl << endl;
                        }
                        else
                        {
                            cout << "Элемента с такой датой рождения нет!" << endl;
                            cout << "===============================================================" << endl << endl;
                        }
                        break;
                    }
                    case 4: 
                    {
                        Date key;
                        key.Get_date();
                        int pos = Boyer_Moor(Humans, key);
                        if (pos == -1)
                        {
                            cout << "Такого элемента нет!" << endl;
                            cout << "===============================================================" << endl << endl;
                        }
                        else
                        {
                            cout << "Такой элемент находится под индексом " << pos << endl;
                            cout << "===============================================================" << endl << endl;
                        }
                        break;
                    }
                    case 5: 
                    {
                        Date key;
                        key.Get_date();
                        int pos = KMP(Humans, key);
                        if (pos == -1) 
                        {
                            cout << "Такого элемента нет!" << endl;
                            cout << "===============================================================" << endl << endl;
                        }
                        else 
                        {
                            cout << "Такой элемент находится под индексом " << pos << endl;
                            cout << "===============================================================" << endl << endl;
                        }
                        break;
                    }
                    case 0: 
                    {
                        cout << "Выход..." << endl;
                        break;
                    }
                }
                menu = -1;
                break;
            }
            case 4: //удаление элемента из списка
            {
                reserveHumans = Humans;
                if (reserveHumans.size() == 0) 
                {
                    cout << "Список пуст!" << endl;
                }
                else
                {
                    cout << "Введите ФИO человека, которого вы хотите удалить:\t";
                    string value;
                    cin.ignore();
                    getline(cin, value);
                    check_delete = DeleteHuman(Humans, value);
                    Print_list(Humans);
                    cout << "===============================================================" << endl << endl;
                }
                menu = -1;
                break;
            }
            case 5: //отмена удаления
            {
                
            if (check_delete)
            {
                cout << "Удаление элементов отменено!" << endl;
                cout << "===============================================================" << endl << endl;
                Humans = reserveHumans;
                check_delete = false;
            }
            else 
            {
                cout << "Элементы из списка не удалялись!" << endl;
                cout << "===============================================================" << endl << endl;
            }
                menu = -1;
                break;
            }
            case 6: //запись в файл
            {
                if (Humans.size() == 0) 
                {
                    cout << "Список пуст, сохранять нечего!" << endl;
                    cout << "===============================================================" << endl << endl;
                    menu = -1;
                    break;
                }
                ofstream output("Saved.txt");
                if (output.is_open()) 
                {
                    Save_list(Humans);
                    cout << "Запись в файл прошла успешно!" << endl;
                    cout << "===============================================================" << endl << endl;
                }
                else 
                {
                    cout << "Не удалось открыть файл для сохранения, проверьте его на существование!" << endl;
                    cout << "===============================================================" << endl << endl;
                }
                output.close();
                menu = -1;
                break;
            }
            case 7: //добавление в список
            {
                int add;
                cout << endl;
                cout << "Введите каким способом вы хотите добавить элемент в список:" << endl;
                cout << "1. Добавить в начало списка." << endl;
                cout << "2. Добавить в конец списка" << endl;
                cout << "3. Вставить по индексу." << endl;
                cout << "0. Выйти в меню." << endl;
                cout << "Поле ввода:\t";
                while (!(cin >> add) || (cin.peek() != '\n') || (add < 0) || (add > 3))
                {
                    cin.clear();
                    while (cin.get() != '\n')
                    {
                        cout << "Введите корректное число:\t";
                    }
                }
                switch (add) 
                {
                    case 1: 
                    {
                        Human tmp;
                        tmp.Fill();
                        Humans.insert(Humans.begin(), tmp);
                        cout << "===============================================================" << endl << endl;
                        break;
                    }
                    case 2: 
                    {
                        Human tmp;
                        tmp.Fill();
                        Humans.push_back(tmp);
                        cout << "===============================================================" << endl << endl;
                        break;
                    }
                    case 3: 
                    {
                        int i;
                        cout << "Введите позицию, куда хотите добавить элемент:\t";
                        while (!(cin >> i) || (cin.peek() != '\n') || (i < 0) || (i > Humans.size()))
                        {
                            cin.clear();
                            while (cin.get() != '\n')
                            {
                                cout << "Введите корректное число:\t";
                            }
                        }
                        Human tmp;
                        tmp.Fill();
                        Humans.insert(Humans.begin() + i, tmp);
                        cout << "===============================================================" << endl << endl;
                        break;
                    }
                    case 0: 
                    {
                        cout << "Выход..." << endl;
                        break;
                    }
                }
                menu = -1;
                break;
            }
            case 0: //выход
            {
                cout << "Работа завершена!" << endl;
                cout << "===============================================================" << endl;
                return 0;
            }
        }
    }
}