/**
 * Texture
 */

#pragma once

#include "Synergy/Core/Settings.hpp"

namespace Synergy {


/// Specification of texture parameters.
struct TextureSpec {
	// Texture dimensions.
	GLuint width;
	GLuint height;
	GLuint depth;

	// Specifies the texture format as stored internally on the GPU.
	// (e.g. GL_R8, GL_RGB8, GL_RGBA, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL, ...).
	GLenum internalFormat;

	// Specifies the component format of pixel data to be uploaded to GL.
	// (e.g. GL_RED, GL_RGB, GL_RGBA, ...).
	GLenum format;

	// Specifies the pixel data type to be uploaded to GL
	// (e.g. GL_UNSIGNED_SHORT, GL_INT, GL_FLOAT, ...).
	GLenum dataType;
};


/// Class for encapsulating a texture object name with its texture parameters.
template <GLenum textureTarget>
class Texture {
public:
	static const GLenum type = textureTarget;

	/// Calls glGenTextures(...) to generate objName.
	Texture();

	/// Calls glDeleteTextures(...) using objName.
	~Texture();

	/// Binds objName to texture type by calling glBindTexture(...).
	void bind() const;

	/// Unbinds objName from it's associated texture target.
	void unbind() const;

	/// Allocates texture storage on the GPU.  If \c data is non-null, pixel data
	// pointed to by \c data is copied into texture storage.
	void allocateStorage (
			const TextureSpec & spec,
			const GLvoid * data = nullptr,
			GLint mipMaplevel = 0
	);

	/// Returns the texture object name generated by GL.
	GLuint name() const;

	/// Returns the texture pixel width.
	GLuint width() const;

	/// Returns the texture pixel height.
	GLuint height() const;

	/// Returns the texture pixel depth.
	GLuint depth() const;

	/// Returns the internal texture storage format.
	GLenum internalFormat() const;

	/// Returns the pixel data format.
	GLenum format() const;

	// Returns the pixel data type (e.g. GL_SHORT, GL_INT, GL_FLOAT, ...).
	GLenum dataType() const;


private:
	// Texture object name, created by GL when calling glGenTextures(...).
	GLuint objName;

	// Texture parameters and data type specifications
	TextureSpec textureSpec;

	void setTextureParameters(const TextureSpec & spec);

};


//-- Type Defines for various Texture Types:
typedef Texture<GL_TEXTURE_1D> Texture1D;
typedef Texture<GL_TEXTURE_2D> Texture2D;
typedef Texture<GL_TEXTURE_3D> Texture3D;
typedef Texture<GL_TEXTURE_1D_ARRAY> Texture1DArray;
typedef Texture<GL_TEXTURE_2D_ARRAY> Texture2DArray;
typedef Texture<GL_TEXTURE_RECTANGLE> TextureRectangle;
typedef Texture<GL_TEXTURE_CUBE_MAP> TextureCubeMap;
typedef Texture<GL_TEXTURE_CUBE_MAP> TextureCubeMap;
typedef Texture<GL_TEXTURE_CUBE_MAP_ARRAY> TextureCubeMapArray;
typedef Texture<GL_TEXTURE_BUFFER> TextureBuffer;
typedef Texture<GL_TEXTURE_2D_MULTISAMPLE> Texture2DMultisample;
typedef Texture<GL_TEXTURE_2D_MULTISAMPLE_ARRAY> Texture2DMultisampleArray;


} // end namespace Synergy

#include "Texture.inl"
