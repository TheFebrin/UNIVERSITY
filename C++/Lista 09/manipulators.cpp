//
// Created by marek on 28.05.18.
//

#include "manipulators.h"

std::istream & clearline(std::istream &in)
{
    while (in.peek() != EOF && in.get() != '\n');

    return in;
}

// ignore stuff

int ignore::get_size() const {
    return size;
}

ignore::ignore(int size_) : size(size_) {}

std::istream &operator>>(std::istream &in, const ignore &ign) {

    in.ignore(ign.get_size(), '\n');

    return in;
}

// comma and colon

std::ostream & comma(std::ostream & out)
{
    out << ", ";
    return out;
}

std::ostream & colon(std::ostream & out)
{
    out << ": ";
    return out;
}

// index stuff

int index::get_x() const {
    return x;
}

int index::get_w() const {
    return w;
};

index::index(int x_, int w_) : x(x_), w(w_) {};

std::ostream& operator<<(std::ostream &out, const index &ind)
{
    int len = std::to_string(ind.get_x()).length();
    int wid = ind.get_w() - len >= 0 ? ind.get_w() - len : 0;


    out << '[';
    out.width(wid);
    out << ind.get_x() << ']';

    return out;
}


// line stuff

int line::s_num = 0;

std::string line::get_m_line()const {
    return m_line;
}

int line::get_m_num()const {
    return m_num;
}

line::line() {

    ++s_num;
    m_num = s_num;
    std::getline(std::cin, m_line);
}

std::ostream& operator<<(std::ostream &out, const line &l)
{
    out << index(l.get_m_num(), 1) << colon << l.get_m_line() << '\n';

    return out;
}