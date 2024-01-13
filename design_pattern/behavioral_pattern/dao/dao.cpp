#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Student {
public:
	Student() = default;
	Student(const std::string& name, int rollNo) : name(name), rollNo(rollNo) {}
	const std::string& getName() const {
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

class StudentDao {
public:
	virtual std::vector<std::shared_ptr<Student>> getAllStudents() = 0;
	virtual void updateStudent(const Student& student) = 0;
	virtual void deleteStudent(const Student& student) = 0;
	virtual void addStudent(const Student& student) = 0;
	virtual ~StudentDao() = default;
};

class StudentDaoImpl : public StudentDao {
public:
	StudentDaoImpl() {
		studentList.push_back(std::make_shared<Student>("Robert", 0));
		studentList.push_back(std::make_shared<Student>("John", 1));
	}
	std::vector<std::shared_ptr<Student>> getAllStudents() override {
		return studentList;
	}
	void updateStudent(const Student& student) override {
		auto it = findStudent(student.getRollNo());
		if (it != studentList.end()) {
			(*it)->setName(student.getName());
			std::cout << "Student: Roll No " << student.getRollNo() << ", updated in the database" << std::endl;
		}
	}

	void deleteStudent(const Student& student) override {
		auto it = findStudent(student.getRollNo());
		if (it != studentList.end()) {
			studentList.erase(it);
			std::cout << "Student: Roll No " << student.getRollNo() << ", deleted from database" << std::endl;
		}
	}
	void addStudent(const Student& student) override {
		studentList.push_back(std::make_shared<Student>(student));
		std::cout << "Student: Roll No " << student.getRollNo() << ", added to database" << std::endl;
	}

private:
	std::vector<std::shared_ptr<Student>> studentList;
	std::vector<std::shared_ptr<Student>>::iterator findStudent(int rollNo) {
		return std::find_if(studentList.begin(), studentList.end(), [rollNo](const std::shared_ptr<Student>& student) {
			return student->getRollNo() == rollNo;
		});
	}
};

int main() {
	std::unique_ptr<StudentDao> studentDao = std::make_unique<StudentDaoImpl>();
	for (const auto& student : studentDao->getAllStudents()) {
		std::cout << "Student: [RollNo: " << student->getRollNo() << ", Name: " << student->getName() << "]"
		          << std::endl;
	}
	std::shared_ptr<Student> student = studentDao->getAllStudents()[0];
	student->setName("Michael");
	studentDao->updateStudent(*student);
	student = studentDao->getAllStudents()[0];
	std::cout << "Student: [RollNo: " << student->getRollNo() << ", Name: " << student->getName() << "]" << std::endl;
	studentDao->deleteStudent(*student);
	student = studentDao->getAllStudents()[0];
	std::cout << "Student: [RollNo: " << student->getRollNo() << ", Name: " << student->getName() << "]" << std::endl;
	student = std::make_shared<Student>("Robert", 0);
	studentDao->addStudent(*student);
	student = studentDao->getAllStudents()[1];
	std::cout << "Student: [RollNo: " << student->getRollNo() << ", Name: " << student->getName() << "]" << std::endl;
	return 0;
}