#pragma once
#include "../class/geometry.h"
#include "../header/array.h"
#include "../header/glm.h"
#include "geometry.h"
#include <memory>
#include <vector>

namespace rtx {
namespace bvh {
    namespace scene {
        class Node {
        public:
            bool _is_leaf;
            int _id;
            std::vector<int> _assigned_object_indices;
            std::shared_ptr<geometry::GeometryBVH> _geometry_bvh;
            glm::vec4f _aabb_min;
            glm::vec4f _aabb_max;
            Node(std::vector<int> assigned_object_indices, std::vector<std::shared_ptr<Geometry>>& geometry_array);
            std::unique_ptr<Node> _left;
            std::unique_ptr<Node> _right;
            std::vector<int>& object_ids();
        };
        class SceneBVH {
        public:
            SceneBVH(std::vector<std::shared_ptr<Geometry>>& geometry_array);
            std::unique_ptr<Node> _root;
            void split(const std::unique_ptr<Node>& parent);
            rtx::array<float> serialize();
        };
    }
}
}