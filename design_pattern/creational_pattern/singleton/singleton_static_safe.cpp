#include <iostream>

class Singleton {
private:
	Singleton() {}
	~Singleton() {}
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
	Singleton(Singleton&&);

public:
	static Singleton& GetInstance() {
		static Singleton instance;
		return instance;
	}
};

int main() {
	// 获取单例的第一个实例
	Singleton& singleton1 = Singleton::GetInstance();
	std::cout << "Singleton 1: " << &singleton1 << std::endl;

	// 再次获取单例的实例
	Singleton& singleton2 = Singleton::GetInstance();
	std::cout << "Singleton 2: " << &singleton2 << std::endl;

	// 检查两个实例是否相同
	if (&singleton1 == &singleton2) {
		std::cout << "线程安全的单例模式：两个实例相同，单例模式工作正常。" << std::endl;
	} else {
		std::cout << "线程安全的单例模式：两个实例不同，单例模式存在问题。" << std::endl;
	}
}