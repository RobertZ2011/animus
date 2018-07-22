#ifndef ANIMUS_GRAPHICS_INTERFACE
#define ANIMUS_GRAPHICS_INTERFACE

#include "types/types.hpp"
#include "version.hpp"
#include "graphics/Shader.hpp"
#include "Stream.hpp"
#include "RenderTarget.hpp"

namespace Animus {
    class GraphicsInterface_;
    typedef Pointer<GraphicsInterface_> GraphicsInterface;

    class Window_;
    class GraphicsInterface_ {
    public:
        virtual ~GraphicsInterface_(void) = default;

        virtual String getName(void) = 0;
        virtual Version getVersion(void) = 0;

        virtual void attachTarget(const RenderTarget& target) = 0;
        virtual void removeTarget(const RenderTarget& target) = 0;

        virtual void render(void) = 0;

        Shader createShader(void);
        VertexStage createVertexStage(const Stream& stream);
        GeometryStage createGeometryStage(const Stream& stream);
        FragmentStage createFragmentStage(const Stream& stream);
    };
}
#endif
