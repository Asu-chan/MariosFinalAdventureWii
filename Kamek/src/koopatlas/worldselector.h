#ifndef __KOOPATLAS_WSEL_H
#define __KOOPATLAS_WSEL_H

#include "koopatlas/core.h"
#include "fileload.h"



class dWMWSEL_c : public dActor_c {
	public:
		dWMWSEL_c();

		int onCreate();
		int onDelete();
		int onExecute();
		int onDraw();
		void specialDraw1();

		m2d::EmbedLayout_c layout;
		dStateWrapper_c<dWMWSEL_c> acState;

   		FileHandle fileHandles[3];

		u32 selectedWorld;
		u32 worldCount;
		int worldIDs[16];

		bool layoutLoaded;
		bool isVisible;

		nw4r::lyt::Picture *BGs[2];
		nw4r::lyt::Picture *Icons[2];
		nw4r::lyt::TextBox *WorldNames[2];
		nw4r::lyt::TextBox *WorldNamesS[2];
		nw4r::lyt::TextBox *WorldIDs[2];

		enum Animation {
			SHOW_ALL = 0,
			IN_ARROW = 1,
			IN_ARROW_L = 1,
			IN_ARROW_R = 2,
			ON_ARROW = 3,
			ON_ARROW_L = 3,
			ON_ARROW_R = 4,
			OFF_ARROW = 5,
			OFF_ARROW_L = 5,
			OFF_ARROW_R = 6,
			LOOP_ARROW = 7,
			LOOP_ARROW_L = 7,
			LOOP_ARROW_R = 8,
			HIT_ARROW = 9,
			HIT_ARROW_L = 9,
			HIT_ARROW_R = 10,
			OUT_ARROW = 11,
			OUT_ARROW_L = 11,
			OUT_ARROW_R = 12,
			IN_BG = 13,
			OUT_BG = 14,
			TO_BEFORE = 15,
			TO_NEXT = 16,
			ON_BUTTON = 17,
			IDLE_BUTTON = 18,
			HIT_BUTTON = 19,
			OFF_BUTTON = 20,
			HIDE_ALL = 21,
		};

		static dWMWSEL_c *build();
		static dWMWSEL_c *instance;

		void show();
		void moveWorld();
		void loadWorld(u32 worldNum, bool isLeft);

		USING_STATES(dWMWSEL_c);
		DECLARE_STATE(Hidden);
		DECLARE_STATE(ShowWait);
		DECLARE_STATE(ButtonAnimWait);
		DECLARE_STATE(WaitForInput);
		DECLARE_STATE(ArrowHit);
		DECLARE_STATE(Select);
		DECLARE_STATE(Exit);

};

#endif

