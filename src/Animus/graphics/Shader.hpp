#ifndef ANIMUS_SHADER
#define ANIMUS_SHADER

#include "../types/types.hpp"

namespace Animus {
    class VertexStage_ {

    };

    typedef Pointer<VertexStage_> VertexStage;

    class GeometryStage_ {

    };

    typedef Pointer<GeometryStage_> GeometryStage;

    class FragmentStage_ {

    };

    typedef Pointer<FragmentStage_> FragmentStage;

    class Shader_ {
    public:
        virtual ~Shader_(void) = default;

        virtual void attach(const VertexStage& stage) = 0;
        virtual void attach(const GeometryStage& stage) = 0;
        virtual void attach(const FragmentStage& stage) = 0;
    };

    typedef Pointer<Shader_> Shader;
}
#endif