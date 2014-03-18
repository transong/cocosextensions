#pragma once

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class ScrollNode : public Node
{
public:
	ScrollNode(CCRect rc);
	~ScrollNode();
	Rect m_rect;
	void visit(Renderer *renderer, const kmMat4& parentTransform, bool parentTransformUpdated) override;

	void beforeDraw();
    void onBeforeDraw();

    void afterDraw();
    void onAfterDraw();

	CustomCommand _beforeDrawCommand;
	CustomCommand _afterDrawCommand;
};