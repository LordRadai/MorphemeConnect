#pragma once
#include <math.h>
#include <Windows.h>

#include <iostream>
#include <cmath>
#include "../framework.h"
#include "../Debug/Debug.h"

namespace MathHelper
{
	float FrameToTime(int frame, int frameRate = 60.f);

	int TimeToFrame(float time, int frameRate = 60.f);
}