#include "linked_list_parser.h"
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>

// TODO(akumanory): only for debug and develop reasons, remove after
#include <tuple>
#include <utility>
//

#include "Utils/defines.h"

namespace linked_list_parser {

void List::Serialize(FILE *file) {
    if (file == nullptr)
        throw std::runtime_error(FUNC_NAME + "File is nullptr, can't write to it");
    
    // NOTE(akumanory): check how much data is written 
    size_t fwrite_ret = 0;

    if (count < 0)
        throw std::runtime_error(FUNC_NAME + " --> Count of nodes is 0, can't not serialize anything");

    // NOTE(akumanory): this node needed for rand idx
    // this help to serialize in one go
    std::unordered_map<ListNode*, int> idx_to_node_map;

    int node_idx = 0;
    for (ListNode* it = head; it != nullptr; it = it->next) {
        idx_to_node_map.insert(std::make_pair(it, node_idx));
        node_idx++;
    }

    if (idx_to_node_map.size() != static_cast<size_t>(count))
        throw std::runtime_error(FUNC_NAME + "Number of nodes doesn't equal to count variable");

    // TODO(akumanory): dont't need counts if we going to use structs (wrong we
    // need to count string size because instead of chars we write pointer)

    // Write count to first line
    fwrite_ret = fwrite(&count, sizeof(count), 1, file);
    if (fwrite_ret < 1)
        throw std::runtime_error(FUNC_NAME + "Error writing count value to file");

    for (ListNode* it = head; it != nullptr; it = it->next) {
// #pragma region rand_idx_write
        // serch corresponding idx for rand pointer
        int rand_idx = -1;
        if (auto search = idx_to_node_map.find(it); search != idx_to_node_map.end())
            rand_idx = search->second;
        // Write rand poitner idx
        fwrite_ret = fwrite(&rand_idx, sizeof(rand_idx), 1, file);
        if (fwrite_ret < 1)
            throw std::runtime_error(FUNC_NAME + "Error writing rand idx value to file");
// #pragma endregion rand_idx_write

        // Write data size
        size_t data_size = it->data.size();
        fwrite_ret = fwrite(&data_size, sizeof(data_size), 1, file);
        if (fwrite_ret < 1)
            throw std::runtime_error(FUNC_NAME + "Error writing data size to file");

        // Write data
        // NOTE(akumanory): need to clarify is it really possible 
        // to write only one by one or the whole string  
        fwrite_ret = fwrite(&it->data[0], sizeof(char), data_size, file);
        if (fwrite_ret < data_size)
            throw std::runtime_error(FUNC_NAME + "Error writing data value to file");
    }
    // TODO(akumanory): maybe need to add fclose for this
    fclose(file);
}

// TODO(akumanory): test, remove later
void test_deserialize_cout(FILE *file) {
    // NOTE(akumanory): check how much data is read
    size_t fread_ret = 0;

    int count = -1;
    int rand_idx = -1;
    size_t data_size = 0;
    std::string data_value = {};


    // NOTE(akumanory): read count of nodes in file
    fread_ret = fread(&count, sizeof(count), 1, file);
    if (fread_ret < 1)
        throw std::runtime_error(FUNC_NAME + "Can't read how much node in file");

    if (count <= 0) {
        std::cout << "No values exist in file" << std::endl; 
    }

    std::cout << "Number of data serialized into file = " << count << std::endl;

    for (int i = 0; i < count; i++) 
    {

        std::cout << "Data idx = " << i << std::endl;

        // 1. Try to read rand_idx   
        fread_ret = fread(&rand_idx, sizeof(rand_idx), 1, file);
        if (fread_ret < 1) {
            throw std::runtime_error(FUNC_NAME + "Can't read rand idx of the node");
        }
        // 2. Try to read data size 
        fread_ret = fread(&data_size, sizeof(data_size), 1, file);
        if (fread_ret < 1) {
            throw std::runtime_error(FUNC_NAME + "Can't read rand idx of the node");
        }
        // 3. Try to read data value
        data_value.resize(data_size);
        fread_ret = fread(&data_value[0], sizeof(char), data_size, file);
        if (fread_ret < data_size) {
            throw std::runtime_error(FUNC_NAME + "Can't read data value of the node");
        }

        std::cout << "  Rand_idx   = " << rand_idx   << std::endl;
        std::cout << "  Data_size  = " << data_size  << std::endl;
        std::cout << "  Data_value = " << data_value << std::endl;
        std::cout << std::endl;
    }

}

void List::Deserialize(FILE *file) {
    if (file == nullptr)
        throw std::runtime_error(FUNC_NAME + " --> File is nullptr, can't read from it");
    // TODO(akumanory): testing serialized data being write correctly

#if 1
    test_deserialize_cout(file);
    fclose(file);
    return;
#endif // 1

    count = -1;

    if (fread(&count, sizeof(count), 1, file) != 1)
        throw std::runtime_error(FUNC_NAME + "Error can't read count value from file");

    if (count == 0)
        return;

    // remove old data
    while (head != tail) {
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

    for (int i = 0; i < count; i++) {
        if (!tail->data.empty()) {
            ListNode* temp = tail;
            tail = new ListNode();
            temp->next = tail;
            tail->prev = temp;
        }

        // if (fread(&count, sizeof(count), 1, file))
        //     throw std::runtime_error(FUNC_NAME + "Error can't read count value from file");
    }
    // TODO(akumanory): maybe need to add fclose for this
    fclose(file);
}
}  // namespace linked_list_parser
