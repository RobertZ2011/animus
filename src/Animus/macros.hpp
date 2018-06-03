#ifndef ANIMUS_MACROS
#define ANIMUS_MACROS

//To make rewritting the engine with a different library easier
#ifdef ANIMUS_USE_STD
#define REQUIRES_STD
#else
#define REQUIRES_STD static_assert(false, "Use of C++ standard library required here");
#endif

#ifdef ANIMUS_USE_SDL
#define REQUIRES_SDL
#else
#define REQUIRES_SDL static_assert(false, "Use of SDL required here");
#endif

#ifdef ANIMUS_ALLOW_TODO
#define TODO(x)
#else
#define TODO(x) static_assert(false, "TODO: " ## x)
#endif

#endif
