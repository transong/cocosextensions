#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
    void menuCloseCallback(Ref* sender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    
    void btnCB(Ref *obj);
    
    void btn2CB(Ref *obj);
    
    void btn3CB(Ref *obj);
    
    LabelTTF *m_labelTitle;
};

#endif // __HELLOWORLD_SCENE_H__
