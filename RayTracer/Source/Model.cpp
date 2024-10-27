#include "Model.h"
#include "Framebuffer.h"
#include "Camera.h"

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

void Model::Draw(Framebuffer& framebuffer, const glm::mat4& model, const Camera& camera)
{
	//
}

bool Model::Load(const std::string& filename)
{
	// open file using ifstream (input file stream)
	std::ifstream stream(filename);

	// check if stream is_open
	if (!stream.is_open())
	{
		std::cerr << "File failed to open: " << filename << std::endl;
		return false;
	}

	vertices_t vertices;
	std::string line;

	while (std::getline(stream, line))
	{
		// read in vertex positions
		// https://cplusplus.com/reference/string/string/substr/
		if (line.substr(0,2) == "v ")
		{
			// read position of vertex
			std::istringstream sstream{ line.substr(2) };
			glm::vec3 position;
			sstream >> position.x;
			// TODO: stream in position y
			// TODO: stream in position z
			sstream >> position.y;
			sstream >> position.z;

			// TODO: add position to vertices vector
			vertices.push_back(position);
		}
		// read in faces (triangles)
		else if (line.substr(0,2) == "f ")
		{
			// read face (triangle), index of vertex position in vertices array [1, 2, 3]
			std::istringstream sstream{ line.substr(2) };
			std::string str;
			// https://en.cppreference.com/w/cpp/string/basic_string/getline
			while (std::getline(sstream, str, ' '))
			{
				std::istringstream sstream(str);
				std::string indexString;

				// read each triangle index (position, normal, uv)
				size_t i = 0;
				unsigned int index[3] = { 0, 0, 0 }; // 0 = position, 1 = normal, 2 = uv
				while (std::getline(sstream, indexString, '/'))
				{
					if (!indexString.empty())
					{
						std::istringstream indexStream{ indexString };
						// TODO: stream indexStream into index[i]
						indexStream >> index[i];

					}
					i++;
				}

				// check if index 0 (position) is valid
				if (index[0])
				{
					// get vertex at index position
					// index is 1 based, need to subtract one for array
					glm::vec3 position = vertices[index[0] - 1];

					// TODO: add position to m_vertices
					m_vertices.push_back(position);

				}
			}
		}
	}

	// TODO: close stream
	stream.close();

	return true;
}
