#pragma once

#include "typedefs.h"

class UGraphics
{
public:
	/**
	 * @brief Adjust color channel with a given factor (0-255).
	 *
	 * @param inChannel Color channel to adjust.
	 * @param inFactor Adjustment factor (0-255).
	 * @return Adjusted channel value.
	 */
	[[nodiscard]] static constexpr uint8_t Adjust(uint8_t inChannel, uint8_t inFactor)
	{
		auto adjusted = inChannel + inFactor;
		if (adjusted > 255)
			adjusted = 255 - ((adjusted - 255) >> 1);

		return static_cast<uint8_t>(max(0, adjusted));
	}

	/**
	 * @brief Adjust color with bleed effect.
	 *
	 * @param inColor Color to adjust.
	 * @param inBleed Amount of bleed to apply.
	 * @return Adjusted color value.
	 */
	[[nodiscard]] static constexpr uint32_t AdjustColorWithBleed(uint32_t inColor, uint8_t inBleed)
	{
		auto red = (inColor >> 16) & 0xFF;
		auto green = (inColor >> 8) & 0xFF;
		auto blue = inColor & 0xFF;

		red = Adjust(red, inBleed);
		green = Adjust(green, inBleed);
		blue = Adjust(blue, inBleed);

		return (red << 16) | (green << 8) | blue;
	}

	/**
	 * @brief Blend a color channel with a given factor (0-255).
	 *
	 * @param inChannel
	 * @param inFactor
	 * @return Blended channel value.
	 */
	[[nodiscard]] static constexpr uint8_t Blend(uint8_t inChannel, uint8_t inFactor)
	{
		return inChannel == 0 ? 0 : 0xFF - ((0xFF - inChannel) * inFactor) / 0xFF;
	}

	/**
	 * @brief Blend color channels with a given factor (0-255).
	 *
	 * @param inColor
	 * @param inFactor
	 * @return Blended color value.
	 */
	[[nodiscard]] static constexpr uint32_t BlendColorChannels(uint32_t inColor, uint8_t inFactor)
	{
		auto red = (inColor >> 16) & 0xFF;
		auto green = (inColor >> 8) & 0xFF;
		auto blue = inColor & 0xFF;
		auto alpha = (inColor >> 24) & 0xFF;

		red = Blend(red, inFactor);
		green = Blend(green, inFactor);
		blue = Blend(blue, inFactor);
		alpha = Blend(alpha, inFactor);

		return (alpha << 24) | (red << 16) | (green << 8) | blue;
	}

	/**
	 * @brief Reduce color channels with a given bleed amount.
	 *
	 * @param inColor Color to reduce.
	 * @param inBleed Amount of bleed to apply.
	 * @return Reduced color value.
	 */
	[[nodiscard]] static constexpr uint32_t ReduceColorWithBleed(uint32_t inColor, uint8_t inBleed)
	{
		auto red = inColor >> 16;
		auto green = inColor >> 8;
		auto blue = inColor;

		red = red - inBleed;
		green = green - inBleed;
		blue = blue - inBleed;

		red = red < 0 ? red >> 1 : red;
		green = green < 0 ? green >> 1 : green;
		blue = blue < 0 ? blue >> 1 : blue;

		return (red << 16) | (green << 8) | blue;
	}
};
