#include "texture.h"
#include "glcommon.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <cmath>

using namespace glwrapper;

Texture::Texture(GLenum type)
{
	GLCall(glCreateTextures(type, 1, &id));
}

Texture::Texture(GLenum type, const char* path)
{
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
	GLCall(glCreateTextures(type, 1, &id));
	if (GL_TEXTURE_2D == type)
	{
		GLuint internalFormat = 0;
		GLuint externalFormat = 0;
		if (3 == channels)
		{
			internalFormat = GL_RGB8;
			externalFormat = GL_RGB;
		}
		else if (4 == channels)
		{
			internalFormat = GL_RGBA8;
			externalFormat = GL_RGBA;
		}
		else if (1 == channels)
		{
			internalFormat = GL_R8;
			externalFormat = GL_RED;
		}
		int levels = static_cast<int>(std::log(std::fmax(width, height)) + 1);
		GLCall(glTextureStorage2D(id, levels, internalFormat, width, height));
		GLCall(glTextureSubImage2D(id, 0, 0, 0, width, height, externalFormat,
			GL_UNSIGNED_BYTE, data));
	}
	else if (GL_TEXTURE_3D == type)
	{
		// TODO: process 3D Texture
	}
	stbi_image_free(data);
}

void Texture::storage1d(GLsizei levels, GLenum internalformat, GLsizei width)
{
	GLCall(glTextureStorage1D(id, levels, internalformat, width));
}

void Texture::storage2d(GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
	GLCall(glTextureStorage2D(id, levels, internalformat, width, height));
}

void Texture::storage2d_multisample(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
	GLCall(glTextureStorage2DMultisample(id, samples, internalformat, width, height, fixedsamplelocations));
}

void Texture::storage3d(GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
{
	GLCall(glTextureStorage3D(id, levels, internalformat, width, height, depth));
}

void Texture::storage3d_multisample(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
	GLCall(glTextureStorage3DMultisample(id, samples, internalformat, width, height, depth, fixedsamplelocations));
}

void Texture::sub_image1d(GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels)
{
	GLCall(glTextureSubImage1D(id, level, xoffset, width, format, type, pixels));
}

void Texture::sub_image2d(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels)
{
	GLCall(glTextureSubImage2D(id, level, xoffset, yoffset, width, height, format, type, pixels));
}

void Texture::sub_image3d(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels)
{
	GLCall(glTextureSubImage3D(id, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels));
}

glwrapper::Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &id));
}

void Texture::generate_mipmap()
{
	GLCall(glGenerateTextureMipmap(id));
}

void Texture::bind(int unit)
{
	GLCall(glBindTextureUnit(unit, id));
}

void Texture::set_wrap_mode(GLenum direction, GLenum mode)
{
	GLCall(glTextureParameteri(id, direction, mode));
}

void Texture::set_border_color(float color[4])
{
	GLCall(glTextureParameterfv(id, GL_TEXTURE_BORDER_COLOR, color));
}

void Texture::set_minification_filter(GLenum fliter)
{
	GLCall(glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, fliter));
}

void Texture::set_magification_filter(GLenum fliter)
{
	GLCall(glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, fliter));
}