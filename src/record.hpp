#ifndef RECORD_HPP
#define RECORD_HPP

#include <list>
#include <utility>
#include <map>
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

    const string& get_isbn() const {
        return isbn;
    }

    const string& get_user_id() const {
        return user_id;
    }

    int get_first_day() const {
        return first_day;
    }

    int get_last_day() const {
        return last_day;
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

    void register_book(const string& isbn) {
        avaliable_books[isbn] = true;
    }

    void unregister_book(const string& isbn) {
        avaliable_books.erase(isbn);
    }

    bool is_book_available(const string& isbn) const {
        auto it = avaliable_books.find(isbn);
        if (it != avaliable_books.end()) {
            return it->second;
        }
        return false;
    }

    bool user_has_active_records(const string& user_id) const {
        auto it = user_info.find(user_id);
        if (it != user_info.end()) {
            return it->second > 0;
        }
        return false;
    }

    void unregister_user(const string& user_id) {
        user_info.erase(user_id);
    }

    int new_record(Book book, User user) {
        if (!avaliable_books[book.isbn]) {
            return 0;
        }

        if (user_info[user.get_id()] >= user.get_max_books()) {
            return 1;
        }

        avaliable_books[book.isbn] = false;
        user_info[user.get_id()]++;
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
                avaliable_books[contact.first] = true;
                if (user_info[contact.second] > 0) {
                    user_info[contact.second]--;
                }
                inactive.splice(inactive.begin(), history, i);
                return true;
            }
        }
        return false;
    }

    void show_history() const {
        cout << "\nActive records (history):\n";
        if (history.empty()) {
            cout << "No active records.\n";
        } else {
            for (const auto& rec : history) {
                cout << "ISBN: " << rec.get_isbn() << ", User ID: " << rec.get_user_id()
                     << ", Issued day: " << rec.get_first_day() << ", Due day: " << rec.get_last_day() << "\n";
            }
        }
        cout << "\nInactive records (closed):\n";
        if (inactive.empty()) {
            cout << "No inactive records.\n";
        } else {
            for (const auto& rec : inactive) {
                cout << "ISBN: " << rec.get_isbn() << ", User ID: " << rec.get_user_id()
                     << ", Issued day: " << rec.get_first_day() << ", Due day: " << rec.get_last_day() << "\n";
            }
        }
    }

    void show_overdue() const {
        cout << "\nOverdue books (current day: " << day_counter << "):\n";
        bool found = false;
        for (const auto& rec : history) {
            if (rec.overdued(day_counter)) {
                cout << "ISBN: " << rec.get_isbn() << ", User ID: " << rec.get_user_id()
                     << ", Issued day: " << rec.get_first_day() << ", Due day: " << rec.get_last_day() << "\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No overdue books.\n";
        }
    }
};

#endif
