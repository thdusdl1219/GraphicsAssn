#pragma once
#include "Angel.h"

class MatrixStack {
	int    _index;
	int    _size;
	mat4*  _matrices;

public:
	MatrixStack(int numMatrices = 32) :_index(0), _size(numMatrices)
	{
		_matrices = new mat4[numMatrices];
	}

	~MatrixStack()
	{
		delete[]_matrices;
	}

	void push(const mat4& m) {		
		_matrices[_index++] = m;
	}

	mat4& pop(void) {		
		_index--;
		return _matrices[_index];
	}
};

