#define STB_IMAGE_IMPLEMENTATION
#include "model.hpp"

namespace Engenie
{
void Model::loadFromFile(std::string const &filePath)
{
    std::ifstream fileStream(filePath);
    auto src = std::string(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
    gltf = Json::parse(src);
    loadBuffers();
    loadImages();
}

void Model::loadBuffers()
{
    Json bffrs = gltf["buffers"];
    for (auto it = bffrs.begin(); it != bffrs.end(); ++it)
    {
        Json bfr = it.value();
        Buffer buffer;
        std::string uri = bfr["uri"];
        if (isDataURI(uri))
        {
            decodeDataURI(buffer.data, std::string(""), uri, 0);
        }
        buffer.byteLength = bfr["byteLength"];
        std::string fullPath = directory + uri;
        std::streampos size;
        size_t sz;
        char *memblock;

        std::ifstream file(fullPath, std::ios::in | std::ios::binary | std::ios::ate);
        if (file.is_open())
        {
            size = file.tellg();
            sz = static_cast<size_t>(size);
            memblock = new char[sz];
            file.seekg(0, std::ios::beg);
            file.read(memblock, size);
            file.close();
        }

        unsigned char *data = (unsigned char *)memblock;
        buffer.data.resize(sz);
        std::copy(data, data + sz, buffer.data.begin());
        buffers.push_back(buffer);
    }
}

void Model::loadImages()
{
    Json imgs = gltf["images"];
    for (auto it = imgs.begin(); it != imgs.end(); ++it)
    {
        Json img = it.value();
        Image image;
        std::string uri = img["uri"];
        if (isDataURI(uri))
        {
            decodeDataURI(image.data, image.mimeType, uri, 0);
        }
        std::string fullPath = directory + uri;
        unsigned char *data = stbi_load(fullPath.c_str(), &image.width, &image.height, &image.component, STBI_rgb_alpha);
        size_t sz = image.width * image.height * image.component;
        image.data.resize(sz);
        std::copy(data, data + sz, image.data.begin());
        images.push_back(image);
    }
}

bool Model::isDataURI(const std::string &in)
{
    std::string header = "data:application/octet-stream;base64,";
    if (in.find(header) == 0)
    {
        return true;
    }

    header = "data:image/jpeg;base64,";
    if (in.find(header) == 0)
    {
        return true;
    }

    header = "data:image/png;base64,";
    if (in.find(header) == 0)
    {
        return true;
    }

    header = "data:image/bmp;base64,";
    if (in.find(header) == 0)
    {
        return true;
    }

    header = "data:image/gif;base64,";
    if (in.find(header) == 0)
    {
        return true;
    }

    header = "data:text/plain;base64,";
    if (in.find(header) == 0)
    {
        return true;
    }

    header = "data:application/gltf-buffer;base64,";
    if (in.find(header) == 0)
    {
        return true;
    }

    return false;
}

void Model::decodeDataURI(std::vector<unsigned char> &buf, std::string &mime_type, const std::string &in, size_t reqBytes)
{
    std::string header = "data:application/octet-stream;base64,";
    std::string data;
    if (in.find(header) == 0)
    {
        data = base64Decode(in.substr(header.size())); // cut mime string.
    }

    if (data.empty())
    {
        header = "data:image/jpeg;base64,";
        if (in.find(header) == 0)
        {
            mime_type = "image/jpeg";
            data = base64Decode(in.substr(header.size())); // cut mime string.
        }
    }

    if (data.empty())
    {
        header = "data:image/png;base64,";
        if (in.find(header) == 0)
        {
            mime_type = "image/png";
            data = base64Decode(in.substr(header.size())); // cut mime string.
        }
    }

    if (data.empty())
    {
        header = "data:image/bmp;base64,";
        if (in.find(header) == 0)
        {
            mime_type = "image/bmp";
            data = base64Decode(in.substr(header.size())); // cut mime string.
        }
    }

    if (data.empty())
    {
        header = "data:image/gif;base64,";
        if (in.find(header) == 0)
        {
            mime_type = "image/gif";
            data = base64Decode(in.substr(header.size())); // cut mime string.
        }
    }

    if (data.empty())
    {
        header = "data:text/plain;base64,";
        if (in.find(header) == 0)
        {
            mime_type = "text/plain";
            data = base64Decode(in.substr(header.size()));
        }
    }

    if (data.empty())
    {
        header = "data:application/gltf-buffer;base64,";
        if (in.find(header) == 0)
        {
            data = base64Decode(in.substr(header.size()));
        }
    }

    std::copy(data.begin(), data.end(), buf.begin());
}

std::string Model::base64Encode(unsigned char const *bytes_to_encode, unsigned int in_len)
{
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (in_len--)
    {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3)
        {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i < 4); i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];

        while ((i++ < 3))
            ret += '=';
    }

    return ret;
}

std::string Model::base64Decode(std::string const &encoded_string)
{
    int in_len = encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;

    while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_]))
    {
        char_array_4[i++] = encoded_string[in_];
        in_++;
        if (i == 4)
        {
            for (i = 0; i < 4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 4; j++)
            char_array_4[j] = 0;

        for (j = 0; j < 4; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++)
            ret += char_array_3[j];
    }

    return ret;
}

} // namespace Engenie