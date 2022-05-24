#include "data_table.h"
#include <fstream>
#include <exception>
#include <array>
#include <iostream>
#include <algorithm>

using namespace std;

data_table::data_table() {
}

void data_table::from_text(const std::string &source) {
    _table.clear();
    ifstream f{source};
    if (f.is_open()) {
        array<char, 100> buffer;
        while (f.getline(&buffer[0], 100)) {
            _table.push_back(stold(string{buffer.data()}));
        }
    } else {
        throw ios_base::failure("File cannot be opened for reading.");
    }
}

void data_table::from_binary(const std::string &source) {
    _table.clear();
    ifstream f{source, std::ios::binary};
    if (f.is_open()) {
        double buffer;
        while (f.read(reinterpret_cast<char *>(&buffer), sizeof(double))) {
            _table.push_back(buffer);
        }
    } else  {
        throw ios_base::failure("File cannot be opened for reading.");
    }
}

void data_table::to_text(const std::string &destination) {
    ofstream f{destination};
    if (f.is_open()) {
        for (const double &value: _table) {
            f << value << endl;
        }
    }
}

void data_table::to_binary(const std::string &destination) {
    ofstream f{destination, std::ios::binary};
    if (f.is_open()) {
        for (const double &value: _table) {
            f.write(reinterpret_cast<const char *>(&value), sizeof(double));
        }
    } else  {
        throw ios_base::failure("File cannot be opened for writing.");
    }
}

void data_table::print_data() const {
    for (const double &value: _table) {
        cout << value << endl;
    }
}

data_table data_table::moving_average(size_t window_width) {
    data_table result;
    if (window_width < _table.size()) {
        double current_sum = 0.0;
        for (size_t i=0; i<window_width; ++i) {
            current_sum += _table[i];
        }
        result._table.push_back(current_sum/window_width);
        for (size_t i=0; i+window_width<_table.size(); ++i) {
            current_sum -= _table[i];
            current_sum += _table[i+window_width];
            result._table.push_back(current_sum/window_width);
        }
    }
    return result;
}

data_table data_table::sort_table(bool ascending) {
    data_table result;
    result._table = _table;
    if (ascending)
        sort(result._table.begin(), result._table.end());
    else
        sort(result._table.begin(), result._table.end(), [](const double &a, const double &b) {
            return a > b;
        });
    return result;
}

data_table data_table::average() {
    data_table result;
    data_table sum_table = table_sum();
    result._table.push_back(sum_table._table[0] / _table.size());
    return result;
}

data_table data_table::table_sum() {
    data_table result;
    double current_sum = 0.0;
    for (const double &value: _table) {
        current_sum += value;
    }
    result._table.push_back(current_sum);
    return result;
}

data_table data_table::table_count() {
    data_table result;
    result._table.push_back(static_cast<double>(_table.size()));
    return result;
}

