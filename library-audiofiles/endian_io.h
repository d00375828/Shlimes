<<<<<<< HEAD
#ifndef _ENDIAN_IO_H_
#define _ENDIAN_IO_H_

#include <iostream>
#include <string>

namespace little_endian_io {
    std::ostream& write_word(std::ostream& output_stream, int value, unsigned size);
    std::ostream& write_4_bytes(std::ostream& output_stream, int value);
    std::ostream& write_3_bytes(std::ostream& output_stream, int value);
    std::ostream& write_2_bytes(std::ostream& output_stream, int value);
=======
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

>>>>>>> b63ca74 (curts quads or burts?)
    std::ostream& write_1_bytes(std::ostream& output_stream, int value);
}

namespace big_endian_io {
<<<<<<< HEAD
    std::ostream& write_string(std::ostream& output_stream, const std::string& value);
}

#endif /* _ENDIAN_IO_H_ */
=======
    std::ostream& write_word(std::ostream& output_stream, int value, unsigned size);

    std::ostream& write_4_bytes(std::ostream& output_stream, int value);

    std::ostream& write_string(std::ostream& output_stream, const std::string& value);
}

#endif
>>>>>>> b63ca74 (curts quads or burts?)
