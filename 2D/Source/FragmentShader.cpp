#include "FragmentShader.h"
#include "Shader.h"

colour4_t FragmentShader::Process(const fragment_input_t& fragment)
{
    glm::vec3 light_position = Shader::uniforms.view * glm::vec4{ Shader::uniforms.light.position, 1 };
    glm::vec3 light_direction = Shader::uniforms.view * glm::vec4{ -Shader::uniforms.light.position, 0 };

    //glm::vec3 vposition = mv * glm::vec4{ fragment.position, 1 };
    glm::vec3 light_dir = glm::normalize(light_position - fragment.position); // normalize light direction
    //glm::vec3 light_dir = glm::normalize(light_direction);

    float intensity = std::max(0.0f, glm::dot(light_dir, fragment.normal));
    colour3_t diffuse = Shader::uniforms.light.colour * intensity;

    colour3_t colour = ((Shader::uniforms.ambient + diffuse));// *Shader::uniforms.material.albedo);

	return colour4_t{ colour, 1 };
}