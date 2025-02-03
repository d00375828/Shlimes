#ifndef _ENDIAN_IO_H_
#define _ENDIAN_IO_H_

#include <iostream>
#include <string>

namespace little_endian_io {
    std::ostream& write_word(std::ostream& output_stream, int value, unsigned size);
    std::ostream& write_4_bytes(std::ostream& output_stream, int value);
    std::ostream& write_3_bytes(std::ostream& output_stream, int value);
    std::ostream& write_2_bytes(std::ostream& output_stream, int value);
    std::ostream& write_1_bytes(std::ostream& output_stream, int value);
}

namespace big_endian_io {
    std::ostream& write_string(std::ostream& output_stream, const std::string& value);
}

#endif /* _ENDIAN_IO_H_ */
