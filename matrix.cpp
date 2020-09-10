#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <stdexcept>
#include <fstream>
using namespace std;

class Matrix {
private:
	vector<vector<int>> data;
	int num_rows = 0;
	int num_cols = 0;

public:
	Matrix() {}

	Matrix(int rows, int cols) {
		if (rows < 0 || cols < 0) throw out_of_range("");
		if (!rows || !cols) {
			num_rows = 0;
			num_cols = 0;
		} else {
			num_rows = rows;
			num_cols = cols;
			data.resize(rows);
			for (size_t i = 0; i < rows; ++i) {
				data[i].resize(cols);
			}
		}
	}

	void Reset(int rows, int cols) {
		if (rows < 0 || cols < 0) throw out_of_range("");
		if (!rows || !cols) {
			data.resize(0);
			num_rows = 0;
			num_cols = 0;
		} else {
			num_rows = rows;
			num_cols = cols;
			data.resize(rows);
			for (size_t i = 0; i < rows; ++i) {
				data[i].assign(cols, 0);
			}
		}
	}

	int At(int row, int col) const {
		if (row >= data.size() || row < 0 || col >= data[0].size() || col < 0)
			throw out_of_range("");
		return data[row][col];
	}

	int& At(int row, int col) {
		if (row >= data.size() || row < 0 || col >= data[0].size() || col < 0)
			throw out_of_range("");
		return data[row][col];
	}

	int GetNumRows() const {
		return num_rows;
	}

	int GetNumColumns() const {
		return num_cols;
	}
};

istream& operator >>(istream& stream, Matrix& obj) {
	int rows, cols;
	stream >> rows >> cols;
	obj = {rows, cols};
	for (size_t i = 0; i < rows; ++i) {
		for (size_t j = 0; j < cols; ++j) {
			stream >> obj.At(i, j);
		}
	}
	return stream;
}

ostream& operator <<(ostream& stream, const Matrix& obj) {
	stream << obj.GetNumRows() << " " << obj.GetNumColumns() << endl;
	if (obj.GetNumColumns() == 0 || obj.GetNumRows() == 0) return stream;
	for (size_t i = 0; i < obj.GetNumRows(); ++i) {
		for (size_t j = 0; j < obj.GetNumColumns(); ++j) {
			stream << obj.At(i, j);
			if (j != obj.GetNumColumns()-1) stream << " ";
		}
		if (i != obj.GetNumRows()-1) stream << endl;
	}
	return stream;
}

bool operator ==(const Matrix& lhs, const Matrix& rhs) {
	if ((lhs.GetNumColumns() == 0 || lhs.GetNumRows() == 0) &&
			(rhs.GetNumColumns() == 0 || rhs.GetNumRows() == 0))
		return true;
	if (rhs.GetNumColumns() == lhs.GetNumColumns() &&
			rhs.GetNumRows() == lhs.GetNumRows()) {
		for (size_t i = 0; i < lhs.GetNumRows(); ++i) {
			for (size_t j = 0; j < lhs.GetNumColumns(); ++j) {
				if (lhs.At(i, j) != rhs.At(i, j)) return false;
			}
		}
		return true;
	}
	return false;
}

Matrix operator +(const Matrix& lhs, const Matrix& rhs) {
	if ((lhs.GetNumColumns() == 0 || lhs.GetNumRows() == 0) &&
				(rhs.GetNumColumns() == 0 || rhs.GetNumRows() == 0))
		return {0, 0};
	if (lhs.GetNumRows() != rhs.GetNumRows() ||
			lhs.GetNumColumns() != rhs.GetNumColumns())
		throw invalid_argument("");
	Matrix res(lhs.GetNumRows(), lhs.GetNumColumns());
	for (size_t i = 0; i < lhs.GetNumRows(); ++i) {
		for (size_t j = 0; j < lhs.GetNumColumns(); ++j) {
			res.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
		}
	}
	return res;
}
