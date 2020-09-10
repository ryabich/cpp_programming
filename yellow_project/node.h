#pragma once
#include "database.h"
#include <memory>

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

enum class LogicalOperation {
	And,
	Or
};


class Node {
public:
	virtual bool Evaluate (const Date& date, const string& event) const = 0;
};


class DateComparisonNode : public Node {
public:
	DateComparisonNode(const Comparison& _cmp, const Date& _date);

	bool Evaluate(const Date& _date, const string& event) const override;

private:
	const Comparison cmp;
	const Date date;
};


class EventComparisonNode : public Node {
public:
	EventComparisonNode(const Comparison& _cmp, const string& _event);

	bool Evaluate(const Date& date, const string& _event) const override;

private:
	const Comparison cmp;
	const string event;
};


class LogicalOperationNode : public Node {
public:
	LogicalOperationNode (const LogicalOperation op,
			shared_ptr<Node> _left, shared_ptr<Node> _right);

	bool Evaluate(const Date& date, const string& event) const override;

private:
	const shared_ptr<Node> left, right;
	const LogicalOperation logic_operation;

};


class EmptyNode : public Node {
public:
	bool Evaluate(const Date& date, const string& event) const override;
};
