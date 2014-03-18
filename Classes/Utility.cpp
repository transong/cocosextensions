#include "Utility.h"
#include "GameConst.h"
//#include "ValueSystem.h"
//#include "BufferSonic.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

bool Utility::isFileExist( const char*path )
{
	return FileUtils::getInstance()->isFileExist(path);
}

void Utility::copyFileFromPathToPath(const char *fromPath, const char *toPath, bool decrpt)
{
	ssize_t nSize = 0;
	unsigned char* pBuffer = FileUtils::getInstance()->getFileData(fromPath, "rb", &nSize);

	if (pBuffer)
	{
			FILE *fp_forwrite = fopen(toPath, "wb");

			if (NULL == fp_forwrite)
			{

			}
			else
			{
				fwrite(pBuffer, sizeof(unsigned char), nSize, fp_forwrite);
				fclose(fp_forwrite);
			}

			CC_SAFE_DELETE_ARRAY(pBuffer);

	}
}

void Utility::preLoadSFX(const char* filename)
{
	if (0 == strlen(filename)) {
		return;
	}

	SimpleAudioEngine::getInstance()->preloadEffect(filename);
}

void Utility::unLoadSFX(const char* filename)
{
	if (0 == strlen(filename)) {
		return;
	}

	SimpleAudioEngine::getInstance()->unloadEffect(filename);
}

unsigned int Utility::playSFX(const char* filename, bool isLoop, float volume, float pitch)
{
   return SimpleAudioEngine::getInstance()->playEffect(filename, isLoop, pitch, 0.0f, volume);
}

void Utility::stopSFX( unsigned int soundId )
{
	SimpleAudioEngine::getInstance()->stopEffect(soundId);
}

void Utility::stopAllSFX()
{
	SimpleAudioEngine::getInstance()->stopAllEffects();
}

void Utility::setSFXVolume( float volume )
{
	SimpleAudioEngine::getInstance()->setEffectsVolume(volume);
}

float Utility::getSFXVolume()
{
	return SimpleAudioEngine::getInstance()->getEffectsVolume();
}

void Utility::preLoadBMG( const char* filename )
{
	if (0 == strlen(filename)) {
		return;
	}

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(filename);
}

void Utility::playBMG( const char* filename, bool isLoop)
{
	if (0 == strlen(filename)) {
		return;
	}

	// 	if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	// 	{
	SimpleAudioEngine::getInstance()->playBackgroundMusic(filename, isLoop);
	/*	}*/
}

bool Utility::isBMGPlaying()
{
	return SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();
}

void Utility::stopBMG()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
}

void Utility::setBMGVolume( float volume )
{
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
}

float Utility::getBMGVolume()
{
	return SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
}

bool Utility::isRectContainsPoint(const cocos2d::Rect& rect, const cocos2d::Point& point)
{
	bool bRet = false;

	if (point.x > rect.getMinX() && point.x < rect.getMaxX()
		&& point.y > rect.getMinY() && point.y < rect.getMaxY())
	{
		bRet = true;
	}

	return bRet;
}

int Utility::randomInt(int lo, int hi)
{
#if CC_PLATFORM_IOS == CC_TARGET_PLATFORM
	return arc4random()%(hi - lo + 1) + lo;
#else
	return rand()%(hi - lo + 1) + lo;
#endif
}

cocos2d::Point Utility::getDeviceScreenRate()
{
	GLView* glView = Director::getInstance()->getOpenGLView();

	return Point(Director::getInstance()->getOpenGLView()->getFrameSize().width/Director::getInstance()->getWinSize().width, Director::getInstance()->getOpenGLView()->getFrameSize().height/Director::getInstance()->getWinSize().height);
}

//xmlNodePtr Utility::addKeyAndDict(xmlNodePtr parent, const char* keyContent)
//{
//	xmlNewTextChild(parent, NULL, BAD_CAST "key", BAD_CAST keyContent);
//	return xmlNewChild(parent, NULL, BAD_CAST "dict", NULL);
//}
//
//xmlNodePtr Utility::addKeyAndString(xmlNodePtr parent, const char* keyContent, const char* strContent)
//{
//	xmlNewTextChild(parent, NULL, BAD_CAST "key", BAD_CAST keyContent);
//	return xmlNewTextChild(parent, NULL, BAD_CAST "string", BAD_CAST strContent);
//}
//
//xmlNodePtr Utility::addKeyAndBool(xmlNodePtr parent, const char* keyContent, bool bValue)
//{
//	xmlNewTextChild(parent, NULL, BAD_CAST "key", BAD_CAST keyContent);
//	return xmlNewChild(parent, NULL, BAD_CAST (bValue ? "true" : "false"), NULL);
//}
//
//xmlNodePtr Utility::addKeyAndFloat(xmlNodePtr parent, const char* keyContent, float fValue)
//{
//	CCString* str = CCString::createWithFormat("%.2f", fValue);
//    
//	xmlNewTextChild(parent, NULL, BAD_CAST "key", BAD_CAST keyContent);
//	return xmlNewTextChild(parent, NULL, BAD_CAST "real", BAD_CAST str->getCString());
//}
//
//xmlNodePtr Utility::addKeyAndPoint(xmlNodePtr parent, const char* keyContent, CCPoint point)
//{
//	CCString* str = CCString::createWithFormat("{%.2f,%.2f}", point.x, point.y);
//    
//	xmlNewTextChild(parent, NULL, BAD_CAST "key", BAD_CAST keyContent);
//	return xmlNewTextChild(parent, NULL, BAD_CAST "string", BAD_CAST str->getCString());
//}
//
//xmlNodePtr Utility::addKeyAndRect(xmlNodePtr parent, const char* keyContent, CCRect rect)
//{
//	CCString* str = CCString::createWithFormat("{{%.2f,%.2f},{%.2f,%.2f}}", rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
//    
//	xmlNewTextChild(parent, NULL, BAD_CAST "key", BAD_CAST keyContent);
//	return xmlNewTextChild(parent, NULL, BAD_CAST "string", BAD_CAST str->getCString());
//}
//
//xmlNodePtr Utility::addKeyAndArray(xmlNodePtr parent, const char* keyContent)
//{
//	xmlNewTextChild(parent, NULL, BAD_CAST "key", BAD_CAST keyContent);
//	return xmlNewChild(parent, NULL, BAD_CAST "array", NULL);
//}
//
//xmlNodePtr Utility::addDictToArray(xmlNodePtr parent)
//{
//    return xmlNewChild(parent, NULL, BAD_CAST "dict", NULL);
//}
//
//xmlNodePtr Utility::addStringToArray(xmlNodePtr parent, const char* strContent)
//{
//    return xmlNewTextChild(parent, NULL, BAD_CAST "string", BAD_CAST strContent);
//}

