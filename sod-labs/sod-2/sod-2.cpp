#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

int main() {
	SetConsoleCP(1251); // ������������� ��������� ��� ���������� ����������� ���������� �������
	SetConsoleOutputCP(1251);

	const int length = 101;

	char key[length];
	char line[length];

	cout << "\tTASK 1\n";
	cout << "Enter search key: "; // ������� ������� ����� ����
	cin >> key;

	ifstream sourceFile1("text_city_UA.txt"); // ������� ���� �� �����
	if (!sourceFile1) { // ���� ���� ��������� ������� - ��������� ������ ����������
		cout << "File can not be opened!\n";
		return true;
	}
	while (sourceFile1.getline(line, length)) // ���������� ���� �� ������ �����
		if (strstr(line, key)) // ���������� ����� �� ������� � �������� ����� ������
			cout << "Match! " << line << " city was found by key: " << key << endl; // ����������� �� ����� �������	
	cout << "No more matches found!\n";

	//////////////////////////////////////////
	cout << "\n\tTASK 2\n";

	cout << "Enter search key: "; // ������� �����, ��� ������ ������������
	cin >> key;

	ifstream sourceFile2("Shakespeare_Hamlet.txt"); // ������� ���� �� �����
	if (!sourceFile2) // ���� ���� ��������� ������� - ��������� ������ ����������
	{
		cout << "File can not be opened!\n";
		return true;
	}

	int count = 0; // ��������� ��������
	char temp[length]; // ��������� ����� ��� ��ﳿ �����
	while (sourceFile2.getline(line, length)) // ���������� ���� �� ������ �����
	{
		strcpy(temp, line); // ��������� ���� ��������� ����� � temp
		bool isFound = false; // ��������� �����, �� �������� ��� �������� �����
		char* separatedLine = strtok(temp, " .,!?-;"); // ������������� ������� strtok ��� ��������� ������
		while (separatedLine != NULL) // ���������� ������� �� ������
		{
			if (strcmp(separatedLine, key) == 0) isFound = true; // ��������� ������� � ������, ��� ���� ������ �����
			separatedLine = strtok(NULL, " .,!?-;");
		}
		if (isFound) // ���� ����� ��������
		{
			cout << "Line: " << line << endl; // �������� ���������
			++count; // ����������� ��������� �� ���������
		}
	}
	cout << "Number of occurrences of word " << key << ": " << count << endl;

	//////////////////////////////////////////
	cout << "\n\tTASK 3\n";



	ifstream sourceFile3("Shakespeare_Winter'sTale_UA.txt"); // ������� ���� �� �����
	if (!sourceFile3) // ���� ���� ��������� ������� - ��������� ������ ����������
	{
		cout << "File can not be opened!\n";
		return true;
	}
	while (sourceFile3.getline(line, length)) // ���������� ���� �� ������ �����
	{
		strcpy(temp, line); // ��������� ���� ��������� ����� � temp
		char* separatedLine = strtok(temp, " -"); // ������������� ������� strtok ��� ��������� ������
		char* tempWord;
		while (separatedLine != NULL) // ���������� ������� �� ������
		{
			tempWord = separatedLine; // ��������� ���� ������� �����
			separatedLine = strtok(NULL, " -"); // ���������� �� ���������� �������
			if (separatedLine != NULL) // ����������, �� �� ����� �� ���� �����
				cout << separatedLine << " " << tempWord << " "; // �������� �����, ���� ����� �����
			else
			{
				cout << tempWord << " "; // �������� ������ �����, ��� �������� �����
				continue; // ����, ����� �� ���� �����, ���������� ��������� �����
			}
			separatedLine = strtok(NULL, " -"); // ���������� �� ���������� �������
		}
		cout << endl; // ���������� �� ������ �����	
	}
}