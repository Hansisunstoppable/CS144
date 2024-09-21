#include "stream_reassembler.hh"
// #include <bits/stdc++.h>

// Dummy implementation of a stream reassembler.

// For Lab 1, please replace with a real implementation that passes the
// automated checks run by `make check_lab1`.

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

// 在构造 StreamReassembler 对象时，构造函数会接收一个名为 capacity 的参数，并直接使用这个参数来初始化两个成员变量 _output 和 _capacity
StreamReassembler::StreamReassembler(const size_t capacity) : _output(capacity), _capacity(capacity) {
}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const std::string &data, const size_t index, const bool eof) 
{
    
    std::string new_data{data};      
    // 将超出滑窗的数据全部丢弃,得到新的new_data
    if (data.length() + index > first_unacceptable()) 
    {
        new_data = data.substr(0, first_unacceptable() - index);
    }
    // 情况1
    if (index < first_unassembled()) 
    {
        // 整段数据都太旧
        if (index + new_data.length() <= first_unassembled()) 
        {
            return ;
        }
        // 有部分数据有效
        new_data = new_data.substr(first_unassembled() - index, new_data.length() - (first_unassembled() - index));
        // push_substring(new_data, first_unassembled(), eof);
    }
    /**
     * test
     */
    // std::cout << "new_data = " << new_data << '\n';
    // std::cout << '\n';

    // 注意 new_data 的起始位置
    // 考虑这两个例子
    add_to_buf(new_data, std::max(index, first_unassembled()));

    /**
     * test
     */
    // std::cout << index << '\n';
    // for (auto [a, b] : _buf) {
    //     std::cout << a << ' ' << b << '\n';
    // }
    // std::cout << '\n';

    reassemble_buf(first_unassembled());

    if (eof) 
    {
        _eof = true;
        _eof_index = index + data.length();
    }    
    check_eof();
}



size_t StreamReassembler::unassembled_bytes() const { return _buf.size(); }

bool StreamReassembler::empty() const { return false; }


size_t StreamReassembler::first_unread() const { return _output.bytes_read(); }

size_t StreamReassembler::first_unassembled() const { return  _output.bytes_written(); }

size_t StreamReassembler::first_unacceptable() const { return _output.bytes_read() + _capacity; }

size_t StreamReassembler::remain_capacity() const { return first_unacceptable() - first_unassembled(); }

void StreamReassembler::check_eof()  
{ 
    if (_eof && first_unassembled() == _eof_index) {
        _buf.clear();
        _output.end_input();
    }
}

void StreamReassembler::add_to_buf(const std::string &data, size_t index) 
{
    for (const char &c : data) 
    {
        if (remain_capacity() > _buf.size()) {
            _buf[index] = c;
            index ++;
        }   
        else 
        {
            return ;
        }
    }
}


void StreamReassembler::reassemble_buf(size_t index) 
{
    if (_if_first_data == false) 
    {
        if (index == 0) 
        {
            _if_first_data = true;
        }
        else 
        {
            return ;
        }
    }
    for ( ; index <= first_unacceptable(); index ++) 
    {
        if (_buf.count(index) > 0) {
            std::string str(1, _buf[index]);
            _output.write(str);
            _buf.erase(index);
        } else {
            return ;
        }
    }
}