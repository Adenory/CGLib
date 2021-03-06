#ifndef __CRYSTAL_IO_PMD_FILE_H__
#define __CRYSTAL_IO_PMD_FILE_H__

#include <vector>
#include "../Math/Vector3d.h"
#include "../Graphics/ColorRGBA.h"

namespace Crystal {
	namespace Core {
		class Vertex;
		class VertexRepository;
		class PolygonMesh;
		class Actor;
		class Bone;
		class Joint;
		class CGModel;
	}
	namespace Graphics {
		class VisualPolygon;
		class Material;
		class MaterialMap;
	}
	namespace IO {

		using DWORD = unsigned long;
		using BYTE = unsigned char;
		using WORD = unsigned short;


struct PMDHeader
{
	PMDHeader();

	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

	bool readEnglishPart(std::istream& stream);

	bool writeEnglishPart(std::ostream& stream) const;

private:
	float version;
	char modelName[20];
	char comment[256];

	BYTE englishNameCompatibility;
	char modelNameInEnglish[20];
	char commentInEnglish[256];


};

class PMDVertex
{
public:
	PMDVertex() = default;

	PMDVertex(const Core::Vertex& v);

	Core::Vertex toVertex(const unsigned int id);

	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

public:
	Math::Vector3d<float> pos;
	Math::Vector3d<float> normal;
	Math::Vector2d<float> texCoord;
	std::array< unsigned short, 2> boneNumers;
	char boneWeight; // [0,100]
	char isEdge;

};

class PMDVertexCollection
{
public:
	PMDVertexCollection() = default;

	PMDVertexCollection(const Core::VertexRepository& vs);

	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

	std::vector<PMDVertex> get() const { return vertices; }

private:
	std::vector<PMDVertex> vertices;
};


class PMDFaceCollection
{
public:
	PMDFaceCollection() = default;

	PMDFaceCollection(const Core::FaceRepository& faces);

	bool read(std::istream& stream);

	bool write(std::ostream& stream, DWORD vertexCount) const;

	std::vector<WORD> get() const { return faces; }

private:
	std::vector<WORD> faces;
};


class PMDMaterial
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

	Graphics::Material toMaterial(const std::string& folderName) const;

	unsigned int getFaceVertexCount() const { return faceVertexCount; }

private:
	Graphics::ColorRGBA<float> diffuse;
	float specularity;
	Graphics::ColorRGBA<float> specular;
	Graphics::ColorRGBA<float> ambient;
	unsigned char toonIndex;
	unsigned char isEdge;
	unsigned int faceVertexCount;
	char textureFileName[20];
};

class PMDMaterialCollection
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

	std::vector<Graphics::MaterialMap> toMaterialMap(const std::string& foldername) const;

private:
	std::vector<PMDMaterial> materials;
};

enum class PMDBoneType
{
	ROTATE = 0,
	ROTATE_AND_TRANSLATE = 1,
	IK = 2,
	UNKNOWN = 3,
	UNDER_IK = 4,
	UNDERO_ROTATION = 5,
	IK_DEST = 6,
	INVISIBLE = 7,
	STRAIN = 8,
	ROTATION_MOVE = 9
};

class PMDBone
{
public:
	PMDBone() = default;

	explicit PMDBone(const Core::Bone& bone);

	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

	bool readEnglishName(std::istream& stream);

	bool writeEnglishName(std::ostream& stream) const;

	Core::Bone toBone() const;

	Core::Joint toJoint() const;

	char name[20];
	char englishName[20];

	unsigned short parentBoneIndex;
	unsigned short tailBoneIndex;
	char type;
	unsigned short ikParentBoneIndex;
	Math::Vector3d<float> boneHeadPos;
};

class PMDBoneCollection
{
public:
	PMDBoneCollection()
	{}

	explicit PMDBoneCollection(const Core::Actor& actor);

	explicit PMDBoneCollection(const std::vector<PMDBone>& bones) :
		bones(bones)
	{}

	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

	bool readEnglishNames(std::istream& stream);

	bool writeEnglishNames(std::ostream& stream) const;

	Core::Actor* toActorObject() const;

	//size_t getSize() const { return bones.size(); }

private:
	std::vector<PMDBone> bones;
};

class PMDIK
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

private:
	WORD boneIndex;
	WORD targetBoneIndex;
	BYTE childrenNumber;
	WORD iterationNumber;
	float limitAngle;
	std::vector<WORD> childBoneIndices;
};

class PMDIKCollection
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

private:
	std::vector<PMDIK> iks;
};

class PMDSkinVertex
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

private:
	DWORD vertexIndex;
	float position[3];
};

class PMDSkin
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

	enum class Type {
		Base = 0,
		EyeBrow = 1,
		Eye = 2,
		Lip = 3,
		Other = 4,
	};

private:
	char name[20];
	DWORD vertexCount;
	char type;
	std::vector<PMDSkinVertex> skinVertices;
};

class PMDSkinCollection
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

	bool readEnglishNames(std::istream& stream);

	bool writeEnglishNames(std::ostream& stream) const;

	size_t size() const { return skins.size(); }


private:
	std::vector<PMDSkin> skins;
	std::vector<std::string> englishNames;
};

class PMDDisplayBoneNameCollection
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

	bool readEnglishNames(std::istream& stream);

	bool writeEnglishNames(std::ostream& stream) const;

	size_t size() const { return names.size(); }

private:
	std::vector<std::string> names;
	std::vector<std::string> englishNames;
};

class PMDDisplaySkinCollection
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

private:
	std::vector<WORD> displaySkinIndices;
};

class PMDDisplayBone
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

private:
	WORD boneIndex;
	BYTE dispFrameIndex;
};


class PMDToonTextures
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;
private:
	std::array<std::string,10> toonTextureFileNames;

};

class PMDRigidBody
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

private:
	char name[20];
	WORD relatedBoneIndex;
	BYTE groupIndex;
	WORD groupTarget;
	BYTE shapeType;
	float width;
	float height;
	float depth;
	float position[3];
	float rotation[3];
	float weight;
	float translateDumpingCoe;
	float rotationDumpingCoe;
	float repulse;
	float friction;
	BYTE rigidType;
};

class PMDRigidBodyCollection
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

private:
	std::vector<PMDRigidBody> rigidBodies;
};

class PMDRigidJoint
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

private:
	char name[20];
	DWORD rigidIndex1;
	DWORD rigidIndex2;
	float position[3];
	float rotation[3];
	float constrainPosition1[3];
	float constrainPosition2[3];
	float constrainAngle1[3];
	float constrainAngle2[3];
	float springPosition[3];
	float springRotation[3];
};

class PMDRigidJointCollection
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

private:
	std::vector<PMDRigidJoint> joints;
};

class PMDDisplayBoneCollection
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

private:
	std::vector<PMDDisplayBone> displayBones;

};

class PMDFile
{
public:
	PMDFile() = default;

	PMDFile(const Graphics::VisualPolygon& object);

	//void add(const Polygon::PolygonObject& object);

	void add(const Core::Actor& actor);

	bool read(const std::string& filename);

	bool write(const std::string& filename) const;

	Core::PolygonMesh* toPolygonObject() const;

	Graphics::VisualPolygon toVisualPolygon() const;

	Core::Actor* toActorObject() const;

	Core::CGModel* toCGModel() const;

private:
	std::string filename;
	PMDHeader header;
	PMDVertexCollection vertices;
	PMDFaceCollection faces;
	PMDMaterialCollection materials;
	PMDBoneCollection bones;
	PMDIKCollection iks;
	PMDSkinCollection skins;
	PMDDisplaySkinCollection displaySkins;
	PMDDisplayBoneNameCollection displayBoneNames;
	PMDDisplayBoneCollection displayBones;
	PMDToonTextures toonTextures;
	PMDRigidBodyCollection rigidBodies;
	PMDRigidJointCollection rigidJoints;
};
	}
}

#endif
