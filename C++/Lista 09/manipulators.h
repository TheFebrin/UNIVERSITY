//
// Created by marek on 28.05.18.
//

#pragma once

#include <iostream>
#include <cmath>

std::istream & clearline(std::istream & in);

class ignore {
private:
    int size;

public:
    ignore(int size_);
    friend std::istream &operator>>(std::istream &in, const ignore &ign);
    int get_size() const;
};

std::ostream& comma(std::ostream &out);

std::ostream& colon(std::ostream &out);

class index {
private:
    int x, w;

public:
    index(int x_, int w_);
    friend std::ostream &operator<<(std::ostream &out, const index &idx);
    int get_x() const;
    int get_w() const;

};

class line {
private:
    std::string m_line;
    static int s_num;
    int m_num;

public:
    line();
    friend std::ostream &operator<<(std::ostream &out, const line &l);
    std::string get_m_line()const;
    int get_m_num()const;

};