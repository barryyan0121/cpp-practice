#include <iostream>
#include <vector>

void insertion_sort(std::vector<int>& v) {
	for (int i = 1; i < v.size(); ++i) {
		int key = v[i];
		int j = i - 1;
		while (j >= 0 && v[j] > key) {
			v[j + 1] = v[j];
			--j;
		}
		v[j + 1] = key;
	}
}

int main() {
	std::cout << "Insertion sort" << std::endl;
	std::vector<int> v = {5, 4, 3, 2, 1};
	std::cout << "Before sorting: ";
	for (int i = 0; i < v.size(); ++i) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
	insertion_sort(v);
	std::cout << "After sorting: ";
	for (int i = 0; i < v.size(); ++i) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
	return 0;
}