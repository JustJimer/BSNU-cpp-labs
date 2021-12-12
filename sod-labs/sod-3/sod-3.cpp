#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <sstream>

using namespace std;

auto& npos = string::npos;


void task1() {
    cout << "\tFIRST TASK\n";
    ifstream file1("Shakespeare_Winter'sTale.txt", ios::binary);
    ofstream file2("Shakespeare's interrogative sentences.txt", ios::out);

    if (!file1.is_open() || !file2.is_open())
    {
        cout << "[TASK 1] file error\n";
        return;
    }


    file1.seekg(0, ios::end);
    long len = file1.tellg();
    cout << "[TASK 1] source file size - " << len << " bytes\n\n";
    char* buf = new char[len + 1];
    file1.seekg(0, ios::beg);
    file1.read(buf, len);
    file1.close();
    buf[len] = '\0';
    long n = 0, i = 0;
    while (buf[i])
    {
        if (buf[i] == '?')
        {
            for (int j = n; j <= i; j++)
            {
                cout << buf[j];
                file2 << buf[j];
                if (j == i)
                {
                    cout << endl;
                    file2 << endl;
                }
            }
            n = i + 1;
        }
        if (buf[i] == '.' || buf[i] == '!' || buf[i] == '\n') n = i + 1;
        i++;
    }
    file2.close();
}

void task2()
{
    cout << "\n\n\n\tSECOND TASK\n";
    int arr1[] = { 23, 65, 1, 87, 0, 1324, 6457, 23, 345, 1, 34, 65, 123, 65, 7, 8, 9 };
    char arr2[] = { 'a', '\0', 'z' };
    double m = 3.14159265;
    double n = 0.0006;

    ofstream file3("Z3.dat", ios::binary);
    if (!file3.is_open())
    {
        cout << "[TASK 2] file error\n";
        return;
    }
    cout << "[TASK 2] 8 bytes - size of m\n";
    file3.write((char*)&m, sizeof(m));
    cout << "[TASK 2] 8 bytes - size of n\n";
    file3.write((char*)&n, sizeof(n));
    cout << "[TASK 2] 4 bytes * " << sizeof(arr1) / sizeof(*arr1) << " - size of arr1\n";
    for (int i = 0; i < (sizeof(arr1) / sizeof(*arr1)); i++)
        file3.write((char*)&arr1[i], sizeof(arr1[i]));
    cout << "[TASK 2] 1 bytes * 3 - size of arr2\n";
    for (int i = 0; i < 3; i++)
        file3.write((char*)&arr2[i], sizeof(arr2[i]));
    file3.close();

    ifstream fout("Z3.dat", ios::binary);
    if (!fout.is_open())
    {
        cout << "[TASK 2] file error\n";
        return;
    }
    fout.seekg(0, ios::end);
    long len = fout.tellg();
    cout << "[TASK 2] total length - " << len << endl;
    fout.close();
    ofstream fin2("Z3.dat", ios::binary | ios::app);
    if (!fin2.is_open())
    {
        cout << "[TASK 2] file error\n";
        return;
    }
    cout << "[TASK 2] 4 bytes - size of len\n";
    fin2.write((char*)&len, sizeof(len));
    fin2.close();
}

void task3() {
    cout << "\n\n\n\tTHIRD TASK\n";
    ifstream file4("task3.txt", ios::binary);
    if (!file4.is_open()) {
        cout << "[TASK 3] file error\n";
        return;
    }
    int n = 10;
    int* arr = new int[n];
    string buf;
    int i = 0;
    for (file4 >> buf; !file4.eof() && i < n; file4 >> buf) {
        arr[i] = stoi(buf);
        cout << arr[i] << "\t";
        i++;
    }
    file4.close();
    int index, value;
    cout << "\n[TASK 3] enter index of element you want to change: ";
    cin >> index;
    if (index > n || index < 0) {
        cout << "[TASK 3] index error\n";
        return;
    }
    cout << "[TASK 3] enter value: ";
    cin >> value;
    arr[index] = value;
    for (i = 0; i < n; ++i) {
        cout << arr[i] << "\t";
    }

    cout << "\n[TASK 3] enter index of element you want to delete: ";
    cin >> index;
    if (index > n || index < 0) {
        cout << "[TASK 3] index error\n";
        return;
    }
    int* new_arr = new int[n - 1];
    int k;
    for (i = 0, k = 0; i < n; ++i, ++k) {
        if (index == i) {
            k--;
            continue;
        }
        new_arr[k] = arr[i];
    }
    arr = new_arr;
    n--;
    for (i = 0; i < n; ++i)
        cout << arr[i] << "\t";
    cout << endl;
    delete[] arr;
}

void task4()
{
    cout << "\n\n\n\tFOURTH TASK\n";
    ifstream file5("task4.txt", ios::binary);
    if (!file5.is_open()) {
        cout << "[TASK 4] file error\n";
        return;
    }
    vector<int> arr;
    string buf;
    for (file5 >> buf; !file5.eof(); file5 >> buf) {
        arr.push_back(stoi(buf));
        cout << arr.at(arr.size() - 1) << "\t";
    }
    file5.close();
    cout << endl;
    int index, value;
    cout << "[TASK 4] enter index of element you want to change: ";
    cin >> index;
    if (index > arr.size() || index < 0) {
        cout << "[TASK 4] index error\n";
        return;
    }
    cout << "[TASK 4] enter value: ";
    cin >> value;
    arr.at(index) = value;
    for (int i = 0; i < arr.size(); ++i)
        cout << arr.at(i) << "\t";
    cout << endl;
}

void task5() {
    cout << "\n\n\n\tFIFTH TASK\n";
    ifstream file6("task5.txt", ios::binary);
    if (!file6.is_open()) {
        cout << "[TASK 5] file error\n";
        return;
    }
    const int N = 5;
    const int M = 10;
    int arr[N][M];
    string buf;
    int i = 0, j = 0;
    for (file6 >> buf; !file6.eof() && i < N; file6 >> buf) {
        arr[i][j] = stoi(buf);
        j++;
        if (j == M) {
            i++;
            j = 0;
        }
    }
    file6.close();
    for (i = 0; i < N; ++i) {
        for (j = 0; j < M; ++j)
            cout << arr[i][j] << "\t";
        cout << endl;
    }
    int index_i, index_j;
    cout << "[TASK 5] enter two indexes of element you want to change: ";
    cin >> index_i >> index_j;
    if (index_i > N || index_i < 0 || index_j > M || index_j < 0) {
        cout << "[TASK 5] index error\n";
        return;
    }
    int value;
    cout << "[TASK 5] enter value: ";
    cin >> value;
    arr[index_i][index_j] = value;
    for (i = 0; i < N; ++i) {
        for (j = 0; j < M; ++j) {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
}

void task6() {
    cout << "\n\n\n\tSIXTH TASK\n";
    ifstream file7("file1.png", ios::binary);
    ifstream file8("file2.png", ios::binary);
    if (!file7.is_open() || !file8.is_open()) {
        cout << "[TASK 6] file error\n";
        return;
    }
    stringstream buf1, buf2;

    buf1 << file7.rdbuf();
    buf2 << file8.rdbuf();
    file7.close();
    file8.close();
    string str_file1 = buf1.str();
    string str_file2 = buf2.str();

    if (str_file1.size() != str_file2.size())
        cout << "[TASK 6] files are not equals\n";
    if (str_file1 == str_file2)
        cout << "[TASK 6] files are equals by content\n";
    if (str_file2.find(str_file1) != string::npos)
        cout << "[TASK 6] file2 contains file1\n";
    if (str_file1.find(str_file2) != string::npos)
        cout << "[TASK 6] file1 contains file2\n";
}

void task7() {
    cout << "\n\n\n\tSEVENTH TASK\n";
    ifstream file9("file1.txt", ios::binary);
    ifstream file10("file2.txt", ios::binary);
    if (!file9.is_open() || !file10.is_open()) {
        cout << "[TASK 7] file error\n";
        return;
    }
    stringstream buf1, buf2;

    buf1 << file9.rdbuf();
    buf2 << file10.rdbuf();
    file9.close();
    file10.close();
    string str_file1 = buf1.str();
    string str_file2 = buf2.str();

    if (str_file1.size() != str_file2.size())
        cout << "[TASK 7] files are not equals\n";
    if (str_file1 == str_file2)
        cout << "[TASK 7] files are equals by content\n";
    if (str_file2.find(str_file1) != string::npos)
        cout << "[TASK 7] file2 contains file1\n";
    if (str_file1.find(str_file2) != string::npos)
        cout << "[TASK 7] file1 contains file2\n";
}

void task8() {
    cout << "\n\n\n\tEIGHTH TASK\n";
    ifstream file11("file3.txt", ios::binary);
    ifstream file12("file4.txt", ios::binary);
    if (!file11.is_open() || !file12.is_open()) {
        cout << "[TASK 8] file error\n";
        return;
    }
    string buf1, buf2;
    int pc1 = 1, pc2 = 1, pc3 = 0;
    set<string> strings;
    string result = "";



    for (file11 >> buf1; !file11.eof(); file11 >> buf1) {
        strings.insert(buf1);
        pc1++;
    }

    for (file12 >> buf2; !file12.eof(); file12 >> buf2) {
        if (strings.find(buf2) != strings.end()) {
            result += buf2 + " ";
            pc3++;
        }
        pc2++;
    }
    file11.close();
    file12.close();
    ofstream file13("task8.txt", ios::binary);
    if (!file13.is_open()) {
        cout << "[TASK 8] file error\n";
        return;
    }
    file13 << result;
    file13.close();

    cout << result << endl;
    cout << "[TASK 8] the percentage of overlapping pieces of the relative total content of the file file3.txt - " << (pc3 * 100) / pc1 << "%\n";
    cout << "[TASK 8] the percentage of overlapping pieces of the relative total content of the file file4.txt - " << (pc3 * 100) / pc2 << "%\n";
}

int main() {
      task1();
      task2();
      task3();
      task4();
      task5();
      task6();
      task7();
      task8();
}