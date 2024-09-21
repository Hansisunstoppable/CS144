/**
 * lab1 调试文件
 * 调试命令：g++ /home/hans/CS144-Sponge/libsponge/single_test.cpp /home/hans/CS144-Sponge/libsponge/byte_stream.cc /home/hans/CS144-Sponge/libsponge/stream_reassembler.cc -o mytest
 * 
 */
#include"wrapping_integers.hh"

#include <exception>
#include <iostream>

using namespace std;

int main() {
    // WrappingInt32 x = wrap(3 * (1ll << 32), WrappingInt32(0));
    uint64_t y = unwrap(WrappingInt32(1), WrappingInt32(0), UINT32_MAX);
    // cout << x.raw_value() << '\n';
    cout << UINT32_MAX << '\n';

    return 0;
}