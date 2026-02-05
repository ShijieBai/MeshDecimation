#include "CGAL_test.h"
#include <chrono>

void cgal::CGAL_test(const std::string &input_file, const std::string &out_file, const double &angle) {
    auto time0 = std::chrono::steady_clock::now();

    Mesh mesh;

    if (!CGAL::IO::read_STL(input_file, mesh)) {
        std::cerr << "Error: cannot read STL file\n";
        return;
    }

    auto is_constrained =
        mesh.add_property_map<boost::graph_traits<Mesh>::edge_descriptor, bool>("e:is_constrained", false)
            .first;

    auto third_vertex = [](Mesh::Halfedge_index h, const Mesh &mesh) -> Mesh::Vertex_index {
        return target(next(h, mesh), mesh);
    };

    for (auto e : edges(mesh)) {
        //  sharp edges
        auto h = halfedge(e, mesh);
        auto ho = opposite(h, mesh);

        auto f1 = face(h, mesh);
        auto f2 = face(ho, mesh);

        if (f1 == Mesh::null_face() || f2 == Mesh::null_face())
            continue;

        auto p = mesh.point(source(h, mesh));
        auto q = mesh.point(target(h, mesh));

        auto r = mesh.point(third_vertex(h, mesh));
        auto s = mesh.point(third_vertex(ho, mesh));

        double angle = CGAL::approximate_dihedral_angle(p, q, r, s);
        if (angle > angle)
            is_constrained[e] = true;
    }

     // Stop when reaching target number of edges
    std::size_t target_edges = mesh.number_of_edges() * 0.3; // keep 30%

    SMS::Edge_count_stop_predicate<Mesh> stop(target_edges);

    // default is QEM
    //std::size_t removed_edges = SMS::edge_collapse(mesh, stop, CGAL::parameters::all_default()); 

    // preserve the feature edge, inwhich defined by dihedral_angle
    std::size_t removed_edges =
        SMS::edge_collapse(mesh, stop, CGAL::parameters::edge_is_constrained_map(is_constrained)); 


    std::cout << "Simplification done:\n";
    std::cout << "  Removed edges: " << removed_edges << "\n";
    std::cout << "  Remaining faces: " << mesh.number_of_faces() << "\n";


    if (!CGAL::IO::write_STL(out_file, mesh)) {
        std::cerr << "Error: cannot write STL file\n";
        return;
    }

    std::cout << "Output written to " << out_file << "\n";
    auto time1 = std::chrono::steady_clock::now();

    double seconds = (double)std::chrono::duration_cast<std::chrono::milliseconds>(time1 - time0).count() / 1000.0;

    std::cout << "CGALºÄÊ±£º " << seconds << " s."<<std::endl;
}