#include "CCMenuItemSpritePro.h"
#include "cocos2d.h"

const unsigned int kZoomActionTag = 0xc0c05002;
const unsigned int kBounceActionTag = 0xc0c05003;

MenuItemSpritePro::MenuItemSpritePro()
:m_labelOnMenu(nullptr)
,m_particleOnMenu(nullptr)
{
    
}

MenuItemSpritePro::~MenuItemSpritePro()
{
    
}

void MenuItemSpritePro::setColor(const Color3B& color)
{
	_normalImage->setColor(color);
}

const Color3B& MenuItemSpritePro::getColor(void)
{
    return _normalImage->getColor();
}

GLubyte MenuItemSpritePro::getOpacity(void)
{
	return _normalImage->getOpacity();
}

void MenuItemSpritePro::setOpacity(GLubyte opacity)
{
	_normalImage->setOpacity(opacity);
}

MenuItemSpritePro* MenuItemSpritePro::create(Node* sprite)
{
	return MenuItemSpritePro::create(sprite, nullptr);
}

MenuItemSpritePro* MenuItemSpritePro::create(Node* sprite, const ccMenuCallback& callback)
{
	MenuItemSpritePro *pRet = new MenuItemSpritePro();
	pRet->initFromNormalSprite(sprite, callback);
	pRet->autorelease();
	return pRet;
}

bool MenuItemSpritePro::initFromNormalSprite(Node* sprite, const ccMenuCallback& callback)
{
	assert(sprite != NULL);
    
	if( MenuItemSprite::initWithNormalSprite(sprite, NULL, NULL, callback))
	{	
		m_selEffectType = SelEffect_ChangeColor;
		m_fOriginalScale = 1.0f;
		setContentSize(sprite->getContentSize());
	}

	return true;
}

void MenuItemSpritePro::selected()
{
	_selected = true;

	if (SelEffect_ChangeColor & m_selEffectType)
	{
		setColor(Color3B(150,150,150));
        
        if (m_labelOnMenu) {
            m_labelOnMenu->setColor(Color3B(150, 150, 150));
        }
        
        if (m_particleOnMenu) {
            m_particleOnMenu->setColor(Color3B(150, 150, 150));
        }
	}
	if(SelEffect_Mag & m_selEffectType)
	{
		Action *action = getActionByTag(kZoomActionTag);
		if (action)
		{
			this->stopAction(action);
		}
		else
		{
			m_fOriginalScale = this->getScale();
		}

		ScaleTo *zoomAction = ScaleTo::create(0.1f, m_fOriginalScale*1.1f);
		EaseSineOut *easeAction = EaseSineOut::create(zoomAction);
		easeAction->setTag(kZoomActionTag);
		this->runAction(easeAction);
	}
    if(SelEffect_Decend & m_selEffectType)
    {
        m_originY = getPositionY();
        
        setPositionY(m_originY - 3);
    }
}

void MenuItemSpritePro::unselected()
{
	_selected = false;

	if (SelEffect_ChangeColor & m_selEffectType)
	{
	    setColor(Color3B(255,255,255));
        
        if (m_labelOnMenu) {
            m_labelOnMenu->setColor(Color3B(255, 255, 255));
        }
        
        if (m_particleOnMenu) {
            m_particleOnMenu->setColor(Color3B(255, 255, 255));
        }
	}
	if(SelEffect_Mag & m_selEffectType)
	{
		this->stopActionByTag(kZoomActionTag);

		ScaleTo *zoomAction = ScaleTo::create(0.1f, m_fOriginalScale);
		EaseSineOut *easeAction = EaseSineOut::create(zoomAction);
		easeAction->setTag(kZoomActionTag);
		this->runAction(easeAction);
	}
    if(SelEffect_Decend & m_selEffectType)
    {
        setPositionY(m_originY);
    }
}

void MenuItemSpritePro::setLabel(LabelTTF *label)
{
    if (m_labelOnMenu) {
        m_labelOnMenu->removeFromParentAndCleanup(true);
        m_labelOnMenu = nullptr;
    }
    
    m_labelOnMenu = label;
    addChild(m_labelOnMenu);
    
    int sizeMax = _normalImage->getContentSize().width - 16;
    
    //if (m_labelOnMenu->getContentSize().width > sizeMax) {
        
        m_labelOnMenu->setScale(sizeMax/m_labelOnMenu->getContentSize().width);
    //}
    
    m_labelOnMenu->setPosition(Point(_normalImage->getContentSize().width/2, _normalImage->getContentSize().height/2));
}

void MenuItemSpritePro::setParticle(ParticleSystem *par)
{
    if (m_particleOnMenu) {
        m_particleOnMenu->removeFromParentAndCleanup(true);
        m_particleOnMenu = nullptr;
    }
    
    m_particleOnMenu = par;
    addChild(m_particleOnMenu);
    
    int sizeMax = _normalImage->getContentSize().width - 16;
    
    //if (m_labelOnMenu->getContentSize().width > sizeMax) {
    
    //m_particleOnMenu->setScale(sizeMax/m_particleOnMenu->getContentSize().width);
    //}
    
    m_particleOnMenu->setPosition(Point(_normalImage->getContentSize().width/2, _normalImage->getContentSize().height/2));
    
}