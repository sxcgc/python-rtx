#include "scene.h"

namespace rtx {
void Scene::add(std::shared_ptr<Mesh> mesh)
{
    _mesh_array.emplace_back(mesh);
    _updated = true;
}
bool Scene::updated()
{
    return _updated;
}
void Scene::set_updated(bool updated)
{
    _updated = updated;
}
}