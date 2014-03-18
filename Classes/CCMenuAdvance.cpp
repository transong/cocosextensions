#include "CCMenuAdvance.h"
#include "CCDirector.h"
#include "Utility.h"

//Menu
MenuAdvance::MenuAdvance()
:m_menuType(MenuType_Block)
,m_priority(0)
,m_isLarger(true)
,m_isEnabled(true)
,m_eventListener(nullptr)
{
	m_responseRect = Rect(0, 0, CCDirector::getInstance()->getWinSize().width, CCDirector::getInstance()->getWinSize().height);

	m_largerRect = Rect(-2, -2, 2, 2);

	//m_tapEnd = "sfx_hit.mp3";
}

MenuAdvance* MenuAdvance::create()
{
    return MenuAdvance::create(nullptr, nullptr);
}

MenuAdvance * MenuAdvance::create(MenuItem* item, ...)
{
    va_list args;
    va_start(args,item);
    
    MenuAdvance *ret = MenuAdvance::createWithItems(item, args);
    
    va_end(args);
    
    return ret;
}

MenuAdvance* MenuAdvance::createWithArray(const Vector<MenuItem*>& arrayOfItems)
{
    auto ret = new MenuAdvance();
    if (ret && ret->initWithArray(arrayOfItems))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    return ret;
}

MenuAdvance* MenuAdvance::createWithItems(MenuItem* item, va_list args)
{
    Vector<MenuItem*> items;
    if( item )
    {
        items.pushBack(item);
        MenuItem *i = va_arg(args, MenuItem*);
        while(i)
        {
            items.pushBack(i);
            i = va_arg(args, MenuItem*);
        }
    }
    
    return MenuAdvance::createWithArray(items);
}

MenuAdvance* MenuAdvance::createWithItem(MenuItem* item)
{
    return MenuAdvance::create(item, nullptr);
}

bool MenuAdvance::initWithArray(const Vector<MenuItem*>& arrayOfItems)
{
	if (Layer::init())
	{
		_enabled = true;
		// menu in the center of the screen
		Size s = Director::getInstance()->getWinSize();

		this->ignoreAnchorPointForPosition(true);
		setAnchorPoint(Point(0.5f, 0.5f));
		this->setContentSize(s);

		setPosition(Point(s.width / 2, s.height / 2));

		int z = 0;

		for (auto& item : arrayOfItems)
		{
			this->addChild(item, z);
			z++;
		}

		_selectedItem = nullptr;
		_state = Menu::State::WAITING;

		// enable cascade color and opacity on menus
		setCascadeColorEnabled(true);
		setCascadeOpacityEnabled(true);

		return true;
	}
	return false;
}

void MenuAdvance::onEnter()
{
	Menu::onEnter();

	m_eventListener = EventListenerTouchOneByOne::create();
	m_eventListener->setSwallowTouches((m_menuType == MenuType_Ghost) ? false : true);

	m_eventListener->onTouchBegan = CC_CALLBACK_2(MenuAdvance::onTouchBegan, this);
	m_eventListener->onTouchMoved = CC_CALLBACK_2(MenuAdvance::onTouchMoved, this);
	m_eventListener->onTouchEnded = CC_CALLBACK_2(MenuAdvance::onTouchEnded, this);
	m_eventListener->onTouchCancelled = CC_CALLBACK_2(MenuAdvance::onTouchCancelled, this);

	if (0 == m_priority)
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_eventListener, this);
	}
	else
	{
		_eventDispatcher->addEventListenerWithFixedPriority(m_eventListener, m_priority);
	}
}

void MenuAdvance::onExit()
{
	Menu::onExit();

	if (m_eventListener)
	{
		_eventDispatcher->removeEventListener(m_eventListener);
		m_eventListener = nullptr;
	}
}

MenuItem* MenuAdvance::getItemForTouch(Touch *touch)
{
	Point touchLocation = touch->getLocation();
    
    if (!_children.empty()) {
        
        for (auto iter = _children.crbegin(); iter != _children.crend(); ++iter) {
            
            MenuItem* child = dynamic_cast<MenuItem*>(*iter);
            if (child && child->isVisible() && child->isEnabled()) {
                
                Point local = child->convertToNodeSpace(touchLocation);
                Rect r = child->rect();
                r.origin = Point::ZERO;
                
                if (m_isLarger) {
                    r.origin =  Point(m_largerRect.origin.x, m_largerRect.origin.y);
					r.size = Size(r.size.width + m_largerRect.size.width - m_largerRect.origin.x, r.size.height + m_largerRect.size.height - m_largerRect.origin.y);
                }
                
                if (r.containsPoint(local)) {
                    return child;
                }
            }
        }
    }
    
	return nullptr;
}

bool MenuAdvance::onTouchBegan(Touch* touch, Event* event)
{
	Point a = touch->getLocation();

	if (!m_responseRect.containsPoint(a))
	{
		return true;
	}

	if (_state != Menu::State::WAITING || ! _visible)
	{
		return false;
	}

	for (Node *c = this->_parent; c != NULL; c = c->getParent())
	{
		if (c->isVisible() == false)
		{
			return false;
		}
	}

	_selectedItem = this->getItemForTouch(touch);
	if (_selectedItem)
	{
		
		_state = Menu::State::TRACKING_TOUCH;
        _selectedItem->selected();
        
		if (MenuType_PreAct == m_menuType)
		{
			_selectedItem->activate();

			if(!m_tapEnd.empty())
				Utility::playSFX(m_tapEnd.c_str(), false, 0.5f);
		}
		
		return true;
	}

	return false;
	
}

void MenuAdvance::onTouchMoved(Touch* touch, Event* event)
{
	if (MenuType_Ghost == m_menuType || MenuType_PreAct == m_menuType)
	{
		if (_selectedItem && touch->getLocation().getDistanceSq(touch->getPreviousLocation()) > 16)
		{
			_selectedItem->unselected();
			_state = Menu::State::WAITING;
		}
	}
	else if(MenuType_Block == m_menuType)
	{
		MenuItem *currentItem = this->getItemForTouch(touch);
		if (currentItem != _selectedItem  )
		{
			if (_selectedItem)
			{
				_selectedItem->unselected();
			}
			_selectedItem = currentItem;
			if (_selectedItem)
			{
				_selectedItem->selected();
			}
		}
	}
}

void MenuAdvance::onTouchEnded(Touch* touch, Event* event)
{

	if (MenuType_Ghost == m_menuType)
	{
		CC_UNUSED_PARAM(touch);
		CC_UNUSED_PARAM(event);
		if (_state == Menu::State::TRACKING_TOUCH && _selectedItem)
		{
			if (m_isEnabled)
			{
				_selectedItem->unselected();
				_selectedItem->activate();
			}

			if(!m_tapEnd.empty())
			  Utility::playSFX(m_tapEnd.c_str(), false, 0.5f);
		}
		_state = Menu::State::WAITING;
	}
	else if (MenuType_PreAct == m_menuType)
	{
		CC_UNUSED_PARAM(touch);
		CC_UNUSED_PARAM(event);
		if (_state == Menu::State::TRACKING_TOUCH && _selectedItem)
		{
			if (m_isEnabled)
			   _selectedItem->unselected();
		}
		_state = Menu::State::WAITING;
	}
	else if(MenuType_Block == m_menuType)
	{
		if (_selectedItem && _selectedItem->isEnabled())
		{
			if (m_isEnabled)
			{
				_selectedItem->unselected();
				_selectedItem->activate();
			}

			if(!m_tapEnd.empty())
			   Utility::playSFX(m_tapEnd.c_str(), false, 0.5f);
		}
		_state = Menu::State::WAITING;
	}
}

void MenuAdvance::onTouchCancelled(Touch* touch, Event* event)
{
    _state = Menu::State::TRACKING_TOUCH;
    
    CCMenu::onTouchCancelled(touch, event);
}

void MenuAdvance::setEnabled( bool value, bool withColor )
{
    for (auto iter = _children.crbegin(); iter != _children.crend(); ++iter) {
        
        MenuItemSpritePro* child = dynamic_cast<MenuItemSpritePro*>(*iter);
        if (child && child->isVisible() && child->isEnabled()) {
        
            child->setEnabled(value, withColor);
        }
    }
}




