#include <iostream>
#include <memory>
#include <string>

class Student {
public:
	std::string getName() const {
		return name;
	}
	void setName(const std::string& name) {
		this->name = name;
	}
	std::string getRollNo() const {
		return rollNo;
	}
	void setRollNo(const std::string& rollNo) {
		this->rollNo = rollNo;
	}

private:
	std::string name;
	std::string rollNo;
};

class StudentView {
public:
	void printStudentDetails(const std::string& studentName, const std::string& studentRollNo) const {
		std::cout << "Printing student details:" << std::endl;
		std::cout << "Name: " << studentName << std::endl;
		std::cout << "Roll No: " << studentRollNo << std::endl;
		std::cout << std::endl;
	}
};

class StudentController {
public:
	StudentController(std::unique_ptr<Student> model, std::unique_ptr<StudentView> view)
	    : model(std::move(model))
	    , view(std::move(view)) {}

	void setStudentName(const std::string& name) {
		model->setName(name);
	}
	std::string getStudentName() const {
		return model->getName();
	}
	void setStudentRollNo(const std::string& rollNo) {
		model->setRollNo(rollNo);
	}
	std::string getStudentRollNo() const {
		return model->getRollNo();
	}
	void updateView() {
		view->printStudentDetails(model->getName(), model->getRollNo());
	}

private:
	std::unique_ptr<Student> model;
	std::unique_ptr<StudentView> view;
};

int main() {
	// fetch student record based on his roll no from the database
	std::unique_ptr<Student> model = std::make_unique<Student>();
	model->setName("Robert");
	model->setRollNo("5");

	// create a view : to write student details on console
	std::unique_ptr<StudentView> view = std::make_unique<StudentView>();

	std::unique_ptr<StudentController> controller =
	    std::make_unique<StudentController>(std::move(model), std::move(view));

	controller->updateView();

	// update model data
	controller->setStudentName("John");
	controller->updateView();
}