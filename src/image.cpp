#include "image.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Engenie
{
void Image::load(std::string path)
{
    unsigned char *dt = stbi_load(path.c_str(), &width, &height, &component, STBI_rgb_alpha);
    size_t sz = width * height * component;
    data.resize(sz);
    std::copy(dt, dt + sz, data.begin());
};
} // namespace Engenie