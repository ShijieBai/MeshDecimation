#include "pmp_test.h"

void pmp_test::pmp_test(const std::string &input_file, const std::string &out_file, const double &angle) {
    auto time0 = std::chrono::steady_clock::now();
    pmp::SurfaceMesh mesh;
    pmp::read(mesh, input_file);
	
    int nv = mesh.n_vertices();
    pmp::decimate(mesh, nv * 0.3);

     //pmp::decimate(mesh,
     //             nv * 0.3, // target vertices
     //        8.0,    // aspect ratio
     //        0.0,
     //        12,                    // max valence
     //             angle, // normal deviation
     //        0.0);


    pmp::write(mesh, out_file);

   

        std::cout
        << "decimated V: " << mesh.n_vertices() << " F: " << mesh.n_faces() << std::endl;

    auto time1 = std::chrono::steady_clock::now();

    double seconds =
        (double)std::chrono::duration_cast<std::chrono::milliseconds>(time1 - time0).count() / 1000.0;

    std::cout << "OpenMeshºÄÊ±£º " << seconds << " s." << std::endl;
}