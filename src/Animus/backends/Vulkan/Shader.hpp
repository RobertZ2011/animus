#ifndef ANIMUS_VULKAN_SHADER
#define ANIMUS_VULKAN_SHADER

#include "../../Stream.hpp"

namespace Animus::Vulkan {
    class ShaderStage_ {
    public:
        virtual ~ShaderStage_(void);
    protected:
        ShaderStage(const Stream& stream);
    };

    class VertexStage_ : public ::Animus::VertexStage_, public ShaderStage_ {
    public:
        VertexStage_(const Stream& stream);
        ~VertexStage_(void) = 0;

        Pointer<VertexStage_> create(const Stream& stream);
    };
    typedef Pointer<VertexStage_> VertexStage;

    class GeometryStage_ : public ::Animus::GeometryStage_, public ShaderStage_ {
    public:
        FragmentStage_(const Stream& stream);
        ~FragmentStage_(void) = default;

        Pointer<GeometryStage_> create(const Stream& stream);
    };
    typedef Pointer<GeometryStage_> GeometryStage;

    class FragmentStage_ : public ::Animus::FragmentStage_, public ShaderStage_ {
    public:
        FragmentStage_(const Stream& stream);
        ~FragmentStage_(void) = default;

        Pointer<FragmentStage_> create(const Stream& stream);
    };
    typedef Pointer<FragmentStage_> FragmentStage;

    class Shader_ : public ::Animus::Shader_ {
        VertexStage vertexStage;
        GeometryStage geometryStage;
        FragmentStage fragmentStage;

    };
}
#endif