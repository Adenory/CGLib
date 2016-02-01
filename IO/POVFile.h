#ifndef __CRYSTAL_IO_POV_FILE_H__
#define __CRYSTAL_IO_POV_FILE_H__

#include <string>

namespace Crystal {
	namespace Polygon {
		class TriangleMesh;
	}
	namespace IO {

class POVFile
{
public:
	bool writeScene(const std::string& file, const Polygon::TriangleMesh& surface);

	bool writeInc(const std::string& file, const Polygon::TriangleMesh& surface);
private:

};
	}
}

#endif