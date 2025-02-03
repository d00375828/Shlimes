#include "endian_io.h"

namespace little_endian_io {

std::ostream& write_word(std::ostream& output_stream, int value, unsigned size) {
    for (unsigned i = 0; i < size; ++i) {
        output_stream.put(static_cast<char>(value & 0xFF));
        value >>= 8;
    }
    return output_stream;
}

std::ostream& write_4_bytes(std::ostream& output_stream, int value) {
    return write_word(output_stream, value, 4);
}

std::ostream& write_3_bytes(std::ostream& output_stream, int value) {
    return write_word(output_stream, value, 3);
}

std::ostream& write_2_bytes(std::ostream& output_stream, int value) {
    return write_word(output_stream, value, 2);
}

std::ostream& write_1_bytes(std::ostream& output_stream, int value) {
    return write_word(output_stream, value, 1);
}

} // namespace little_endian_io

namespace big_endian_io {

std::ostream& write_string(std::ostream& output_stream, const std::string& value) {
    output_stream.write(value.c_str(), value.size());
    return output_stream;
}

} // namespace big_endian_io