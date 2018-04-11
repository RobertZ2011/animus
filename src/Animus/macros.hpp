#ifndef ANIMUS_MACROS
#define ANIMUS_MACROS

//To make rewritting the engine with a different library easier
#ifdef ANIMUS_USE_STD
#define REQUIRES_STD
#else
#define REQUIRES_STD static_assert(false, "Use of C++ standard library required here");
#endif

#endif
