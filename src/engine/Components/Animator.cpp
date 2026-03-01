#include "engine/Components/Animator.h"

Animator::Animator(GameObject* obj, SDL_Renderer* renderer) : Component("Animator", obj), m_renderer(renderer)
{
	m_anyNode = std::make_unique<AnimationNode>();
}

void Animator::OnStart()
{
	if(m_startNode)
	{
		m_currNode = m_startNode;
	}
}

void Animator::OnIterate()
{
	for(auto i = 0; i < m_anyNode->conds.size(); ++i)
	{
		if(m_anyNode->conds[i](this->gameObject))
		{
			m_currNode = m_anyNode->adj[i];
			return;
		}
	}

	if(!m_currNode) return;

	for(auto i = 0; i < m_currNode->conds.size(); ++i)
	{
		if(m_currNode->conds[i](this->gameObject))
		{
			m_currNode = m_currNode->adj[i];
			return;
		}
	}
}

AnimationNode* Animator::AddAnimation(AnimationNode* prevNode, const std::string& filepath, int width, int height, int num_frame, int scale, cond_func* cond)
{
	AnimationNode* node = new AnimationNode;
	node->anim = std::make_unique<Animation>(m_renderer, filepath, width, height, num_frame, scale);

	if(prevNode)
	{
		prevNode->adj.push_back(node);
		prevNode->conds.push_back(cond);
	}
	else
	{
		m_anyNode->adj.push_back(node);
		m_anyNode->conds.push_back(cond);
	}

	m_animations.emplace_back(node);

	return node;
}

AnimationNode* Animator::AddAnimation(AnimationNode* node)
{
	this->AddAnimation(nullptr, node->anim->m_filepath, node->anim->m_width, node->anim->m_height, node->anim->m_num_frames, node->anim->m_scale, nullptr);
	return nullptr;
}

AnimationNode* Animator::CopyAnyNode(AnimationNode* node)
{
	return nullptr;

}

AnimationNode* Animator::GetAnyNode()
{
	return m_anyNode.get();
}

//I WILL NEVER COPY

std::unique_ptr<Component> Animator::copy()
{
	return nullptr;
	Animator* anim = new Animator(gameObject, m_renderer);

	anim->CopyAnyNode(m_anyNode.get());
	return std::unique_ptr<Animator>(anim);
}
