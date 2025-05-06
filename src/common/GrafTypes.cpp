#include "GrafTypes.h"

#include "UMemory.h"

bool SRect::GetIntersection(const SRect &inRect, SRect &outSect) const
{
	int left = max(left, inRect.left);
	int top = max(top, inRect.top);
	int right = min(right, inRect.right);
	int bottom = min(bottom, inRect.bottom);

	if (Intersects(inRect))
	{
		outSect.left = left;
		outSect.top = top;
		outSect.right = right;
		outSect.bottom = bottom;
		return true;
	}

	UMemory::Clear(&outSect, sizeof(SRect));
	return false;
}

bool SRect::GetUnion(const SRect &inRect, SRect &outUnion) const
{
	if (left >= right || top >= bottom || inRect.left >= inRect.right ||
	    inRect.top >= inRect.bottom)
	{
		UMemory::Clear(&outUnion, sizeof(SRect));
		return false;
	}

	outUnion.left = min(left, inRect.left);
	outUnion.top = min(top, inRect.top);
	outUnion.right = max(right, inRect.right);
	outUnion.bottom = max(bottom, inRect.bottom);

	return true;
}

void SRect::Constrain(const SRect &inMax)
{
	if (left < inMax.left)
		left = inMax.left;
	else if (left > inMax.right)
		left = inMax.right;

	if (right < inMax.left)
		right = inMax.left;
	else if (right > inMax.right)
		right = inMax.right;

	if (top < inMax.top)
		top = inMax.top;
	else if (top > inMax.bottom)
		top = inMax.bottom;

	if (bottom < inMax.top)
		bottom = inMax.top;
	else if (bottom > inMax.bottom)
		bottom = inMax.bottom;
}

void SRect::Center(const SRect &inBase, const SRect &inContainer)
{
	auto width = inBase.right - inBase.left;
	auto height = inBase.bottom - inBase.top;

	left = ((inContainer.left + inContainer.right) - width) >> 1;
	right = left + width;

	top = ((inContainer.top + inContainer.bottom) - height) >> 1;
	bottom = top + height;
}

void SRect::CenterHoriz(const SRect &inBase)
{
	auto width = right - left;
	auto center = (inBase.left + inBase.right) >> 1;

	left = center - (width >> 1);
	right = left + width;
}

void SRect::MoveTo(const SRect &inRect, int inLeft, int inTop)
{
	auto width = inRect.right - inRect.left;
	auto height = inRect.bottom - inRect.top;

	left = inLeft;
	right = inLeft + width;
	top = inTop;
	bottom = inTop + height;
}

void SRect::Validate()
{
	if (right < left)
		swap(left, right);

	if (bottom < top)
		swap(top, bottom);
}

void SRect::Align(const SRect &inSourceRect, unsigned inOptions, const SRect &inRefRect)
{
	auto sourceWidth = inSourceRect.right - inSourceRect.left;
	auto sourceHeight = inSourceRect.bottom - inSourceRect.top;

	if (inOptions & kAlignLeft)
	{
		left = inRefRect.left;
		right = left + sourceWidth;
	}
	else if (inOptions & kAlignRight)
	{
		right = inRefRect.right;
		left = right - sourceWidth;
	}
	else if (inOptions & kAlignCenterHoriz)
	{
		left = (inRefRect.left + inRefRect.right - sourceWidth) >> 1;
		right = left + sourceWidth;
	}
	else if (inOptions & kAlignClipHoriz)
	{
		left = max(inRefRect.left, inSourceRect.left);
		right = min(inRefRect.right, left + sourceWidth);
	}
	else
	{
		left = inSourceRect.left;
		right = inSourceRect.right;
	}

	if (inOptions & kAlignTop)
	{
		top = inRefRect.top;
		bottom = top + sourceHeight;
	}
	else if (inOptions & kAlignBottom)
	{
		bottom = inRefRect.bottom;
		top = bottom - sourceHeight;
	}
	else if (inOptions & kAlignCenterVert)
	{
		top = (inRefRect.top + inRefRect.bottom - sourceHeight) >> 1;
		bottom = top + sourceHeight;
	}
	else if (inOptions & kAlignClipVert)
	{
		top = max(inRefRect.top, inSourceRect.top);
		bottom = min(inRefRect.bottom, top + sourceHeight);
	}
	else
	{
		top = inSourceRect.top;
		bottom = inSourceRect.bottom;
	}
}
