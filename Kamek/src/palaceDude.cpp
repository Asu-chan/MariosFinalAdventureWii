#include <game.h>
#include <stage.h>
#include "msgbox.h"
#include "boss.h" // for stopbgmmusic and crap
#include "worldinfo.h"

const char *PalaceDudeFileList[] = {"OpeningScene", 0};

class dPalaceDude_c : public dStageActor_c {
	public:
		static dPalaceDude_c *build();

		bool hasBeenActivated;
		bool hasExitedStage;
		int onExecute();
};

/*****************************************************************************/
// Glue Code
dPalaceDude_c *dPalaceDude_c::build() {
	void *buffer = AllocFromGameHeap1(sizeof(dPalaceDude_c));
	dPalaceDude_c *c = new(buffer) dPalaceDude_c;
	return c;
}


int dPalaceDude_c::onExecute() {
	if (dFlagMgr_c::instance->flags & spriteFlagMask) {
		if (!hasBeenActivated) {
//			OSReport("Activating Palace Dude\n");
			hasBeenActivated = true;

			int delay;
			if (!(settings & 0xF000000)) {
				delay = 270;
				StopBGMMusic();
				SaveBlock *save = GetSaveFile()->GetBlock(-1);
				GameMgrP->switchPalaceFlag |= (1 << (settings >> 28));
			} else {
				delay = 1020;
			}

			dMsgBoxManager_c::instance->showMessage(
				settings & 0xFFFFFF, // message ID
				false, // cannot cancel
				delay // delay
				);
		}
	}

	if (hasBeenActivated) {
		if (hasExitedStage)
			return true;
//		OSReport("Palace Dude is activated, %d\n", dMsgBoxManager_c::instance->visible);
		if (!dMsgBoxManager_c::instance->visible) {
//			OSReport("Exiting\n");
			u32 wmsettings = 0;
			if (settings & 0xF000000) {
				SaveBlock *save = GetSaveFile()->GetBlock(-1);
				if(save->newerWorldName[0] == -1) { // De-hardcoded the W1 name & info :D
					WorldInfo *worldInfo = dWorldInfo_c::instance->getWorldInfo(0);

					save->current_world = worldInfo->worldmapID;
					save->current_path_node = worldInfo->nodeID;

					strncpy(save->newerWorldName, dWorldInfo_c::instance->getNameForWorld(0), 32);
					save->newerWorldName[31] = 0;
					save->newerWorldID = worldInfo->NWID;
					save->currentMapMusic = worldInfo->musicID;

					save->fsTextColours[0] = worldInfo->FSTextColour0;
					save->fsHintColours[0] = worldInfo->FSHintColour0;
					save->hudTextColours[0] = worldInfo->HUDTextColour0;
					save->fsTextColours[1] = worldInfo->FSTextColour1;
					save->fsHintColours[1] = worldInfo->FSHintColour1;
					save->hudTextColours[1] = worldInfo->HUDTextColour1;

					save->hudHintH = worldInfo->HUDH;
					save->hudHintS = worldInfo->HUDS;
					save->hudHintL = worldInfo->HUDL;

					if (!(save->titleScreenWorld == 3 && save->titleScreenLevel == 10)) {
						save->titleScreenWorld = worldInfo->titlescreenWorld;
						save->titleScreenLevel = worldInfo->titlescreenLevel;
					}
				}

				SaveGame(0, false);
				wmsettings = 0x80000000;
			}
			ExitStage(WORLD_MAP, wmsettings, BEAT_LEVEL, MARIO_WIPE);
			hasExitedStage = true;
		}
	}

	return true;

}


