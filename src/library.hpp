#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <map>
#include <string>
#include <iostream>
#include "users.hpp"
#include "book.hpp"
#include "record.hpp"


using namespace std;


class Library {
private:
    map<string, Book> books;
    map<string, User> users;
    Recorder recorder;

public:
    int add_book(Book book) {
        if (book.isbn.empty() || book.title.empty()) {
            return 2;
        }
        if (books.contains(book.isbn)) {
            return 1;
        }
        books[book.isbn] = book;
        recorder.register_book(book.isbn);
        return 0;
    }

    int add_user(User user) {
        if (user.get_name().empty()) {
            return 1;
        }
        users[user.get_id()] = user;
        return 0;
    }

    int remove_book(const string& isbn) {
        if (!books.contains(isbn)) {
            return 1;
        }
        if (!recorder.is_book_available(isbn)) {
            return 2;
        }
        books.erase(isbn);
        recorder.unregister_book(isbn);
        return 0;
    }

    int remove_user(const string& id) {
        if (!users.contains(id)) {
            return 1;
        }
        if (recorder.user_has_active_records(id)) {
            return 2;
        }
        users.erase(id);
        recorder.unregister_user(id);
        return 0;
    }

    void find_book_by_title(const string& query) {
        int zero_flag = 1;
        for (const auto& [isbn, book] : books) {
            if (book.title.find(query) != string::npos) {
                cout << isbn << ". " << book << "\n";
                zero_flag = 0;
            }
        }
        if (zero_flag) {
            cout << "There's no any books with this title!\n";
        }
    }

    void find_book_by_author(const string& query) {
        int zero_flag = 1;
        for (const auto& [isbn, book] : books) {
            if (book.author.find(query) != string::npos) {
                cout << isbn << ". " << book << "\n";
                zero_flag = 0;
            }
        }
        if (zero_flag) {
            cout << "There's no any books with this author!\n";
        }
    }
    
    void find_book_by_genre(const string& query) {
        int zero_flag = 1;
        for (const auto& [isbn, book] : books) {
            if (book.genre.find(query) != string::npos) {
                cout << isbn << ". " << book << "\n";
                zero_flag = 0;
            }
        }
        if (zero_flag) {
            cout << "There's no any books with this genre!\n";
        }
    }

    void find_book_by_isbn(const string& query) {
        int zero_flag = 1;
        for (const auto& [isbn, book] : books) {
            if (isbn.find(query) != string::npos) {
                cout << isbn << ". " << book << "\n";
                zero_flag = 0;
            }
        }
        if (zero_flag) {
            cout << "There's no any books with this ISBN!\n";
        }
    }

    void find_user(const string& query) {
        int zero_flag = 1;
        for (const auto& [id, user] : users) {
            if (user.get_name().find(query) != string::npos) {
                cout << id << ". " << user << "\n";
                zero_flag = 0;
            }
        }
        if (zero_flag) {
            cout << "There's no any users with this query!\n";
        }
    }

    void show_users() const {
        if (users.empty()) {
            cout << "There's no users in library..\n";
            return;
        }
        cout << "\nLibrary users:\n";
        for (const auto& [id, user] : users) {
            cout << id << ". " << user << "\n";
        }
    }

    void show_books() const {
        if (books.empty()) {
            cout << "There's no books in library..\n";
            return;
        }
        cout << "\nBooks in library (ISBN. title, author, genre):\n";
        for (const auto& [isbn, book] : books) {
            cout << isbn << ". " << book << "\n";
        }
    }

    int new_record(const string& isbn, const string& user_id) {
        if (!books.contains(isbn) || !users.contains(user_id)) {
            return 3;
        }
        return recorder.new_record(books[isbn], users[user_id]);
    }

    int close_record(const string& isbn, const string& user_id) {
        if (!books.contains(isbn) || !users.contains(user_id)) {
            return 2;
        }
        bool res = recorder.close_record({isbn, user_id});
        return res ? 0 : 1;
    }

    void show_history() const {
        recorder.show_history();
    }

    void show_overdue() const {
        recorder.show_overdue();
    }

    void next_day() {
        recorder.new_day();
        cout << "Advanced to next day.\n";
    }

};

#endif
