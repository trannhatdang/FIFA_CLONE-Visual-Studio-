#ifndef ANIMATOR_H_
#define ANIMATOR_H_

#include "Component.h"
#include "../Animation.h"
#include "../AnimationNode.h"

class Animator : public Component
{
	private:
		SDL_Renderer* m_renderer;
		AnimationNode* m_currNode = nullptr;
		AnimationNode* m_startNode;
		std::unique_ptr<AnimationNode> m_anyNode;

		std::vector<std::unique_ptr<AnimationNode>> m_animations;
	public:
		Animator(GameObject* obj, SDL_Renderer* renderer);
		void OnStart();
		void OnIterate();
		std::unique_ptr<Component> copy();

		AnimationNode* AddAnimation(AnimationNode* prevNode, const std::string& filepath, int width, int height, int num_frame, int scale, cond_func* cond);
		AnimationNode* AddAnimation(AnimationNode* node);
		AnimationNode* CopyAnyNode(AnimationNode* node);
		AnimationNode* GetAnyNode();
		void SetStartNode(AnimationNode* node);
};

#endif
