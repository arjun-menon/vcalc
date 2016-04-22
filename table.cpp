#include "stdinclude.h"

void Table::startRow() {
    row_count++;
}

void Table::addReal(real val, size_t len) {
    if(col_count <= cur_col) {
        addColumn();
        col_count++;
    }

    cols[cur_col++].get()->addRealCell(val, len);
}

void Table::endRow() {
    while(cur_col < col_count)
        cols[cur_col++].get()->addNullCell();

    cur_col = 0;
}

const Column &Table::getColumn(const size_t col) const {
    if(col < col_count)
        return *cols.at(col).get();
    else
        throw out_of_range(string("Requested column ") + to_string(col) +
                           " does not exist. Number of columns = " + to_string(col_count));

}

const Cell &Table::getCell(const size_t col, const size_t row) const {
    return getColumn(col).getCell(row);
}

std::ostream &Table::display(ostream& stream, vector<size_t> column_indices) const {
    for(size_t row = 0; row < row_count; row++) {
        for(auto col : column_indices)
            stream << setw(cols[col].get()->cell_width()) << getCell(col, row);
        stream << endl;
    }
    return stream;
}

std::ostream &operator<<(std::ostream& stream, Table& table) {
    return table.display(stream);
}
