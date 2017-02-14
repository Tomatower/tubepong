// Copyright 2017-2017 the openage authors. See copying.md for legal info.

#pragma once

#include "tube.h"

namespace openage {
namespace tube {

template <class _T>
class TubeObject {
public:
	const _T &at(tube_time_t time);
};

}} // openage::tube
