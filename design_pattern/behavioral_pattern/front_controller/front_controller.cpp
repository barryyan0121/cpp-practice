#include <iostream>
#include <memory>
#include <string>


class HomeView {
public:
    void show() {
        std::cout << "Displaying Home Page" << std::endl;
    }
};

class StudentView {
public:
    void show() {
        std::cout << "Displaying Student Page" << std::endl;
    }
};

class Dispatcher {
public:
    Dispatcher() {
        homeView = std::make_shared<HomeView>();
        studentView = std::make_shared<StudentView>();
    }
    void dispatch(const std::string& request) {
        if (request == "STUDENT") {
            studentView->show();
        } else {
            homeView->show();
        }
    }
private:
    std::shared_ptr<HomeView> homeView;
    std::shared_ptr<StudentView> studentView;
};

class FrontController {
public:
    FrontController() {
        dispatcher = std::make_shared<Dispatcher>();
    }
    void dispatchRequest(const std::string& request) {
        trackRequest(request);
        if (isAuthenticUser()) {
            dispatcher->dispatch(request);
        }
    }
private:
    void trackRequest(const std::string& request) {
        std::cout << "Page requested: " << request << std::endl;
    }
    bool isAuthenticUser() {
        std::cout << "User is authenticated successfully." << std::endl;
        return true;
    }
    std::shared_ptr<Dispatcher> dispatcher;
};

int main() {
    auto frontController = std::make_shared<FrontController>();
    frontController->dispatchRequest("HOME");
    frontController->dispatchRequest("STUDENT");
}