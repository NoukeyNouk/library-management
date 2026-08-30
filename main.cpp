#include <iostream>
#include <map>
#include <ostream>
#include <string>

using namespace std;

void user_loop();

struct Book {
public:
    string isbn;
    string author;
    string title;
    string genre;

    Book() = default;
    Book(const string& _isbn, const string& _author, const string& _title, const string& _genre):
        isbn(_isbn),
        author(_author),
        title(_title),
        genre(_genre) {}

};


ostream& operator << (ostream& out, const Book& book) {
    out << book.title;
    return out;
}

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


class Library {
private:
    map<string, Book> books;
    map<string, User> users;

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

    void show_users() const {
        cout << "\nLibrary users:\n";
        for (const auto& [id, user] : users) {
            cout << id << ". " << user << "\n";
        }
    }

    void show_books() const {
        cout << "\nBooks in library:\n";
        for (const auto& [isbn, book] : books) {
            cout << isbn << ". " << book << "\n";
        }
    }

};

int main() {
    user_loop();
}

void user_loop() {
    int day_counter = 1;
    int end = 0;
    string isbn, author, title, genre, query;
    Library lib = Library();

    while (end != 1) {
        int command = 0;
        int find_option = 0;
        cout << "\n=====  Library manager  =====\n";
        cout << "Commands:\n";
        cout << "1. quit\n";
        cout << "2. add new book to library\n";
        cout << "3. remove book from library\n";
        cout << "4. find book in library\n";
        cout << "5. select book and give it to library user\n";
        cin >> command;

        switch (command) {
            case 1:
                end = 1;
                break;
            case 2:
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
                break;
            case 3:
                cout << "put ISBN: ";
                getline(cin, isbn);
                lib.remove_book(isbn);
                break;
            case 4:
                cout << "find by (1: title, 2: author, 3: genre)\n";
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
                break;
        }
    }
}










