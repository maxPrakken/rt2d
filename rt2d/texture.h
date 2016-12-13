/**
 * @file texture.h
 *
 * @brief The Texture header file.
 *
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <time.h>
#include <ctime>
#include <glfw3.h>
#include "stringutil.h"

/// @brief defines a PixelBuffer
struct PixelBuffer
{
	/// @brief the width of the file
	int width;
	/// @brief the height of the file
	int height;
	/// @brief the size of the file
	///
	/// 1 = grayscale
	/// 3 = 24 bit RGB
	/// 4 = 32 bit RGBA
	unsigned char bitdepth;
	/// @brief the filtering level of the pixel data
	///
	/// 0 = none
	/// 1 = linear
	/// 2 = bilinear
	/// 3 = trilinear
	int filter;
	/// @brief the wrapping of the pixel data
	///
	/// 0 = GL_REPEAT
	/// 1 = GL_MIRRORED_REPEAT
	/// 2 = GL_CLAMP_TO_EDGE
	int wrap;
	/// @brief the pixel data
	unsigned char* data;

	/// @brief constructor
	PixelBuffer()
	{
		/// @brief initialize the width of the buffer
		width = 0;
		/// @brief initialize the height of the buffer
		height = 0;
		/// @brief initialize the color depth of the pixels
		bitdepth = 0;
		/// @brief initialize the filtering of the pixels
		filter = 0;
		/// @brief initialize the wrapping of the pixels
		wrap = 0;
		/// @brief initialize the pixel data
		data = (unsigned char*)0;
	}
	/// @brief overloaded constructor
	PixelBuffer(int w, int h, unsigned char b, int f, int wr)
	{
		/// @brief initialize the width of the buffer
		width = w;
		/// @brief initialize the height of the buffer
		height = h;
		/// @brief initialize the color depth of the pixels
		bitdepth = b;
		/// @brief initialize the filtering of the pixels
		filter = f;
		/// @brief initialize the wrapping of the pixels
		wrap = wr;
		/// @brief initialize the pixel data
		long size = w * h * b;
		data = new unsigned char[size];
		//create white opaque pixels
		for (long i=0; i<size; i++) {
			data[i] = 255;
		}
	}

	/// @brief destructor
	~PixelBuffer() { delete[] data; data = 0; /*std::cout << "delete PixelBuffer" << std::endl;*/ }

	/// @brief destroy the pixel data
	void destroy() { delete[] data; data = 0; /*std::cout << "destroy PixelBuffer" << std::endl;*/ }
};

/// @brief The Texture class loads images from files and converts them to OpenGL textures.
class Texture
{
public:
	Texture(); ///< @brief Constructor of the Texture
	virtual ~Texture(); ///< @brief Destructor of the Texture

	/// @brief get the OpenGL texture
	/// @return GLuint _texture
	GLuint getGLTexture() { return _gltexture[0]; };

	/// @brief get the PixelBuffer
	/// @return PixelBuffer* _pixelbuffer
	PixelBuffer* pixels() { return _pixelbuffer; };

	/// @brief get the width of the OpenGL texture
	/// @return int _width
	int width() { return _width; };
	/// @brief get the height of the OpenGL texture
	/// @return int _height
	int height() { return _height; };
	/// @brief bytes per pixel. 3=RGB, 4=RGBA.
	/// @return int _depth
	int depth() { return _depth; };

	/// @brief load an image from file (tga only)
	/// @param filename the path to the image
	/// @param filter the filter
	/// @param wrap the wrap
	/// @return GLuint _texture, 0 if failed
	GLuint loadTGAImage(const std::string& filename, int filter, int wrap);
	/// @brief write an image to file (tga only)
	/// @param pixels the PixelBuffer to write
	/// @return int 0 if failed
	int writeTGAImage(PixelBuffer* pixels);
	/// @brief create a width x height white PixelBuffer & GLpixeldata
	/// @param width the width of the white Texture
	/// @param height the height of the white Texture
	/// @return GLuint _texture, 0 if failed
	GLuint createWhitePixels(int width, int height);
	/// @brief create a Texture from a PixelBuffer
	/// @param pixels a PixelBuffer pointer
	/// @return GLuint _texture, 0 if failed
	void createFromBuffer(PixelBuffer* pixels);

	/// @brief get the warranty bit
	/// @return unsigned char _warrantybit
	unsigned char warranty() { return _warrantybit; };

private:
	/// @brief swap every first and third byte of the pixels
	void BGR2RGB(PixelBuffer* pixels);

	/// @brief the width of the file
	int _width;
	/// @brief the height of the file
	int _height;
	/// @brief the color depth of the pixels
	int _depth;
	/// @brief a number of texture names (1 for now)
	GLuint _gltexture[1];

	unsigned char _warrantybit; ///< @brief flipped if not a power of 2
	PixelBuffer* _pixelbuffer; ///< @brief pixelbuffer pointer. Will not be used if NULL.

	/// @brief delete the PixelBuffer of this Entity.
	/// @return void
	void deletePixelBuffer() {
		if (_pixelbuffer != NULL) {
			delete _pixelbuffer;
			_pixelbuffer = NULL;
		}
	};
};


#endif
