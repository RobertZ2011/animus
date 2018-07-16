#ifndef ANIMUS_GRAPHICS_INTERFACE
#define ANIMUS_GRAPHICS_INTERFACE

#include "types/types.hpp"
#include "version.hpp"
#include "Window.hpp"
#include "Shader.hpp"
#include "Stream.hpp"

namespace Animus {
    class GraphicsInterface_;
    typedef Pointer<GraphicsInterface_> GraphicsInterface;

    class Window_;
    class GraphicsInterface_ {
    public:
        virtual ~GraphicsInterface_(void) = default;

        virtual String getName(void) = 0;
        virtual Version getVersion(void) = 0;

        virtual void setWindow(const Pointer<Window_>& window) = 0;
        virtual void resize(const Vec2i& size) = 0;
        virtual void enableVsync(bool enable) = 0;
        virtual void setBuffering(uint32_t images) = 0;
        virtual void setDisplayProperties(const Vec2i& size, bool vsync, uint32_t buffering) = 0;
        virtual void present(void) = 0;

        VertexStage createVertexStage(const Stream& stream);
        GeometryStage createGeometryStage(const Stream& stream);
        FragmentStage createFragmentStage(const Stream& stream);
    };
}
#endif
