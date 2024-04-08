#include <iostream>
#include <mutex>

class Singleton {
  private:
    Singleton() {}
    static Singleton *instance;
    static std::mutex mutex;

  public:
    // 禁用复制构造函数和赋值操作符
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

    static Singleton *getInstance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
};

Singleton *Singleton::instance = nullptr;
std::mutex Singleton::mutex;

int main() {
    // 获取单例的第一个实例
    Singleton *singleton1 = Singleton::getInstance();
    std::cout << "Singleton 1: " << singleton1 << std::endl;

    // 再次获取单例的实例
    Singleton *singleton2 = Singleton::getInstance();
    std::cout << "Singleton 2: " << singleton2 << std::endl;

    // 检查两个实例是否相同
    if (singleton1 == singleton2) {
        std::cout << "两个实例相同，单例模式工作正常。" << std::endl;
    } else {
        std::cout << "两个实例不同，单例模式存在问题。" << std::endl;
    }
    
}
