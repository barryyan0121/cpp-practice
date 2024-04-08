#include <iostream>

class AbstractLogger {
public:
	static const int INFO = 1;
	static const int DEBUG = 2;
	static const int ERROR = 3;

	AbstractLogger(int level) : level(level), nextLogger(nullptr) {}
	void setNextLogger(AbstractLogger* nextLogger) {
		this->nextLogger = nextLogger;
	}
	void logMessage(int level, const std::string& message) {
		if (this->level <= level) {
			write(message);
		}
		if (nextLogger != nullptr) {
			nextLogger->logMessage(level, message);
		}
	}
	virtual ~AbstractLogger() = default;

protected:
	virtual void write(const std::string& message) = 0;
	int level;
	AbstractLogger* nextLogger;
};

class ConsoleLogger : public AbstractLogger {
public:
	ConsoleLogger(int level) : AbstractLogger(level) {}

protected:
	void write(const std::string& message) override {
		std::cout << "Standard Console::Logger: " << message << std::endl;
	}
};

class ErrorLogger : public AbstractLogger {
public:
	ErrorLogger(int level) : AbstractLogger(level) {}

protected:
	void write(const std::string& message) override {
		std::cout << "Error Console::Logger: " << message << std::endl;
	}
};

class FileLogger : public AbstractLogger {
public:
	FileLogger(int level) : AbstractLogger(level) {}

protected:
	void write(const std::string& message) override {
		std::cout << "File::Logger: " << message << std::endl;
	}
};

class ChainPatternDemo {
public:
	static AbstractLogger* getChainOfLoggers() {
		AbstractLogger* errorLogger = new ErrorLogger(AbstractLogger::ERROR);
		AbstractLogger* fileLogger = new FileLogger(AbstractLogger::DEBUG);
		AbstractLogger* consoleLogger = new ConsoleLogger(AbstractLogger::INFO);

		errorLogger->setNextLogger(fileLogger);
		fileLogger->setNextLogger(consoleLogger);

		return errorLogger;
	}
};

int main() {
	AbstractLogger* loggerChain = ChainPatternDemo::getChainOfLoggers();

	loggerChain->logMessage(AbstractLogger::INFO, "This is an information.");
	loggerChain->logMessage(AbstractLogger::DEBUG, "This is an debug level information.");
	loggerChain->logMessage(AbstractLogger::ERROR, "This is an error information.");

	return 0;
}
