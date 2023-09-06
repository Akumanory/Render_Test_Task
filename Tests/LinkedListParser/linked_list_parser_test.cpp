// Don't know how to test private members of class without runing the structure
// Can have friend keyword but it will ruin previous declaration
// Same with changind private --> protected (create child class to list with additional mehtods)
#include <bits/types/FILE.h>
#include <cstdio>
#include <stdexcept>
#include <tuple>

#define private public
#include "LinkedListParser/linked_list_parser.h"
#undef private

#include <cstdint>
#include <iostream>


struct test_struct
{
    test_struct()
    {};
    test_struct(int _a, double _b)
        : a(_a)
        , b(_b)
    {};

    int a = 0;
    double b = 0.0;
};


int main()
{
    ///////////////////

    test_struct test(20, 69.420);
    test_struct test_2(28, 59.320);

    FILE* test_write = fopen("test_data/test_data.bin", "wb");
    auto answer = fwrite(&test, sizeof(test), 1, test_write);
    auto answer_2 = fwrite(&test_2, sizeof(test_2), 1, test_write);
    std::cout << "write answer = " << answer << std::endl;
    auto fclose_answer = fclose(test_write);
    std::cout << "fclose answer = " << fclose_answer << std::endl;


    FILE* test_read = fopen("test_data/test_data.bin", "rb");
    test_struct read_struct;
    while (fread(&read_struct, sizeof(read_struct), 1, test_read)) {
        std::cout << "read answer = " << "Yes" << std::endl;
    }
    if (feof(test_read)) {
        std::cout << "At the end of file" << std::endl;
    }
    else {
        std::cout << "Not at the end of file" << std::endl;
    }
    fclose_answer = fclose(test_read);
    std::cout << "fclose answer = " << fclose_answer << std::endl;

    ///////////////////

    linked_list_parser::List test_list{};
    // FILE* serialization_file  = fopen("test_data/serialized_data.bin", "wb");
    FILE* deserilization_file = fopen("test_data/serialized_data.bin", "rb");

    // if (serialization_file == nullptr)
    //     throw std::runtime_error("fopen --> can't open file");

    if (deserilization_file == nullptr)
        throw std::runtime_error("fopen --> can't open file");

    linked_list_parser::ListNode test_list_node;
    test_list_node.prev = nullptr;
    test_list_node.next = nullptr;
    test_list_node.rand = &test_list_node;
    test_list_node.data = "test_list_node";

    test_list.head = &test_list_node;
    test_list.tail = &test_list_node;
    test_list.count = 1;

    // serialization_file = nullptr;

    // test_list.Serialize(serialization_file);
    test_list.Deserialize(deserilization_file);

    return 0;
}