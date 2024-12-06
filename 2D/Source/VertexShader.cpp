#include "VertexShader.h"
#include "Shader.h"

//#define GOURAUD

void VertexShader::Process(const vertex_t& ivertex, vertex_output_t& overtex)
{
    glm::mat4 mvp = Shader::uniforms.projection * Shader::uniforms.view * Shader::uniforms.model;
    overtex.position = mvp * glm::vec4{ ivertex.position, 1 };
    glm::mat4 mv = Shader::uniforms.view * Shader::uniforms.model;
    overtex.normal = glm::vec3{ glm::normalize(glm::mat3{ mv } *ivertex.normal) };
    overtex.vposition = mv * glm::vec4{ ivertex.position, 1 };
 
    //glm::vec3 light_position = Shader::uniforms.view * glm::vec4{ Shader::uniforms.light.position, 1 };
    //glm::vec3 light_direction = Shader::uniforms.view * glm::vec4{ -Shader::uniforms.light.position, 0 };

    //glm::vec3 vposition = mv * glm::vec4{ ivertex.position, 1 };
    //glm::vec3 light_dir = glm::normalize(light_position - vposition); // normalize light direction
    ////glm::vec3 light_dir = glm::normalize(light_direction);

    ////diffuse
    //float intensity = std::max(0.0f, glm::dot(light_dir, overtex.normal));
    //colour3_t diffuse = Shader::uniforms.light.colour * intensity;

    ////specular
    //colour3_t specular = colour3_t{ 0 };
    //if (intensity > 0)
    //{
    //    glm::vec3 reflection = glm::reflect(-light_dir, overtex.normal);
    //    glm::vec3 view_dir = glm::normalize(-vposition);
    //    intensity = std::max(glm::dot(reflection, view_dir), 0.0f);
    //    intensity = pow(intensity, Shader::uniforms.material.shininess);
    //    specular = Shader::uniforms.material.specular * intensity;
    //}

    //overtex.colour = ((Shader::uniforms.ambient + diffuse) * Shader::uniforms.material.albedo) + specular;
}
