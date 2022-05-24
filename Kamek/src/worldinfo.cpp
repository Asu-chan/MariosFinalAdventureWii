#include "worldinfo.h"

dDvdLoader_c s_worldInfoLoader;
bool s_worldInfoLoaded = false;

dWorldInfo_c *dWorldInfo_c::instance;

bool LoadWorldInfo() {
	if (s_worldInfoLoaded)
		return true;

	void *data = s_worldInfoLoader.load("/NewerRes/WorldInfo.bin");
	if (data) {
		dWorldInfo_c::instance = (dWorldInfo_c*)data;
		s_worldInfoLoaded = true;
		return true;
	}

	return false;
}
