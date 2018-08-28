#pragma once
#include "../../../class/ray.h"
#include "../../../class/renderer.h"
#include "../../options/ray_tracing.h"
#include <array>
#include <memory>
#include <pybind11/numpy.h>
#include <random>

namespace rtx {
class RayTracingCUDARenderer : public Renderer {
private:
    // host
    float* _rays;
    float* _faces;
    float* _vertices;
    float* _object_colors;
    int* _geometry_types;
    int* _material_types;
    float* _color_buffer;
    float* _bvh_hit_path;
    float* _bvh_miss_path;
    bool* _bvh_is_leaf;
    float* _bvh_geometry_type;
    float* _bvh_face_start_index;
    float* _bvh_face_end_index;
    // device
    float* _gpu_rays;
    float* _gpu_faces;
    float* _gpu_vertices;
    float* _gpu_object_colors;
    int* _gpu_geometry_types;
    int* _gpu_material_types;
    float* _gpu_color_buffer;
    float* _gpu_bvh_hit_path;
    float* _gpu_bvh_miss_path;
    bool* _gpu_bvh_is_leaf;
    float* _gpu_bvh_object_index;
    float* _gpu_bvh_face_start_index;
    float* _gpu_bvh_face_end_index;

    std::shared_ptr<Scene> _scene;
    std::shared_ptr<Camera> _camera;
    std::shared_ptr<RayTracingOptions> _options;

    void construct_bvh();
    void pack_objects();
    void allocate_mesh_buffer(int num_faces);
    void delete_mesh_buffer();

public:
    RayTracingCUDARenderer();
    void render(std::shared_ptr<Scene> scene,
        std::shared_ptr<Camera> camera,
        std::shared_ptr<RayTracingOptions> options,
        pybind11::array_t<float, pybind11::array::c_style> buffer);
    void render(std::shared_ptr<Scene> scene,
        std::shared_ptr<Camera> camera,
        std::shared_ptr<RayTracingOptions> options,
        unsigned char* buffer,
        int height,
        int width,
        int channels);
};
}