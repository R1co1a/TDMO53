#ifndef DATA_LIST_H
#define DATA_LIST_H


#include <vector>
#include <string>

class list_element {
    double _value;
    list_element *_prev;
    list_element *_next;

public:
    list_element(double v=0.0, list_element *p=nullptr, list_element *n=nullptr):
        _value(v), _prev(p), _next(n) {}
    ~list_element() {}

    list_element *get_next() {return _next;}
    void set_next(list_element *n) {_next = n;}
    list_element *get_prev() {return _prev;}
    void set_prev(list_element *n) {_prev = n;}
    double get_value()const {return _value;}
    void set_value(double v) {_value = v;}
};

class values_list {
    list_element *_head;
    list_element *_tail;

public:
    values_list(): _head(nullptr), _tail(nullptr) {}
    values_list(const values_list &other);
    ~values_list() {clear_list();}
    values_list &operator=(const values_list &other);

    void clear_list();
    void add_value(double v); // Always add at the end
    void pop_element(); // Remove last element
    size_t size()const;
    double get_value(size_t position)const;

    void sort_list(bool ascending);
};

class data_list {
    values_list _values;
public:
    data_list();
    data_list(const data_list &other);
    ~data_list() {_values.clear_list();}

    // Input methods
    void from_text(const std::string &source);
    void from_binary(const std::string &source);

    // Output methods
    void to_text(const std::string &destination);
    void to_binary(const std::string &destination);
    void print_data()const;

    // Computation (return new instances of data_table)
    data_list moving_average(size_t window_width);
    data_list sort_table(bool ascending=true);
    data_list average(); // returns a data_table with only one value
    data_list table_sum(); // returns a data_table with only one value
    data_list table_count(); // returns a data_table with only one value
};

#endif // DATA_LIST_H
