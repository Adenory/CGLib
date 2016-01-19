#include "LegacySurfaceRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

namespace {
	GLfloat yellow[] = { 1.0, 0.0, 0.0, 1.0 };
}

void LegacySurfaceRenderer::render(const ICamera<float>& camera, const PointLight<float>& light, const TriangleBuffer& buffer)
{
	const auto& positions = buffer.positions.get();// buffers[0].get();
	const auto& normals = buffer.normals.get();//buffers[1].get();

	if (positions.empty()) {
		return;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	const auto& projectionMatrix = camera.getProjectionMatrix();
	const auto& modelviewMatrix = camera.getModelviewMatrix();;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(projectionMatrix.toArray().data());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(modelviewMatrix.toArray().data());

	glLightfv(GL_LIGHT0, GL_POSITION, light.getPos().toArray3().data());
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.getDiffuse().toArray4().data());

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, yellow);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, positions.data());

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normals.data());

	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(positions.size()) / 3);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_DEPTH_TEST);


	glFlush();

}