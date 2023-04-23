#include "Matrix.h"
#include <algorithm>
#include <exception>
#include <iterator>

template<class T>
Matrix<T>::Matrix(size_t row, size_t col) {
	_rows_n = row;
	_cols_n = col;

	//new matrix has default values for T in all of its cells
	_elems.resize(_rows_n);
	std::for_each(_elems.begin(), _elems.end(), [this](typename Matrix<T>::Row_t& r) {
		r.resize(_cols_n);
		fill(r.begin(), r.end(), *(new T()));
	});	
}

template<class T>
Matrix<T>::Matrix(const Matrix& mtx) {
	_rows_n = mtx.Rows();
	_cols_n = mtx.Cols();
	_elems = mtx._elems;
	adjust_rows();
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix& mtx) {
	_rows_n = mtx.Rows();
	_cols_n = mtx.Cols();
	_elems = mtx._elems;
	adjust_rows();
	return *this;
}

template<class T>
void Matrix<T>::adjust_rows() {
	for(size_t row = 0; row < _rows_n; row++) {
		Row_t& r = _elems[row];
		//if row_length is not enough -> fill "tail" with default elements
		//else if row_length is too big -> cut the "tail"
		if(r.size() < _cols_n) {
			fill_n(r.end(), _cols_n - r.size(), *(new T()));
		}
		else if(r.size() > _cols_n) {
			r.resize(_cols_n);
		}
	}
}

template<class T>
void Matrix<T>::resize(size_t rows, size_t cols) {
	adjust_rows();

	size_t old_rows_n = _rows_n;
	size_t old_cols_n = _cols_n;

	_rows_n = rows;
	_cols_n = cols;
	_elems.resize(_rows_n);
	for(size_t row = 0; row < _rows_n; row++) {
		_elems[row].resize(_cols_n);
	}
	//in case if new size is bigger than the old one,
	//"extra" cell are filled with default value for T

	//if both dimensions became smaller -> do nothing

	//if rows_n became became bigger -> fill new rows
	if(_rows_n > old_rows_n) {
		std::for_each(_elems.begin() + old_rows_n, _elems.end(), 
			[](typename Matrix<T>::Row_t& r) {
				fill(r.begin(), r.end(), *(new T()));
		});	
	}

	//if cols_n became bigger -> fill every row's "tail"
	if(_cols_n > old_cols_n) {
		std::for_each(_elems.begin(), _elems.end(), 
			[this, &old_cols_n](typename Matrix<T>::Row_t& r) {
				fill_n(r.begin() + old_cols_n, _cols_n - old_cols_n, *(new T()));
		});	
	}
}

template<class T>
typename Matrix<T>::Row_t& Matrix<T>::operator[](size_t row) {
	adjust_rows();
	if(row >= _rows_n) {
		throw std::out_of_range("Row index out of bounds");
	}
	return _elems[row];
}


template<class T>
template<class Compare>
void Matrix<T>::sort_rows(size_t row_idx, const Compare& cmp) {
	adjust_rows();
	if(row_idx >= _rows_n) {
		throw std::out_of_range("Row index out of bounds");
	}
	sort(_elems[row_idx].begin(), _elems[row_idx].end(), cmp);
}

template<class T>
template<class Compare>
void Matrix<T>::sort_cols(size_t col_idx, const Compare& cmp) {
	adjust_rows();
	if(col_idx >= _cols_n) {
		throw std::out_of_range("Column index out of bounds");
	}
	Row_t to_be_sorted(_rows_n);
	for(size_t row = 0; row < _rows_n; row++) {
		to_be_sorted[row] = _elems[row][col_idx];
	}
	sort(to_be_sorted.begin(), to_be_sorted.end(), cmp);
	for(size_t row = 0; row < _rows_n; row++) {
		_elems[row][col_idx] = to_be_sorted[row];
	}
}

template<class T>
Matrix<T> Matrix<T>::operator+(Matrix<T>& mtx) {
	adjust_rows();
	mtx.adjust_rows();
	if(mtx.Rows() != _rows_n or mtx.Cols() != _cols_n) {
		throw std::out_of_range("Dimensions do not fit");
	}
	Matrix<T> res(_rows_n, _cols_n);
	for(size_t row = 0; row < _rows_n; row++) {
		for(size_t col = 0; col < _cols_n; col++) {
			res[row][col] = _elems[row][col] + mtx[row][col];
		}
	}
	return res;
}

template<class T>
Matrix<T> Matrix<T>::operator-(Matrix<T>& mtx) {
	adjust_rows();
	mtx.adjust_rows();
	if(mtx.Rows() != _rows_n or mtx.Cols() != _cols_n) {
		throw std::out_of_range("Dimensions do not fit");
	}
	Matrix<T> res(_rows_n, _cols_n);
	for(size_t row = 0; row < _rows_n; row++) {
		for(size_t col = 0; col < _cols_n; col++) {
			res[row][col] = _elems[row][col] - mtx[row][col];
		}
	}
	return res;
}

template <typename T, typename VOID = void>
struct Delimiter;

template <typename T>
struct Delimiter<T, 
	typename std::enable_if_t<std::is_arithmetic_v<T>, void>> {
		static constexpr const char* delim = " : ";
};

template <typename T>
struct Delimiter<T, 
	typename std::enable_if_t<!std::is_arithmetic_v<T>, void>> {
		static constexpr const char* delim = " | ";
};


template<class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& mtx) {
	const char* delimiter = Delimiter<T>::delim;
	for_each(mtx._elems.begin(), mtx._elems.end(), [&](const typename Matrix<T>::Row_t& r) {
		if(r.size() < mtx.Cols()) {
			for(const T& elem : r) {
				os << elem << delimiter;
			}
			T tdefault = *(new T());
			for(size_t i = 1; i < mtx.Cols() - r.size(); i++) {
				os << tdefault << delimiter;
			}
			os << tdefault;

		}
		else if(r.size() == mtx.Cols()) {
			copy(r.begin(), r.end() - 1, std::ostream_iterator<T>(os, delimiter));
			copy(r.end() - 1, r.end(), std::ostream_iterator<T>(os));
		}
		else {
			auto r_new_end = r.begin() + mtx.Cols();
			copy(r.begin(), r_new_end - 1, std::ostream_iterator<T>(os, delimiter));
			copy(r_new_end - 1, r_new_end, std::ostream_iterator<T>(os));
		}
		os << '\n';
	});
	return os;
}

template<class T>
size_t Matrix<T>::Rows() const {
	//as expected, gives an error.
	//i don't get how to use integral_constant in this task, sorry
	/*
	if(std::is_const_v<decltype(this)>) {
		return std::integral_constant<size_t, _rows_n>::value;
	}
	*/
	return _rows_n;
}

template<class T>
size_t Matrix<T>::Cols() const {
	return _cols_n;
}
