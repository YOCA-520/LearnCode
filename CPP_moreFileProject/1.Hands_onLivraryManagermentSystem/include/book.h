//
// Created by Administrator on 2026/8/14.
//

#ifndef LIBRARYMANAGER_BOOK_H
#define LIBRARYMANAGER_BOOK_H

#include <optional>
#include <string>

struct Book {
    std::string id;
    std::string title;
    std::string author;//author[作者]
    std::string category;//category[种类]
    int totalCopies{};//totalCopis[总拷贝数]
    int availableCopies{};//availableCopies[可用副本数]
};

class Catalog {
public:
    std::optional <Book> findById(const std::string& id)const;
    bool addBook(Book book);
    bool borrow(const std::string& id);
    bool giveBock(const std::string& id);

};
#endif //LIBRARYMANAGER_BOOK_H
