#pragma once
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/IO/STL.h>
#include <CGAL/Polygon_mesh_processing/measure.h>
#include <CGAL/Polygon_mesh_processing/compute_normal.h>

#include <CGAL/Surface_mesh_simplification/edge_collapse.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Edge_count_stop_predicate.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Midpoint_placement.h>

namespace cgal {
    namespace SMS = CGAL::Surface_mesh_simplification;
    namespace PMP = CGAL::Polygon_mesh_processing;

    using Kernel = CGAL::Simple_cartesian<double>;
    using Point  = Kernel::Point_3;
    using Mesh =  CGAL::Surface_mesh<Point>;

    void CGAL_test(const std::string &input_file, const std::string& out_file, const double &angle);
}
