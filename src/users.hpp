#ifndef USERS_HPP
#define USERS_HPP

#include <string>

using namespace std;

class User {
private:
    inline static int id_counter = 1;

    string name;
    string type;
    string id;
    int max_books;
    int max_days;

protected:
    User(const string& _name, int _max_books, int _max_days, const string& _type):
        name(_name),
        id(id_counter++), 
        max_books(_max_books),
        max_days(_max_days),
        type(_type) {}

public:
    User() = default;

    const string& get_id() const {
        return id;
    }

    const string& get_name() const {
        return name;
    }

    const string& get_type() const {
        return type;
    }

    int get_max_days() const {
        return max_days;
    }

    int get_max_books() const {
        return max_books;
    }

    friend ostream& operator << (ostream& out, const User& user);
};

ostream& operator << (ostream& out, const User& user) {
    out << user.name << " (" << user.type << ")";
    return out;
}

class Student: public User {
public:
    Student(const string& name): User(name, 3, 14, "student") {}
};

class Faculty: public User {
public:
    Faculty(const string& name): User(name, 10, 30, "faculty") {}
};

class Guest: public User {
public:
    Guest(const string& name): User(name, 1, 7, "guest") {}
};

#endif
