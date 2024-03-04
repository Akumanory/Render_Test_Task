// Don't know how to test private members of class without runing the structure
// Can have friend keyword but it will ruin previous declaration
// Same with changind private --> protected (create child class to list with additional mehtods)
#include <bits/types/FILE.h>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <tuple>

#define private public
#include "LinkedListParser/linked_list_parser.h"
#undef private

#include <cstdint>
#include <iostream>

// TODO(akumanory): remove, used only for test reasons
#include <type_traits>

// TODO(akumanory): remove, used only for test reasons
// testing whole struct serialization
struct test_struct {
    test_struct()
    {};
    test_struct(int _a, double _b, const char* _data)
        : a(_a)
        , b(_b)
        , data(_data)
    {};

    int a = 0;
    double b = 0.0;
    const char* data;
};

// TODO(akumanory): test for binary representation
// You can only pass the signed integer
// ============= 
template<typename T,
    std::enable_if_t<
        std::is_signed<T>::value &&
        std::is_integral<T>::value,
        bool> = true>
void test(T test_var) {
    std::cout << test_var << std::endl;
}
// =============

#define TEST 0
#define TEST_2 0
#define SERIALIZE 1
#define DESERIALIZE 1


void test_serialization();
void test_deserialization();


int main() 
{
#if TEST_2
    // Writing to file 
    // FILE* test_write = fopen("../../../Tests/LinkedListParser/test_data/serialized_data.bin", "wb");
    FILE* test_write = fopen("test_data/serialized_data.bin", "wb");
    std::string write_str = "This is test string here";
    size_t write_len = write_str.size(); 

    fwrite(&write_len, sizeof(write_len), 1, test_write);
    fwrite(&write_str[0], sizeof(char), write_len, test_write);
    fclose(test_write);

    // Reading from file
    // FILE* test_read = fopen("../../../Tests/LinkedListParser/test_data/serialized_data.bin", "rb");
    FILE* test_read = fopen("test_data/serialized_data.bin", "rb");
    std::string read_str = {};
    size_t read_len = 0;

    fread(&read_len, sizeof(read_len), 1, test_read);
    read_str.resize(read_len);
    fread(&read_str[0], sizeof(char), read_len, test_read);
    fclose(test_read);

    std::cout << "read str: " << read_str << std::endl;

#endif // TEST_2

#if TEST
    /////////////////// begin -> Struct serialization test
    {
        // NOTE(akumanory): can't write string only as struct, 
        // because it seems that string is pointer in that case 
        
        test_struct test(20, 69.420, "test1");
        test_struct test_2(28, 59.320, "test2_test4_test5_test6_test7_test8_test9");

        std::cout << "test.data = " << test.data << std::endl;
        std::cout << "test_2.data = " << test_2.data << std::endl;
        std::cout << "sizeof(test) = " << sizeof(test) << std::endl;
        std::cout << "sizeof(test_2) = " << sizeof(test_2) << std::endl;

        FILE* test_write = fopen("test_data/test_data.bin", "wb");
        auto answer = fwrite(&test, sizeof(test), 1, test_write);
        auto answer_2 = fwrite(&test_2, sizeof(test_2), 1, test_write);
        std::cout << "write answer = " << answer << std::endl;
        auto fclose_answer = fclose(test_write);
        std::cout << "fclose answer = " << fclose_answer << std::endl;
    }

    FILE* test_read = fopen("test_data/test_data.bin", "rb");
    test_struct read_struct;
    while (fread(&read_struct, sizeof(read_struct), 1, test_read)) {
        std::cout << "read answer = " << "Yes" << std::endl;
        std::cout << "read_struct.data = " << read_struct.data << std::endl;
        std::cout << "sizeof(read_struct) = " << sizeof(read_struct) << std::endl;
    }
    if (feof(test_read)) {
        std::cout << "At the end of file" << std::endl;
    } else {
        std::cout << "Not at the end of file" << std::endl;
    }
    auto fclose_answer = fclose(test_read);
    std::cout << "fclose answer = " << fclose_answer << std::endl;

    /////////////////// end -> Struct serialization test
#endif // TEST


    try {

#if SERIALIZE
        test_serialization();
#endif // SERIALIZE

#if DESERIALIZE
        test_deserialization();
#endif // DESERIALIZE

    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

void test_serialization() {
    linked_list_parser::List test_list{};
    // FILE* serialization_file = fopen("../../../Tests/LinkedListParser/test_data/serialized_data.bin", "wb");
    FILE* serialization_file  = fopen("test_data/serialized_data.bin", "wb");

    if (serialization_file == nullptr)
        throw std::runtime_error("fopen --> can't open file");
    
    linked_list_parser::ListNode test_list_node;
    test_list_node.prev = nullptr;
    test_list_node.next = nullptr;
    test_list_node.rand = nullptr;
    test_list_node.data = "test_list_node";

    linked_list_parser::ListNode test_list_node_2;
    test_list_node_2.prev = &test_list_node_2;
    test_list_node_2.next = nullptr;
    test_list_node_2.rand = &test_list_node;
    test_list_node_2.data = "test_list_node_2";
    
    // Update for first list node
    test_list_node.next = &test_list_node_2;


    test_list.head = &test_list_node;
    test_list.tail = &test_list_node_2;
    test_list.count = 2;

    test_list.Serialize(serialization_file);

    std::cout << "Great, serialization complete" << std::endl;
}

void test_deserialization() {
    linked_list_parser::List test_list{};
    FILE* deserilization_file = fopen("test_data/serialized_data.bin", "rb");

    if (deserilization_file == nullptr)
        throw std::runtime_error("fopen --> can't open file");

    test_list.Deserialize(deserilization_file);
    std::cout << "Great, deserialization complete" << std::endl;
}
