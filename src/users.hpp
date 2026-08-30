#ifndef USERS_HPP
#define USERS_HPP

#include <string>

using namespace std;

class User {
private:
    inline static int id_counter = 1;

    string name;
    int id;
    int max_books;
    int max_days;

protected:
    User(const string& _name, int _max_books, int _max_days):
        name(_name),
        id(id_counter++), 
        max_books(_max_books),
        max_days(_max_days) {}

public:
    User() = default;

    string get_id() const {
        return to_string(id);
    }

    string get_name() const {
        return name;
    }

};

ostream& operator << (ostream& out, const User& user) {
    out << user.get_name();
    return out;
}

class Student: public User {
public:
    Student(const string& name): User(name, 3, 14) {}
};

class Faculty: public User {
public:
    Faculty(const string& name): User(name, 10, 30) {}

};

class Guest: public User {
public:
    Guest(const string& name): User(name, 1, 7) {}

};

#endif
