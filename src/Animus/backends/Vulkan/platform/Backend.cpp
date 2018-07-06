#ifdef __linux__
#include "linux/Backend.cpp"
#else
static_assert(false, "Unknow platform");
#endif