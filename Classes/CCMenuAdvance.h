/****************************************************************************
Copyright (c) Sonic Zhao
*/

#ifndef __CCMENU_ADVANCE_H__
#define __CCMENU_ADVANCE_H__

#include "cocos2d.h"
#include "CCMenuItemSpritePro.h"

using namespace cocos2d;
using namespace std;
enum eMenuType
{
   MenuType_Block,
   MenuType_Ghost,
   MenuType_PreAct,
};

class MenuAdvance : public Menu
{
public:
    
	MenuAdvance();

    static MenuAdvance* create();
    static MenuAdvance* create(MenuItem* item, ...) CC_REQUIRES_NULL_TERMINATION;
    static MenuAdvance* createWithArray(const Vector<MenuItem*>& arrayOfItems);
    static MenuAdvance* createWithItem(MenuItem* item);
    static MenuAdvance* createWithItems(MenuItem *firstItem, va_list args);
    
	bool initWithArray(const Vector<MenuItem*>& arrayOfItems);

	void onEnter();

	void onExit();

    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    virtual void onTouchCancelled(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);

	CCMenuItem* getItemForTouch(Touch *touch);

	void setResponseRect(CCRect& rc) { m_responseRect = rc; }

	void setMenuType(int type){ m_menuType = type; }
	void setPriority(int pri){ m_priority = pri; }
	void setIsLarger(bool b) { m_isLarger = b; }
	void setLargerRect(CCRect larRc){ m_largerRect = larRc;}
    
	void setEnabled( bool value, bool withColor = false );
public:
	bool m_isEnabled;
	//sound
	string m_tapBefore;
	string m_tapEnd;
protected:
private:
	bool m_isLarger;
	CCRect m_largerRect;
	CCRect m_responseRect;
	int m_menuType;
	int m_priority;

	EventListenerTouchOneByOne *m_eventListener;
};

#endif //__CCMENU_ADVANCE_H__