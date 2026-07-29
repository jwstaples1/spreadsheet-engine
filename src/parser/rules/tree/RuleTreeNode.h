#pragma once

#include "../../tokens/TokenType.h"

#include <unordered_map>
#include <memory>
#include <optional>

namespace Parser {

	class RuleTreeNode {

	public:
		RuleTreeNode(TokenType val);

		TokenType getValue() const;
		const std::optional<TokenType>& getTerminalRule() const;
		const std::unordered_map<TokenType, std::unique_ptr<RuleTreeNode>>& getChildren() const;

		RuleTreeNode& addChild(TokenType type);
		void setTerminalRule(TokenType type);

	private:
		TokenType m_value;
		std::unordered_map<TokenType, std::unique_ptr<RuleTreeNode>> m_children;
		std::optional<TokenType> m_terminalRule;
	};

}