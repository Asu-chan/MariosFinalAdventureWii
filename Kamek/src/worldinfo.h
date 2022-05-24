#ifndef __NEWER_WORLDINFO_H
#define __NEWER_WORLDINFO_H

#include <game.h>

class WorldInfo {
public:
	u8 worldmapID;
	u8 nodeID;
	u8 NWID;
	u8 musicID;
	GXColor FSTextColour0;
	GXColor FSTextColour1;
	GXColor FSHintColour0;
	GXColor FSHintColour1;
	GXColor HUDTextColour0;
	GXColor HUDTextColour1;

	s16 HUDH;
	s8 HUDS;
	s8 HUDL;

	u16 titlescreenWorld;
	u16 titlescreenLevel;

	u32 worldNameIdx;
};

class dWorldInfo_c {
public:
	u32 magic;
	u8 shopInventory[10][12];

	u32 worldCount;
	WorldInfo worldInfos[];

	WorldInfo *getWorldInfo(u32 worldNumber) {
		return &worldInfos[worldNumber];
	}

	const char *getNameForWorld(u32 worldNumber) {
		return (const char*)((u32)instance + worldInfos[worldNumber].worldNameIdx);
	}

	/*wchar_t *wgetNameForWorld_t(u32 worldNumber) {
		const char* worldChr = getNameForWorld(worldNumber);

		OSReport("wname: %s\n", worldChr);

		wchar_t result[32];

		int currentChar = 0;
		while(worldChr[currentChar] > 0) {
			result[currentChar] = worldChr[currentChar];
			currentChar++;
		}
		result[currentChar] = 0;

		return (wchar_t *)&result;
	}*/

	static dWorldInfo_c *instance;
};


#endif

