#pragma once

#include "utils.h"

using namespace utils;

namespace smooth_per_vertex_normals
{
    // C a l c u l a t e s m o o t h ( a v e r a g e ) p e r - ve rtex norm als
    //
    // [out] normals - output per - vertex normals
    // [in]  verts   - input per - vertex positions
    // [in]  faces   - triangles (triplet s of vertex indices)
    // [in]  nverts  - total number of vertices (# of elements in verts and normals arrays)
    // [in]  nfaces  - total number of faces (# of elements in faces array)
    //
    void calc_mesh_normals(
        vec3* normals,
        const vec3* verts,
        const int* faces,
        int nverts,
        int nfaces);

} // namespace smooth_per_vertex_normals
