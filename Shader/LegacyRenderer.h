#ifndef __CRYSTAL_SHADER_LEGACY_RENDERER_H__
#define __CRYSTAL_SHADER_LEGACY_RENDERER_H__



namespace Crystal {
	namespace Graphics {
		template<typename>
		class ICamera;
		template<typename>
		class PointLight;
		class PointBuffer;
		class PointIdBuffer;
		class LineBuffer;
		class LineIdBuffer;
		class TriangleBuffer;
		class TriangleIdBuffer;
	}
	namespace Shader {

class LegacyRenderer
{
public:
	void render(const Graphics::ICamera<float>& camera, const Graphics::PointBuffer& buffer, const float pointSize = 10.0f);

	void render(const Graphics::ICamera<float>& camera, const Graphics::PointIdBuffer& buffer);

	void renderAlphaBlend(const Graphics::ICamera<float>& camera, const Graphics::PointBuffer& buffer);

	void render(const Graphics::ICamera<float>& camera, const Graphics::LineBuffer& buffer, const GLfloat width);

	void render(const Graphics::ICamera<float>& camera, const Graphics::Line2dBuffer& buffer, const GLfloat width);

	void render(const Graphics::LineBuffer& buffer, const GLfloat width);

	void render(const Math::Matrix4d<float>& projectionMatrix, const Math::Matrix4d<float>& modelviewMatrix, const Graphics::LineBuffer& buffer, const GLfloat width);

	void render(const Math::Matrix4d<float>& projectionMatrix, const Math::Matrix4d<float>& modelviewMatrix, const Graphics::Line2dBuffer& buffer, const GLfloat width);

	void renderId(const Graphics::ICamera<float>& camera, const Graphics::LineIdBuffer& buffer);

	void render(const Graphics::ICamera<float>& camera, const Graphics::PointLight<float>& light, const Graphics::TriangleBuffer& buffer);

	//void render(const Graphics::ICamera<float>& camera, const Graphics::TriangleIdBuffer& buffer);

};

	}
}

#endif