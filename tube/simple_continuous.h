// Copyright 2017-2017 the openage authors. See copying.md for legal info.

#pragma once

#include "simple_type.h"

namespace openage {
namespace tube {

template<typename _T>
class SimpleContinuous : public SimpleType<_T> {
	tube_time_t diff_time;
	tube_time_t offset;

public:
	void set_now(const tube_time_t &t);

	_T get();

public:
};

template <typename _T>
void SimpleContinuous<_T>::set_now(const tube_time_t &t) {
	SimpleType<_T>::set_now(t);

	diff_time = this->e_now->next->time - this->e_now->time;
	offset = t - this->e_now->time;
}

template <typename _T>
_T SimpleContinuous<_T>::get() {
	double elapsed_frac = (double)diff_time / (double)offset;
	return this->e_now->value + (this->e_now->next->value - this->e_now->value) * elapsed_frac;
}

}} // openage::tube

