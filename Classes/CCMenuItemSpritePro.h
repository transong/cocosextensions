/****************************************************************************
Songyuan
*/

#ifndef __CCMENU_ITEM_SPRITEPRO_H__
#define __CCMENU_ITEM_SPRITEPRO_H__

#include "cocos2d.h"

using namespace cocos2d;

enum 
{
	SelEffect_None,
	SelEffect_ChangeColor = 1 << 1,
	SelEffect_Mag = 1 << 2,
    SelEffect_Decend = 1 << 3,
};

class MenuItemSpritePro : public MenuItemSprite
{
public :
    MenuItemSpritePro();
    ~MenuItemSpritePro();
    
	void selected();
	void unselected();

	void setEnabled(bool bEnabled, bool withColor = false)
	{
		_enabled = bEnabled;

		if (withColor)
		{
			if(bEnabled)
				setColor(ccc3(255,255,255));
			else
				setColor(ccc3(130,130,130));
		}
	}

	//RGBAProtocol
	void setColor(const Color3B& color);
	const Color3B& getColor(void);

	GLubyte getOpacity(void);
	void setOpacity(GLubyte opacity);

	static MenuItemSpritePro* create(Node* sprite);
	static MenuItemSpritePro* create(Node* sprite, const ccMenuCallback& callback);
	bool initFromNormalSprite(Node* sprite, const ccMenuCallback& callback);
    
	float        m_fOriginalScale;
    
    float        m_originY;

	int          m_selEffectType;
    
    void setLabel(LabelTTF *label);
    LabelTTF *m_labelOnMenu;
    
    void setParticle(ParticleSystem *par);
    ParticleSystem *m_particleOnMenu;

};
#endif //__CCMENU_ITEM_SPRITEPRO_H__