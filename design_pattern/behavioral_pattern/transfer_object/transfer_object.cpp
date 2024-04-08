#include <iostream>
#include <memory>
#include <string>
#include <vector>

class StudentVO {
public:
	StudentVO() = default;
	StudentVO(const std::string& name, int rollNo) : name(name), rollNo(rollNo) {}
	std::string getName() const {
		return name;
	}
	void setName(const std::string& name) {
		this->name = name;
	}
	int getRollNo() const {
		return rollNo;
	}
	void setRollNo(int rollNo) {
		this->rollNo = rollNo;
	}

private:
	std::string name;
	int rollNo;
};

class StudentBO {
public:
	std::vector<std::shared_ptr<StudentVO>> getAllStudents() {
		std::vector<std::shared_ptr<StudentVO>> students;
		students.push_back(std::make_shared<StudentVO>("Robert", 0));
		students.push_back(std::make_shared<StudentVO>("John", 1));
		return students;
	}
	std::shared_ptr<StudentVO> getStudent(int rollNo) {
		return std::make_shared<StudentVO>("Robert", 0);
	}
	void updateStudent(std::shared_ptr<StudentVO> student) {
		std::cout << "Student: Roll No " << student->getRollNo() << ", updated in the database" << std::endl;
	}
	void deleteStudent(std::shared_ptr<StudentVO> student) {
		std::cout << "Student: Roll No " << student->getRollNo() << ", deleted from database" << std::endl;
	}
};

int main() {
	auto studentBusinessObject = std::make_unique<StudentBO>();

	// print all students
	for (auto& student : studentBusinessObject->getAllStudents()) {
		std::cout << "Student: [RollNo : " << student->getRollNo() << ", Name : " << student->getName() << " ]"
		          << std::endl;
	}

	// update student
	auto student = studentBusinessObject->getAllStudents()[0];
	student->setName("Michael");
	studentBusinessObject->updateStudent(student);

	// get the student
	student = studentBusinessObject->getStudent(0);
	std::cout << "Student: [RollNo : " << student->getRollNo() << ", Name : " << student->getName() << " ]"
	          << std::endl;

	return 0;
}
