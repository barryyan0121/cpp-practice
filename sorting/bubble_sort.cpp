#include <iostream>
#include <vector>

void bubble_sort(std::vector<int>& v) {
	for (int i = 0; i < v.size(); ++i) {
		for (int j = 0; j < v.size() - i - 1; ++j) {
			if (v[j] > v[j + 1]) {
				std::swap(v[j], v[j + 1]);
			}
		}
	}
}

int main() {
	std::cout << "Bubble sort" << std::endl;
	std::vector<int> v = {5, 4, 3, 2, 1};
	std::cout << "Before sorting: ";
	for (int i = 0; i < v.size(); ++i) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
	bubble_sort(v);
	std::cout << "After sorting: ";
	for (int i = 0; i < v.size(); ++i) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
	return 0;
}
