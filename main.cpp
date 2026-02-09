#include "CGAL_test.h"
#include "OpenMesh_test.h"

int main() {

    std::string input_file = R"(D:\A-work\mesh\MeshDecimation\MeshDecimation\input\2.stl)";
    std::string out_file = R"(D:\A-work\mesh\MeshDecimation\MeshDecimation\output\2.stl)";

    double sharp_angle_deg = 45.0;
    double sharp_angle_rad = sharp_angle_deg * M_PI / 180.0;   // math defined

    // CGAL mesh decimation
     //cgal::CGAL_test(input_file, out_file, sharp_angle_rad);

    // OpenMesh mesh decimation
     OpenMesh::OpenMesh_test(input_file, out_file, sharp_angle_rad);


    return 0;
}