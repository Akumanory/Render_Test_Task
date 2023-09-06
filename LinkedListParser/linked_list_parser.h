#pragma once

#include <string>

namespace linked_list_parser
{

struct ListNode
{
    ListNode*   prev;
    ListNode*   next;
    ListNode*   rand;
    std::string data;
};

class List
{
public:
    void Serialize(FILE* file);
    void Deserialize(FILE* file);

private:
    ListNode* head;
    ListNode* tail;
    int       count;
};


} // linked_list_parser