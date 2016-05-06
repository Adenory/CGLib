#include "PMDFile.h"


#include "../Polygon/PolygonObject.h"
#include "../Polygon/ActorObject.h"
#include "../Polygon/Bone.h"
#include "../Polygon/Joint.h"
#include "../Polygon/CGModel.h"

#include <ostream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Polygon;
using namespace Crystal::IO;

namespace {
	//void read( stream, )
}

PMDHeader::PMDHeader() :
version(1.0f)
{
}


/*
namespace {
	std::string readChar(std::istream& stream, int howMany)
	{
		std::vector<char> str(howMany);
		stream.read(str.data(), howMany);
	}
}*/

bool PMDHeader::read(std::istream& stream)
{
	char magic[3];
	stream.read(magic, 3);
	//assert(magic == "Pmd");
	stream.read((char*)&version, sizeof(version));
	stream.read(modelName, sizeof(modelName));
	stream.read(comment, sizeof(comment));
	return stream.good();
}


bool PMDHeader::write(std::ostream& stream) const
{
	stream.write("Pmd", 3);
	stream.write((char *)&version, sizeof(version));
	stream.write(modelName, 20);
	stream.write(comment, 256);
	return stream.good();
}

PMDVertex::PMDVertex(const Vertex& v)
{
	this->pos = v.getPosition();
	this->normal = v.getNormal();
	this->texCoord = Vector2d<float>( v.getTexCoord().getX(), v.getTexCoord().getY() );
}

Vertex PMDVertex::toVertex(const unsigned int id)
{
	Vector3d<float> t(this->texCoord.getX(), this->texCoord.getY(), 0.0f);
	return Vertex(id, this->pos, this->normal, t);
}

PMDVertexCollection::PMDVertexCollection(const VertexCollection& vs)
{
	for (auto v : vs) {
		PMDVertex pmdv(*v);
		vertices.push_back(pmdv);
	}
}

bool PMDVertex::read(std::istream& stream)
{
	float posx = 0.0f;
	stream.read((char*)&posx, sizeof(float));
	float posy = 0.0f;
	stream.read((char*)&posy, sizeof(float));
	float posz = 0.0f;
	stream.read((char*)&posz, sizeof(float));
	this->pos = Vector3d<float>(posx, posy, posz);

	float normx = 0.0f;
	stream.read((char*)&normx, sizeof(float));
	float normy = 0.0f;
	stream.read((char*)&normy, sizeof(float));
	float normz = 0.0f;
	stream.read((char*)&normz, sizeof(float));
	this->normal = Vector3d<float>(normx, normy, normz);

	float u = 0.0f;
	float v = 0.0f;
	stream.read((char*)&u, sizeof(u));
	stream.read((char*)&v, sizeof(v));
	texCoord = Vector2d<float>(u, v);

	stream.read((char*)&boneNumers[0], sizeof(boneNumers[0]));
	stream.read((char*)&boneNumers[1], sizeof(boneNumers[1]));
	stream.read((char*)&boneWeight, sizeof(boneWeight));
	stream.read((char*)&isEdge, sizeof(isEdge));

	return stream.good();
}

bool PMDVertex::write(std::ostream& stream) const
{
	const auto& poss = pos.toArray3();
	stream.write((char *)poss.data(), sizeof(poss));

	const auto& norms = normal.toArray3();
	stream.write((char *)norms.data(), sizeof(norms));

	float u = texCoord.getX();
	float v = texCoord.getY();
	stream.write((char*)&u, sizeof(u));
	stream.write((char*)&v, sizeof(v));

	stream.write((char*)&boneNumers[0], sizeof(boneNumers[0]));
	stream.write((char*)&boneNumers[1], sizeof(boneNumers[1]));
	stream.write((char*)&boneWeight, sizeof(boneWeight));
	stream.write((char*)&isEdge, sizeof(isEdge));

	return stream.good();
}

bool PMDVertexCollection::read(std::istream& stream)
{
	DWORD vertexCount = 0;
	stream.read((char*)&vertexCount, sizeof(vertexCount));
	for (DWORD i = 0; i < vertexCount; ++i) {
		PMDVertex vertex;
		vertex.read(stream);
		vertices.emplace_back(vertex);
	}
	return stream.good();
}

bool PMDVertexCollection::write(std::ostream& stream) const
{
	const auto vertexCount = static_cast<DWORD>(vertices.size());
	stream.write((char*)&vertexCount, sizeof(vertexCount));
	for (DWORD i = 0; i < vertexCount; ++i) {
		vertices[i].write(stream);
	}
	return stream.good();
}

PMDFaceCollection::PMDFaceCollection(const FaceCollection& fs)
{
	for (auto f : fs) {
		faces.push_back(f->getV1()->getId());
		faces.push_back(f->getV2()->getId());
		faces.push_back(f->getV3()->getId());
	}
}

bool PMDFaceCollection::read(std::istream& stream)
{
	DWORD vertexCount = 0;
	stream.read((char*)&vertexCount, sizeof(vertexCount));
	for (DWORD i = 0; i < vertexCount; ++i) {
		unsigned short vindex = 0;
		stream.read((char*)&vindex, sizeof(vindex));
		faces.push_back(vindex);
	}
	return stream.good();
}

bool PMDFaceCollection::write(std::ostream& stream) const
{
	DWORD vertexCount = 0;
	stream.write((char*)&vertexCount, sizeof(vertexCount));
	for (DWORD i = 0; i < vertexCount; ++i) {
		unsigned short vindex = faces[i];
		stream.write((char*)&vindex, sizeof(vindex));
	}
	return stream.good();
}


bool PMDMaterial::read(std::istream& stream)
{
	float red = 0.0f;
	float green = 0.0f;
	float blue = 0.0f;
	float alpha = 0.0f;
	stream.read((char*)&red, sizeof(red));
	stream.read((char*)&green, sizeof(green));
	stream.read((char*)&blue, sizeof(blue));
	stream.read((char*)&alpha, sizeof(alpha));
	diffuse = ColorRGBA<float>(red, green, blue, alpha);
	stream.read((char*)&specularity, sizeof(specularity));

	stream.read((char*)&red, sizeof(red));
	stream.read((char*)&green, sizeof(green));
	stream.read((char*)&blue, sizeof(blue));
	specular = ColorRGBA<float>(red, green, blue, 1.0f);

	stream.read((char*)&red, sizeof(red));
	stream.read((char*)&green, sizeof(green));
	stream.read((char*)&blue, sizeof(blue));
	ambient = ColorRGBA<float>(red, green, blue, 1.0f);

	stream.read((char*)&toonIndex, sizeof(toonIndex));
	stream.read((char*)&isEdge, sizeof(isEdge));
	stream.read((char*)&faceVertexCount, sizeof(faceVertexCount));
	
	stream.read(textureFileName, sizeof(textureFileName));

	return stream.good();
}

bool PMDMaterial::write(std::ostream& stream) const
{
	float red = diffuse.getRed();
	float green = diffuse.getGreen();
	float blue = diffuse.getBlue();
	float alpha = diffuse.getAlpha();
	stream.write((char*)&red, sizeof(red));
	stream.write((char*)&green, sizeof(green));
	stream.write((char*)&blue, sizeof(blue));
	stream.write((char*)&alpha, sizeof(alpha));

	red = specular.getRed();
	green = specular.getGreen();
	blue = specular.getBlue();
	stream.write((char*)&red, sizeof(red));
	stream.write((char*)&green, sizeof(green));
	stream.write((char*)&blue, sizeof(blue));

	red = ambient.getRed();
	green = ambient.getGreen();
	blue = ambient.getBlue();
	stream.write((char*)&red, sizeof(red));
	stream.write((char*)&green, sizeof(green));
	stream.write((char*)&blue, sizeof(blue));

	stream.write((char*)&toonIndex, sizeof(toonIndex));
	stream.write((char*)&isEdge, sizeof(isEdge));
	stream.write((char*)&faceVertexCount, sizeof(faceVertexCount));

	stream.write(textureFileName, sizeof(textureFileName));

	return stream.good();
}

bool PMDMaterialCollection::read(std::istream& stream)
{
	int materialCount = 0;
	stream.read((char*)&materialCount, sizeof(materialCount));
	for (auto i = 0; i < materialCount; ++i) {
		PMDMaterial material;
		material.read(stream);
		materials.emplace_back(material);
	}
	return stream.good();
}

bool PMDMaterialCollection::write(std::ostream& stream) const
{
	int materialCount = static_cast<int>(materials.size());
	stream.write((char*)&materialCount, sizeof(materialCount));
	for (auto& m : materials) {
		m.write(stream);
	}
	return stream.good();
}

bool PMDBone::read(std::istream& stream)
{
	stream.read(name, sizeof(name));
	stream.read((char*)&parentBoneIndex, sizeof(parentBoneIndex));
	stream.read((char*)&tailBoneIndex, sizeof(tailBoneIndex));
	stream.read((char*)&type, sizeof(type));
	stream.read((char*)&ikParentBoneIndex, sizeof(ikParentBoneIndex));

	float posx = 0.0f;
	stream.read((char*)&posx, sizeof(float));
	float posy = 0.0f;
	stream.read((char*)&posy, sizeof(float));
	float posz = 0.0f;
	stream.read((char*)&posz, sizeof(float));
	this->boneHeadPos = Vector3d<float>(posx, posy, posz);
	return stream.good();
}

bool PMDBone::write(std::ostream& stream) const
{
	stream.write(name, sizeof(name));
	stream.write((char*)&parentBoneIndex, sizeof(parentBoneIndex));
	stream.write((char*)&tailBoneIndex, sizeof(tailBoneIndex));
	stream.write((char*)&type, sizeof(type));
	stream.write((char*)&ikParentBoneIndex, sizeof(ikParentBoneIndex));

	float posx = boneHeadPos.getX();
	stream.write((char*)&posx, sizeof(float));
	float posy = boneHeadPos.getY();
	stream.write((char*)&posy, sizeof(float));
	float posz = boneHeadPos.getZ();
	stream.write((char*)&posz, sizeof(float));
	return stream.good();
}


/*
Bone PMDBone::toActorBone() const
{
	Bone bone()
}
*/

Joint PMDBone::toJoint() const
{
	return Joint(boneHeadPos);
}

bool PMDBoneCollection::read(std::istream& stream)
{
	short int boneCount = 0;
	stream.read((char*)&boneCount, sizeof(boneCount));
	for (auto i = 0; i < boneCount; ++i) {
		PMDBone bone;
		bone.read(stream);
		bones.emplace_back(bone);
	}
	return stream.good();
}

bool PMDBoneCollection::write(std::ostream& stream) const
{
	short int boneCount = static_cast<short int>( bones.size() );
	stream.write((char*)&boneCount, sizeof(boneCount));
	for (auto i = 0; i < boneCount; ++i) {
		bones[i].write(stream);
	}
	return stream.good();
}


bool PMDBoneCollection::readEnglishNames(std::istream& stream)
{
	for (int i = 0; i < bones.size(); ++i) {
		char boneName[20];
		stream.read(boneName, sizeof(boneName));
		englishNames.emplace_back(boneName);
	}
	return stream.good();
}


ActorObject* PMDBoneCollection::toActorObject() const
{
	ActorObject* object = new ActorObject();
	std::vector<Joint*> joints;
	for (size_t i = 0; i < bones.size(); ++i) {
		//vertices.push_back(new Vertex());
		//bones[i].toJoint();
		auto j = object->createJoint(bones[i].boneHeadPos);
		joints.emplace_back(j);
	}
	for (size_t i = 0; i < bones.size(); ++i) {
		const auto parentBoneIndex = bones[i].parentBoneIndex;
		Joint* headJoint = nullptr;
		if (parentBoneIndex != 0xFFFF) {
			headJoint = joints[parentBoneIndex];
		}
		const auto tailBoneIndex = bones[i].tailBoneIndex;
		Joint* tailJoint = nullptr;
		if (tailBoneIndex != 0xFFFF) {
			if (tailBoneIndex != 0) {
				tailJoint = joints[tailBoneIndex];
			}
		}
		object->createBone(headJoint, tailJoint);
	}
	return object;
}

bool PMDIK::read(std::istream& stream)
{
	stream.read((char*)&boneIndex, sizeof(boneIndex));
	stream.read((char*)&targetBoneIndex, sizeof(targetBoneIndex));
	stream.read((char*)&childrenNumber, sizeof(childrenNumber));
	stream.read((char*)&iterationNumber, sizeof(iterationNumber));
	stream.read((char*)&limitAngle, sizeof(limitAngle));
	for (int i = 0; i < childrenNumber; ++i) {
		unsigned short childBoneIndex;
		stream.read((char*)&childBoneIndex, sizeof(childBoneIndex));
		childBoneIndices.emplace_back(childBoneIndex);
	}

	return stream.good();
}

bool PMDIK::write(std::ostream& stream) const
{
	stream.write((char*)&boneIndex, sizeof(boneIndex));
	stream.write((char*)&targetBoneIndex, sizeof(targetBoneIndex));
	stream.write((char*)&childrenNumber, sizeof(childrenNumber));
	stream.write((char*)&iterationNumber, sizeof(iterationNumber));
	stream.write((char*)&limitAngle, sizeof(limitAngle));
	for (int i = 0; i < childBoneIndices.size(); ++i) {
		unsigned short childBoneIndex = childBoneIndices[i];
		stream.write((char*)&childBoneIndex, sizeof(childBoneIndex));
	}

	return stream.good();
}

bool PMDIKCollection::read(std::istream& stream)
{
	unsigned short ikCount = 0;
	stream.read((char*)&ikCount, sizeof(ikCount));
	for (auto i = 0; i < ikCount; ++i) {
		PMDIK ik;
		ik.read(stream);
		iks.emplace_back(ik);
	}

	return stream.good();
}

bool PMDIKCollection::write(std::ostream& stream) const
{
	unsigned short ikCount = 0;
	stream.write((char*)&ikCount, sizeof(ikCount));
	for (auto i = 0; i < ikCount; ++i) {
		iks[i].write(stream);
	}
	return stream.good();
}

bool PMDSkinVertex::read(std::istream& stream)
{
	stream.read((char*)&vertexIndex, sizeof(vertexIndex));
	stream.read((char*)&position, sizeof(position));
	return stream.good();
}

bool PMDSkinVertex::write(std::ostream& stream) const
{
	stream.write((char*)&vertexIndex, sizeof(vertexIndex));
	stream.write((char*)&position, sizeof(position));
	return stream.good();
}


bool PMDSkin::read(std::istream& stream)
{
	stream.read(name, sizeof(name));
	stream.read((char*)&vertexCount, sizeof(vertexCount));
	stream.read(&type, sizeof(type));
	for (unsigned int i = 0; i < vertexCount; ++i) {
		PMDSkinVertex skinVertex;
		skinVertex.read(stream);
		skinVertices.emplace_back(skinVertex);
		
		//if (type == 0) {

		//}
	}
	return stream.good();
}

bool PMDSkin::write(std::ostream& stream) const
{
	stream.write(name, sizeof(name));
	stream.write((char*)&vertexCount, sizeof(vertexCount));
	stream.write(&type, sizeof(type));
	for (unsigned int i = 0; i < vertexCount; ++i) {
		skinVertices[i].write(stream);
	}
	return stream.good();

}

bool PMDSkinCollection::read(std::istream& stream)
{
	WORD skinCount = 0;
	stream.read((char*)&skinCount, sizeof(skinCount));
	for (unsigned int i = 0; i < skinCount; ++i) {
		PMDSkin skin;
		skin.read(stream);
		skins.emplace_back(skin);
	}
	return stream.good();
}

bool PMDSkinCollection::write(std::ostream& stream) const
{
	WORD skinCount = static_cast<WORD>(skins.size());
	for (unsigned int i = 0; i < skinCount; ++i) {
		skins[i].write(stream);
	}
	return stream.good();
}


bool PMDDisplayBone::read(std::istream& stream)
{
	stream.read((char*)&boneIndex, sizeof(boneIndex));
	stream.read((char*)&dispFrameIndex, sizeof(dispFrameIndex));
	return stream.good();
}

bool PMDNamesInEnglish::read(std::istream& stream)
{
	BYTE englishNameCompatibility;
	stream.read((char*)&englishNameCompatibility, sizeof(englishNameCompatibility));
	char modelNameInEnglish[20];
	stream.read(modelNameInEnglish, sizeof(modelNameInEnglish));
	char commentInEnglish[256];
	stream.read(commentInEnglish, sizeof(commentInEnglish));

	/*
	unsigned char boneCount;
	stream.read((char*)&boneCount, sizeof(boneCount));
	for (int i = 0; i < boneCount; ++i) {
		char boneName[20];
		stream.read(boneName, sizeof(boneName));
		boneNamesInEnglish.emplace_back(boneName);
	}

	unsigned char skinCount = 16;
	//stream.read((char*)&skinCount, sizeof(skinCount));
	for (int i = 0; i < skinCount - 1; ++i) {
		char skinName[20];
		stream.read(skinName, sizeof(skinName));
		skinNamesInEnglish.emplace_back(skinName);
	}

	unsigned char boneDispCount = 0;
	stream.read((char*)boneDispCount, sizeof(boneDispCount));
	for (int i = 0; i < boneDispCount; ++i) {
		char name[50];
		stream.read(name, sizeof(name));
		boneDispNames.emplace_back(name);
	}
	*/
	return stream.good();
}

#include <fstream>

bool PMDRigidBody::read(std::istream& stream)
{
	stream.read(name, sizeof(name));
	stream.read((char*)&relatedBoneIndex, sizeof(relatedBoneIndex));
	stream.read((char*)&groupIndex, sizeof(groupIndex));
	stream.read((char*)&groupTarget, sizeof(groupTarget));
	stream.read((char*)&shapeType, sizeof(shapeType));
	stream.read((char*)&width, sizeof(width));
	stream.read((char*)&height, sizeof(height));
	stream.read((char*)&depth, sizeof(depth));
	stream.read((char*)&position, sizeof(position));
	stream.read((char*)&rotation, sizeof(rotation));
	stream.read((char*)&weight, sizeof(weight));
	stream.read((char*)&translateDumpingCoe, sizeof(translateDumpingCoe));
	stream.read((char*)&rotationDumpingCoe, sizeof(rotationDumpingCoe));
	stream.read((char*)&repulse, sizeof(repulse));
	stream.read((char*)&friction, sizeof(friction));
	stream.read((char*)&rigidType, sizeof(rigidType));
	return stream.good();
}

bool PMDRigidJoint::read(std::istream& stream)
{
	stream.read(name,sizeof(name));
	stream.read((char*)&rigidIndex1, sizeof(rigidIndex1));
	stream.read((char*)&rigidIndex2, sizeof(rigidIndex2));
	stream.read((char*)&position, sizeof(position));
	stream.read((char*)&rotation, sizeof(rotation));
	stream.read((char*)&constrainPosition1, sizeof(constrainPosition1));
	stream.read((char*)&constrainPosition2, sizeof(constrainPosition2));
	stream.read((char*)&constrainAngle1, sizeof(constrainAngle1));
	stream.read((char*)&constrainAngle2, sizeof(constrainAngle2));
	stream.read((char*)&springPosition, sizeof(springPosition));
	stream.read((char*)&springRotation, sizeof(springRotation));
	return stream.good();
}



PMDFile::PMDFile(const PolygonObject& polygon)
{
	vertices = PMDVertexCollection( polygon.getVertices() );
	faces = PMDFaceCollection(polygon.getFaces());
	/*
	const auto& fs = polygon.getFaces();
	for (auto f : fs) {
		 faces.push_back( f->getV1()->getId() );
		 faces.push_back( f->getV2()->getId() );
		 faces.push_back( f->getV3()->getId() );
	}
	*/
}


bool PMDFile::read(const std::string& filename)
{
	std::ifstream stream(filename, std::ios::binary);
	if (!stream.is_open()) {
		return false;
	}
	header.read(stream);
	vertices.read(stream);
	faces.read(stream);
	materials.read(stream);

	bones.read(stream);
	iks.read(stream);
	skins.read(stream);

	BYTE displaySkinCount = 0;
	stream.read((char*)&displaySkinCount, sizeof(displaySkinCount));
	for (unsigned int i = 0; i < displaySkinCount; ++i) {
		WORD skinIndex;
		stream.read((char*)&skinIndex, sizeof(skinIndex));
		displaySkinIndices.push_back(skinIndex);
	}

	BYTE displayBoneCount = 0;
	stream.read((char*)&displayBoneCount, sizeof(displayBoneCount));
	for (unsigned int i = 0; i < displayBoneCount; ++i) {
		char dispName[50];
		stream.read((char*)&dispName, sizeof(dispName));
		displayBoneNames.push_back(dispName);
	}

	DWORD displayBonesCount = 0;
	stream.read((char*)&displayBonesCount, sizeof(displayBonesCount));
	for (unsigned int i = 0; i < displayBonesCount; ++i) {
		PMDDisplayBone dispBone;
		dispBone.read(stream);
		displayBones.emplace_back(dispBone);
	}

	namesInEnglish.read(stream);
	bones.readEnglishNames(stream);

	std::vector<std::string> skinNamesInEnglish;
	for (int i = 0; i < skins.size() - 1; ++i) {
		char skinName[20];
		stream.read(skinName, sizeof(skinName));
		skinNamesInEnglish.emplace_back(skinName);
	}

	std::vector<std::string> displayBoneNamesInEnglish;
	for (int i = 0; i < displayBoneCount; ++i) {
		char skinName[50];
		stream.read(skinName, sizeof(skinName));
		displayBoneNamesInEnglish.emplace_back(skinName);
	}

	for (int i = 0; i < 10; ++i) {
		char toonTextureFileName[100];
		stream.read(toonTextureFileName, sizeof(toonTextureFileName));
		toonTextureFileNames.emplace_back(toonTextureFileName);
	}

	DWORD rigidBodyCount = 0;
	stream.read((char*)&rigidBodyCount, sizeof(rigidBodyCount));
	for (unsigned int i = 0; i < rigidBodyCount; ++i) {
		PMDRigidBody rigidBody;
		rigidBody.read(stream);
		rigidBodies.emplace_back(rigidBody);
	}

	DWORD rigidJointCount = 0;
	stream.read((char*)&rigidJointCount, sizeof(rigidJointCount));
	for (unsigned int i = 0; i < rigidJointCount; ++i) {
		PMDRigidJoint joint;
		joint.read(stream);
		rigidJoints.emplace_back(joint);
	}

	return stream.good();
}

bool PMDFile::write(const std::string& filename) const
{
	std::ofstream stream(filename, std::ios::binary);
	if (!stream.is_open()) {
		return false;
	}
	header.write(stream);
	vertices.write(stream);
	faces.write(stream);
	materials.write(stream);

	bones.write(stream);
	iks.write(stream);
	skins.write(stream);
	return false;
}


/*
void PMDFile::add(const ActorObject& actor)
{
	actor.get
}
*/

PolygonObject* PMDFile::toPolygonObject() const
{
	PolygonObject* object = new PolygonObject();
	auto vs = this->vertices.get();
	for (size_t i = 0; i < vs.size(); ++i ) {
		object->createVertex(vs[i].pos, vs[i].normal);
	}
	auto is = this->faces.get();
	for (size_t i = 0; i < is.size(); i+=3 ) {
		object->createFace(is[i], is[i + 1], is[i + 2]);
	}
	return object;
}

ActorObject* PMDFile::toActorObject() const
{
	return bones.toActorObject();
}

CGModel* PMDFile::toCGModel() const
{
	return new CGModel(toPolygonObject(), toActorObject());
}
