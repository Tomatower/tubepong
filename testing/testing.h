#pragma once

#include <iostream>

#define TESTFAILMSG(a) \
	std::cerr << a; \
	throw 1

#define TESTEQUALS(left, right) \
	do { \
		auto &&test_result_left = (left); \
		if (test_result_left != (right)) { \
			TESTFAILMSG("unexpected value: " << (test_result_left)); \
		} \
	} while (0)


#define TESTEQUALS_FLOAT(left, right, epsilon) \
	do { \
		auto &&test_result_left = (left); \
		if ((test_result_left < (right - epsilon)) or \
		    (test_result_left > (right + epsilon))) { \
			TESTFAILMSG("unexpected value: " << (test_result_left)); \
		} \
	} while (0)

