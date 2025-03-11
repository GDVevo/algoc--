#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
#include <cmath>
using namespace std;

template <typename Func, typename... Args>
auto measure_exec_time(Func&& func, Args&&... args) {
	auto start_time = chrono::high_resolution_clock::now();
	func(std::forward<Args>(args)...);
	auto end_time = chrono::high_resolution_clock::now();  
	auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
	return duration.count();
}

void genArr(vector<int>& arr, int size, int min, int max) {
	arr.clear();
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(min, max);

	for (int i = 0; i < size; i++) {
		arr.push_back(dist(gen));
	}
}

void radixSort(vector<int>& arr) {
	int maxVal = *std::max_element(arr.begin(), arr.end());
	int exp = 1;
	while (maxVal / exp > 0) {
		std::vector<int> output(arr.size());
		std::vector<int> count(10, 0);

		for (int i = 0; i < arr.size(); i++) {
			int digit = (arr[i] / exp) % 10;
			count[digit]++;
		}

		for (int i = 1; i < 10; i++) {
			count[i] += count[i - 1];
		}

		for (int i = arr.size() - 1; i >= 0; i--) {
			int digit = (arr[i] / exp) % 10;
			output[count[digit] - 1] = arr[i];
			count[digit]--;
		}

		arr = output;
		exp *= 10;
	}
}

void gnomeSort(vector<int>& arr) {
	int n = arr.size();
	int index = 0;

	while (index < n) {
		if (index == 0) {
			index++;
		}
		if (arr[index] >= arr[index - 1]) {
			index++;
		}
		else {
			swap(arr[index], arr[index - 1]);
			index--;
		}
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

bool checkArrs(vector<int>& arr1, vector<int>& arr2, vector<int>& arr3) { // это пришлось писать потому что юнит тесты не воспринимают and
	size_t max_size = max(arr1.size(), arr2.size());
	max_size = max(max_size, arr3.size()); // костыль?? но даже если да то не думаю что много памяти сжирает :D
	bool flag = true;
	for (int i = 0; i < max_size; i++) {
		if (arr1[i] == arr2[i]) {
			if (arr1[i] == arr3[i]) {
				if (arr2[i] == arr3[i]) {
					continue;
				}
				else {
					flag = false;
					break;
				}
			}
			else {
				flag = false;
				break;
			}
		}
		else {
			flag = false;
			break;
		}
	}
	return flag;
}

int main() {
	vector<int> arr1;
	genArr(arr1, 10, 1, 10); // пример ввод/вывод данных
	cout << "New: ";
	for (int i = 0; i < arr1.size(); i++) {
		cout << arr1[i] << ' ';
	}
	gnomeSort(arr1);
	cout << endl << "Sorted: ";
	for (int i = 0; i < arr1.size(); i++) {
		cout << arr1[i] << ' ';
	}
	genArr(arr1, 10, 5123, 9999);
	cout << endl << "New: ";
	for (int i = 0; i < arr1.size(); i++) {
		cout << arr1[i] << ' ';
	}
	radixSort(arr1);
	cout << endl << "Sorted: ";
	for (int i = 0; i < arr1.size(); i++) {
		cout << arr1[i] << ' ';
	}
	genArr(arr1, 10, 1, 256);
	cout << endl << "New: ";
	for (int i = 0; i < arr1.size(); i++) {
		cout << arr1[i] << ' ';
	}
	quickSort(arr1, 0, arr1.size()-1);
	cout << endl << "Sorted: ";
	for (int i = 0; i < arr1.size(); i++) {
		cout << arr1[i] << ' ';
	}
	genArr(arr1, 10, 0, 0);
	cout << endl << "New: ";
	for (int i = 0; i < arr1.size(); i++) {
		cout << arr1[i] << ' ';
	}
	radixSort(arr1);
	cout << endl << "Sorted: ";
	for (int i = 0; i < arr1.size(); i++) {
		cout << arr1[i] << ' ';
	}
	for (int i = 1; i < 8; i++) { // this is where the fun begins, проверка на время
		cout << endl << "current array len: " << pow(10, i) << endl;
		genArr(arr1, pow(10, i), 1, pow(10, i));
		cout << "gnome exec time: " << measure_exec_time(gnomeSort, arr1) << " microseconds" << endl;
		genArr(arr1, pow(10, i), 1, pow(10, i));
		cout << "radix exec time: " << measure_exec_time(radixSort, arr1) << " microseconds" << endl;
		genArr(arr1, pow(10, i), 1, pow(10, i));
		cout << "qS exec time: " << measure_exec_time(quickSort, arr1, 0, arr1.size() - 1) << " microseconds" << endl;
	}
}