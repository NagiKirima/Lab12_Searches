#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

struct Date
{
    int Day, Month, Year;
};
struct Human
{
    string FIO;
    Date DateOfBirth;
    unsigned int passportNumber;
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
    while (!(cin >> menu) || (cin.peek() != '\n') || (menu < 0) || (menu > 6))
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

    for (int i = 0; i < humans.size(); i++)
    {
        listOfDates.append(to_string(humans[i].DateOfBirth.Day) + to_string(humans[i].DateOfBirth.Month) + to_string(humans[i].DateOfBirth.Year));
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

int main()
{
    setlocale(LC_ALL, "ru");
    vector <Human> Humans;
    vector <Human> reserveHumans;
    bool check_delete = false;
    int menu = -1;
    while (menu == -1)
    {
        menu = GetMenu();
        reserveHumans = Humans;
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
                    cout << "===============================================================" << endl;
                }
                else
                {
                    cout << "Список пуст!" << endl;
                    cout << "===============================================================" << endl;
                }
                menu = -1;
                break;
            }
            case 3: // поиск элемента в списке по ключу
            {
                cout << "Выберете способ поиска!" << endl;
                cout << "1. Подстроки в строке." << endl;
                cout << "2. Линейный." << endl;
                cout << "3. Интерполяционный." << endl;
                cout << "0. Вернуться в меню." << endl;
                int search;
                cout << "Поле ввода:\t";
                while (!(cin >> search) || (cin.peek() != '\n') || (search < 0) || (search > 3)) 
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
                        cout << "Введите день:\t";
                        cin >> key.Day;
                        cout << "Введите месяц:\t";
                        cin >> key.Month;
                        cout << "Введите год:\t";
                        cin >> key.Year;
                        int pos = Substring_search(Humans, key);
                        if (pos != -1) 
                        {
                            cout << "Элемент с такой датой рождения найден. Он находится в списке под номером: " << pos + 1 << endl;
                            cout << "===============================================================" << endl;
                        }
                        else 
                        {
                            cout << "Элемента с такой датой рождения нет!" << endl;
                            cout << "===============================================================" << endl;
                        }
                        break;
                    }
                    case 2: 
                    {
                        Date key;
                        cout << "Введите день:\t";
                        cin >> key.Day;
                        cout << "Введите месяц:\t";
                        cin >> key.Month;
                        cout << "Введите год:\t";
                        cin >> key.Year;
                        break;
                    }
                    case 3: 
                    {
                        Date key;
                        cout << "Введите день:\t";
                        cin >> key.Day;
                        cout << "Введите месяц:\t";
                        cin >> key.Month;
                        cout << "Введите год:\t";
                        cin >> key.Year;
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
                    cout << "===============================================================" << endl;
                }
                menu = -1;
                break;
            }
            case 5: //отмена удаления
            {
                
            if (check_delete)
            {
                cout << "Удаление элементов отменено!" << endl;
                cout << "===============================================================" << endl;
                Humans = reserveHumans;
                check_delete = false;
            }
            else 
            {
                cout << "Элементы из списка не удалялись!" << endl;
                cout << "===============================================================" << endl;
            }
                menu = -1;
                break;
            }
            case 6: //запись в файл
            {
                break;
            }
            case 7: //добавление в список
            {
                
                break;
            }
            case 0: //выход
            {
                cout << "Работа завершена!" << endl;
                return 0;
            }
        }
    }
}