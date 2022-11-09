#include <iostream>
#include <chrono>
#include <fstream>

using namespace std;

int compare(const void * x1, const void * x2){
    return (*(int*)x1 - *(int*)x2);
}


//ф-ция "шейкер"-сортировки
void ShakerSort(int *arr, int size)
{
    int left = 1;
    int right = size - 1;
    int temp;
    int flag = 1;
    int bound;
    while ((left < right) && flag > 0)
    {
        flag = 0;
        for (int i = right; i > left; i--)
            if (arr[i - 1] > arr[i]){
                temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
                flag = 1;
                bound = i;
            }
        left = bound;

        for (int i = left; i < right; i++)
            if (arr[i] > arr[i + 1]){
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                flag = 1;
                bound = i;
            }
        right = bound;
    }
}

void BubbleSort(int *arr, int size)
{
    int temp, t = 0;
    int right = size - 1;
    while(t >= 0) {
        t = -1;
        for (int j = 0; j < right; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                t = j;
            }
        }
        right = t;
    }
}

int main()
{
    int size = 0;
    setlocale(LC_ALL, "rus");


    string alg,path;

    cout << "Введите название алгоритма(QSort, BubbleSort, ShakerSort):\n";
    cin >> alg;

    while(not(alg == "QSort" or alg == "BubbleSort" or alg == "ShakerSort")){
        cout << "Введите название алгоритма(QSort, BubbleSort, ShakerSort):\n";
        cin >> alg;
    }


    cout << "Введите путь файла:\n";
    cin >> path;


    ifstream fin("../"+path);


    if (!fin.is_open()) // если файл не открыт
        cout << "Файл не может быть открыт!\n";
    string a;
    while (fin >> a)
    {
        size++;
    }
    fin.close();
    fin.open("../"+path);

    //cin >> size;

    int *array = new int[size];


    for (int i = 0; i < size; i++)
    {
        fin >> array[i];
    }

    cout << "Массив до сортировки: \n";
    for (int i = 0; i < 16; i++)
    {
        cout << array[i] << " ";
    }
    cout << "... \n";


    if(alg == "QSort"){
        auto begin = std::chrono::steady_clock::now();
        qsort(array, size, sizeof(int), compare);
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << "Время выполнения: " << duration.count() << " мкрсек\n";
    }
    else if(alg == "ShakerSort"){
        auto begin = std::chrono::steady_clock::now();
        ShakerSort(array, size);
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << "Время выполнения: " << duration.count() << " мкрсек\n";
    }
    else if(alg == "BubbleSort"){
        auto begin = std::chrono::steady_clock::now();
        BubbleSort(array, size);
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << "Время выполнения: " << duration.count() << " мкрсек\n";
    }

    else{
        return 0;
    }




    cout << "\nМассив после сортировки:\n";
    for (int i = 0; i < 16; i++)
    {
        cout << array[i] << " ";
    }
    cout << "... \n";

    ofstream fout;
    string save_path;
    cout << "Введите названия файла для сохранения массива: \n";
    cin >> save_path;
    fout.open("../"+save_path);

    for (int i = 0; i < size; i++){
        fout << array[i] << " ";
    }
    cout << "Массив успешно сохранён в файле " << save_path;

    return 0;
}