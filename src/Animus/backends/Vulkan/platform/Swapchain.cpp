#ifdef __linux__
#include "linux/Swapchain.cpp"
#else
static_assert(false, "Unknow platform");
#endif