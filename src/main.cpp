#include <iostream>
#include <string>

#include "book.hpp"
#include "users.hpp"
#include "library.hpp"

using namespace std;


void add_book_to_library(Library& lib);
void remove_book_from_library(Library& lib);
void find_book_in_library(Library& lib);
void add_user_to_library(Library& lib);
void remove_user_from_library(Library& lib);


int main() {
    int day_counter = 1;
    int end = 0;
    Library lib = Library();

    while (end != 1) {
        int command = 0;
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
        // cout << "5. select book and give it to library user\n";
        cin >> command;

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
        }
    }
}


void add_book_to_library(Library& lib) {
    string query, isbn, author, title, genre;
    getline(cin, query);
    cout << "put ISBN: ";
    getline(cin, isbn);
    cout << "put author: ";
    getline(cin, author);
    cout << "put title: ";
    getline(cin, title);
    cout << "put genre: ";
    getline(cin, genre);
    lib.add_book(Book(isbn, author, title, genre));
    cout << "New book added to library!!\n";
}

void remove_book_from_library(Library& lib) {
    string isbn;
    cout << "put ISBN: ";
    getline(cin, isbn);
    lib.remove_book(isbn);
    cout << "Book was removed!!\n";
}

void find_book_in_library(Library& lib) {
    int find_option = 0;
    string query;
    cout << "find by (1 or any: title, 2: author, 3: genre)\n";
    cin >> find_option;
    cout << "put your query: ";
    getline(cin, query);
    getline(cin, query);
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
    }
}

void add_user_to_library(Library& lib) {
    int user_option = 0;
    string name;
    User new_user;
    cout << "Select user type (1: student, 2: faculty, 3 or any: guest): ";
    cin >> user_option;
    cout << "put user's name: ";
    getline(cin, name);
    getline(cin, name);
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
    lib.add_user(new_user);
    cout << "New user added!!\n";
}

void remove_user_from_library(Library& lib) {
    string id;
    cout << "put user id: ";
    getline(cin, id);
    lib.remove_user(id);
}

void find_user_in_library(Library& lib) {
    string query;
    cout << "put your query: ";
    getline(cin, query);
    lib.find_user(query);
}
