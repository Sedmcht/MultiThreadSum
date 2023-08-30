#include <iostream>
#include <thread>
#include <vector>
#include <functional>
#include <mutex>

using namespace std;

void summ(int* arr, int start, int end, int& result, mutex& mtx)
{
    int sum = 0;
    for (int i = start; i < end; i++)
        sum += arr[i];
    mtx.lock();
        result += sum;
    mtx.unlock();
}

void multiThreadSum(int size, int parts)
{
    if (parts < size && size && parts)
    {
        int* arr = new int[size];

        for (int i = 0; i < size; i++)
            arr[i] = rand() % 100;
        
        int segment = size / parts;
        int start = 0;
        int end = segment;

        vector<thread> threads;
        int result = 0;
        mutex mtx;

        for (int i = 0; i < parts - 1; i++)
        {
            threads.push_back(thread(summ,arr,start,end,ref(result),ref(mtx)));
            start = end;
            end += segment;
        }
            threads.push_back(thread(summ, arr, end - segment, size, ref(result), ref(mtx)));


            for (auto& th : threads)
                if (th.joinable())
                    th.join();


            delete[] arr;

            cout << result;
    }
    
}



int main()
{
    multiThreadSum(20,4);
}
