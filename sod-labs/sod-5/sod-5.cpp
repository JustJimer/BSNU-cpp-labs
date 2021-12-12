#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <fstream>
#include <cstring> 
#include <windows.h> 
#include <cstdlib> 
#include <conio.h>
#include <algorithm>
#include <string>

using namespace std;

int task1()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(0, "rus");

    const int l_name = 35, l_year = 5, l_pay = 5; // Довжини полів рядка
    const int l_buf = l_name + l_year + l_pay; // Довжина буфера
    struct Sotr // Структура
    {
        char name[l_name + 1]; // Довжина поля задана з урахуванням нуль-символу
        int birth_year;
        float pay;
    };

    const int l_dbase = 100; // Максимальная кількість рядків
    Sotr dbase[l_dbase]; // Масив зберігання бази даних
    char buf[l_buf + 1]; // Буфер
    char name[l_name + 1]; // Рядок для ПІБ
    ifstream fin("db_otd-kadr.txt");
    if (!fin.is_open())
    {
        cout << "file error\n";
        system("pause");
        return false;
    }
    int i = 0;
    while (!fin.eof())
    {
        fin.getline(buf, l_buf);
        strncpy(dbase[i].name, buf, l_name);
        dbase[i].name[l_name] = '\0';
        dbase[i].birth_year = atoi(&buf[l_name]); // Перетворюємо y int
        dbase[i].pay = atof(&buf[l_name + l_year]); // Перетворюємо y int
        i++;
        if (i > l_dbase)
        {
            puts("file is to long\n");
            system("pause");
            return false;
        }
    }
    fin.close(); // Закриваємо потік

    // 1.1 - 1.2
    int n_record = i, n_sotr = 0; // n_record - кількість записів про співробітників, n_sotr - кількість співробітників, про які виводяться дані
    float sum_pay = 0; // Сума окладів
    while (true) // Нескінчений пошук
    {
        cout << "enter surname to search (CAPS only) (ESC - for stop searching):\n";
        if (_getch() == 27) break; // Якщо натиснули ESC - припиняємо цикл
        cin >> name; // Вводимо прізвище
        bool IsNotFound = true;
        for (int i = 0; i < n_record; i++)
        {
            for (char* c = dbase[i].name; *c = toupper(*c); ++c); // Переводимо ПІБ у великі літери
            if (strstr(dbase[i].name, name))
            {
                if (dbase[i].name[strlen(name)] == ' ')
                {
                    cout << dbase[i].name << dbase[i].birth_year << "\t" << dbase[i].pay << endl;
                    n_sotr++;
                    sum_pay += dbase[i].pay;
                    IsNotFound = false;
                }
            }
        }
        if (IsNotFound)
            cout << "no worker founnd\n";
    }
    if (n_sotr > 0)
        cout << "average wage - " << sum_pay / n_sotr << endl; // Виводимо середный оклад


    // 1.3
    ofstream fout("out-db_otd-kadr.txt");
    if (!fout)
    {
        cout << "file error\n";
        system("pause");
        return false;
    }
    Sotr bufTemp;

    for (int i = l_dbase - 1; i >= 0; i--) // sort birth_year
    {
        for (int j = 0; j < i; j++)
        {
            if (dbase[j].birth_year > dbase[j + 1].birth_year)
            {
                bufTemp = *(dbase + j);
                *(dbase + j) = *(dbase + j + 1);
                *(dbase + j + 1) = bufTemp;
            }
        }
    }
    for (int i = l_dbase - 1; i >= 0; i--) // sort pay
    {
        for (int j = 0; j < i; j++)
        {
            if (dbase[j].pay > dbase[j + 1].pay)
            {
                bufTemp = *(dbase + j);
                *(dbase + j) = *(dbase + j + 1);
                *(dbase + j + 1) = bufTemp;
            }
        }
    }
    for (int i = 0; i < l_dbase; i++)
        fout << dbase[i].name << dbase[i].birth_year << "\t" << dbase[i].pay << endl;

    fout.close();
    system("pause");
    return false;
}

int task2()
{
    const int l_name = 35;
    struct // Структура
    {
        char name[l_name + 1]; // Довжина поля
        int birth_year;
        float pay;
    }

    Sotr;

    FILE* fin, * fout;
    fin = fopen("db_otd-kadr.txt", "r");
    if (fin == NULL)
    {
        cout << "file error\n";
        system("pause");
        return false;
    }
    fout = fopen("db_otd-kadr.bin", "wb");
    if (fout == NULL)
    {
        cout << "file error\n";
        system("pause");
        return false;
    }
    while (!feof(fin)) // Читаємо, поки не кінець файлу
    {
        fgets(Sotr.name, l_name, fin);
        fscanf(fin, "%i%f\n", &Sotr.birth_year, &Sotr.pay);
        printf("%s\t%i\t%f\n", Sotr.name, Sotr.birth_year, Sotr.pay);
        fwrite(&Sotr, sizeof(Sotr), 1, fout); // Вивід у бінарний файл
    }
    fclose(fout);
    fclose(fin);
    cout << "binary file created\n";
    FILE* fout1;
    fout1 = fopen("db_otd-kadr.bin", "r + b"); // Відкриття файлу db_otd-kadr.bin, r + - читання і запис, b - бінарний режим
    if (fout1 == NULL) // Файл відкрився?
    {
        cout << "file db_otd-kadr.bin error";
        system("pause");
        return false;
    }
    fseek(fout1, 0, SEEK_END); // Перейти в кінець
    int n_record = 100; // Поточна позиція в байтах
    cout << "number of workers: " << n_record << endl; // Виводимо результат
    int num = 0;
    int action = 0;
    while (num != -1)
    {
        cout << "enter the employee number (to exit the program enter: -1): ";
        cin >> num;
        if (num != -1 && (num < 0 || num >= n_record))
            cout << "expected employee number";
        else if (num != -1)
        {
            action = 0;
            while (action != -1)
            {
                cout << "Choose:\n1 - change wage\n2 - change name\n3 - change both\n";
                cin >> action;
                if (action != -1 && (action < 1 || num > 3))
                    cout << "try again";
                else if (action != -1)
                {
                    fseek(fout1, num * sizeof(Sotr), SEEK_SET); // Установка поточної позиції у файлі
                    fread(&Sotr, sizeof(Sotr), 1, fout1); // Зчитування запису в структуру Sotr
                    printf("%s\t%i\t%f\n", Sotr.name, Sotr.birth_year, Sotr.pay);
                    if (action == 1)
                    {
                        cout << "enter new wage: ";
                        float temp1 = (Sotr.pay / 100) * 50; // 50%
                        float temp2; // Новий оклад
                        cin >> temp2;
                        if (temp2 < Sotr.pay - temp1 || temp2 > temp1 + Sotr.pay) // Перевіряємо оклад
                            cout << "50% rule error\n"; // Виведення помилки
                        else
                            Sotr.pay = temp2; // Встановлюємо новий оклад
                    }
                    else if (action == 2)
                    {
                        cout << "enter new name: "; // Виведення повідомлення
                        string temp; // Новий ПІБ
                        getline(cin >> ws, temp); // вводимо новий ПІБ
                        strcpy(Sotr.name, temp.c_str()); // Копіюємо новий ПІБ у Sotr.name
                    }
                    else if (action == 3)
                    {
                        cout << "enter new wage: ";
                        float temp1 = (Sotr.pay / 100) * 50; // 50%
                        float temp2; // Новий оклад
                        cin >> temp2; // Введення нового окладу
                        if (temp2 < Sotr.pay - temp1 || temp2 > temp1 + Sotr.pay) // Перевіряємо новий оклад
                            cout << "50% rule error"; // Виведення помилки
                        else
                            Sotr.pay = temp2; // Встановлюємо новий оклад

                        cout << "enter new birth year: ";
                        cin >> Sotr.birth_year; // Введення нового дня народження
                        cout << "enter new name: "; // Виведення повідомлення
                        string temp; // Новий ПІБ
                        getline(cin >> ws, temp); // вводимо новий ПІБ
                        strcpy(Sotr.name, temp.c_str()); // Копіюємо новий ПІБ у Sotr.name
                    }
                    fseek(fout1, num * sizeof(Sotr), SEEK_SET);
                    fwrite(&Sotr, sizeof(Sotr), 1, fout1);
                    printf("%s\t%i\t%f\n", Sotr.name, Sotr.birth_year, Sotr.pay); // Вивід результату на екран
                    action = -1;
                }
            }
        }
    }

    fclose(fout1);
    cout << "editing finished\n";
    system("pause");
    return false;
}

const int l_name = 35; // Довжини поля
struct Sotr // Структура
{
    char name[l_name + 1]; // Довжина поля задана з урахуванням нуль-символу
    int birth_year;
    float pay;
};
int compare1(const void* str1, const void* str2) // Порівняння рядків
{
    return strcmp(((Sotr*)str1)->name, ((Sotr*)str2)->name); // Лексиграфічне порівняння двох рядків
}
int compare2(const void* str2, const void* str1) // Порівняння рядків
{
    return strcmp(((Sotr*)str1)->name, ((Sotr*)str2)->name); // Лексиграфічне порівняння двох рядків
}
int compare3(const void* by1, const void* by2) // Порівняння чисел
{
    return ((Sotr*)by1)->birth_year > ((Sotr*)by2)->birth_year ? -1 : ((Sotr*)by1)->birth_year == ((Sotr*)by2)->birth_year ? 0 : 1; // Лексиграфічне порівняння двох чисел
}
int compare4(const void* by2, const void* by1) // Порівняння чисел
{
    return ((Sotr*)by1)->birth_year > ((Sotr*)by2)->birth_year ? -1 : ((Sotr*)by1)->birth_year == ((Sotr*)by2)->birth_year ? 0 : 1; // Лексиграфічне порівняння двох чисел
}
int compare5(const void* by3, const void* by4) // Порівняння чисел
{
    return ((Sotr*)by3)->pay > ((Sotr*)by4)->pay ? -1 : ((Sotr*)by3)->pay == ((Sotr*)by4)->pay ? 0 : 1; // Лексиграфічне порівняння двох чисел
}
int compare6(const void* by4, const void* by3) // Порівняння чисел
{
    return ((Sotr*)by3)->pay > ((Sotr*)by4)->pay ? -1 : ((Sotr*)by3)->pay == ((Sotr*)by4)->pay ? 0 : 1; // Лексиграфічне порівняння двох чисел
}
int task3() {
    FILE* fbin;
    fbin = fopen("db_otd-kadr.bin", "rb"); // Відкриття файлу db_otd-kadr.bin, r - читання, b - бінарний режим
    if (fbin == NULL)
    {
        cout << "error file";
        system("pause");
        return false;
    }
    fseek(fbin, 0, SEEK_END); // Перейти в кінець файлу
    int n_record = ftell(fbin) / sizeof(Sotr); // Поточна позиція в байтах, виміряна від початку файлу
    cout << "number of employees: " << n_record << endl;
    Sotr* st = new Sotr[n_record];
    fseek(fbin, 0, SEEK_SET);
    fread(st, sizeof(Sotr), n_record, fbin); // Зчитування файлу у масив
    fclose(fbin);

    int action = 0;
    while (action != -1)
    {
        cout << "Enter the sort number (to exit the program, enter: -1):\
            \n1 - alphabetically (descending)\n2 - alphabetically (ascending)\
            \n3 - by date of birth (descending)\n4 - by date of birth (ascending)\
            \n5 - by salary (descending)\n6 - by salary (ascending)\n";
        cin >> action;
        if (action != -1 && (action < 1 || action > 6))
            cout << "expected sort number";

        else if (action != -1)
        {
            if (action == 1) qsort(st, n_record, sizeof(Sotr), compare1); // Сортування масиву структур
            else if (action == 2) qsort(st, n_record, sizeof(Sotr), compare2);
            else if (action == 3) qsort(st, n_record, sizeof(Sotr), compare3);
            else if (action == 4) qsort(st, n_record, sizeof(Sotr), compare4);
            else if (action == 5) qsort(st, n_record, sizeof(Sotr), compare5);
            else if (action == 6) qsort(st, n_record, sizeof(Sotr), compare6);
            for (int i = 0; i < n_record; i++) // Друк
            {
                printf("%s\t%i\t%f\n", st[i].name, st[i].birth_year, st[i].pay);
            }
        }
    }
    system("pause");
    return false;
}

struct AEROFLOT
{
    string destination;
    string flightNumber;
    string aircraftType;
};
void flightInput(AEROFLOT* flight, const int& n)
{
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Entering information for the " << i + 1 << " flight\n";
        cout << "Enter destination - ";
        cin >> flight[i].destination;
        cout << "Enter flight number - ";
        cin >> flight[i].flightNumber;
        cout << "Enter aircraft type - ";
        cin >> flight[i].aircraftType;
        cout << endl;
    }
}
void sortFlight(AEROFLOT* flight, const int& n, const int& m)
{
    for (int i = n - 1; i >= 0; i--)
        for (int j = 0; j < i; j++)
            switch (m)
            {
            case 1:
                if (flight[j].destination > flight[j + 1].destination)
                    swap(flight[j], flight[j + 1]);
                break;
            case 2:
                if (flight[j].flightNumber > flight[j + 1].flightNumber)
                    swap(flight[j], flight[j + 1]);
                break;
            case 3:
                if (flight[j].aircraftType > flight[j + 1].aircraftType)
                    swap(flight[j], flight[j + 1]);
                break;
            default:
                cout << "key error";
                break;
            }
}
void findFlight(AEROFLOT* flight, const int& n, string& key, const int& m)
{
    int k = 0;
    for (int i = 0; i < n; ++i)
        switch (m)
        {
        case 1:
            if (flight[i].destination == key)
                cout << "Flight destination - " << flight[i].destination << "\tFlight number - " << flight[i].flightNumber << "\tAircraft type - " << flight[i].aircraftType << endl;
            else k++;
            break;
        case 2:
            if (flight[i].flightNumber == key)
                cout << "Flight destination - " << flight[i].destination << "\tFlight number - " << flight[i].flightNumber << "\tAircraft type - " << flight[i].aircraftType << endl;
            else k++;
            break;
        case 3:
            if (flight[i].aircraftType == key)
                cout << "Flight destination - " << flight[i].destination << "\tFlight number - " << flight[i].flightNumber << "\tAircraft type - " << flight[i].aircraftType << endl;
            else k++;
            break;
        default:
            cout << "key error";
            break;
        }
    if (k == n)
        cout << "No flights found\n";
}
void printFlightFile(AEROFLOT* flight, const int& n)
{
    ofstream file("sod5.txt", ios_base::app);
    if (!file.is_open())
    {
        cout << "file error\n";
        return;
    }
    for (int i = 0; i < n; i++)
        file << "Flight destination - " << flight[i].destination << "\tFlight number - " << flight[i].flightNumber << "\tAircraft type - " << flight[i].aircraftType << endl;
    file.close();
}
void printFlightConsole(AEROFLOT* flight, const int& n)
{
    for (int i = 0; i < n; i++)
        cout << "Flight destination - " << flight[i].destination << "\tFlight number - " << flight[i].flightNumber << "\tAircraft type - " << flight[i].aircraftType << endl;
}
int task4()
{
    int n;
    cout << "Enter number of flights - ";
    cin >> n;
    AEROFLOT* flight = new AEROFLOT[n];

    flightInput(flight, n);

    int again = 1;
    while (again)
    {
        cout << "\nEnter number for:\n\t[1] - sort flights\n\t[2] - print flights to console\n\t[3] - print flights to file\n\t[4] - find flight\n\t[0] - close program\n";
        cin >> again;
        if (again == 0) continue;
        else if (again < 0 || again > 4) {
            cout << "wrong number";
            continue;
        }

        int m;
        string key;
        switch (again)
        {
        case 1:
            cout << "\nEnter sort attribute:\n\t[1] - destination\n\t[2] - flight number\n\t[3] - aircraft type\n";
            cin >> m;
            sortFlight(flight, n, m);
            break;
        case 2:
            printFlightConsole(flight, n); break;
        case 3:
            printFlightFile(flight, n); break;
        case 4:
            cout << "\nEnter search attribute:\n\t[1] - destination\n\t[2] - flight number\n\t[3] - aircraft type\n";
            cin >> m;
            cout << "\nEnter key to search - ";
            cin >> key;
            findFlight(flight, n, key, m);
            break;
        default:
            cout << "wrong number"; break;
        }
    }
    delete[]flight;
    return 0;
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(0, "rus");

    task1();
    task2();
    task3();
    task4();
}