#include "standard.h"

namespace rtx {
namespace py = pybind11;
StandardGeometry::StandardGeometry()
{
}
StandardGeometry::StandardGeometry(pybind11::array_t<int, pybind11::array::c_style> np_face_vertex_indeces, pybind11::array_t<float, pybind11::array::c_style> np_vertices)
{
    if (np_face_vertex_indeces.ndim() != 2) {
        throw std::runtime_error("num_np_face_vertex_indeces.ndim() != 2");
    }
    if (np_vertices.ndim() != 2) {
        throw std::runtime_error("num_np_vertices.ndim() != 2");
    }
    int num_faces = np_face_vertex_indeces.shape(0);
    int num_vertices = np_vertices.shape(0);
    int ndim_vertex = np_vertices.shape(1);
    if (ndim_vertex != 4) {
        throw std::runtime_error("ndim_vertex != 4");
    }
    auto faces = np_face_vertex_indeces.mutable_unchecked<2>();
    auto vertices = np_vertices.mutable_unchecked<2>();
    for (int n = 0; n < num_faces; n++) {
        glm::vec<3, int> face = glm::vec<3, int>(faces(n, 0), faces(n, 1), faces(n, 2));
        _face_vertex_indices_array.emplace_back(face);
    }
    for (int n = 0; n < num_vertices; n++) {
        glm::vec3 vertex = glm::vec3(vertices(n, 0), vertices(n, 1), vertices(n, 2));
        _vertex_array.emplace_back(vertex);
    }
}
GeometryType StandardGeometry::type()
{
    return GeometryTypeStandard;
}
}