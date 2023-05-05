#include "Matrix.h"

int main() {
	int n = 10, m = 10;

	std::cout << "Example for int" << '\n';
	//implicit instantiation
	Matrix<int> mtx1(n, m);
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			mtx1[i][j] = i * j;
		}
	}
	std::cout << "mtx1\n" << mtx1 << '\n';
	mtx1.resize(5, 5);
	std::cout << "mtx1 resized to (5, 5)\n" <<mtx1 << '\n';

	//implicit instantiation
	Matrix mtx2(5, 5);
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			mtx2[i][j] = i + j;
		}
	}
	mtx2[2] = {1, 2, 3};
	std::cout << "mtx2\n" << mtx2 << '\n';
	std::cout << "mtx1 + mtx2\n" << mtx1 + mtx2 << '\n';
	std::cout << "mtx1 - mtx2\n" << mtx1 - mtx2 << '\n';

	mtx1.sort_rows(1, std::greater<int>());
	std::cout << "mtx1 after sorting the 1st row with greater<int>\n" << mtx1 << '\n';
	mtx1.sort_cols(1, std::less<int>());
	std::cout << "mtx1 after sorting the 1st col with less<int>\n" << mtx1 << '\n';

	std::cout << "mtx1 rank\n" << mtx1.rank() << '\n'; 


	std::cout << "Example for double" << '\n';
	Matrix<double> mtx3(n, m);
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			mtx3[i][j] = i * j * 0.5;
		}
	}
	std::cout << "mtx3\n" << mtx3 << '\n';
	mtx3.resize(5, 5);
	std::cout << "mtx3 resized to (5, 5)\n" <<mtx3 << '\n';

	//implicit instantiation
	Matrix<double> mtx4(5, 5);
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			mtx4[i][j] = (i + j) * 0.5;
		}
	}
	std::cout << "mtx4\n" << mtx4 << '\n';
	std::cout << "mtx3 + mtx4\n" << mtx3 + mtx4 << '\n';
	std::cout << "mtx3 - mtx4\n" << mtx3 - mtx4 << '\n';

	mtx3.sort_rows(1, std::greater<double>());
	std::cout << "mtx3 after sorting the 1st row with greater<double>\n" << mtx3 << '\n';
	mtx3.sort_cols(1, std::less<double>());
	std::cout << "mtx3 after sorting the 1st col with less<double>\n" << mtx3 << '\n';




	std::cout << "Example for string" << '\n';
	Matrix<std::string> mtx5("ab", "cde");
	Matrix<std::string> mtx6("cd", "efg");

	std::cout << "mtx5(\"ab\", \"cde\")\n" << mtx5 << '\n';
	std::cout << "mtx6(\"cd\", \"efg\")\n" << mtx6 << '\n';

	std::cout << "mtx5 + mtx6\n";
	std::cout << mtx5 + mtx6 << '\n';
	std::cout << "mtx5 - mtx6\n";
	std::cout << mtx5 - mtx6 << '\n';

	std::cout << "mtx5 rank\n" << mtx5.rank() << '\n';
}