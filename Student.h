#ifndef OP_2_1_1_STUDENTAS_H
#define OP_2_1_1_STUDENTAS_H

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <random>
#include <chrono>
#include <list>
#include <deque>
#include <functional>
#include <utility>
#include "Vector.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;
using std::sort;
using std::setprecision;
using std::setw;
using std::left;
using std::ifstream;
using std::list;
using std::deque;
using std::istream;

/// Abstrakti žmogaus klasė
class Person {
protected:
    string name;
    string surname;
public:
    virtual const string &getName() const = 0;
    virtual const string &getSurname() const = 0;
    Person(string name, string surname);
    Person();
};

/// Studento klasė
class Student : public Person {
private:
    vector<double> nd;
    int exam;
    double res;
public:
    const string &getName() const override;
    const string &getSurname() const override;
    const vector<double> &getNd() const;
    int getExam() const;
    double getRes() const; // get'eriai


    void setName(const string &name_);
    void setSurname(const string &surname_);

    Student(const string &name, const string &surname, vector<double> nd, int exam, double res);
    Student(const string &name, const string &surname, double res);
    Student(const string &name, const string &surname, vector<double> nd, int exam);

    Student();

    void setNd(const vector<double> &nd_);
    void setExam(int exam_);
    void setRes(double res_); // set'eriai

    void sortNd() {
        sort(nd.begin(), nd.end());
    }

    // Student& operator =(const Student& origin);

    friend std::istream& operator >>(std::istream& in, Student& s) {
        in >> s.name >> s.surname;
        in >> s.exam;
        s.nd.clear();
        for (int random_int; in >> random_int;) {
            s.nd.push_back(random_int);
        }
        s.nd.shrink_to_fit();
        return in;
    }
    friend std::ostream& operator <<(std::ostream& out, Student& s) {
        out << left << setw(17) << s.name << left << std::setw(19) << s.surname
            << left << setw(17);
        for (double j : s.nd) {
            out << left << setw(10) << j;
        }
        out << s.exam << endl;
        return out;
    }
    bool operator<(const Student& other) const {
        return res < other.res;
    }
    bool operator<(const double x) const {
        return res < x;
    }
    bool operator>(const Student& other) const {
        return res > other.res;
    }
    bool operator>(const double x) const {
        return res > x;
    }
    bool operator<=(const Student& other) const {
        return res <= other.res;
    }
    bool operator<=(const double x) const {
        return res <= x;
    }
    bool operator>=(const Student& other) const {
        return res >= other.res;
    }
    bool operator>=(const double x) const {
        return res >= x;
    }
    bool operator==(const Student& other) const {
        return res == other.res;
    }
    bool operator==(const double x) const {
        return res == x;
    }
    bool operator!=(const Student& other) const {
        return res != other.res;
    }
    bool operator!=(const double x) const {
        return res != x;
    }
    /*
    lyginimo operatoriai, skirti palyginti dviems objektams (studentų rezultatams) arba
    objektui (studento rezultatui) ir realiajam skaičiui.
    */
};

#endif