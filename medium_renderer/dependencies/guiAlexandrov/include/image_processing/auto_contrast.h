#pragma once

#include <stdint.h>
#include "image/image.h"
#include "histogram.h"


namespace gui
{
	namespace cpu
	{
		
		template <typename T>
		Image_base<T> auto_contrast(const Image_base<T>& image, const Histogram<Image_base<T>>& hist)
		{
			Image_base<T> res;
			res.resize(image.width, image.height);

			// cut 1% from bounds
			int cut_amount = 0.01f * image.height * image.width;
			int x_min, x_max;

			// find new bounds
			int count = 0;
			for (int i = 0; i < 256; i++)
			{
				count += hist.cbrightness[i];
				if (count >= cut_amount)
				{
					x_min = i;
					break;
				}
			}

			count = 0;
			for (int i = 255; i >= 0; i--)
			{
				count += hist.cbrightness[i];
				if (count >= cut_amount)
				{
					x_max = i;
					break;
				}
			}

			float c = 255.0f / (x_max - x_min);
			for (int i = 0; i < image.height * image.width; i++)
			{
				const fColor& pixel = image[i];
				fColor temp;

				float Y = 0.2126f * pixel.r + 0.7152f * pixel.g + 0.0722 * pixel.b;
				float U = -0.0999f * pixel.r - 0.336f * pixel.g + 0.436f * pixel.b;
				float V = 0.615f * pixel.r - 0.5586f * pixel.g - 0.0563 * pixel.b;

				// corection
				Y = (Y - float(x_min) / 255.0f) * c;

				temp.r = chanel_clip(Y + 1.2803f * V);
				temp.g = chanel_clip(Y - 0.2148f * U - 0.4805f * V);
				temp.b = chanel_clip(Y + 2.1279f * U);
				res[i] = temp;
			}

			return res;
		}



		template <typename T>
		Image_base<T> auto_contrast(const Image_base<T>& image, float skip_persent)
		{
			Histogram<Image_base<T>> hist(image);

			Image_base<T> res;
			res.resize(image.width, image.height);

			// skip 5% from bounds
			int cut_amount = skip_persent * image.height * image.width;
			int x_min, x_max;

			// find new bounds
			int count = 0;
			for (int i = 0; i < 256; i++)
			{
				count += hist.cbrightness[i];
				if (count >= cut_amount)
				{
					x_min = i;
					break;
				}
			}

			count = 0;
			for (int i = 255; i >= 0; i--)
			{
				count += hist.cbrightness[i];
				if (count >= cut_amount)
				{
					x_max = i;
					break;
				}
			}

			float c = 255.0f / (x_max - x_min);
			for (int i = 0; i < image.height * image.width; i++)
			{
				const fColor& pixel = image[i];
				fColor temp;

				float Y = 0.2126f * pixel.r + 0.7152f * pixel.g + 0.0722 * pixel.b;
				float U = -0.0999f * pixel.r - 0.336f * pixel.g + 0.436f * pixel.b;
				float V = 0.615f * pixel.r - 0.5586f * pixel.g - 0.0563 * pixel.b;

				// corection
				Y = (Y - float(x_min) / 255.0f) * c;

				temp.r = chanel_clip(Y + 1.2803f * V);
				temp.g = chanel_clip(Y - 0.2148f * U - 0.4805f * V);
				temp.b = chanel_clip(Y + 2.1279f * U);
				res[i] = temp;
			}

			return res;
		}

	}
}