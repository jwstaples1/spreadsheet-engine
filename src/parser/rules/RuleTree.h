#pragma once

#include "Rules.h"
#include "tree/RuleTreeNode.h"

#include <memory>

namespace Parser {

	class RuleTree {

	public:
		static RuleTree& getInstance();

		int getSize();
		const RuleTreeNode& getRoot();
		
		RuleTree(const RuleTree&) = delete;
		RuleTree& operator=(const RuleTree&) = delete;
		RuleTree(RuleTree&&) = delete;
		RuleTree& operator=(RuleTree&&) = delete;

		~RuleTree() = default;

	private:
		RuleTree();

		RuleTreeNode m_root;
		int m_size;

		void _readRules();
	};


}