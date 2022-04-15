#pragma once

#include <tuple>

#include "core/log.h"
#include <ecs/ecs.hpp>

#include "renderer/renderer.h"
#include "renderer/renderer_api.h"
#include "../components/transform_component.h"
#include "../components/mesh_component.h"

#include <glbinding/glbinding.h>
#include <glbinding/gl46core/gl.h>

using namespace gl;

PH_NAMESPACE_BEGIN

    class RenderSystem : public ecs::BaseSystem<RenderSystem>
    {
    public:
        using Signature = std::tuple<TransformComponent, MeshComponent>;

        uint32_t vertex;
        uint32_t fragment;
        uint32_t shader;

        const char* vertex_src = "#version 330 core\n\
                    layout(location = 0) in vec3 aPos;\n\
                layout(location = 1) in vec2 aTexCoord;\n\
\n\
                out vec2 TexCoord;\n\
\n\
                uniform mat4 model;\n\
                uniform mat4 view;\n\
                uniform mat4 projection;\n\
\n\
                void main()\n\
                {\n\
                    gl_Position = projection * view * model * vec4(aPos, 1.0f);\n\
                    TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n\
                }";

        const char* fragment_src = "#version 330 core\n\
            out vec4 FragColor;\n\
\n\
        in vec2 TexCoord;\n\
\n\
        // texture samplers\n\
        uniform sampler2D texture1;\n\
        uniform sampler2D texture2;\n\
\n\
        void main()\n\
        {\n\
            FragColor = vec4(1,0,0,1);\n\
        }";

        RenderSystem() {
            vertex = glCreateShader(GL_VERTEX_SHADER);
            fragment = glCreateShader(GL_FRAGMENT_SHADER);

            glShaderSource(vertex, 1, &vertex_src, NULL);
            glCompileShader(vertex);
            checkCompileErrors(vertex, "VERTEX");

            glShaderSource(fragment, 1, &fragment_src, NULL);
            glCompileShader(fragment);
            checkCompileErrors(fragment, "FRAGMENT");

            shader = glCreateProgram();
            glAttachShader(shader, vertex);
            glAttachShader(shader, fragment);
            glLinkProgram(shader);
            checkCompileErrors(shader, "PROGRAM");

            glUseProgram(shader);
            Log::core_info("Init render system");
        };

        ~RenderSystem() = default;

        template<typename Settings>
        void update(ecs::Manager<Settings>* manager)
        {
            static glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)1280 / (float)720, 0.1f, 100.0f);
            static glm::mat4 view = glm::lookAt(glm::vec3(0,0,-5), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
           
            for(ecs::EntityID entity : m_registered_entities)
            {
                TransformComponent& transform = manager->template get_component<TransformComponent>(entity);
                MeshComponent& mesh = manager->template get_component<MeshComponent>(entity);

                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(0,0,5));
                model = glm::scale(model, transform.scale);

                glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, &projection[0][0]);
                glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, &view[0][0]);
                glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &model[0][0]);

                RendererAPI::draw_indexed(mesh.vertex_array_object, mesh.vertex_buffer_object, mesh.element_buffer_object, 12);
                Log::core_info("Render entity {}", entity);
            }
        }

        void checkCompileErrors(GLuint shader, std::string type)
        {
            GLint success;
            GLchar infoLog[1024];
            if (type != "PROGRAM")
            {
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                    Log::core_error("ERROR::SHADER_COMPILATION_ERROR of type: {} \n {}\n -- --------------------------------------------------- -- ", type, infoLog);
                }
            }
            else
            {
                glGetProgramiv(shader, GL_LINK_STATUS, &success);
                if (!success)
                {
                    glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                    Log::core_error("ERROR::PROGRAM_LINKING_ERROR of type: {} \n {}\n -- --------------------------------------------------- -- ", type, infoLog);
                }
            }
        }
    };
    
PH_NAMESPACE_END
