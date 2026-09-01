#ifndef RECORD_HPP
#define RECORD_HPP

#include "book.hpp"
#include "users.hpp"

class Record {
private:
    int first_day;
    int last_day;
    string isbn;
    string user_id;

public:
    Record(Book book, User user, int day_counter) {
        first_day = day_counter;
        last_day = first_day + user.get_max_days();
        isbn = book.isbn;
        user_id = user.get_id();
    }

    bool overdued(int day_counter) const {
        if (last_day >= day_counter) {
            return false;
        }
        return true;
    }

    pair<string, string> get_contact() const {
        return {isbn, user_id};
    }
};


class Recorder {
private:
    int day_counter;
    list<Record> history;
    list<Record> inactive;
    map<string, bool> avaliable_books;
    map<string, int> user_info;
    
public:
    Recorder() {
        day_counter = 0;
    }

    void new_day() {
        day_counter++;
    }

    int new_record(Book book, User user) {
        if (!avaliable_books[book.isbn]) {
            return 0;
        }

        if (user_info[user.get_id()] >= user.get_max_books()) {
            return 1;
        }

        history.push_front(Record(book, user, day_counter));
        return 2;
    }

    list<list<Record>::const_iterator> check_overdue() const {
        list<list<Record>::const_iterator> overdues;
        for (auto i = history.cbegin(); i != history.cend(); ++i) {
            if (i->overdued(day_counter)) {
                overdues.push_front(i);
            }
        }
        return overdues;
    }

    bool close_record(pair<string, string> contact) {
        for (auto i = history.begin(); i != history.end(); ++i) { 
            if (i->get_contact() == contact) {
                inactive.splice(inactive.begin(), history, i);
                return true;
            }
        }
        return false;
    }
};

#endif
