#ifndef ENDIAN_IO_H
#define ENDIAN_IO_H

#include <ostream>
#include <istream>
#include <cstdint>

namespace little_endian_io {
    std::ostream& write_word(std::ostream& output_stream, int value, unsigned size);

    std::ostream& write_4_bytes (std::ostream& output_stream, int value);

    std::ostream& write_3_bytes(std::ostream& output_stream, int value);

    std::ostream& write_2_bytes(std::ostream& output_stream, int value);

    std::ostream& write_1_bytes(std::ostream& output_stream, int value);
}

namespace big_endian_io {
    std::ostream& write_word(std::ostream& output_stream, int value, unsigned size);

    std::ostream& write_4_bytes(std::ostream& output_stream, int value);

    std::ostream& write_string(std::ostream& output_stream, const std::string& value);
}

#endif