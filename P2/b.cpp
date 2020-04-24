#include <iostream>
#include <string>
#include <sstream>
#include "source.cpp"
#include <stdio.h>

int main() {
//    std::cout << addToNumber(2,5);
    int* set1 = new int;
    int* set2 = new int;
    std::string* out = new std::string;
    Emplace(" 11111 00000 10101", set1);
    Emplace("  00000  11111 ", set2);
    std::cout << howManySets(*set1) << " " << howManySets(*set2) << '\n';
//    std::cout << howManySets(*set1) << " ";
//    std::cout << howManySets(*set2);
//    std::cout << *set1 << " " << *set2 << '\n';
    Print(*set1, out);
    std::cout << "set1: " << *out << "\n";
    Print(*set2, out);
    std::cout << "set2: " << *out << "\n";
    std::cout << "LessThen: " << LessThen(*set1, *set2) << '\n';
    std::cout << "LessEqual: " << LessEqual(*set1, *set2) << '\n';
    std::cout << "GreatThen: " << GreatThen(*set1, *set2) << '\n';
    std::cout << "GreatEqual: " << GreatEqual(*set1, *set2) << '\n';
//    std::cout << *out;
//    std::cout << Disjoint(*set1, *set2);
    delete set1;
    delete set2;
    delete out;
    return 0;
}
