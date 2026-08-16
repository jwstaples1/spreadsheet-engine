#pragma once

#include "../../tokens/TokenType.h"
#include "../Rules.h"

#include <unordered_map>
#include <memory>
#include <optional>

namespace Parser {

	class RuleTreeNode {

	public:
		RuleTreeNode(TokenType val);

		TokenType getValue() const;
		const std::optional<RuleTransformFunction>& getTransformFunction() const;
		const std::unordered_map<TokenType, std::unique_ptr<RuleTreeNode>>& getChildren() const;

		RuleTreeNode& addChild(TokenType type);
		void setTransform(RuleTransformFunction type);

	private:
		TokenType m_value;
		std::unordered_map<TokenType, std::unique_ptr<RuleTreeNode>> m_children;
		std::optional<RuleTransformFunction> m_transformFunction;
	};

}