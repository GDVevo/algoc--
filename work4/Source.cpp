#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <chrono>
#include <algorithm>
using namespace std;

template <typename Func, typename... Args>
auto measure_exec_time(Func&& func, Args&&... args) {
    auto start_time = chrono::high_resolution_clock::now();
    func(forward<Args>(args)...);
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    return duration.count();
}

void genArr(vector<int>& arr, int size, int min, int max) {
    arr.clear();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(min, max);

    for (int i = 0; i < size; i++) {
        arr.push_back(dist(gen));
    }
}

int qS_part(vector<int>& arr, int min, int max) {
	int max_arr = arr[max];
	int i = min - 1;
	for (int j = min; j <= max - 1; j++) {
		if (arr[j] <= max_arr) {
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[max]);
	return i + 1;
}

void quickSort(vector<int>& arr, int min, int max) {
    if (min < max) {
        int part = qS_part(arr, min, max);
        quickSort(arr, min, part - 1);
        quickSort(arr, part + 1, max);
    }
}

void threadQS(vector<int>& arr, int num_threads) {
    int size = arr.size();
    int chunk = size / num_threads;
    vector<thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        int start = i * chunk;
        int end = (i == num_threads - 1) ? size - 1 : start + chunk - 1;
        threads.emplace_back(quickSort, ref(arr), start, end);
    }
    for (auto& thread:threads) {
        thread.join();
    }
    int step = chunk;
    while (step < size) {
        for (int i = 0; i < size - step; i += 2 * step) {
            int left = i;
            int mid = i + step;
            int right = min(i + 2 * step, size);
            inplace_merge(arr.begin() + left, arr.begin() + mid, arr.begin() + right);
        }
        step *= 2;
    }
}

int main() {
    vector<int> arr;
    for (int i = 2; i < 8; i++) { 
        cout << "array length: " << pow(10, i) << endl;
        genArr(arr, pow(10, i), 1, pow(10, i));
        float time = measure_exec_time(threadQS, arr, 1);
        float basetime = time;
        cout << "thread count: 1; time taken: " << time << " MICROseconds" << endl;

        genArr(arr, pow(10, i), 1, pow(10, i));
        time = measure_exec_time(threadQS, arr, 2);
        cout << "thread count: 2; time taken: " << time << " MICROseconds; speedup: " << basetime / time << endl;

        genArr(arr, pow(10, i), 1, pow(10, i));
        time = measure_exec_time(threadQS, arr, 4);
        cout << "thread count: 4; time taken: " << time << " MICROseconds; speedup: " << basetime / time << endl;

        genArr(arr, pow(10, i), 1, pow(10, i));
        time = measure_exec_time(threadQS, arr, 8);
        cout << "thread count: 8; time taken: " << time << " MICROseconds; speedup: " << basetime / time << endl << endl;
    }
    return 0;
}
