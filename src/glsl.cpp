#include "glsl.hpp"

namespace Engenie
{
void GLSL::compile()
{
    if (type != ShaderType::none && shader == 0)
    {
        GLint status;
        shader = glCreateShader(type);
        const char *src = source.str().c_str();
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

        if (status > 0)
        {
            GLint logLength;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
            std::unique_ptr<char[]> buffer(new char[logLength]);
            glGetShaderInfoLog(shader, logLength, nullptr, buffer.get());
            fprintf(stderr, "%s", buffer.get());
        }
    }
}

void GLSL::release()
{
    if (shader > 0)
    {
        glDeleteShader(shader);
    }
}

GLSL &GLSL::initializeContext()
{
    ctx.add_entity("constants", koura::object_t{});
    ctx.add_entity("layout", koura::object_t{});
    ctx.add_entity("ins", koura::object_t{});
    ctx.add_entity("outs", koura::object_t{});
    ctx.add_entity("uniforms", koura::object_t{});
    return *this;
}

GLSL &GLSL::setVersionDirective(size_t version)
{
    ctx.add_entity("version", koura::number_t(version));

    return *this;
}

GLSL &GLSL::addConstant(const std::string constName, size_t value)
{
    koura::entity e = ctx.get_entity("constants");
    koura::object_t consts = e.get_value<koura::object_t>();
    consts[constName] = koura::number_t(value);

    return *this;
}

GLSL &GLSL::addLayoutIdentifier(const std::string varName, const std::string type)
{
    koura::entity e = ctx.get_entity("layout");
    koura::sequence_t vars = e.get_value<koura::sequence_t>();
    koura::object_t var;
    var["name"] = varName;
    var["type"] = type;
    vars.push_back(var);
    return *this;
}

GLSL &GLSL::addInputVariable(const std::string varName, const std::string type)
{
    koura::entity e = ctx.get_entity("ins");
    koura::sequence_t vars = e.get_value<koura::sequence_t>();
    koura::object_t var;
    var["name"] = varName;
    var["type"] = type;
    vars.push_back(var);
    return *this;
}

GLSL &GLSL::addOutputVariable(const std::string varName, const std::string type)
{
    koura::entity e = ctx.get_entity("outs");
    koura::sequence_t vars = e.get_value<koura::sequence_t>();
    koura::object_t var;
    var["name"] = varName;
    var["type"] = type;
    vars.push_back(var);
    return *this;
}

GLSL &GLSL::addUniformVariable(const std::string varName, const std::string type)
{
    koura::entity e = ctx.get_entity("uniforms");
    koura::sequence_t vars = e.get_value<koura::sequence_t>();
    koura::object_t var;
    var["name"] = varName;
    var["type"] = type;
    vars.push_back(var);
    return *this;
}

GLSL &GLSL::generateSource()
{
    source.clear();
    return generateVersionDirective()
        .generateLayoutIdentifiers()
        .generateUniformVariables()
        .generateInputVariables()
        .generateOutputVariables();
}

GLSL &GLSL::generateVersionDirective()
{
    source << R"(#version {{version}} core\n)";
    return *this;
}

GLSL &GLSL::generateLayoutIdentifiers()
{
    koura::entity e = ctx.get_entity("layout");
    koura::sequence_t vars = e.get_value<koura::sequence_t>();
    size_t i = 0;
    for (koura::entity lv : vars)
    {
        koura::object_t var = lv.get_value<koura::object_t>();

        source << R"(layout(location = )";
        source << std::to_string(i);
        source << R"() in )";
        source << var["type"].get_value<koura::text_t>();
        source << R"( )";
        source << var["name"].get_value<koura::text_t>();
        source << R"(;\n)";
        i++;
    }

    return *this;
}

GLSL &GLSL::generateInputVariables()
{
    source << R"({%for var in ins%}in {{var.type}} {{var.name}};\n {%endfor%})";
    return *this;
}

GLSL &GLSL::generateOutputVariables()
{
    source << R"({%for var in outs%}out {{var.type}} {{var.name}};\n {%endfor%})";
    return *this;
}

GLSL &GLSL::generateUniformVariables()
{
    source << R"({%for var in uniforms%}uniform {{var.type}} {{var.name}};\n {%endfor%})";
    return *this;
}
} // namespace Engenie