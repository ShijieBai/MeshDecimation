#include "OpenMesh_test.h"

void OpenMesh::OpenMesh_test(const std::string &input_file,
                             const std::string &out_file,
                             const double &percent) {
    auto time0 = std::chrono::steady_clock::now();
    Mesh mesh;

    mesh.request_vertex_status();
    mesh.request_edge_status();
    mesh.request_face_status();
    mesh.request_face_normals();
    mesh.request_vertex_normals();
    mesh.update_face_normals();

    if (!OpenMesh::IO::read_mesh(mesh, input_file)) {
        std::cerr << "OpenMesh failed to read STL\n";
        return;
    }

    std::cout << "V: " << mesh.n_vertices() << " F: " << mesh.n_faces() << std::endl;

    // boundary edge
    //mesh.request_edge_status();
    //mesh.request_vertex_status();
    //mesh.request_face_status();

    //for (auto e : mesh.edges()) {
    //    if (mesh.is_boundary(e))
    //        mesh.status(e).set_locked(true);
    //}

   /* double sharp_cos = std::cos(angle);

    mesh.request_face_normals();
    mesh.update_face_normals();

    for (auto e : mesh.edges()) {
        if (mesh.is_boundary(e))
            continue;

        auto h0 = mesh.halfedge_handle(e, 0);
        auto h1 = mesh.halfedge_handle(e, 1);

        auto f0 = mesh.face_handle(h0);
        auto f1 = mesh.face_handle(h1);

        if (!f0.is_valid() || !f1.is_valid())
            continue;

        auto n0 = mesh.normal(f0);
        auto n1 = mesh.normal(f1);

        double cos_angle = OpenMesh::dot(n0, n1);

        if (cos_angle < sharp_cos)
            mesh.status(e).set_locked(true);
    }*/

    using Decimater = OpenMesh::Decimater::DecimaterT<Mesh>;
    using HModQuadric = OpenMesh::Decimater::ModQuadricT<Mesh>;
    using HModQuadricHandle = OpenMesh::Decimater::ModHandleT<HModQuadric>;

    using HNormal =  OpenMesh::Decimater::ModNormalFlippingT<Mesh>::Handle;
    using HAspect =  OpenMesh::Decimater::ModAspectRatioT<Mesh>::Handle;
    using HHausdorff =  OpenMesh::Decimater::ModHausdorffT<Mesh>::Handle;

    Decimater decimater(mesh);
    HModQuadricHandle hModQuadric;
    HNormal hnormal;
    HAspect haspect;
    HHausdorff hausdorff;
    decimater.add(hModQuadric);
    decimater.add(hnormal);
    decimater.add(haspect);
    decimater.add(hausdorff);

    decimater.module(hModQuadric).unset_max_err();
    decimater.module(hModQuadric).set_binary(false);

    decimater.module(hnormal).set_max_normal_deviation(20);

    decimater.module(haspect).set_binary(true);
    decimater.module(haspect).set_aspect_ratio(4);

    decimater.module(hausdorff).set_binary(true);
    //decimater.module(hausdorff).set_tolerance();    // 1e-4 * bdx_diag

    size_t num_v = mesh.n_vertices();
    size_t iter_count = 5;
    double r = std::pow(percent, 1.0 / iter_count);

    size_t current = num_v;
    for (int i = 0; i < iter_count; i++) {
        current = static_cast<size_t>(num_v * std::pow(r, i + 1));
        decimater.initialize();
        decimater.decimate_to(current);
        mesh.garbage_collection();
        mesh.update_normals();
    }

    std::cout << "decimated V: " << mesh.n_vertices() << " F: " << mesh.n_faces() << std::endl;

    OpenMesh::IO::write_mesh(mesh, out_file);

    auto time1 = std::chrono::steady_clock::now();

    double seconds =
        (double)std::chrono::duration_cast<std::chrono::milliseconds>(time1 - time0).count() / 1000.0;

    std::cout << "OpenMeshºÄÊ±£º " << seconds << " s." << std::endl;
}