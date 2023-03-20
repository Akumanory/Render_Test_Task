#include "smooth_per_vertex_normals.h"
#include <stdexcept>

namespace smooth_per_vertex_normals
{
    void calc_mesh_normals(
        vec3* normals,
        const vec3* verts,
        const int* faces,
        int nverts,
        int nfaces)
    {
        if (nfaces % 3 != 0)
            std::runtime_error("nfaces is not a multiple of three");

        for (auto i = 0; i < nverts; i++)
            normals[i] = vec3();

        for (auto i = 0; i < nfaces; i = i + 3)
        {
            int P0_idx = faces[i];
            int P1_idx = faces[i + 1];
            int P2_idx = faces[i + 2];

            vec3 P1_P0 = verts[P1_idx] - verts[P0_idx];
            vec3 P2_P0 = verts[P2_idx] - verts[P0_idx];

            vec3 normal = vec3::cross_product(P1_P0, P2_P0);

            /// COMMENT - SECOND VARIAN FOR NORMAL CALCULATION
            /// formula with normalization, does not used (but can be viable, depends on requirements)
            // vec3 normal = vec3::cross_product(P1_P0, P2_P0) / vec3::cross_product(P1_P0, P2_P0).magnitude();

            normals[P0_idx] = normals[P0_idx] + normal;
            normals[P1_idx] = normals[P1_idx] + normal;
            normals[P2_idx] = normals[P2_idx] + normal;
        }

        for (auto i = 0; i < nverts; i++)
        {
            normals[i] = normals[i] / normals[i].magnitude();
        }
    }
} // namespace smooth_per_vertex_normals