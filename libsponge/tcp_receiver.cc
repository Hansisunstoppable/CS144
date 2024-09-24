#include "tcp_receiver.hh"

// Dummy implementation of a TCP receiver

// For Lab 2, please replace with a real implementation that passes the
// automated checks run by `make check_lab2`.

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {} 

void TCPReceiver::segment_received(const TCPSegment &seg) {
    // 不同的 syn 重复出现, 冲突情况
    // if (_isn.has_value() && )

    // 当起始序号还不存在时
    if (_isn.has_value() == false) {
        // 当 syn = true
        if (seg.header().syn == true) {
            // 设定接收的起始序号
            _isn = seg.header().seqno;
            // 将数据段压入缓冲区, index 从 0 开始（这是字节流的序号）
            _reassembler.push_substring(seg.payload().copy(), 0, seg.header().fin);
            update_ackno();
        }
        return ;
    }
    // checkpoint ??
    uint64_t abs_seqno = unwrap(
        seg.header().seqno, 
        _isn.value(), 
        _reassembler.first_unassembled());
    _reassembler.push_substring(seg.payload().copy(), abs_seqno - 1, seg.header().fin);
    update_ackno();
}

std::optional<WrappingInt32> TCPReceiver::ackno() const { return _ackno; }

void TCPReceiver::update_ackno() {
    // syn 也算1个byte
    // fin 也算1个byte
    // 要根据 当前的状态，加1 或 加2
    if (_reassembler.stream_out().input_ended() == true) {
        _ackno = wrap(_reassembler.first_unassembled() + 2, _isn.value());
    } else {
        _ackno = wrap(_reassembler.first_unassembled() + 1, _isn.value());
    }
}

size_t TCPReceiver::window_size() const { return _reassembler.first_unacceptable() - _reassembler.first_unassembled(); }
