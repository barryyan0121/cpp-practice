#include <iostream>
#include <vector>

void selection_sort(std::vector<int>& v) {
	for (int i = 0; i < v.size(); ++i) {
		int min = i;
		for (int j = i + 1; j < v.size(); ++j) {
			if (v[j] < v[min]) {
				min = j;
			}
		}
		std::swap(v[i], v[min]);
	}
}

int main() {
	std::cout << "Selection sort" << std::endl;
	std::vector<int> v = {5, 4, 3, 2, 1};
	std::cout << "Before sorting: ";
	for (int i = 0; i < v.size(); ++i) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
	selection_sort(v);
	std::cout << "After sorting: ";
	for (int i = 0; i < v.size(); ++i) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
	return 0;
}