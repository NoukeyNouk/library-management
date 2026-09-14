#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>

using namespace std;

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
    out << book.title << ", " << book.author << ", " << book.genre;
    return out;
}


#endif
