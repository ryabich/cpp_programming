#include "node.h"


	DateComparisonNode::DateComparisonNode(const Comparison& _cmp, const Date& _date) :
	cmp(_cmp), date(_date) {}

	bool DateComparisonNode::Evaluate(const Date& _date, const string& event) const {
		if (cmp == Comparison::Less) return _date < date;
		if (cmp == Comparison::LessOrEqual) return _date <= date;
		if (cmp == Comparison::Greater) return _date > date;
		if (cmp == Comparison::GreaterOrEqual) return _date >= date;
		if (cmp == Comparison::Equal) return _date == date;
		if (cmp == Comparison::NotEqual) return _date != date;
	}

	EventComparisonNode::EventComparisonNode(const Comparison& _cmp, const string& _event) :
	cmp(_cmp), event(_event) {}

	bool EventComparisonNode::Evaluate(const Date& date, const string& _event) const {
		if (cmp == Comparison::Less) return _event < event;
		if (cmp == Comparison::LessOrEqual) return _event <= event;
		if (cmp == Comparison::Greater) return _event > event;
		if (cmp == Comparison::GreaterOrEqual) return _event >= event;
		if (cmp == Comparison::Equal) return _event == event;
		if (cmp == Comparison::NotEqual) return _event != event;
	}



	LogicalOperationNode::LogicalOperationNode (const LogicalOperation op,
			shared_ptr<Node> _left, shared_ptr<Node> _right) :
			left(_left), right(_right), logic_operation(op) {}

	bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
		if (logic_operation == LogicalOperation::And) return
				left->Evaluate(date, event) && right->Evaluate(date, event);
		return left->Evaluate(date, event) || right->Evaluate(date, event);
	}


	bool EmptyNode::Evaluate(const Date& date, const string& event) const {
		return true;
	}



