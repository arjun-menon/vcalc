/*
 * A cell in the table is represented by the `Cell` class here.
 * A concrete implementation of Cell is provided by `RealCell`.
 */

#ifndef VECTORCALC_CELL_H
#define VECTORCALC_CELL_H

typedef double real;

enum CellType {
    NULL_CELL,
    REAL_CELL
};

/*
 * Pure virtual interface representing a generic cell.
 */
struct Cell {
    virtual CellType getType() const = 0;

    // Arithmetic operations that must be supported by all cells
    virtual unique_ptr<Cell> operator+(const Cell &other) const = 0;
    virtual unique_ptr<Cell> operator-(const Cell &other) const = 0;
    virtual unique_ptr<Cell> operator*(const Cell &other) const = 0;
    virtual unique_ptr<Cell> operator/(const Cell &other) const = 0;

    virtual std::ostream& display(std::ostream &stream) const = 0;
};

/*
 * Cell used in place of empty or missing data (i.e. NULL).
 */
struct NullCell : Cell {
    NullCell() {}

    virtual CellType getType() const { return NULL_CELL; }

    /*
     * Operations against a NULL cell always result in another NULL.
     */
    virtual unique_ptr<Cell> operator+(const Cell &other) const { return unique_ptr<Cell>(dynamic_cast<Cell *>(new NullCell())); }
    virtual unique_ptr<Cell> operator-(const Cell &other) const { return unique_ptr<Cell>(dynamic_cast<Cell *>(new NullCell())); }
    virtual unique_ptr<Cell> operator*(const Cell &other) const { return unique_ptr<Cell>(dynamic_cast<Cell *>(new NullCell())); }
    virtual unique_ptr<Cell> operator/(const Cell &other) const { return unique_ptr<Cell>(dynamic_cast<Cell *>(new NullCell())); }

    virtual std::ostream& display(std::ostream &stream) const;
};

/*
 * Cell that stores a real number (double).
 */
struct RealCell : Cell {
    const real val;

    RealCell(real val) : val(val) {}

    virtual CellType getType() const { return REAL_CELL; }

    virtual unique_ptr<Cell> operator+(const Cell &other) const;
    virtual unique_ptr<Cell> operator-(const Cell &other) const;
    virtual unique_ptr<Cell> operator*(const Cell &other) const;
    virtual unique_ptr<Cell> operator/(const Cell &other) const;

    virtual std::ostream& display(std::ostream &stream) const;
};

std::ostream& operator<<(std::ostream &stream, const Cell &cell);
std::ostream& operator<<(std::ostream &stream, const unique_ptr<Cell> &cell);

#endif //VECTORCALC_CELL_H
