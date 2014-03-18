#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "CCMenuAdvance.h"
#include "CCScreenLayer.h"
#include "GameConst.h"

USING_NS_CC;


Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    m_labelTitle = LabelTTF::create("", "Arial", 12);
    m_labelTitle->setPosition(ccp_percent(50, 86));
    addChild(m_labelTitle);
    
    {
        LabelTTF *label = LabelTTF::create("Block", "Arial", 20);
        label->setAnchorPoint(ccp(0, 0.5));
        label->setPosition(ccp_percent(10, 70));
        addChild(label);
        
        MenuAdvance *menuAd = MenuAdvance::create(NULL);
        menuAd->setPosition(ccp_percent(60, 70));
        addChild(menuAd);
        
        MenuItemSpritePro *item_1 = MenuItemSpritePro::create(Sprite::create("bang.png"), CC_CALLBACK_1(HelloWorld::btnCB, this));
        item_1->m_selEffectType = SelEffect_ChangeColor;
        item_1->setTag(0);
        menuAd->addChild(item_1);
        
        MenuItemSpritePro *item_2 = MenuItemSpritePro::create(Sprite::create("bang.png"), CC_CALLBACK_1(HelloWorld::btnCB, this));
        item_2->setTag(1);
        item_2->m_selEffectType = SelEffect_Mag;
        menuAd->addChild(item_2);
        
        MenuItemSpritePro *item_3 = MenuItemSpritePro::create(Sprite::create("bang.png"), CC_CALLBACK_1(HelloWorld::btnCB, this));
        item_3->setTag(2);
        item_3->m_selEffectType = SelEffect_Decend;
        menuAd->addChild(item_3);
        
        MenuItemSpritePro *item_4 = MenuItemSpritePro::create(Sprite::create("bang.png"), CC_CALLBACK_1(HelloWorld::btnCB, this));
        item_4->setLabel(LabelTTF::create("MENU", "Arial", 20));
        item_4->setTag(3);
        item_4->m_selEffectType = SelEffect_ChangeColor | SelEffect_Mag | SelEffect_Decend;
        menuAd->addChild(item_4);
        
        menuAd->alignItemsHorizontallyWithPadding(20);
        
 		ParticleSystemQuad *par = ParticleSystemQuad::create("particle_same.plist");
        par->setScale(1.5f);
        
        MenuItemSpritePro *item_5 = MenuItemSpritePro::create(Sprite::create("bang.png"), CC_CALLBACK_1(HelloWorld::btnCB, this));
        item_5->setParticle(par);
        item_5->setTag(3);
        item_5->m_selEffectType = SelEffect_ChangeColor | SelEffect_Mag;
        menuAd->addChild(item_5);
        
        menuAd->alignItemsHorizontallyWithPadding(20);

    }

    {
        LabelTTF *label = LabelTTF::create("PreAct", "Arial", 20);
        label->setAnchorPoint(ccp(0, 0.5f));
        label->setPosition(ccp_percent(10, 50));
        addChild(label);
        
        MenuAdvance *menuAd_PreAct = MenuAdvance::create(NULL);
        menuAd_PreAct->m_tapEnd = "sfx_hit.mp3";
        menuAd_PreAct->setMenuType(MenuType_PreAct);
        menuAd_PreAct->setPosition(ccp_percent(60, 50));
        addChild(menuAd_PreAct);
        
        MenuItemSpritePro *item_1 = MenuItemSpritePro::create(Sprite::create("bang.png"), CC_CALLBACK_1(HelloWorld::btn2CB, this));
        item_1->m_selEffectType = SelEffect_ChangeColor;
        item_1->setTag(0);
        menuAd_PreAct->addChild(item_1);
        
        MenuItemSpritePro *item_2 = MenuItemSpritePro::create(Sprite::create("bang.png"), CC_CALLBACK_1(HelloWorld::btn2CB, this));
        item_2->setTag(1);
        item_2->m_selEffectType = SelEffect_Mag;
        menuAd_PreAct->addChild(item_2);
        
        MenuItemSpritePro *item_3 = MenuItemSpritePro::create(Sprite::create("bang.png"), CC_CALLBACK_1(HelloWorld::btn2CB, this));
        item_3->setTag(2);
        item_3->m_selEffectType = SelEffect_Decend;
        menuAd_PreAct->addChild(item_3);
        
        MenuItemSpritePro *item_4 = MenuItemSpritePro::create(Sprite::create("bang.png"), CC_CALLBACK_1(HelloWorld::btn2CB, this));
        item_4->setLabel(LabelTTF::create("MENU", "Arial", 20));
        item_4->setTag(3);
        item_4->m_selEffectType = SelEffect_ChangeColor | SelEffect_Mag | SelEffect_Decend;
        menuAd_PreAct->addChild(item_4);
        
        ParticleSystemQuad *par = ParticleSystemQuad::create("particle_same.plist");
        par->setScale(1.5f);
        
        MenuItemSpritePro *item_5 = MenuItemSpritePro::create(Sprite::create("bang.png"), CC_CALLBACK_1(HelloWorld::btn2CB, this));
        item_5->setParticle(par);
        item_5->setTag(3);
        item_5->m_selEffectType = SelEffect_ChangeColor | SelEffect_Mag;
        menuAd_PreAct->addChild(item_5);
        
        menuAd_PreAct->alignItemsHorizontallyWithPadding(20);
        
    }
    
    {
        
        LabelTTF *label = LabelTTF::create("ScreenLayer And Ghost Menu", "Arial", 8);
        label->setAnchorPoint(Point(0, 0.5f));
        label->setPosition(ccp_percent(10, 20));
        addChild(label);
        
        vector<Node*> vecNodes;
        
        for (int i = 0; i < 16; i++) {
            
            Node *nod = Node::create();
            
            MenuAdvance *menu = MenuAdvance::create(NULL);
            menu->setPosition(Point::ZERO);
            menu->setMenuType(MenuType_Ghost);
            menu->setPriority(-1);
            
            MenuItemSpritePro *item = MenuItemSpritePro::create(Sprite::create("bang.png"), CC_CALLBACK_1(HelloWorld::btn3CB, this));
            
            item->setLabel(LabelTTF::create("MENU", "Arial", 20));
            
            menu->addChild(item);
            
            nod->addChild(menu);
            
            vecNodes.push_back(nod);
        }
        
        Rect rc = Rect(30, 30, x_percent(80), y_percent(20)); //test clipping. if you want full screen just set Rect(0, 0, x_percent(100), y_percent(100));
        
        ScreenLayer * m_screenLay = ScreenLayer::create(&vecNodes, rc);
        m_screenLay->setPriority(-1); //test priority
        m_screenLay->setSpacing(x_percent(50));
        m_screenLay->setPriority(0);
        m_screenLay->setStaffNumPerPage(1);
        m_screenLay->setIsLoop(false);
        addChild(m_screenLay);
    }
    
    return true;
}

void HelloWorld::menuCloseCallback(Ref* sender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::btnCB(Ref *obj)
{
    MenuItemSpritePro *item = (MenuItemSpritePro *)obj;
    
    int selEffect = item->m_selEffectType;
    
    string strEffectType;
    
    if (SelEffect_ChangeColor & selEffect) {
        
        strEffectType = "Color";
        
    }
    if (SelEffect_Mag & selEffect) {
        
        strEffectType += " Mag";
        
    }
    if (SelEffect_Decend & selEffect) {
        
        strEffectType += " Decend";
    }
    
    __String *str = __String::createWithFormat("MenuType : Block | EffectType : %s", strEffectType.c_str());
    
    m_labelTitle->setString(str->getCString());
}

void HelloWorld::btn2CB(Ref *obj)
{
    MenuItemSpritePro *item = (MenuItemSpritePro *)obj;
    
    int selEffect = item->m_selEffectType;
    
    string strEffectType;
    
    if (SelEffect_ChangeColor & selEffect) {
        
        strEffectType = "Color";
        
    }
    if (SelEffect_Mag & selEffect) {
        
        strEffectType += " Mag";
        
    }
    if (SelEffect_Decend & selEffect) {
        
        strEffectType += " Decend";
    }
    
    __String *str = __String::createWithFormat("MenuType : PreAct With Sound | EffectType : %s", strEffectType.c_str());
    
    m_labelTitle->setString(str->getCString());
}

void HelloWorld::btn3CB(Ref *obj)
{
    m_labelTitle->setString("MenuType : Ghost In ScreenLayer.You can drag two chapters at once");
}
