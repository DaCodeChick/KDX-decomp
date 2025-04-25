#pragma once

#include "typedefs.h"

struct SPoint
{
	int x, y;

#ifdef _WIN32
	operator LPPOINT() const { return (LPPOINT)this; }
#endif // _WIN32
};

struct SRect
{
	int left, top, right, bottom;

	bool GetIntersection(SRect &inRect, SRect &outSect) const;
	bool GetUnion(SRect &inRect, SRect &outUnion) const;
	void Constrain(SRect &inMax);
	void CenterHoriz(SRect &inBase);

#ifdef _WIN32
	operator LPRECT() const { return (LPRECT)this; }
#endif // _WIN32
};
