#pragma once

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

template<class T = int>
class Matrix {

using Row_t = std::vector<T>;

private:
	size_t _rows_n;
	size_t _cols_n;
	std::vector<Row_t> _elems;
	void adjust_rows();
public: 
	Matrix(size_t row, size_t col);

	template<size_t N, size_t M>
	constexpr Matrix(std::integral_constant<size_t, N>, std::integral_constant<size_t, M>);

	//for Matrix<std::string> only
	Matrix(std::string row, std::string col);	
	Matrix(const Matrix& mtx);
	Matrix& operator=(const Matrix& mtx);

	void resize(size_t row, size_t col);

	//this causes a problem, that a user now
	//can assign the whole rows, making matrix
	//be able to have rows of different sizes.
	//i tried to make custom class for matrix_row, 
	//but failed with[] again, so i'm just gonna to adjust
	//row lengths inside of every function i can ¯\_(ツ)_/¯
	Row_t& operator[](size_t row);

	template<class Compare>
	void sort_rows(size_t row_idx, const Compare& comp);
	template<class Compare>
	void sort_cols(size_t col_idx,const Compare& comp);

	Matrix<T> operator+(Matrix<T>& mtx);
	Matrix<T> operator-(Matrix<T>& mtx);

	size_t Rows() const;
	size_t Cols() const;

	int rank() const;

	template<typename X>
	friend std::ostream& operator<<(std::ostream& os, const Matrix<X>& mtx);
};

#include "Matrix.cpp"
#include "StringMatrix.cpp"

//explicit instantiation
template class Matrix<double>;