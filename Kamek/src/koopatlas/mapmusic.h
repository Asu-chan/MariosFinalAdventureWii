#ifndef MAPMUSIC_H
#define MAPMUSIC_H 

class dKPMusic {
	public:
		static bool loadInfo();
		static void play(int id);
		static void execute();
		static void stop();
		static void playStarMusic();
		static void lowerMusic();
		static void higherMusic();
};

#endif /* MAPMUSIC_H */
