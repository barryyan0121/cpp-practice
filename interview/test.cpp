#include <iostream>
#include <memory>
#include <queue>

class Test {
public:
	Test(int value) : value_(value) {}
	void Display() const {
		std::cout << "Value: " << value_ << std::endl;
	}

private:
	int value_;
};

int main() {
	std::queue<std::unique_ptr<Test>> myQueue;

	for (int i = 0; i < 5; ++i) {
		// 在循环中创建 unique_ptr
		std::unique_ptr<Test> ptr = std::make_unique<Test>(i);
		// 将 unique_ptr 移动到队列中
		myQueue.push(std::move(ptr));
	}

	std::cout << "haha" << std::endl;

	// 循环结束后，从队列中取出并使用 unique_ptr
	while (!myQueue.empty()) {
		myQueue.front()->Display(); // 调用对象的方法
		myQueue.pop();  // 从队列中移除
	}

	return 0;
}
