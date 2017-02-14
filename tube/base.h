// Copyright 2017-2017 the openage authors. See copying.md for legal info.

#pragma once

#include "tube.h"

namespace openage {
namespace tube {

template <typename _T>
class tubeelement;
/**
 * A timely ordered list with several management functions
 *
 * This class manages different time-based management functions for the double-
 * linked list approach that lies underneath. It contains a double-linked list
 * to be accessed via a non-accurate timing functionality, this means, that for
 * getting a value, not the exact timestamp has to be known, it will always return
 * the one closest, less or equal to the requested one.
 **/
template <typename _T>
class tubebase {
	tubeelement<_T> *begin = nullptr;
	tubeelement<_T> *end = nullptr;

	// TODO create a pool where it might be possible to draw memory from
public:
	// Get the last element with e->time <= time
	tubeelement<_T> *last(const tube_time_t &time, tubeelement<_T>* hint=nullptr);

	// Create a new element and insert it into the tree
	tubeelement<_T> *create(const tube_time_t &, const _T& value);

	// Insert a newly ekement into the tree, that has not yet been inserted.
	void insert(tubeelement<_T> *);

	// Erase the whole list after this element until the end.
	void erase_after(tubeelement<_T> *last_valid);

	// Remove the tubeelement from its container
	void erase(tubeelement<_T> *e);
};

/**
 * A element of the double-linked list tubebase
 */
template <typename _T>
class tubeelement {
friend class tubebase<_T>;
public:
	tubeelement *next = nullptr;
	tubeelement *prev = nullptr;
private:
	// These folks are for tubebase only!
	tubeelement(const tube_time_t &time) :
		time(time)
	{}

	// Contruct it from time and value
	tubeelement(const tube_time_t &time, const _T &value) :
		time(time),
		value(value)
	{}

public:
	const tube_time_t time = 0;
	_T value = _T();
};




template <typename _T>
tubeelement<_T> *tubebase<_T>::last(const tube_time_t &time, tubeelement<_T> *hint) {
	tubeelement<_T> *e = hint ? hint : begin;

	if (e == nullptr) {
		//AUAUAUAUAUA!
//		throw Error(ERR << "Empty container list!");
	}

	// Search backward for this timeblob
	if (e->time < time) { 
		while(e != nullptr && e->time < time) {
			e = e->next;
		}
	} else { // Search forward
		while (e != nullptr && e->time > time) {
			e = e->prev;
		}
		e = e->next;
	}
	return e;
}

template <typename _T>
tubeelement<_T> *tubebase<_T>::create(const tube_time_t &time, const _T& value) {
	// TODO this has to be managed by a memory pool!
	auto e = new tubeelement<_T>(time, value);
	insert(e);
	return e;
}

template <typename _T>
void tubebase<_T>::insert(tubeelement<_T> *e) {
	// There are no elements in the list right now.
	if (begin == nullptr) {
		begin = e;
		end = e;
		return;
	}

	tubeelement<_T>* at = last(e->time);

	// if "last" cannot point at a location, so there was no element _before_
	// the newly inserted
	if (at == nullptr) {
		begin->prev = e;
		e->next = begin;
		begin = e;

		return;
	}

	// if next is nullptr, then it has to be at the end, so update the end
	if (at->next == nullptr || end == at) { // TODO VERIFY THIS!
		at->next = e;
		e->prev = e;
		end = e;
	}

	// the list is not empty, it is not at the beginning, it is not at the end:
	// it has to be in the middle! Yay-normal insert
	at->next->prev = e;
	e->next = at->next->prev;
	at->next = e;
	e->prev = at;
}

template <typename _T>
void tubebase<_T>::erase_after(tubeelement<_T> *last_valid) {
	tubeelement<_T> *e = end;
	//Delete from the end to last_valid
	while (e != nullptr && e != last_valid) {
		tubeelement<_T> *prev = e->prev;
		erase(e);
		e = prev;
	}
}

template <typename _T>
void tubebase<_T>::erase(tubeelement<_T> *e) {
	if (e == nullptr) return;
	if (e->next != nullptr) {
		e->next->prev = e->prev;
	}
	if (e->prev != nullptr) {
		e->prev->next = e->next;
	}
	delete e; // TODO Memory management magick!
}

}} // openage::tube