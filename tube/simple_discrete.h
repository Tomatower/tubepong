// Copyright 2017-2017 the openage authors. See copying.md for legal info.

#pragma once

#include "simple_type.h"

namespace openage {
namespace tube {

template<typename _T>
class SimpleDiscrete : public SimpleType<_T> {
public:

	_T get();

public:
};

template <typename _T>
_T SimpleDiscrete<_T>::get() {
	return this->e_now->value;
}

}} // openage::tube

