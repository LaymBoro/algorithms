#include<iostream>
#include<random>
#include<chrono>

uint32_t min = 0;
uint32_t max = 1024;
const size_t arrSize = 3;

int randomize() 
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int32_t> uni(min, max);

    return uni(rng);
}

void bubleSort(int* arr, size_t& bubleCounter, size_t arrSize)
{
    int temp = 0;
    for (size_t i = 0; i < arrSize; i++) {
        for (size_t j = i + 1; j < arrSize ; j++) {
            if (arr[i] > arr[j]) {
                temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
                bubleCounter++;
            }
        }
    }


}

void exchange(int i, int j, int* x)
{
    int tmp;
    tmp = x[i];
    x[i] = x[j];
    x[j] = tmp;
}

void sort_(int left, int right, int* arr, size_t& count)
{
    int i, j, support_element, temp;
    i = left;
    j = right;
    support_element = arr[(i + j + 1) / 2];
    do {
        while (arr[i] < support_element) i++;
        while (arr[j] > support_element) j--;
        if (i <= j) {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            count++;
            i++;
            j--;
        }
    } while (i <= j);
    if (left < j)
        sort_(left, j, arr, count);
    if (i < right)
        sort_(i, right, arr, count);
}

void Hoare_Sort(int size, int* array, size_t& count)
{
    sort_(0, size - 1, array, count);
}


int main()
{
    const size_t arrSize = 1000;
    int arr[arrSize] ={};
    int forBuble[arrSize] = {};
    int forHoar[arrSize] = {};
    int temp = 0;
    size_t bubleCounter = 0;
    size_t hoarCounter = 0;

    for(size_t i = 0; i < arrSize; i++)
    {
        arr[i] = randomize();
        forBuble[i] = arr[i];
        forHoar[i] = arr[i];
    }

    auto bubbleStart = std::chrono::steady_clock::now();
    bubleSort(forBuble, bubleCounter, arrSize);
    auto bubbleEnd = std::chrono::steady_clock::now();
    auto bubbleTime = std::chrono::duration_cast<std::chrono::nanoseconds>(bubbleEnd - bubbleStart);

    auto hoarStart = std::chrono::steady_clock::now();
    Hoare_Sort(arrSize, forHoar, hoarCounter);
    auto hoarEnd = std::chrono::steady_clock::now();
    auto hoarTime = std::chrono::duration_cast<std::chrono::nanoseconds>(hoarEnd - hoarStart);
    int timeProfit = bubbleTime.count()/hoarTime.count();
    int iterationsProfit = bubleCounter/hoarCounter; 

    std::cout << "\nBubble sort: " << bubbleTime.count() << " nanoseconds " << bubleCounter << " iterations \n";
    std::cout << "Hoare sort: " << hoarTime.count() << " nanoseconds " << hoarCounter << " iterations \n";
    std::cout << "Hoare coefficient profit: " << timeProfit << " time " << iterationsProfit << " iterations \n";

    return 0;
}