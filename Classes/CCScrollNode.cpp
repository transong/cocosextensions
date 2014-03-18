#include "CCScrollNode.h"
#include "Utility.h"

void ScrollNode::visit(Renderer *renderer, const kmMat4& parentTransform, bool parentTransformUpdated)
{


	// quick return if not visible
	if (!isVisible())
	{
		return;
	}

	bool dirty = parentTransformUpdated || _transformUpdated;
	if(dirty)
		_modelViewTransform = this->transform(parentTransform);
	_transformUpdated = false;

	// IMPORTANT:
	// To ease the migration to v3.0, we still support the kmGL stack,
	// but it is deprecated and your code should not rely on it
	kmGLPushMatrix();
	kmGLLoadMatrix(&_modelViewTransform);

	beforeDraw();

	if (!_children.empty())
	{
		int i=0;

		// draw children zOrder < 0
		for( ; i < _children.size(); i++ )
		{
			Node *child = _children.at(i);
			if ( child->getLocalZOrder() < 0 )
			{
				child->visit(renderer, _modelViewTransform, dirty);
			}
			else
			{
				break;
			}
		}

		// this draw
		this->draw(renderer, _modelViewTransform, dirty);

		// draw children zOrder >= 0
		for( ; i < _children.size(); i++ )
		{
			Node *child = _children.at(i);
			child->visit(renderer, _modelViewTransform, dirty);
		}

	}
	else
	{
		this->draw(renderer, _modelViewTransform, dirty);
	}

	afterDraw();

	kmGLPopMatrix();

}

ScrollNode::ScrollNode(Rect rc)
{
	m_rect = rc;
}

ScrollNode::~ScrollNode()
{
    
}

void ScrollNode::beforeDraw()
{
	_beforeDrawCommand.init(_globalZOrder);
	_beforeDrawCommand.func = CC_CALLBACK_0(ScrollNode::onBeforeDraw, this);
	Director::getInstance()->getRenderer()->addCommand(&_beforeDrawCommand);
}

void ScrollNode::onBeforeDraw()
{
	float systemRate = 1.0f;

#if CC_PLATFORM_WIN32 == CC_TARGET_PLATFORM
	systemRate = Director::getInstance()->getOpenGLView()->getFrameZoomFactor();
#endif

	glEnable(GL_SCISSOR_TEST);

	glScissor(m_rect.origin.x * Utility::getDeviceScreenRate().x * systemRate, m_rect.origin.y * Utility::getDeviceScreenRate().y * systemRate, m_rect.size.width * Utility::getDeviceScreenRate().x * systemRate, m_rect.size.height * Utility::getDeviceScreenRate().y * systemRate);
}

void ScrollNode::afterDraw()
{
	_afterDrawCommand.init(_globalZOrder);
	_afterDrawCommand.func = CC_CALLBACK_0(ScrollNode::onAfterDraw, this);
	Director::getInstance()->getRenderer()->addCommand(&_afterDrawCommand);
}

void ScrollNode::onAfterDraw()
{
	glDisable(GL_SCISSOR_TEST);
}
