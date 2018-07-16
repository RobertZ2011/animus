#ifndef ANIMUS_MACROS
#define ANIMUS_MACROS

//To make rewritting the engine with a different library easier
#ifdef ANIMUS_USE_STD
#define ANIMUS_REQUIRES_STD
#else
#define ANIMUS_REQUIRES_STD static_assert(false, "Use of C++ standard library required here");
#endif

#ifdef ANIMUS_USE_SDL
#define ANIMUS_REQUIRES_SDL
#else
#define ANIMUS_REQUIRES_SDL static_assert(false, "Use of SDL required here");
#endif

#ifdef ANIMUS_ALLOW_ANIMUS_TODO
#define ANIMUS_TODO(x)
#else
#define ANIMUS_TODO(x) static_assert(false, "ANIMUS_TODO: " ## x)
#endif

#endif
