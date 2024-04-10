#pragma once

#include "glcommon.h"

namespace glwrapper
{
	class Texture
	{
	public:
		explicit Texture(GLenum type);
		explicit Texture(GLenum type, const char* path);
		~Texture();
		Texture(const Texture&) = delete;
		Texture(Texture&&) = delete;

		void storage1d(GLsizei levels, GLenum internalformat, GLsizei width);
		void storage2d(GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
		void storage2d_multisample(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
		void storage3d(GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
		void storage3d_multisample(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
		void sub_image1d(GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels);
		void sub_image2d(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
		void sub_image3d(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels);

		void generate_mipmap();
		void bind(int unit);
		void set_wrap_mode(GLenum direction, GLenum mode);
		void set_border_color(float color[4]);
		void set_minification_filter(GLenum fliter);
		void set_magification_filter(GLenum fliter);

		int get_width() const { return width; }
		int get_height() const { return height; }
		int get_channels() const { return channels; }
		GLuint get_id() const { return id; }
	private:
		GLuint id;
		int width;
		int height;
		int channels;
	};
}
