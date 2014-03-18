#pragma once

#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

class ScrollNode;
class ScreenLayer : public Layer
{
public:

    //properties
	void setIsVertical(bool b) { m_isVertical = b; }
	bool getIsVertical() { return m_isVertical; }

	void setIsLoop(bool b) { m_isLoop = b; }
	bool getIsLoop() { return m_isLoop; }

	void setStaffNumPerPage(unsigned char num){ m_staffNumPerPage = num; }
	unsigned char getStaffNumPerPage(){ return m_staffNumPerPage;}

	ScrollNode* getBoss(){return m_nodeBoss;}

	//per page only
	unsigned char getPage();
	void setPage(int page);

	void gotoNextPage();
	void gotoPreviousPage();
	//
	static ScreenLayer* create(vector<Node*>* nodes, Rect pageRect);

	bool initWithNodes(vector<Node*>* nodes, Rect pageRect); 

	ScreenLayer();
	~ScreenLayer();

    void onEnter();
	void onExit();
    
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	virtual void onTouchCancelled(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);

	//void visit();

	void setMoveEndTarget(Object* target, SEL_CallFunc selector){m_pListener = target; m_pfnSelector = selector;}
	void moveEnd();

	void setSpacing(float s) { m_spacing = s;}
	float getSpacing() { return m_spacing; }
public:

	CCRect m_pageRect;
	float m_spacing;
	CCSize m_winSize;

	int m_priority;

	void setPriority(int pri){ m_priority = pri; }

public:
	ScrollNode* m_nodeBoss;

    bool m_isVertical;
	bool m_isLoop;
	int getCurIndex();
	void loopRearrange();

	unsigned char m_staffNumPerPage;

	//per page only
	short m_totalScreens;
    short m_curScreen;

	vector<Point> m_vecPos;
	vector<Node*> m_vecStaff;

	Object*       m_pListener;
	SEL_CallFunc    m_pfnSelector;

    Touch *m_touch;

	bool m_touchMoved;

	EventListenerTouchOneByOne *m_eventListener;
};
