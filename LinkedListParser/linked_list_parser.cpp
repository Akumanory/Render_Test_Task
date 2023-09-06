#include "linked_list_parser.h"
#include <cstddef>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <unordered_map>

// TODO: only for debug and develop reasons, remove after
#include <tuple>
#include <utility>
//

#include "Utils/defines.h"

namespace linked_list_parser
{

void List::Serialize(FILE *file)
{
    if (file == nullptr)
        throw std::runtime_error(FUNC_NAME + "File is nullptr, can't write to it");

    if (count < 0)
        throw std::runtime_error(FUNC_NAME + " --> Count of nodes is 0, can't not serialize anything");

    std::unordered_map<ListNode*, int> idx_to_node_map;

    int node_idx = 0;
    for (ListNode* it = head; it != nullptr; it = it->next)
    {
        idx_to_node_map.insert(std::make_pair(it, node_idx));
        node_idx++;
    }

    if (idx_to_node_map.size() != static_cast<size_t>(count))
        throw std::runtime_error(FUNC_NAME + "Number of nodes doesn't equal to count variable");

    // Write count to first line
    if (fwrite(&count, sizeof(count), 1, file) != 1)
        throw std::runtime_error(FUNC_NAME + " --> Error writing count value to file");

    for (ListNode* it = head; it != nullptr; it = it->next)
    {
        // serch corresponding idx for rand pointer
        int rand_idx = -1;
        if (auto search = idx_to_node_map.find(it); search != idx_to_node_map.end())
            rand_idx = search->second;

        // Write rand poitner idx
        if (fwrite(&rand_idx, sizeof(rand_idx), 1, file) != 1)
            throw std::runtime_error(FUNC_NAME + " --> Error writing rand idx value to file");
        // Write data size
        size_t data_size = it->data.size();
        if (fwrite(&data_size, sizeof(data_size), 1, file) != 1)
            throw std::runtime_error(FUNC_NAME + " --> Error writing data size to file");
        // Write data
        if (fwrite(&it->data, sizeof(it->data), 1, file) != 1)
            throw std::runtime_error(FUNC_NAME + " --> Error writing data value to file");
    }
}

void List::Deserialize(FILE *file)
{
    if (file == nullptr)
        throw std::runtime_error(FUNC_NAME + " --> File is nullptr, can't read from it");


    count = -1;

    if (fread(&count, sizeof(count), 1, file) != 1)
        throw std::runtime_error(FUNC_NAME + "Error can't read count value from file");

    if (count == 0)
        return;

    // remove old data
    while (head != tail)
    {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
    delete head;

    // reinit head and tail
    head = new ListNode();
    tail = head;

    // pointer and idx in list
    std::unordered_map<ListNode*, int> idx_of_node_map;
    // idx of node and idx of node pointed to by rand
    std::unordered_map<int, int>  idx_to_rand_idx_map;

    for (int i = 0; i < count; i++)
    {
        if (!tail->data.empty())
        {
            ListNode* temp = tail;
            tail = new ListNode();
            temp->next = tail;
            tail->prev = temp;
        }




        // if (fread(&count, sizeof(count), 1, file))
        //     throw std::runtime_error(FUNC_NAME + "Error can't read count value from file");

    }

}

} // linked_list_parser