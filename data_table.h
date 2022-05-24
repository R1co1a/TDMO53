#ifndef DATA_TABLE_H
#define DATA_TABLE_H

#include <vector>
#include <string>

class data_table {
    std::vector<double> _table;

public:
    data_table();
    ~data_table() {}

    // Input methods
    void from_text(const std::string &source);
    void from_binary(const std::string &source);

    // Output methods
    void to_text(const std::string &destination);
    void to_binary(const std::string &destination);
    void print_data()const;

    // Computation (return new instances of data_table)
    data_table moving_average(size_t window_width);
    data_table sort_table(bool ascending=true);
    data_table average(); // returns a data_table with only one value
    data_table table_sum(); // returns a data_table with only one value
    data_table table_count(); // returns a data_table with only one value
};

#endif // DATA_TABLE_H
