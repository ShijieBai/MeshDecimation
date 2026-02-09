#pragma once
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Tools/Decimater/DecimaterT.hh>
#include <OpenMesh/Tools/Decimater/ModQuadricT.hh>

namespace OpenMesh {
    typedef OpenMesh::TriMesh_ArrayKernelT<> Mesh;

	void OpenMesh_test(const std::string &input_file, const std::string &out_file, const double &angle);

}
