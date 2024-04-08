#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Filter {
public:
	virtual void execute(const std::string& request) = 0;
	virtual ~Filter() = default;
};

class AuthenticationFilter : public Filter {
public:
	void execute(const std::string& request) override {
		std::cout << "Authenticating request: " << request << std::endl;
	}
};

class DebugFilter : public Filter {
public:
	void execute(const std::string& request) override {
		std::cout << "request log: " << request << std::endl;
	}
};

class Target {
public:
	void execute(const std::string& request) {
		std::cout << "Executing request: " << request << std::endl;
	}
};

class FilterChain {
public:
	void addFilter(std::shared_ptr<Filter> filter) {
		filters.push_back(filter);
	}
	void execute(const std::string& request) {
		for (auto& filter : filters) {
			filter->execute(request);
		}
		target->execute(request);
	}
	void setTarget(std::shared_ptr<Target> target) {
		this->target = target;
	}

private:
	std::vector<std::shared_ptr<Filter>> filters;
	std::shared_ptr<Target> target;
};

class FilterManager {
public:
	FilterManager(std::shared_ptr<Target> target) {
		filterChain = std::make_shared<FilterChain>();
		filterChain->setTarget(target);
	}
	void setFilter(std::shared_ptr<Filter> filter) {
		filterChain->addFilter(filter);
	}
	void filterRequest(const std::string& request) {
		filterChain->execute(request);
	}

private:
	std::shared_ptr<FilterChain> filterChain;
};

class Client {
public:
	void setFilterManager(std::shared_ptr<FilterManager> filterManager) {
		this->filterManager = filterManager;
	}

	void sendRequest(const std::string& request) {
		filterManager->filterRequest(request);
	}

	std::shared_ptr<FilterManager> filterManager;
};

int main() {
	auto filterManager = std::make_shared<FilterManager>(std::make_shared<Target>());
	filterManager->setFilter(std::make_shared<AuthenticationFilter>());
	filterManager->setFilter(std::make_shared<DebugFilter>());

	auto client = std::make_shared<Client>();
	client->setFilterManager(filterManager);
	client->sendRequest("HOME");
	client->sendRequest("AWAY");
}
