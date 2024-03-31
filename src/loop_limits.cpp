#include <loop_limits.hpp>

static size_t count = 0;

bool lplim::count_loop() {
	if (count >= MAX_IT) return false;
	return ++count <= MAX_IT;
}

bool lplim::reset_loop() {
	bool retval = false;
	if (count >= MAX_IT) retval = true;
	count = 0;
	return retval;
}
