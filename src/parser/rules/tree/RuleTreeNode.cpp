#include "RuleTreeNode.h"
#include "../Rules.h"

namespace Parser {

	RuleTreeNode::RuleTreeNode(TokenType val) : m_value(val) {}

	TokenType RuleTreeNode::getValue() const {
		return m_value;
	}

	const std::unordered_map<TokenType, std::unique_ptr<RuleTreeNode>>& RuleTreeNode::getChildren() const {
		return m_children;
	}

	const std::optional<RuleTransformFunction>& RuleTreeNode::getTransformFunction() const {
		return m_transformFunction;
	}

	RuleTreeNode& RuleTreeNode::addChild(TokenType type) {
		auto [it, _] = m_children.try_emplace(type, std::make_unique<RuleTreeNode>(type));

		return *it->second;
	}

	void RuleTreeNode::setTransform(RuleTransformFunction transformFunction) {
		m_transformFunction = transformFunction;
	}

}