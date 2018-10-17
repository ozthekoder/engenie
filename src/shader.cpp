#include "shader.hpp"

// Define Namespace
namespace Engenie
{

Shader *Shader::init()
{
    mProgram = glCreateProgram();
    return this;
}

Shader *Shader::activate()
{
    glUseProgram(mProgram);
    return this;
}

void Shader::bind(GLuint location, GLuint value) { glUniform1i(location, value); }
void Shader::bind(GLuint location, GLfloat value) { glUniform1f(location, value); }
void Shader::bind(GLuint location, glm::mat4 const &matrix) { glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)); }
void Shader::bind(GLuint location, glm::vec4 const &vector) { glUniform4f(location, vector.x, vector.y, vector.z, vector.w); }
void Shader::bind(GLuint location, glm::vec3 const &vector) { glUniform3f(location, vector.x, vector.y, vector.z); }

Shader *Shader::attach(unsigned int shader, const char *source)
{
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &mStatus);

    // Display the Build Log on Error
    if (mStatus == false)
    {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &mLength);
        std::unique_ptr<char[]> buffer(new char[mLength]);
        glGetShaderInfoLog(shader, mLength, nullptr, buffer.get());
        fprintf(stderr, "%s", buffer.get());
    }

    // Attach the Shader and Free Allocated Memory
    glAttachShader(mProgram, shader);
    glDeleteShader(shader);
    return this;
}

std::string Shader::loadFile(const std::string &filename)
{
    // Load GLSL Shader Source from File
    std::ifstream fd(filename);
    std::string src = std::string(std::istreambuf_iterator<char>(fd),
                                  (std::istreambuf_iterator<char>()));

    return src;
}

GLuint Shader::create(std::string const &filename)
{
    auto index = filename.rfind(".");
    auto ext = filename.substr(index + 1);
    if (ext == "comp")
        return glCreateShader(GL_COMPUTE_SHADER);
    else if (ext == "frag")
        return glCreateShader(GL_FRAGMENT_SHADER);
    else if (ext == "geom")
        return glCreateShader(GL_GEOMETRY_SHADER);
    else if (ext == "vert")
        return glCreateShader(GL_VERTEX_SHADER);
    else
        return false;
}

Shader *Shader::link()
{
    glLinkProgram(mProgram);
    glGetProgramiv(mProgram, GL_LINK_STATUS, &mStatus);
    if (mStatus == false)
    {
        glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &mLength);
        std::unique_ptr<char[]> buffer(new char[mLength]);
        glGetProgramInfoLog(mProgram, mLength, nullptr, buffer.get());
        fprintf(stderr, "%s", buffer.get());
    }
    assert(mStatus == true);
    return this;
}

Shader *Shader::addDirective(std::string const &varName, unsigned int value, std::string &src)
{
    std::size_t found = src.find("\n");

    std::string addition = "\n#define " + varName + " " + std::to_string(value) + "\n\n";
    src.insert(found, addition);
    return this;
}

} // namespace Engenie