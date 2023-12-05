#include <iostream>
#include <vector>

void comparison_sort(std::vector<int>& v) {
	for (int i = 0; i < v.size(); ++i) {
		for (int j = i + 1; j < v.size(); ++j) {
			if (v[i] > v[j]) {
				std::swap(v[i], v[j]);
			}
		}
	}
}

int main() {
	std::cout << "Comparison sort" << std::endl;
	std::vector<int> v = {5, 4, 3, 2, 1};
	std::cout << "Before sorting: ";
	for (int i = 0; i < v.size(); ++i) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
	comparison_sort(v);
	std::cout << "After sorting: ";
	for (int i = 0; i < v.size(); ++i) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
	return 0;
}
