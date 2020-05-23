#include "Student.h"

class Person;
class Student;

// kopijavimo priskyrimo operatorius
//Student& Student::operator =(const Student& origin) {
//    name = origin.name;
//    surname = origin.surname;
//    nd = origin.nd;
//    exam = origin.exam;
//    res = origin.res;
//    return *this;
//}

// get'eriai:
const string &Student::getName() const {
    return name;
}
const string &Student::getSurname() const {
    return surname;
}
const vector<double> &Student::getNd() const {
    return nd;
}
int Student::getExam() const {
    return exam;
}
double Student::getRes() const {
    return res;
}

// set'eriai:
void Student::setName(const string &name_) {
    Student::name = name_;
}
void Student::setSurname(const string &surname_) {
    Student::surname = surname_;
}
void Student::setNd(const vector<double> &nd_) {
    Student::nd = nd_;
}
void Student::setExam(int exam_) {
    Student::exam = exam_;
}
void Student::setRes(double res_) {
    Student::res = res_;
}

// konstruktoriai:

Student::Student(const string &name, const string &surname, vector<double> nd, int exam, double res) : Person(
        name, surname), nd(std::move(nd)), exam(exam), res(res) {}
Student::Student(const string &name, const string &surname, double res) : Person(name, surname), res(res) {}
Student::Student() {}
Student::Student(const string &name, const string &surname, vector<double> nd, int exam) : Person(name, surname), nd(std::move(nd)), exam(exam) {}

Person::Person(string name, string surname) : name(std::move(name)), surname(std::move(surname)) {}
Person::Person() {}
