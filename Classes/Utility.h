#pragma once

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class Utility
{
public:

    static bool isFileExist(const char* path);
	static void copyFileFromPathToPath(const char *fromPath, const char *toPath, bool decrpt = false);
    static vector<string> iterateFolder(const char* path);
	
	//sound
	static void preLoadSFX(const char* filename);
	static void unLoadSFX(const char* filename);
	static unsigned int playSFX(const char* filename, bool isLoop = false, float volume = 0.8f, float pitch = 1.0f);
	static void stopSFX(unsigned int soundId);
	static void stopAllSFX();
	static float getSFXVolume();
	static void setSFXVolume(float volume);

	static void preLoadBMG(const char *filename);
	static void playBMG(const char *filename, bool isLoop = true);
	static bool isBMGPlaying();
	static void stopBMG();
	static float getBMGVolume();
	static void setBMGVolume(float volume);

	//rate
	static void rateThisApp();
    static void openAppStore();
    
	//utils
	static int  randomInt(int lo, int hi);
	static bool isRectContainsPoint(const cocos2d::Rect& rect, const cocos2d::Point& point);

    //xml
    static void iterateFolder(const char* path, CCObject* target, SEL_CallFuncO selector);

	static Point getDeviceScreenRate();
    
    //xml methods
//    static xmlNodePtr addKeyAndDict(xmlNodePtr parent, const char* keyContent = "");
//    static xmlNodePtr addKeyAndString(xmlNodePtr parent, const char* keyContent, const char* strContent);
//    static xmlNodePtr addKeyAndBool(xmlNodePtr parent, const char* keyContent, bool bValue);
//    static xmlNodePtr addKeyAndFloat(xmlNodePtr parent, const char* keyContent, float fValue);
//    static xmlNodePtr addKeyAndPoint(xmlNodePtr parent, const char* keyContent, CCPoint point);
//    static xmlNodePtr addKeyAndRect(xmlNodePtr parent, const char* keyContent, CCRect rect);
//    
//    static xmlNodePtr addKeyAndArray(xmlNodePtr parent, const char* keyContent = "");
//    static xmlNodePtr addDictToArray(xmlNodePtr parent);
//    static xmlNodePtr addStringToArray(xmlNodePtr parent, const char* strContent);

};



