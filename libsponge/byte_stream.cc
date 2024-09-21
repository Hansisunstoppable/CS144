#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

ByteStream::ByteStream(const size_t capacity) { 
    _capacity = capacity;
}

size_t ByteStream::write(const std::string &data) {
    if (_input_end) {
        return 0;
    }
    size_t write_count = std::min(data.size(), _capacity - _buf.size());
    _buf.insert(_buf.end(), data.begin(), data.begin() + write_count);
    _write_byte += write_count;
    return write_count;
}

//! \param[in] len bytes will be copied from the output side of the buffer
std::string ByteStream::peek_output(const size_t len) const {
    size_t read_count = std::min(len, _buf.size());
    // return std::string(_buf.begin(), _buf.begin() + read_count);
    return _buf.substr(0, read_count);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) { 
    size_t pop_count = std::min(len, _buf.size());
    _buf.erase(_buf.begin(), _buf.begin() + pop_count); // 迭代器要与迭代器配合使用
    _read_byte += pop_count;
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    std::string read_data = peek_output(len);
    pop_output(len);
    return read_data;
}

void ByteStream::end_input() { _input_end = true; }

bool ByteStream::input_ended() const { return _input_end; }

size_t ByteStream::buffer_size() const { return _buf.size(); }

bool ByteStream::buffer_empty() const { return _buf.empty(); }

bool ByteStream::eof() const { return _input_end && _buf.empty(); }

size_t ByteStream::bytes_written() const { return _write_byte; }

size_t ByteStream::bytes_read() const { return _read_byte; }

size_t ByteStream::remaining_capacity() const { return _capacity - _buf.size(); }
