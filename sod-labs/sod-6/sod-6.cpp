#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <string>
#include <windows.h>

using namespace std;

struct Node // Структура
{
    int data;
    Node* right;
    Node* left;
};
struct NodePrint {
    NodePrint* child;
    bool printing_last_child;
};

// Прототипи функцій:
NodePrint* root = NULL;
void printSubTree(const Node* tree);
void printTree(const Node* root_tree);
bool searchNode(Node* root, int value, bool& result);
Node* addNode(Node* root, int value);
Node* removeNode(Node* root, int value);
Node* minValueNode(Node* root);
Node* maxValueNode(Node* root);
void sumValuesNode(Node* root);
int sumLevelValuesNode(Node* root, int level);
void saveValuesNode(Node* root, FILE& pFile);
int sum = 0; // Сума

void printTree(const Node* root_tree) {
    try {
        if (root_tree != NULL) {
            printSubTree(root_tree);
        }
    }
    catch (...) { // перевірка стану і вихід з програми
        root = NULL;
        throw;
    }
}
void printSubTree(const Node* tree) {
    NodePrint* parent;
    if (root != NULL) {
        printf(" ");
        NodePrint* s = root;
        while (s->child != NULL) {
            printf(s->printing_last_child ? " " : "| ");
            s = s->child;
        }
        parent = s;
        printf(parent->printing_last_child ? "-" : "+");
    }
    else {
        parent = NULL;
    }
    printf(">%i\n", tree->data);
    if ((tree->left != NULL) || (tree->right != NULL)) { // якщо є дочірній правий або лівий вузли
        NodePrint s;
        if (parent != NULL) {
            parent->child = &s;
        }
        else {
            root = &s;

        }
        s.child = NULL;
        // друк дочірніх вузлів
        if (tree->left != NULL) {
            s.printing_last_child = (tree->right == NULL);
            printSubTree(tree->left);
        }
        if (tree->right != NULL) {
            s.printing_last_child = true;
            printSubTree(tree->right);
        }
        if (parent != NULL) {
            parent->child = NULL;
        }
        else {
            root = NULL;
        }
    }
}
Node* addNode(Node* root, int value)
{
    if (root == NULL)
    {
        Node* node = new Node();
        node->data = value;
        return node;
    }
    else
    {
        if (value < root->data) root->left = addNode(root->left, value);
        else root->right = addNode(root->right, value);
    }
    return root; // Повертаємо дерево
}
Node* minValueNode(Node* root)
{
    Node* current = root;
    while (current != NULL && current->left != NULL) current = current->left;
    return current;
}
Node* maxValueNode(Node* root)
{
    Node* current = root;
    while (current != NULL && current->right != NULL) current = current->right;
    return current;
}
void sumValuesNode(Node* root)
{
    if (root != NULL)
    {
        sumValuesNode(root->right);
        sum += root->data;
        sumValuesNode(root->left);
    }
}
int sumLevel(Node* root, int level, int k)
{
    if (root == NULL) return 0;
    if (k == level) return root->data;
    return sumLevel(root->left, level, k + 1) + sumLevel(root->right, level, k + 1);
}
int sumLevelValuesNode(Node* root, int level)
{
    int result = 0;
    if (root != NULL)
    {
        result = sumLevel(root, level, 1);
    }
    return result;
}
void saveValuesNode(Node* root, FILE& pFile)
{
    if (root != NULL)
    {
        fprintf(&pFile, "%d", root->data);
        saveValuesNode(root->right, pFile);
        saveValuesNode(root->left, pFile);
    }
}
Node* removeNode(Node* root, int value)
{
    if (root == NULL) return root;
    if (value < root->data) root->left = removeNode(root->left, value);
    else if (value > root->data) root->right = removeNode(root->right, value);
    else
    {
        if (root->left == NULL)
        {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else
        {
            Node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = removeNode(root->right, temp->data);
        }
    }
    return root;
}
bool searchNode(Node* root, int value, bool& result)
{
    if (root != NULL)
    {
        if (root->data == value) result = true;
        else if (root->data < value) searchNode(root->right, value, result);
        else searchNode(root->left, value, result);
    }
    return result;
}
int task1()
{
    int size_input;
    char* input = new char();
    int array[100];
    memset(array, -1, 100); // Заповнюємо байтами блок пам'яті
    cout << "Введіть скільки чисел ви хочете ввести в дерево: "; // Виводимо текст
    cin >> size_input; // Вводимо значення
    cin.get();

    cout << "Введіть " << size_input << " чисел, розділені пробілом:" << endl; // Виводимо текст
    for (int i = 0; i < size_input; i++) cin >> array[i]; // Вводимо значення
    cin.get();

    Node* root = NULL;
    for (int i = 0; i < size_input; i++) root = addNode(root, array[i]);
    bool running = true; // Чи не закінчили роботу?
    while (running)
    {
        cout << "Що б Ви хотіли зробити? Введіть: \n1 - Додати вузол\n2 - Видалити вузол\n3 - Знайти вузол\n4 - Вивести дерево\
                \n5 - Знайти мінімальне значення\n6 - Знайти максимальне значення\n7 - Знайти суму всіх вузлів\
                \n8 - Знайти суму всіх вузлів на певному рівні \n9 - Вийти" << endl;
        cin.getline(input, 80, '\n');
        if (strcmp(input, "1") == 0)
        {
            int number; // Номер
            cout << "Введіть номер, який бажаєте додати: ";
            cin >> number;
            cin.get();
            root = addNode(root, number);
            printTree(root);
        }
        else if (strcmp(input, "2") == 0)
        {
            int number; // Номер
            cout << "Введіть номер, який ви хочете видалити:";
            cin >> number; // Вводимо номер
            cin.get();
            root = removeNode(root, number);
            printTree(root);
        }
        else if (strcmp(input, "3") == 0)
        {
            int number; // Номер
            bool result = false;
            cout << "Введіть номер, який ви хочете знайти: ";
            cin >> number; // Вводимо номер
            cin.get();
            if (searchNode(root, number, result) == true) // Повернення, якщо знайдено
            {
                cout << "Це число є на дереві!" << endl;
                printTree(root);
            }
            else cout << "Цього числа немає на дереві!" << endl; // Інакше повідомляємо, що не знайдено
        }
        else if (strcmp(input, "4") == 0) printTree(root); // Перевіряємо номер, який запровадили
        else if (strcmp(input, "5") == 0) cout << "Результат: " << minValueNode(root)->data << endl;
        else if (strcmp(input, "6") == 0) cout << "Результат: " << maxValueNode(root)->data << endl;
        else if (strcmp(input, "7") == 0)
        {
            sum = 0; // Обнулюємо суму
            sumValuesNode(root);
            cout << "Результат: " << sum << endl;
        }
        else if (strcmp(input, "8") == 0)
        {
            int level; // Номер
            cout << "Введіть номер рівня, на якому хочете знайти суму всіх вузлів:";
            cin >> level; // Вводимо номер
            cin.get();
            if (level <= 0) cout << "Введіть номер рівня більше 0!" << endl; // Виводимо помилку
            else cout << "На рівні " << level << " сума вузлів = " << sumLevelValuesNode(root, level) << endl;
        }
        else if (strcmp(input, "9") == 0) // Перевіряємо номер, який ввели
        {
            running = false;
            FILE* pFile = NULL;
            pFile = fopen("sod6.txt", "w");
            if (pFile == NULL) // Перевіряємо чи відкрився файл
            {
                cout << "Помилка при відкритті файлу sod6.txt!" << endl;
                system("pause");
                return false;
            }
            saveValuesNode(root, *pFile);
            fclose(pFile);
        }
    }
    system("pause");
    return false;
}


struct LIBRARY
{
    char number[20];
    char PIB[30];
    char name[30];
    int year;
    int kolvo;
};
struct ITEM
{
    LIBRARY* Library;
    ITEM* next;
};
ITEM* create(LIBRARY* Library)
{
    ITEM* head = new ITEM;
    head->Library = Library;
    head->next = NULL;
    return head;
}
void add(LIBRARY* Library, ITEM* head)
{
    while (head->next)
        head = head->next;
    head->next = new ITEM;
    head->next->Library = Library;
    head->next->next = NULL;
    cout << endl;
}
LIBRARY* make()
{
    LIBRARY* Library = new LIBRARY;

    cout << "Enter book number: ";
    cin >> Library->number;

    cout << "\nEnter PIB: ";
    cin >> Library->PIB;

    cout << "\nEnter book name: ";
    cin >> Library->name;

    cout << "\nEnter made year: ";
    cin >> Library->year;

    cout << "\nEnter count of books: ";
    cin >> Library->kolvo;

    return Library;
}
void printLIBRARY(LIBRARY* Library)
{

    cout << "Number of book => " << Library->number << endl;
    cout << "FIO => " << Library->PIB << endl;
    cout << "Name of book => " << Library->name << endl;
    cout << "Year => " << Library->year << endl;
    cout << "Count of book => " << Library->kolvo << endl;
    cout << endl;
}
ITEM* remove(ITEM* str)
{
    ITEM* tail = str, * head = str;
    char nomer[30];
    cout << "Enter name of book\n";
    cin >> nomer;
    while (head)
    {
        if (!strcmp(nomer, head->Library->name))
        {
            head->Library = NULL;
            if (tail == head)
                str = head->next;
            tail->next = head->next;
            tail = head;
            head = head->next;
        }
        else head = head->next;
    }
    cout << "Information about book deleted" << endl;
    return str;
}
int choice()
{
    int answer;
    cout << "Add new books - enter [1]\n";
    cout << "Print LIBRARY - enter [2]\n";
    cout << "Delete book - enter [3]\n";
    cout << "Exit - enter [4]\n\n\n";
    cout << "Enter your choice: ";
    cin >> answer;
    if (answer >= 1 && answer <= 5)
        return answer;
    else
        return 0;
}
int task2()
{
    ITEM* head = NULL;
    int ch;
    while (1)
    {
        ch = choice();
        if (ch == 1)
        {
            cout << endl;

            if (head == NULL)
                head = create(make());
            else
                add(make(), head);
        }
        else if (ch == 2)
        {
            cout << endl;
            int i = 0;
            int N = 0;

            ITEM* phead = head;
            while (head)
            {
                N++;
                head = head->next;
            }

            LIBRARY* buf;
            LIBRARY** pLibrary = new LIBRARY * [N];
            head = phead;

            while (head)
            {
                pLibrary[i] = head->Library;
                head = head->next;
                i++;
            }

            head = phead;
            for (i = 0; i < N; i++)
                printLIBRARY(pLibrary[i]);
        }
        else if (ch == 3)
        {
            head = remove(head);
        }
        else if (ch == 4)
        {
            break;
            cout << endl;
        }

    }
    return 0;
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_CTYPE, "rus");

    task1();
    task2();
}