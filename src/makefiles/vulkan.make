FILE_NAMES_VULKAN := functions VulkanManager Vulkan
OBJECT_FILES_VULKAN := $(FILE_NAMES_VULKAN:%=Animus/build/vulkan/%.o)
CPP_FILES_VULKAN := $(FILE_NAMES_VULKAN:%=Animus/backends/Vulkan/%.cpp)

CPPFLAGS_VULKAN := $(CPPFLAGS) -fPIC
LDFLAGS_VULKAN := $(LDFLAGS)

.PHONY: build_vulkan

vulkan: Animus/build/libanimus.so Animus/build/backends/libanimus-vulkan.so

build_vulkan:
	-mkdir -p Animus/build/backends
	-mkdir -p Animus/build/vulkan

Animus/build/backends/libanimus-vulkan.so: build_vulkan $(CPP_FILES_VULKAN) $(OBJECT_FILES_VULKAN)
	$(CPP) -shared $(LDFLAGS_VULKAN) -o Animus/build/backends/libanimus-vulkan.so $(OBJECT_FILES_VULKAN)

Animus/build/vulkan/%.o: Animus/backends/Vulkan/%.cpp
	$(CPP) -o $@ -c $^ $(CPPFLAGS_VULKAN)
