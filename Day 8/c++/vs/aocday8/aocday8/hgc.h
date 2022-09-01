#pragma once
#include <vector>
#include <set>
#include <string>

class HGC
{
public:
	enum class operation {
		acc, // accumulator
		jmp, // jump
		nop  // no operation
	};

	HGC();

	void insert_op(operation op, int arg);

	void clear_history();
	void reset_acc();
	void reset_curr_op();

	void update_history(const std::vector<std::pair<operation, int> >::iterator& op);
	bool check_history(const std::vector<std::pair<operation, int> >::iterator& op);

	bool run();

	const std::vector<std::pair<operation, int> >::iterator& jump_op(const size_t& pos);
	const std::vector<std::pair<operation, int> >::iterator& next_op();
	const std::vector<std::pair<operation, int> >::iterator& get_curr_op();

	const std::vector<std::pair<HGC::operation, int> >& get_op_codes();

	int find_bugged_line(std::vector<std::pair<int, int>>& operations);
	bool find_bugged_line_helper(const std::vector<std::pair<int, int>>& operations, std::set<int>& not_winning, size_t& current_line);

	const int get_acc();

private:

	int acc_total;

	size_t broken_line;

	std::vector<std::pair<operation, int> >::iterator curr_op;

	std::vector<std::pair<operation, int> > op_codes;

	std::set<int> line_history;
	std::set<int> line_not_winning;
};

