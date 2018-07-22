#ifndef ANIMUS_GRAPHICS_PIPELINE
#define ANIMUS_GRAPHICS_PIPELINE

#include "Shader.hpp"

namespace Animus {
    class GraphicsPipeline_ {
    public:
        virtual ~GraphicsPipeline_(void) = default;
    };

    typedef Pointer<GraphicsPipeline_> GraphicsPipeline;
}
#endif