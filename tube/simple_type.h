// Copyright 2017-2017 the openage authors. See copying.md for legal info.

#pragma once

#include "base.h"

namespace openage {
namespace tube {

template<typename _T>
class SimpleType {
protected:
	tubebase<_T> container;
	mutable tubeelement<_T> *e_now;
	mutable tube_time_t now;

public:
	SimpleType(); 

	// Reader mode
	virtual void set_now(const tube_time_t &t) const;

	virtual _T get() const = 0;
	virtual _T get(const tube_time_t &t) const;
public:
	// Inserter mode
	void set_drop(const tube_time_t &at, const _T &value);
	void set_insert(const tube_time_t &at, const _T &value);
};

template <typename _T>
SimpleType<_T>::SimpleType() :
	now(),
	e_now(nullptr)
{}

template <typename _T>
void SimpleType<_T>::set_now(const tube_time_t &t) const {
	now = t;

	// Iterate forward until the element time is smaller than time
	while (e_now != nullptr && e_now->prev != e_now && e_now->time >= now) {
		e_now = e_now->prev;
	}

	// Iterate back until the element time is larger than time
	while (e_now != nullptr && e_now->next != e_now && e_now->time < now) {
		e_now = e_now->next;
	}

	// If the shaking-operation above was not successfull, find a new one
	if (e_now == nullptr) {
		e_now = container.last(t);
	}
}

template <typename _T>
_T SimpleType<_T>::get(const tube_time_t &t) const {
	set_now(t);
	return get();
}

template <typename _T>
void SimpleType<_T>::set_drop(const tube_time_t &at, const _T &value) {
	container.erase_after(container.last(at, e_now));
	container.create(at, value);
}

template <typename _T>
void SimpleType<_T>::set_insert(const tube_time_t &at, const _T &value) {
	container.create(at, value);
}

}} // openage::tube

