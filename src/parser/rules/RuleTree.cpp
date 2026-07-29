#include "RuleTree.h"

#include <optional>
#include <iostream>

namespace Parser {

	RuleTree& RuleTree::getInstance() {
		
		static RuleTree instance;
		return instance;
	}

	RuleTree::RuleTree() : m_root(TokenType::Empty) {
		_readRules();
	};

	const RuleTreeNode& RuleTree::getRoot() {
		return m_root;
	}


	void RuleTree::_readRules() {
		for (const auto& [target, rules] : RULES) {

			RuleTreeNode* lastNode = &m_root;

			for (auto rule : rules) {
				
				for (TokenType token : rule) {
					lastNode = &lastNode->addChild(token);
				}
				lastNode->setTerminalRule(target);

			}

			
		}

	}


}