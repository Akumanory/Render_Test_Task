// #include <SmoothPerVertexNormals/utils.h>
#include <SmoothPerVertexNormals/smooth_per_vertex_normals.h>

#include <cstdio>
#include <string>
#include <vector>
#include <iostream>

struct scenario_values {
    // name
    const char* scenarion_name;
    // test values
    std::vector<vec3> verts_vec;
    std::vector<int> faces_vec;

    // etalon normals
    std::vector<vec3> normals_vec_etalon;
};

// NOTE(akumanory): maybe another possible option would be 
// read test data from file 

// Test Data
std::vector<scenario_values> test_scenarious = {
    //  scenraio_1
    {
        //  name
        "scenario_1 - pyramid",
        // verts vec
        {
            {0, 0, 0},
            {0, 0, 1},
            {1, 0, 0},
            {0, 1, 0}
        },
        // faces vec
        {
            0, 2, 1,
            0, 3, 2,
            0, 1, 3,
            1, 2, 3
        },
        // etalon normals
        {
            {-0.577, -0.577, -0.577},
            {0, 0, 1},
            {1, 0, 0},
            {0, 1, 0}
        }
    },
    // scenraio_2
    {
        // name
        "scenario_2 - 2 perpendicular triangles",
        // verts vec
        {
            {0, 0, 0},
            {0, 0, 1},
            {1, 0, 0},
            {0, 1, 0}
        },
        // faces vec
        {
            0, 3, 2,
            0, 1, 3,
        },
        // etalon normals
        {
            {-0.707, 0, -0.707},
            {-1, 0, 0},
            {0, 0, -1},
            {-0.707, 0, -0.707}
        }
    },
};


bool normals_test(const scenario_values& data) {
    std::vector<vec3> out_normals_vec;
    out_normals_vec.resize(data.verts_vec.size());

    smooth_per_vertex_normals::calc_mesh_normals(
        out_normals_vec.data(),
        data.verts_vec.data(),
        data.faces_vec.data(),
        static_cast<int>(data.verts_vec.size()),
        static_cast<int>(data.faces_vec.size()));

    for (size_t i = 0; i < data.normals_vec_etalon.size(); i++) {
        if (data.normals_vec_etalon != out_normals_vec)
            return false;
    }

    return true;
}

int main() {
    for (const auto& scenario : test_scenarious) {
        std::cout << "Test " << scenario.scenarion_name << " ";
        if (normals_test(scenario))
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }

    return 0;
}
