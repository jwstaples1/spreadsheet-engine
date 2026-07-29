#include "RuleTree.h"

#include <optional>
#include <iostream>

namespace Parser {

	RuleTree& RuleTree::getInstance() {
		
		static RuleTree instance;
		return instance;
	}

	RuleTree::RuleTree() : m_root(TokenType::Empty), m_size(1) {
		_readRules();
	};

	int RuleTree::getSize() {
		return m_size;
	}

	const RuleTreeNode& RuleTree::getRoot() {
		return m_root;
	}


	void RuleTree::_readRules() {
		for (const auto& [target, rule] : RULES) {

			RuleTreeNode* lastNode = &m_root;

			for (TokenType token : rule) {
				lastNode = &lastNode->addChild(token);
			}

			lastNode->setTerminalRule(target);
		}

	}


}