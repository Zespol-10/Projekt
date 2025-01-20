#include <cstdint>
#include <fstream>
#include <string>
#include <string_view>

namespace arithmetic {

class bit_istream {
    std::uint8_t buf;
    std::uint8_t mask;

    virtual char get_char() = 0;
    virtual bool stream_eof() const = 0;

  public:
    bit_istream();

    bool get_bit();
    bool eof() const;
};

class bit_ifstream : std::ifstream, public bit_istream {
    char get_char() override;
    bool stream_eof() const override;

  public:
    bit_ifstream(const std::string &filename);
};

class bit_string_istream : public bit_istream {
    std::string_view::const_iterator iter;
    std::string_view::const_iterator end;

    char get_char() override;
    bool stream_eof() const override;

  public:
    bit_string_istream(const std::string_view input);
};

class bit_ostream {
    std::uint8_t buf;
    std::uint8_t count;

    virtual void put_char(std::uint8_t) = 0;

  protected:
    void fill();

  public:
    bit_ostream();

    void put_bit(bool bit);
    virtual void flush() = 0;
};

class bit_ofstream : std::ofstream, public bit_ostream {
    void put_char(std::uint8_t ch) override;

  public:
    bit_ofstream(const std::string &filename);
    void flush() override;

    void close();
};

class bit_string_ostream : public bit_ostream {
    std::string output;
    void put_char(std::uint8_t ch) override;

  public:
    bit_string_ostream();
    void flush() override;

    std::string result();
};

void compress(std::istream &input, bit_ostream &output);
void decompress(bit_istream &input, std::ostream &output);
} // namespace arithmetic
