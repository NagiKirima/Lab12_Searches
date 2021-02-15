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
            cout << "������� ���������� ������ ������:\t";
        }
    }
    return size;
}
int GetMenu()
{
    int menu;
    cout << "�������� ��������:" << endl;
    cout << "1. ������� ������." << endl;
    cout << "2. ������� ������." << endl;
    cout << "3. ����� �������� � ������." << endl;
    cout << "4. ������� ������� �� ������." << endl;
    cout << "5. �������� ��������." << endl;
    cout << "6. ��������� ��������� � ����." << endl;
    cout << "7. �������� ������� � ������." << endl;
    cout << "0. �����." << endl;
    cout << "���� �����:\t";
    while (!(cin >> menu) || (cin.peek() != '\n') || (menu < 0) || (menu > 6))
    {
        cin.clear();
        while (cin.get() != '\n')
        {
            cout << "������� ���������� ����� �������:\t";
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
        cout << i + 1 << "-� ������� � ������:" << endl;
        cout << "���:\t" << list[i].FIO << endl;
        cout << "���� ��������:\t" << list[i].DateOfBirth.Day << "." << list[i].DateOfBirth.Month << "." << list[i].DateOfBirth.Year << endl;
        cout << "����� ��������:\t" << list[i].passportNumber << endl;

    }
}
vector<Human> CreateArray(int size)
{
    srand(time(0));
    vector<Human> result;
    vector <string> names = { "Nikolay", "Oleg", "Vadim", "Alexander", "Artem" }; //������� �������������� ������� �������
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
        cout << "������� ������� ������ �� ������!" << endl;
    }
    else 
    {
        cout << "������ �������� � ������ ���!" << endl;
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
            case 1: //���������� ������
            {
                cout << "===============================================================" << endl;
                cout << "������� ������ ������:\t";
                int size = GetSize();
                Humans = CreateArray(size);
                cout << "������ ������� ������!" << endl;
                cout << "===============================================================" << endl;
                menu = -1;
                break;
            }
            case 2://����� ������
            {
                if (Humans.size() != 0)
                {
                    cout << "������ � ������:" << endl;
                    Print_list(Humans);
                    cout << "===============================================================" << endl;
                }
                else
                {
                    cout << "������ ����!" << endl;
                    cout << "===============================================================" << endl;
                }
                menu = -1;
                break;
            }
            case 3: // ����� �������� � ������ �� �����
            {
                cout << "�������� ������ ������!" << endl;
                cout << "1. ��������� � ������." << endl;
                cout << "2. ��������." << endl;
                cout << "3. ����������������." << endl;
                cout << "0. ��������� � ����." << endl;
                int search;
                cout << "���� �����:\t";
                while (!(cin >> search) || (cin.peek() != '\n') || (search < 0) || (search > 3)) 
                {
                    cin.clear();
                    while (cin.get() != '\n') 
                    {
                        cout << "������� ���������� �����:\t";
                    }
                }
                switch (search) 
                {
                    case 1: 
                    {
                        Date key;
                        cout << "������� ����:\t";
                        cin >> key.Day;
                        cout << "������� �����:\t";
                        cin >> key.Month;
                        cout << "������� ���:\t";
                        cin >> key.Year;
                        int pos = Substring_search(Humans, key);
                        if (pos != -1) 
                        {
                            cout << "������� � ����� ����� �������� ������. �� ��������� � ������ ��� �������: " << pos + 1 << endl;
                            cout << "===============================================================" << endl;
                        }
                        else 
                        {
                            cout << "�������� � ����� ����� �������� ���!" << endl;
                            cout << "===============================================================" << endl;
                        }
                        break;
                    }
                    case 2: 
                    {
                        Date key;
                        cout << "������� ����:\t";
                        cin >> key.Day;
                        cout << "������� �����:\t";
                        cin >> key.Month;
                        cout << "������� ���:\t";
                        cin >> key.Year;
                        break;
                    }
                    case 3: 
                    {
                        Date key;
                        cout << "������� ����:\t";
                        cin >> key.Day;
                        cout << "������� �����:\t";
                        cin >> key.Month;
                        cout << "������� ���:\t";
                        cin >> key.Year;
                        break;
                    }
                    case 0: 
                    {
                        cout << "�����..." << endl;
                        break;
                    }
                }
                menu = -1;
                break;
            }
            case 4: //�������� �������� �� ������
            {
                if (reserveHumans.size() == 0) 
                {
                    cout << "������ ����!" << endl;
                }
                else
                {
                    cout << "������� ��O ��������, �������� �� ������ �������:\t";
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
            case 5: //������ ��������
            {
                
            if (check_delete)
            {
                cout << "�������� ��������� ��������!" << endl;
                cout << "===============================================================" << endl;
                Humans = reserveHumans;
                check_delete = false;
            }
            else 
            {
                cout << "�������� �� ������ �� ���������!" << endl;
                cout << "===============================================================" << endl;
            }
                menu = -1;
                break;
            }
            case 6: //������ � ����
            {
                break;
            }
            case 7: //���������� � ������
            {
                
                break;
            }
            case 0: //�����
            {
                cout << "������ ���������!" << endl;
                return 0;
            }
        }
    }
}