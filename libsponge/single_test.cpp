/**
 * lab1 调试文件
 * 调试命令：g++ /home/hans/CS144-Sponge/libsponge/single_test.cpp /home/hans/CS144-Sponge/libsponge/byte_stream.cc /home/hans/CS144-Sponge/libsponge/stream_reassembler.cc -o mytest
 * 
 */
#include "stream_reassembler.hh"

#include <exception>
#include <iostream>

using namespace std;

int main() {
    StreamReassembler streamreassembler(8);
    
    streamreassembler.push_substring("abc", 0, 0);
   
    size_t a = streamreassembler.first_unread();
    size_t b = streamreassembler.first_unassembled();
    size_t c = streamreassembler.first_unacceptable();
    cout << a << ' ' << b << ' ' << c << '\n';

    streamreassembler.push_substring("bcdefgh", 1, 1);
    a = streamreassembler.first_unread();
    b = streamreassembler.first_unassembled();
    c = streamreassembler.first_unacceptable();
    cout << a << ' ' << b << ' ' << c << '\n';

    return 0;
}