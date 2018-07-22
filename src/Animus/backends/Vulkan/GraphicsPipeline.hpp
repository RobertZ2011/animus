#ifndef ANIMUS_VULKAN_GRAPHICS_PIPELINE
#define ANIMUS_VULKAN_GRAPHICS_PIPELINE

#include "../../graphics/GraphicsPipeline.hpp"
#include <functions.hpp>
#include <vulkan/vulkan.hpp>

namespace Animus::Vulkan {
    class GraphicsPipeline_ : public ::Animus::GraphicsPipeline_ {
        vk::Pipeline pipeline;
        vk::PipelineCache cache;

    public:
        virtual ~GraphicsPipeline_(void);

    private:
    };
}
#endif