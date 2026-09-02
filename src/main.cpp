#include <iostream>
#include <string>
#include <list>
#include <utility>

#include "book.hpp"
#include "users.hpp"
#include "library.hpp"

using namespace std;

int read_int();
void add_book_to_library(Library& lib);
void remove_book_from_library(Library& lib);
void find_book_in_library(Library& lib);
void add_user_to_library(Library& lib);
void remove_user_from_library(Library& lib);
void find_user_in_library(Library& lib);
void new_record_to_library(Library& lib);
void close_record_from_library(Library& lib);

int main() {
    int day_counter = 1;
    int end = 0;
    Library lib = Library();

    while (end != 1) {
        cout << "\n========  Library manager  ========\n\n";
        cout << "Commands:\n";
        cout << "0. quit\n";
        cout << "1. add new book\n";
        cout << "2. remove book from library\n";
        cout << "3. find book\n";
        cout << "4. show all books\n";
        cout << "5. add new user\n";
        cout << "6. remove user\n";
        cout << "7. find user\n";
        cout << "8. show all users\n";
        cout << "9. new record\n";
        cout << "10. close record\n";
        cout << "11. show history\n";
        cout << "12. view overdue books\n";
        cout << "13. advance to next day\n";

        int command = read_int();

        switch (command) {
            case 0:
                end = 1;
                break;
            case 1:
                add_book_to_library(lib);
                break;
            case 2:
                remove_book_from_library(lib);
                break;
            case 3:
                find_book_in_library(lib);
                break;
            case 4:
                lib.show_books();
                break;
            case 5:
                add_user_to_library(lib);
                break;
            case 6:
                remove_user_from_library(lib);
                break;
            case 7:
                find_user_in_library(lib);
                break;
            case 8:
                lib.show_users();
                break;
            case 9: {
                new_record_to_library(lib);
                break;
            }
            case 10: {
                close_record_from_library(lib);
                break;
            }
            case 11:
                lib.show_history();
                break;
            case 12:
                lib.show_overdue();
                break;
            case 13:
                lib.next_day();
                break;
        }
    }
}

int read_int() {
    string line;
    if (!getline(cin, line)) {
        return 0;
    }
    try {
        return stoi(line);
    } catch (...) {
        return 0;
    }
}

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

void add_book_to_library(Library& lib) {
    string isbn, author, title, genre;
    cout << "put ISBN: ";
    getline(cin, isbn);
    isbn = trim(isbn);
    cout << "put author: ";
    getline(cin, author);
    author = trim(author);
    cout << "put title: ";
    getline(cin, title);
    title = trim(title);
    cout << "put genre: ";
    getline(cin, genre);
    genre = trim(genre);
    int res = lib.add_book(Book(isbn, author, title, genre));
    if (res == 0) {
        cout << "New book added to library!!\n";
    } else if (res == 1) {
        cout << "Error: Book with this ISBN already exists!\n";
    } else if (res == 2) {
        cout << "Error: ISBN and Title cannot be empty!\n";
    }
}

void remove_book_from_library(Library& lib) {
    string isbn;
    cout << "put ISBN: ";
    getline(cin, isbn);
    isbn = trim(isbn);
    int res = lib.remove_book(isbn);
    if (res == 0) {
        cout << "book was removed!!\n";
    } else if (res == 1) {
        cout << "error: Book not found!!\n";
    } else if (res == 2) {
        cout << "error: Cannot remove book because it is currently borrowed!\n";
    }
}

void find_book_in_library(Library& lib) {
    string query;
    cout << "find by (1 or any: title, 2: author, 3: genre, 4: ISBN)\n";
    int find_option = read_int();
    cout << "put your query: ";
    getline(cin, query);
    query = trim(query);
    if (query.empty()) {
        cout << "search query cannot be empty!\n";
        return;
    }
    switch (find_option) {
        default:
        case 1:
            lib.find_book_by_title(query);
            break;
        case 2:
            lib.find_book_by_author(query);
            break;
        case 3:
            lib.find_book_by_genre(query);
            break;
        case 4:
            lib.find_book_by_isbn(query);
            break;
    }
}

void add_user_to_library(Library& lib) {
    string name;
    cout << "Select user type (1: student, 2: faculty, 3 or any: guest): ";
    int user_option = read_int();
    cout << "put user's name: ";
    getline(cin, name);
    name = trim(name);
    if (name.empty()) {
        cout << "Error: User name cannot be empty!\n";
        return;
    }
    User new_user;
    switch (user_option) {
        case 1:
            new_user = Student(name);
            break;
        case 2:
            new_user = Faculty(name);
            break;
        case 3:
        default:
            new_user = Guest(name);
            break;
    }
    int res = lib.add_user(new_user);
    if (res == 0) {
        cout << "New user added!!\n";
    } else {
        cout << "Error adding user!\n";
    }
}

void remove_user_from_library(Library& lib) {
    string id;
    cout << "put user id: ";
    getline(cin, id);
    id = trim(id);
    int res = lib.remove_user(id);
    if (res == 0) {
        cout << "User was removed!!\n";
    } else if (res == 1) {
        cout << "Error: User not found!\n";
    } else if (res == 2) {
        cout << "Error: Cannot remove user with active borrowed books!\n";
    }
}

void find_user_in_library(Library& lib) {
    string query;
    cout << "put your query: ";
    getline(cin, query);
    query = trim(query);
    if (query.empty()) {
        cout << "Search query cannot be empty!\n";
        return;
    }
    lib.find_user(query);
}

void new_record_to_library(Library& lib) {
    string isbn, user_id;
    cout << "put ISBN: ";
    getline(cin, isbn);
    isbn = trim(isbn);
    cout << "put user id: ";
    getline(cin, user_id);
    user_id = trim(user_id);
    int res = lib.new_record(isbn, user_id);
    if (res == 2) {
        cout << "Record created!!\n";
    } else if (res == 0) {
        cout << "Book is not available!\n";
    } else if (res == 1) {
        cout << "User limit reached!\n";
    } else {
        cout << "Book or user not found!\n";
    }
}

void close_record_from_library(Library& lib) {
    string isbn, user_id;
    cout << "put ISBN: ";
    getline(cin, isbn);
    isbn = trim(isbn);
    cout << "put user id: ";
    getline(cin, user_id);
    user_id = trim(user_id);
    int res = lib.close_record(isbn, user_id);
    if (res == 0) {
        cout << "Record closed!!\n";
    } else if (res == 1) {
        cout << "Active record for this book and user not found!\n";
    } else {
        cout << "Book or user not found!\n";
    }
}
