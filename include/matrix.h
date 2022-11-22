#ifndef MATRIX_H
#define MATRIX_H

#include "types.h"
#include <iostream>

namespace matrix {
	template<class Type>
	class Matrix {
	private:
		int rows;
		int columns;
		Type **matrix;
	public:
		Matrix(int rows, int columns);
		virtual ~Matrix();
		void set_element(types::Ordered_pair<int> element, Type value);
		void set_all_elements(Type value);
		void set_row(int row, Type *values);
		Type get_element(types::Ordered_pair<int> element);
		void print() const;
	};

	template<class Type>
	Matrix<Type>::Matrix(int rows, int columns) {
		this->rows = rows;
		this->columns = columns;

		this->matrix = new Type *[rows];
		for (int k = 0; k < rows; k++) {
			this->matrix[k] = new Type[columns];
		}
	}

	template<class Type>
	Matrix<Type>::~Matrix() {}

	template<class Type>
	void Matrix<Type>::set_element(types::Ordered_pair<int> element, Type value) {
		this->matrix[element.x][element.y] = value;
	}

	template<class Type>
	void Matrix<Type>::set_all_elements(Type value) {
		for (int i = 0; i < this->rows; i++) {
			for (int j = 0; j < this->columns; j++) this->matrix[i][j] = value;
		}
	}

	template<class Type>
	void Matrix<Type>::set_row(int row, Type *values) {
		this->matrix[row] = values;
	}

	template<class Type>
	Type Matrix<Type>::get_element(types::Ordered_pair<int> element) {
		return this->matrix[element.x][element.y];
	}

	template<class Type>
	void Matrix<Type>::print() const {
		for (int i = 0; i < this->rows; i++) {
			for (int j = 0; j < this->columns; j++) std::cout << this->matrix[i][j] << ' ';
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
} // namespace matrix

#endif // MATRIX_H
