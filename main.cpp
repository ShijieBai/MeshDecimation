#include "OpenMesh_test.h"
#include "CGAL_test.h"
#include "pmp_test.h"
#include <string>

int main() {

    std::string input_file = R"(D:\A-work\mesh\MeshDecimation\MeshDecimation\input\1.stl)";
    std::string out_file = R"(D:\A-work\mesh\MeshDecimation\MeshDecimation\output\1.stl)";

    double sharp_angle_deg = 45.0;
    double sharp_angle_rad = sharp_angle_deg * M_PI / 180.0;   // math defined

    // CGAL mesh decimation
     //cgal::CGAL_test(input_file, out_file, sharp_angle_rad);

    // OpenMesh mesh decimation
     //OpenMesh::OpenMesh_test(input_file, out_file, sharp_angle_rad);

     // pmp mesh decimation
     pmp_test::pmp_test(input_file, out_file, sharp_angle_rad);

    return 0;
}