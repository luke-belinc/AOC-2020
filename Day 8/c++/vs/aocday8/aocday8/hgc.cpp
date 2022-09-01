#include "hgc.h"
#include <iostream>

HGC::HGC() 
{
	acc_total = 0;
    broken_line = -1;
}

void HGC::insert_op(HGC::operation op, int arg) 
{
	this->op_codes.push_back(std::pair<HGC::operation, int>(op, arg));
	curr_op = op_codes.begin();
}

void HGC::update_history(const std::vector<std::pair<HGC::operation, int> >::iterator& op)
{
	line_history.insert(op - op_codes.begin());
}

bool HGC::check_history(const std::vector<std::pair<HGC::operation, int> >::iterator& op)
{
    if (curr_op != op_codes.end()) {
        if (line_history.find(op - op_codes.begin()) != line_history.end())
        {
            return true;
        }
    }
       
    return false;
}

bool HGC::run()
{

    // run the operation
    // uncomment cout lines to print operation to console
	switch (curr_op->first) {
	case HGC::operation::acc:
		//std::cout << "\n(" << curr_op - op_codes.begin() << ") " << "Adding " << curr_op->second << " to the accumulator..."  ;
		acc_total += curr_op->second;
		next_op();
		break;

	case HGC::operation::jmp:
		//std::cout << "\n(" << curr_op - op_codes.begin() << ") " << "Jumping " << curr_op->second << " lines...";
		jump_op(curr_op->second);
		break;

	case HGC::operation::nop:
		//std::cout << "\n(" << curr_op - op_codes.begin() << ") " << "Nop " << curr_op->second << "...";
		next_op();
		break;

	default:
		return false;
	}

	return true;
}

const std::vector<std::pair<HGC::operation, int> >::iterator& HGC::jump_op(const size_t& pos)
{
    if (curr_op + pos < op_codes.end()) {
        update_history(curr_op);
        curr_op += pos;
    }
    else {
        curr_op = op_codes.end();
    }

    return curr_op;
}

const std::vector<std::pair<HGC::operation, int> >::iterator& HGC::next_op()
{
	update_history(curr_op);
	return ++curr_op;
}

const std::vector<std::pair<HGC::operation, int> >::iterator& HGC::get_curr_op()
{
	return curr_op;
}

const std::vector<std::pair<HGC::operation, int> >& HGC::get_op_codes()
{
    return op_codes;
}

const int HGC::get_acc()
{
	return acc_total;
}

void HGC::clear_history()
{
	line_history.clear();
}

void HGC::reset_acc() 
{
	acc_total = 0;
}

void HGC::reset_curr_op()
{
    curr_op = op_codes.begin();
}


int HGC::find_bugged_line(std::vector<std::pair<int, int> >& operations)
{
    // set of lines that result in the program not terminating
    std::set<int> not_terminating;

    // current line to be modified
    size_t current_line = 0;

    do {

        size_t temp_line = current_line;

        if (operations[current_line].first == 2) {

            temp_line += operations[current_line].second;
            if (find_bugged_line_helper(operations, not_terminating, temp_line)) {
                break;
            }

            ++current_line;
        }
        else if (operations[current_line].first == 1) {

            ++temp_line;
            if (find_bugged_line_helper(operations, not_terminating, temp_line)) {
                break;
            }

            current_line += operations[current_line].second;
        }
        else {

            ++current_line;
        }

    } while (current_line < operations.size());

    if (current_line < operations.size()) {
        op_codes[current_line].first = (op_codes[current_line].first == HGC::operation::jmp) ? HGC::operation::nop : HGC::operation::jmp;
    }

    return current_line;

}

bool HGC::find_bugged_line_helper(const std::vector<std::pair<int, int>>& operations, std::set<int>& not_terminating, size_t& current_line)
{
    if (not_terminating.find(current_line) != not_terminating.end())
    {
        return false;
    }

    not_terminating.insert(current_line);

    if (operations[current_line].first == 1) {
        current_line += operations[current_line].second;
    }
    else {
        ++current_line;
    }

    if (current_line >= operations.size()) {
        return false;
    }
    
    if (current_line == operations.size() - 1) {
        return true;
    }

    return find_bugged_line_helper(operations, not_terminating, current_line);
}