#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

template <class T>
void bubbleSort(std::vector<T>& v) {
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v.size() - i - 1; j++) {
			if (v[j] > v[j + 1]) {
				std::swap(v[j], v[j + 1]);
			}
		}
	}
}

template <class T>
int partition(std::vector<T>& v, int left, int right) {
	int i = left;
	
	for (int j = left + 1; j <= right; j++) {
		if (v[j] < v[left]) {
			i++;
			std::swap(v[i], v[j]);
		}
	}
	
	std::swap(v[i], v[left]);
	return i;
}

template <class T>
void quickSort(std::vector<T>& v, int left, int right) {
	if (right > left) {
		int r = partition(v, left, right);
		quickSort(v, left, r - 1);
		quickSort(v, r + 1, right);
	}
}

template <class T>
void quickSort(std::vector<T>& v) {
	quickSort(v, 0, v.size() - 1);
}

template <class T>
void insertionSort(std::vector<T>& v) {
	for (int j = 1; j < v.size(); j++) {
		T key = v[j];
		int i = j - 1;
		
		while (v[i] > key && i >= 0) {
			v[i + 1] = v[i];
			i--;
		}
		
		v[i + 1] = key;
	}
}

int main() {
	std::srand(std::time(nullptr));
	std::vector<int> values;
	
	for (int i = 0; i < 1000000; i++) {
		values.push_back(std::rand());
	}
	
	auto start = std::chrono::system_clock::now();
	quickSort(values);
	auto time = std::chrono::system_clock::now() - start;
	
	std::cout << std::duration_cast<
	std::cout << std::endl;
}