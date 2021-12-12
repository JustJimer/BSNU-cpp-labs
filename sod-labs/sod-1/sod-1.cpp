#include <iostream>
#include <ctime> 
#include <fstream>
#include <chrono>

using namespace std::chrono;
using namespace std;

int n;
unsigned int start_time;
unsigned int end_time;

void printArray(int* arr)
{
    for (int i = 0; i < n; ++i)
        cout << arr[i] << endl;
}

void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void bubbleSort(int arr[])
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

void selectionSort(int arr[])
{
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        swap(&arr[min_idx], &arr[i]);
    }
}

void insertionSort(int arr[])
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void inversedInsertionSort(int arr[])
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] < key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void merge(int array[], int const left, int const mid, int const right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    auto* leftArray = new int[subArrayOne],
        * rightArray = new int[subArrayTwo];

    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    auto indexOfSubArrayOne = 0,
        indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}

void mergeSort(int array[], int const begin, int const end)
{
    if (begin >= end)
        return;

    auto mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

void fileData(int key) {
    ofstream file;
    file.open("file.txt");

    for (int i = 1000; i < 100001; i += 1000) {
        n = i;
        int* array = new int[n];

        for (int i = 0; i < n; i++) array[i] = rand() % 2001 - 1000;
        start_time = clock();

        switch (key)
        {
        case 1: bubbleSort(array);          break;
        case 2: insertionSort(array);       break;
        case 3: selectionSort(array);       break;
        case 4: mergeSort(array, 0, n - 1); break;
        case 5: quickSort(array, 0, n - 1); break;
        default: cout << "error";           break;
        }
        end_time = clock();

        file << i << " " << end_time - start_time << endl;
        cout << i << " " << end_time - start_time << endl;
        delete[] array;
    }
    file.close();
}

bool PromptConfirmation(string confirmText)
{
    cout << confirmText << " [y/n] : " << endl;
    char key;
    cin >> key;
    if (key != 'Y' && key != 'y')
        return false;
    else
        return true;
}

class Map {
public:
    int key;
    int value;
};

void printArrayMap(Map* map, int n) {
    for (int i = 0; i < n; i++) {
        cout << map[i].value << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << map[i].key << " ";
    }
    cout << endl;
}

void swapMap(Map& a, Map& b) {
    Map temp = a;
    a = b;
    b = temp;
}

void bubbleSortMap(Map* map, int n) {
    cout << "Bubble sort\n";
    printArrayMap(map, n);
    cout << endl;

    for (int j = n - 1; j >= 0; j--)
        for (int i = 0; i < j; i++)
            if (map[i].key > map[i + 1].key)
                swapMap(map[i], map[i + 1]);

    printArrayMap(map, n);
    cout << endl;
}

void insertionSortMap(Map* map, int n) {
    cout << "Insertion sort\n";
    printArrayMap(map, n);
    cout << endl;

    Map key;
    for (int i = 1; i < n; i++)
    {
        key = map[i];
        int j = i - 1;

        while (j >= 0 && map[j].key > key.key)
        {
            map[j + 1] = map[j];
            j = j - 1;
        }
        map[j + 1] = key;
    }
    printArrayMap(map, n);
    cout << endl;

}

void selectionSortMap(Map* map, int n) {
    cout << "Selection sort\n";
    printArrayMap(map, n);
    cout << endl;

    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (map[j].key < map[min_idx].key)
                min_idx = j;

        swapMap(map[min_idx], map[i]);
    }
    printArrayMap(map, n);
    cout << endl;
}

void mergeMap(Map* map, int n, int m) {
    int i, j, k;
    Map* x = new Map[n];
    for (i = 0, j = m, k = 0; k < n; k++) {
        x[k] = j == n ? map[i++]
            : i == m ? map[j++]
            : map[j].key < map[i].key ? map[j++]
            : map[i++];
    }
    for (int i = 0; i < n; i++)
        map[i] = x[i];
    delete x;
}

void mergeSortMap(Map* map, int n) {
    if (n < 2)
        return;
    int m = n / 2;
    mergeSortMap(map, m);
    mergeSortMap(map + m, n - m);
    mergeMap(map, n, m);
}

void mergeSortMap2(Map* map, int n) {
    cout << "Merge sort\n";
    printArrayMap(map, n);
    cout << endl;
    mergeSortMap(map, n);
    printArrayMap(map, n);
    cout << endl;
}

void partitionMap(Map* map, int n) {
    if (n < 2) return;

    int pivot = map[n / 2].key;

    int i, j;

    for (i = 0, j = n - 1; ; i++, j--) {
        while (map[i].key < pivot) i++;
        while (map[j].key > pivot) j--;

        if (i >= j) break;
        swapMap(map[i], map[j]);
    }

    partitionMap(map, i);
    partitionMap(map + i, n - i);
}

void quickSortMap(Map* map, int n) {
    cout << "Quick sort\n";
    printArrayMap(map, n);
    cout << endl;
    partitionMap(map, n);
    printArrayMap(map, n);
    cout << endl;
}

void isSustainability(void(*sort)(Map*, int)) {
    Map* map = new Map[10];
    Map* map_copy = new Map[10];
    int numbers[10] = { 1,0,1,1,1,0,1,0,0,1 };
    for (int i = 0; i < 10; i++) {
        map[i].key = numbers[i];
        map_copy[i].key = numbers[i];
        map[i].value = i;
        map_copy[i].value = i;
    }
    sort(map, 10);
    mergeSortMap(map_copy, 10);
    for (int i = 0; i < 10; i++)
        if (map[i].value != map_copy[i].value) {
            cout << "Algorithm is NOT sustained\n";
            return;
        }
    cout << "Algorithm is sustained\n";
}

void main()
{
    cout << "\tFIRST TASK" << endl;

    cout << "Enter size of array: ";
    cin >> n;
    int* array = new int[n];
    if (PromptConfirmation("Fill an array with random numbers?"))
    {
        for (int i = 0; i < n; i++) array[i] = rand() % 2001 - 1000;
        cout << "Array filled successfully" << endl;
    }
    else if (PromptConfirmation("Fill an array with numbers sorted in reverse order?"))
    {
        for (int i = 0; i < n; i++) array[i] = rand() % 2001 - 1000;
        inversedInsertionSort(array);
        cout << "Array filled successfully" << endl;
    }
    else if (PromptConfirmation("Fill an array with two numbers?"))
    {
        for (int i = 0; i < n; i++) array[i] = rand() % 2 - 0;
        cout << "Array filled successfully" << endl;
    }
    else if (PromptConfirmation("Fill an array with one number?"))
    {
        for (int i = 0; i < n; i++) array[i] = rand() % 1 - 0;
        cout << "Array filled successfully" << endl;
    }
    if (PromptConfirmation("Use bubble sort?"))
    {
        start_time = clock();
        bubbleSort(array);
        end_time = clock();
    }
    else if (PromptConfirmation("Use insertion sort?"))
    {
        start_time = clock();
        insertionSort(array);
        end_time = clock();
    }
    else if (PromptConfirmation("Use selection sort?"))
    {
        start_time = clock();
        selectionSort(array);
        end_time = clock();
    }
    else if (PromptConfirmation("Use merge sort?"))
    {
        start_time = clock();
        mergeSort(array, 0, n - 1);
        end_time = clock();
    }
    else if (PromptConfirmation("Use quick sort?"))
    {
        start_time = clock();
        quickSort(array, 0, n - 1);
        end_time = clock();
    }
    cout << "Array sorted successfully" << endl;
    cout << "Sorting time (ms) = " << end_time - start_time << endl;
    delete[] array;

    cout << "\n\n\tSECOND TASK" << endl;

    if (PromptConfirmation("Check bubble sort for sustainability?"))
        isSustainability(bubbleSortMap);
    if (PromptConfirmation("Check insertion sort for sustainability?"))
        isSustainability(insertionSortMap);
    if (PromptConfirmation("Check selection sort for sustainability?"))
        isSustainability(selectionSortMap);
    if (PromptConfirmation("Check merge sort for sustainability?"))
        isSustainability(mergeSortMap2);
    if (PromptConfirmation("Check quick sort for sustainability?"))
        isSustainability(quickSortMap);

    cout << "\n\n\tTHIRD TASK" << endl;

    if (PromptConfirmation("Use bubble sort?")) fileData(1);
    else if (PromptConfirmation("Use insertion sort?")) fileData(2);
    else if (PromptConfirmation("Use selection sort?")) fileData(3);
    else if (PromptConfirmation("Use merge sort?")) fileData(4);
    else if (PromptConfirmation("Use quick sort?")) fileData(5);
}