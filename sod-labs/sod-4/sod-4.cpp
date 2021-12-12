#include <iostream>
#include <fstream>
#include <ctime> 
#include <set>
#include <map>

#include <nlohmann/json.hpp> // підключення бібліотеки json.hpp, написаної Нільсом Лоухменном для полегшення роботи з json

using namespace std;
using json = nlohmann::json;

string findWhatDayIsIt(string& date) { // Відокремлення дня від цілого формату дати
    string result;
    size_t pos = date.find(',');
    return date.substr(0, pos);
}

string findWhatYearIsIt(string date) { // Відокремлення року від цілого формату дати
    string result;
    size_t pos;
    int x = 0;

    while ((pos = date.find(' ')) != string::npos) {
        result = date.substr(0, pos);
        date.erase(0, pos + 1);
        x++;
        if (x == 4)
            return result;
    }
    return result;
}

int main() {
    ifstream jsonFile("mails2.json"); // відкриваємо файл mails.json для читання

    if (!jsonFile.is_open()) { // перевірка на існування/доступ до файлу
        cout << "file error\n";
        return 1;
    }

    string line; // рядок з файлу mails.json
    json json; // об'єкт класу json
    unsigned int task1Counter = 0; // лічильник для першого завдання
    set<string> task2Set{}; // набір для другого завдання
    map<string, int> task3Map{}; // карта для третього завдання
    unsigned int task4Shanna = 0; // лічильник №1 для четвертого завдання
    unsigned int task4Eric = 0; // лічильник №2 для четвертого завдання
    map<string, int> task5Map{}; // карта для п'ятого завдання
    map<string, unsigned int> task6Map{}; // карта №1 для шостого завдання
    pair<string, unsigned int> task6Max{ "",0 }; // карта №2 для шостого завдання
    unsigned int startTime = clock(); // відлік часу роботи програми почато

    while (getline(jsonFile, line)) { // перебираємо кожен рядок mails.json по черзі
        json = json::parse(line); // передаємо значення поточного рядка об'єкту класа json

        if (!json["_id"].empty() && !json["_id"]["$oid"].empty())
            task1Counter++; // якщо в рядку існує ключ _id, і він не пустий, інкрементуємо перший лічильник

        if (!json["headers"].empty()) {
            bool isSkip = !json["headers"]["From"].empty()
                && !json["headers"]["To"].empty()
                && !json["headers"]["Date"].empty()
                && !json["headers"]["Subject"].empty();
            if (!isSkip) continue; // якщо яке небудь із важливих полів не заповнено - пропускаємо рядок

            task2Set.insert((string)json["headers"]["From"]); // додаємо до набору значення кожного рядку

            if ((string)json["headers"]["To"] == "ebass@enron.com") {
                string temp = json["headers"]["Date"];
                string key = findWhatDayIsIt(temp);
                task3Map[key] += 1; // додаємо до карти день тижня кожного листа, що був надісланий до ebass@enron.com
            }

            string from = json["headers"]["From"],
                to = json["headers"]["To"];
            if (from == "shanna.husser@enron.com" && to == "eric.bass@enron.com")
                task4Shanna++; // інкрементуємо лічильник четвертого завдання, якщо виконується умова
            else if (from == "eric.bass@enron.com" && to == "shanna.husser@enron.com")
                task4Eric++; // інкрементуємо лічильник четвертого завдання, якщо виконується умова

            if ((string)json["headers"]["From"] == "laurie.ellis@enron.com") {
                string year = findWhatYearIsIt(json["headers"]["Date"]);
                string key = json["headers"]["Subject"];
                if (year == "2000")
                    task5Map[key] ++; // шукаємо повторюванні теми листів laurie.ellis@enron.com
            }

            string temp = json["headers"]["Date"];
            string key = findWhatDayIsIt(temp);
            task6Map[key] ++; // додаємо до карти день тижня кожного листа
        }
    }

    for (int i = 0; i < 7; i++)
    {
        string days[] = { "Mon","Tue","Wed","Thu","Fri","Sat","Sun" };
        auto it = task6Map.find(days[i]);
        if (task6Max.second < it->second) // знаходимо день з найбільшою кількістю листів
        {
            task6Max.first = it->first;
            task6Max.second = it->second;
        }
    }

    unsigned int endTime = clock(); // запиняємо лічильник часу

    cout << "\t[TASK 1]\n";
    cout << "total number of emails (according to the key \"_id\") - " << task1Counter;

    cout << "\n\n\t[TASK 2]\n";
    cout << "number of unique senders (according to the \"From\" key) - " << task2Set.size();

    cout << "\n\n\t[TASK 3]\n";
    cout << "how many emails were sent to the address ebass@enron.com \n(according to the \"To\" key) every day of the week?\n";
    for (auto& pair : task3Map) // виводимо значення кожної пари в карті
        cout << pair.first << " - " << pair.second << endl;

    cout << "\n\t[TASK 4]\n";
    cout << "emails sent from Shanna Husser to Eric Bass - " << task4Shanna;
    cout << "\nemails sent from Eric Bass to Shanna Husser - " << task4Eric;

    cout << "\n\n\t[TASK 5]\n";
    cout << "recurrence of the themes of Laurie Ellis' emails:\n";
    for (auto& pair : task5Map) // виводимо значення кожної пари в карті
        cout << pair.first << " - " << pair.second << endl;

    cout << "\n\t[TASK 6]\n";
    cout << "on which day of the week are the maximum number of emails sent?\n" << task6Max.first << " - " << task6Max.second;

    cout << "\n\n\t[TIME]\n";
    cout << "time taken - " << endTime - startTime << " ms\n";
}