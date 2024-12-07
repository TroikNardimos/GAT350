# Computer Graphics Software Renderer

<img width="1280" alt="Screenshot 2024-12-04 235625" src="https://github.com/user-attachments/assets/1428e090-aa30-4e7d-be0a-d8abce2d8f7c">

## Introduction
This repository contains two projects: a **Software Renderer** and a **Ray Tracer**, both built from scratch in C++. These projects aim to provide an in-depth understanding of computer graphics by implementing key techniques such as shading, material handling, and post-processing without relying on hardware-accelerated APIs. The repository is an excellent resource for learning the fundamentals of rendering and ray tracing.

## Features
### Software Renderer
- **Triangle Rasterization**: Efficiently rasterizes triangles onto a 2D framebuffer.
- **Shader Support**: Implements basic and advanced shading models.
- **Lighting Techniques**: Supports both Gouraud and Phong shading.
- **Post-Processing**: Includes basic effects to enhance rendered images.

### Ray Tracer
- **Material Types**: Handles different materials like reflective, refractive, and diffuse surfaces.
- **Anti-Aliasing**: Improves image quality by reducing jagged edges.
- **Lighting Models**: Supports multiple light types for realistic illumination.

## Installation
### Prerequisites
Ensure you have the following dependencies installed:
- **SDL2**: For window and input management.
- **glm**: For mathematics operations (vectors and matrices).
- **C++ Compiler**: A modern compiler supporting C++17 or later.
- **Visual Studio** (or another IDE): Recommended for project setup and debugging.

### Build Instructions
1. Clone the repository:
   ```bash
   git clone https://github.com/TroikNardimos/GAT350.git
   cd GAT350
   ```
2. Install dependencies (e.g., using a package manager like vcpkg):
   ```bash
   vcpkg install sdl2 glm
   ```
3. Open the project in Visual Studio:
   - Load the `.sln` file from the root directory.
   - Configure the build settings (Release/Debug) and target platform.
4. Build the project using Visual Studio’s build system.

## Usage
### Software Renderer
Run the software renderer executable:
```bash
./2D
```
This project processes a set of triangles and applies rasterization, shading, and post-processing. Configuration options are defined in the source code.

### Ray Tracer
Run the ray tracer executable:
```bash
./RayTracer
```
Specify scene settings and material properties in the configuration file or source code to generate high-quality ray-traced images.

## Technical Details
### Shader Support
The software renderer includes programmable shaders for applying shading models like Gouraud and Phong. These shaders operate per-vertex or per-pixel to calculate lighting and color.

### Lighting Techniques
- **Gouraud Shading**: Computes lighting at vertices and interpolates across the triangle.
- **Phong Shading**: Computes lighting per-pixel for smoother and more realistic results.

### Material Types and Anti-Aliasing
The ray tracer supports:
- **Diffuse Materials**: For basic matte surfaces.
- **Reflective Materials**: Simulates mirror-like reflections.
- **Refractive Materials**: Handles light bending through transparent objects.
- **Anti-Aliasing**: Reduces aliasing artifacts by sampling multiple rays per pixel.

## Visual Showcase
### Software Renderer
- Rendered models with **Gouraud Shading**:
  <img width="1279" alt="directional_light" src="https://github.com/user-attachments/assets/5e13723e-1242-4741-abcb-1af831b51e24">
- Rendered models with **Phong Shading**:
  <img width="1280" alt="phong" src="https://github.com/user-attachments/assets/339bd777-6dfe-4205-be65-cc966d1b2837">
- Post-Processed Scenes:
  <img width="1280" alt="invert" src="https://github.com/user-attachments/assets/62da64a7-2697-47c0-b6d0-91aa6534ee46">

### Ray Tracer
- Scenes showcasing **reflective and refractive materials**:
  <img width="1280" alt="Screenshot 2024-11-06 204522" src="https://github.com/user-attachments/assets/39d7d5d1-26ca-4c3b-ae80-b86c2045cb21">
- Anti-Aliased Ray-Traced Scenes:
  <img width="1280" alt="Screenshot 2024-11-09 173016" src="https://github.com/user-attachments/assets/9c9b2eb1-8976-466c-ae6d-80486ac06fa6">

## Attribution
This project utilizes the following libraries and assets:
- **SDL2**: For windowing and input management.
- **glm**: For mathematical operations.
- Sample assets and reference models from free and open-source repositories.

## Conclusion
Explore the repository to learn more about graphics programming and rendering techniques. Contributions and suggestions for improvements are always welcome! Feel free to open issues or submit pull requests.
