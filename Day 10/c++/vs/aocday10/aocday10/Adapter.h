#pragma once

//
// Created by Luke Belinc on 3/29/21.
//


class Adapter {

public:

    Adapter() {
        num_adapters = 0;
        begin = new Connector(0);
        curr = begin;
        end = begin;
    }

    ~Adapter() {
        delete begin;
    }

    struct Connector {
        int jolts;
        Connector* next;
        Connector* prev;

        explicit Connector(int j) {
            jolts = j;
            next = nullptr;
            prev = nullptr;
        }

        ~Connector() {
            delete next;
        }
    };

    unsigned int size() const {
        return num_adapters;
    }

    int get_jolts() {
        if (curr != nullptr)
            return curr->jolts;
        else return -1;
    }

    void add_next(int jolts) {
        end->next = new Connector(jolts);
        end->next->prev = end;
        end = end->next;
        begin->prev = end;

        ++num_adapters;
    }

    bool has_next() {
        if (curr->next != nullptr) {
            return true;
        }

        return false;
    }

    Connector*& next() {
        curr = curr->next;
        return curr;
    }

    Connector*& prev() {
        curr = curr->prev;
        return curr;
    }

private:
    Connector* begin;
    Connector* end;
    Connector* curr;

    unsigned int num_adapters;

};