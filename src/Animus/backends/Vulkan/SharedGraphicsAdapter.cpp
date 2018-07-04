#include "SharedGraphicsAdapter.hpp"

namespace Animus::Vulkan {
    SharedGraphicsAdapter::SharedGraphicsAdapter(WMInterface * wmInterface, SharedDevice *sharedDevice) {

    }

    SharedGraphicsAdapter::~SharedGraphicsAdapter(void) {

    }

    void SharedGraphicsAdapter::resize(const Vec2i& size) {
        this->size = size;
        this->wmInterface->create(this->vsync, this->images, size);
    }

    void SharedGraphicsAdapter::enableVsync(bool enable) {
        this->vsync = enable;
        this->wmInterface->create(enable, this->images, this->size);
    }

    void SharedGraphicsAdapter::setBuffering(uint32_t images) {
        this->images = images;
        this->wmInterface->create(this->vsync, images, this->size);
    }

    void SharedGraphicsAdapter::setDisplayProperties(const Vec2i& size, bool vsync, uint32_t buffering) {
        this->size = size;
        this->vsync = vsync;
        this->images = buffering;
        this->wmInterface->create(vsync, buffering, size);
    }

    void SharedGraphicsAdapter::present(void) {
    }
}
