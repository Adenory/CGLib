#ifndef __CRYSTAL_GRAPHICS_MARCHING_CUBE_H__
#define __CRYSTAL_GRAPHICS_MARCHING_CUBE_H__


#include "PolygonReduction.h"
#include "../Math/Triangle.h"
#include "../Math/Vector3d.h"
#include "../Util/UnCopyable.h"
#include "../Math/MarchingCubeTable.h"
#include <vector>
#include <array>

namespace Crystal {
	namespace Math {
		template<typename, typename>
		class Volume3d;

		template<typename, typename>
		class VolumeCell3d;
	}

	namespace Graphics {
		namespace Experiment {

	class MarchingCube final : UnCopyable
	{
	public:
		MarchingCube() {
			table.buildEdgeTable();
			table.buildTriangleTable();
		}

		~MarchingCube() = default;

		void march(const Math::Volume3d<float, float>& volume, const float isolevel) const;

		TriangleMesh getMesh() const { return mesh; }

	private:
		Math::MarchingCubeTable table;
		TriangleMesh mesh;

		std::vector<TriangleFace> build(const Math::VolumeCell3d<float, float>& cell, const float isolevel);

		std::vector<TriangleFace> build(const int cubeindex, const std::array<std::shared_ptr<Vertex>, 12>& vertices);

		int getCubeIndex(const std::array< float, 8 >& val, const float isolevel) const;

		std::array< std::shared_ptr<Vertex>, 12 > getPositions(const int cubeindex, const Math::VolumeCell3d<float, float>& cell, const float isolevel);

	};
		}
	}
}

#endif