#include <vector>

using namespace std;

template <typename T>
class Table {
public:
	Table(const size_t& rows, const size_t& columns) {
		if (rows != 0) {
			_rows = rows;
			_columns = columns;
			data.resize(rows);
			for (size_t i = 0; i < rows; ++i)
				data[i].resize(columns);
		}
	}

	const vector<T>& operator [](const int& i) const {
		return data[i];
	}

	vector<T>& operator [](const int i) {
		return data[i];
	}

	void Resize(const size_t& rows, const size_t& columns) {
		if (rows != 0) {
			_rows = rows;
			_columns = columns;
			data.resize(rows);
			for (size_t i = 0; i < rows; ++i)
				data[i].resize(columns);
		} else {
			_columns = 0;
			_rows = 0;
			data.resize(_rows);
		}
	}

	pair<size_t, size_t> Size() const {
		return {_rows, _columns};
	}
private:
	size_t _rows = 0, _columns = 0;
	vector<vector<T>> data;
};
