#include <iostream>
#include <fstream>
#include <ctime> 
#include <set>
#include <map>

#include <nlohmann/json.hpp> // ���������� �������� json.hpp, �������� ͳ����� ���������� ��� ���������� ������ � json

using namespace std;
using json = nlohmann::json;

string findWhatDayIsIt(string& date) { // ³����������� ��� �� ������ ������� ����
    string result;
    size_t pos = date.find(',');
    return date.substr(0, pos);
}

string findWhatYearIsIt(string date) { // ³����������� ���� �� ������ ������� ����
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
    ifstream jsonFile("mails2.json"); // ��������� ���� mails.json ��� �������

    if (!jsonFile.is_open()) { // �������� �� ���������/������ �� �����
        cout << "file error\n";
        return 1;
    }

    string line; // ����� � ����� mails.json
    json json; // ��'��� ����� json
    unsigned int task1Counter = 0; // �������� ��� ������� ��������
    set<string> task2Set{}; // ���� ��� ������� ��������
    map<string, int> task3Map{}; // ����� ��� �������� ��������
    unsigned int task4Shanna = 0; // �������� �1 ��� ���������� ��������
    unsigned int task4Eric = 0; // �������� �2 ��� ���������� ��������
    map<string, int> task5Map{}; // ����� ��� �'����� ��������
    map<string, unsigned int> task6Map{}; // ����� �1 ��� ������� ��������
    pair<string, unsigned int> task6Max{ "",0 }; // ����� �2 ��� ������� ��������
    unsigned int startTime = clock(); // ���� ���� ������ �������� ������

    while (getline(jsonFile, line)) { // ���������� ����� ����� mails.json �� ����
        json = json::parse(line); // �������� �������� ��������� ����� ��'���� ����� json

        if (!json["_id"].empty() && !json["_id"]["$oid"].empty())
            task1Counter++; // ���� � ����� ���� ���� _id, � �� �� ������, ������������ ������ ��������

        if (!json["headers"].empty()) {
            bool isSkip = !json["headers"]["From"].empty()
                && !json["headers"]["To"].empty()
                && !json["headers"]["Date"].empty()
                && !json["headers"]["Subject"].empty();
            if (!isSkip) continue; // ���� ��� ������ �� �������� ���� �� ��������� - ���������� �����

            task2Set.insert((string)json["headers"]["From"]); // ������ �� ������ �������� ������� �����

            if ((string)json["headers"]["To"] == "ebass@enron.com") {
                string temp = json["headers"]["Date"];
                string key = findWhatDayIsIt(temp);
                task3Map[key] += 1; // ������ �� ����� ���� ����� ������� �����, �� ��� ��������� �� ebass@enron.com
            }

            string from = json["headers"]["From"],
                to = json["headers"]["To"];
            if (from == "shanna.husser@enron.com" && to == "eric.bass@enron.com")
                task4Shanna++; // ������������ �������� ���������� ��������, ���� ���������� �����
            else if (from == "eric.bass@enron.com" && to == "shanna.husser@enron.com")
                task4Eric++; // ������������ �������� ���������� ��������, ���� ���������� �����

            if ((string)json["headers"]["From"] == "laurie.ellis@enron.com") {
                string year = findWhatYearIsIt(json["headers"]["Date"]);
                string key = json["headers"]["Subject"];
                if (year == "2000")
                    task5Map[key] ++; // ������ ����������� ���� ����� laurie.ellis@enron.com
            }

            string temp = json["headers"]["Date"];
            string key = findWhatDayIsIt(temp);
            task6Map[key] ++; // ������ �� ����� ���� ����� ������� �����
        }
    }

    for (int i = 0; i < 7; i++)
    {
        string days[] = { "Mon","Tue","Wed","Thu","Fri","Sat","Sun" };
        auto it = task6Map.find(days[i]);
        if (task6Max.second < it->second) // ��������� ���� � ��������� ������� �����
        {
            task6Max.first = it->first;
            task6Max.second = it->second;
        }
    }

    unsigned int endTime = clock(); // ��������� �������� ����

    cout << "\t[TASK 1]\n";
    cout << "total number of emails (according to the key \"_id\") - " << task1Counter;

    cout << "\n\n\t[TASK 2]\n";
    cout << "number of unique senders (according to the \"From\" key) - " << task2Set.size();

    cout << "\n\n\t[TASK 3]\n";
    cout << "how many emails were sent to the address ebass@enron.com \n(according to the \"To\" key) every day of the week?\n";
    for (auto& pair : task3Map) // �������� �������� ����� ���� � ����
        cout << pair.first << " - " << pair.second << endl;

    cout << "\n\t[TASK 4]\n";
    cout << "emails sent from Shanna Husser to Eric Bass - " << task4Shanna;
    cout << "\nemails sent from Eric Bass to Shanna Husser - " << task4Eric;

    cout << "\n\n\t[TASK 5]\n";
    cout << "recurrence of the themes of Laurie Ellis' emails:\n";
    for (auto& pair : task5Map) // �������� �������� ����� ���� � ����
        cout << pair.first << " - " << pair.second << endl;

    cout << "\n\t[TASK 6]\n";
    cout << "on which day of the week are the maximum number of emails sent?\n" << task6Max.first << " - " << task6Max.second;

    cout << "\n\n\t[TIME]\n";
    cout << "time taken - " << endTime - startTime << " ms\n";
}