//explicit specialization

#include "Matrix.h"

template<>
Matrix<std::string>::Matrix(std::string row_str, std::string col_str) {
	_rows_n = row_str.length();
	_cols_n = col_str.length();

	//every cell i,j of matrix contains 
	//a concatenation of row_str[i] and col_str[j]
	_elems.resize(_rows_n);
	for(size_t row = 0; row < _rows_n; row++) {
		_elems[row].resize(_cols_n);
		for(size_t col = 0; col < _cols_n; col++) {
			_elems[row][col] = "";
			_elems[row][col] += row_str[row];
			_elems[row][col] += col_str[col];
		}
	}
}

//every cell i,j in result matrix
//contains a string which consists of
//elements which are in the left matrix i,j
//and NOT in the right matrix i,j
template<>
Matrix<std::string> Matrix<std::string>::operator-(Matrix<std::string>& mtx) {
	adjust_rows();
	mtx.adjust_rows();
	if(mtx.Rows() != _rows_n or mtx.Cols() != _cols_n) {
		throw std::out_of_range("Dimensions do not fit");
	}
	Matrix<std::string> res(_rows_n, _cols_n);
	for(size_t row = 0; row < _rows_n; row++) {
		for(size_t col = 0; col < _cols_n; col++) {

			std::string& left_str = _elems[row][col];
			std::string& right_str = mtx[row][col];
			std::string& res_str = res[row][col];

			std::set_difference(left_str.begin(), left_str.end(), 
								right_str.begin(), right_str.end(),
                        		std::inserter(res_str, res_str.begin()));
		}
	}
	return res;
}

template<>
int Matrix<std::string>::rank() const {
	const double EPS = 1e-9;
    int rank = 0;
    
    std::vector<std::vector<double> > A;
    A.resize(_rows_n);
    for(int i = 0; i < _rows_n; i++) {
    	A[i].resize(_cols_n);
    	for(int j = 0; j < _cols_n; j++) {
    		A[i][j] = _elems[i][j].size();
    	}
    }
    

    std::vector<bool> row_selected(_rows_n, false);
    for (int i = 0; i < _cols_n; ++i) {
        int j;
        for (j = 0; j < _rows_n; ++j) {
            if (!row_selected[j] && abs(A[j][i]) > EPS)
                break;
        }

        if (j != _rows_n) {
            ++rank;
            row_selected[j] = true;
            for (int p = i + 1; p < _cols_n; ++p)
                A[j][p] /= A[j][i];
            for (int k = 0; k < _rows_n; ++k) {
                if (k != j && abs(A[k][i]) > EPS) {
                    for (int p = i + 1; p < _cols_n; ++p)
                        A[k][p] -= A[j][p] * A[k][i];
                }
            }
        }
    }
    return rank;
}