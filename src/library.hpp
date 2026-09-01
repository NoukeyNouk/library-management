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
    void add_book(Book book) {
        books[book.isbn] = book;
    }

    void add_user(User user) {
        users[user.get_id()] = user;
    }

    void remove_book(const string& isbn) {
        books.erase(isbn);
    }

    void remove_user(const string& id) {
        users.erase(id);
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
            }
        }
        if (zero_flag) {
            cout << "There's no any books with this genre!\n";
        }
    }

    void find_user(const string& query) {
        int zero_flag = 1;
        for (const auto& [id, user] : users) {
            if (user.get_name().find(query) != string::npos) {
                cout << id << ". " << user << "\n";
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



};

#endif
