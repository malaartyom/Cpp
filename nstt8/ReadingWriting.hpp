#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>



class IO {
protected:
    bool open;
    bool eof;

public:
    IO() : open(true), eof(false) {}
    virtual ~IO() { close(); }

    bool is_open() const { return open; }
    bool is_eof() const { return eof; }

    virtual void close() {
        open = false;
    }
};

class Reader : virtual public IO {
public:
    virtual int read_int() = 0;
    virtual std::string read_string() = 0;
    virtual char read_char() = 0;
};

class Writer : virtual public IO {
public:
    virtual void write_int(int value) = 0;
    virtual void write_string(const std::string &str) = 0;
    virtual void write_char(char c) = 0;
};


class ReaderWriter : public Reader, public Writer {
};


class StringReaderWriter : public ReaderWriter {
protected:
    std::string &source;
    size_t read_pos;

public:
    StringReaderWriter(std::string &src) : source(src), read_pos(0) {}

    int read_int() override {
        std::string value;
        char c;
        while (!eof) {
            c = read_char();
            if (c == '\0' || !isdigit(c)) {
                break;
            }
            value.push_back(c);
        }
        return value.empty() ? -1 : std::stoi(value);
    }

    std::string read_string() override {
        std::string line;
        char c;
        while (!eof) {
            c = read_char();
            if (c == '\0' || c == '\n') {
                break;
            }
            line.push_back(c);
        }
        return line;
    }

    char read_char() override {
        if (read_pos >= source.size()) {
            eof = true;
            return '\0';
        }
        return source[read_pos++];
    }

    void write_int(int value) override {
        source.insert(source.size(), std::to_string(value));
    }

    void write_string(const std::string &str) override {
        source.insert(source.size(), str);
    }

    void write_char(char c) override {
        source.insert(source.size(), 1, c);
    }
};


class FileReaderWriter : public ReaderWriter {
protected:
    FILE* file;
    std::string file_name;
    int read_pos;

public:
    FileReaderWriter(const std::string &filename) : file_name(filename), read_pos(0) {
        file = fopen(filename.c_str(), "r+");
        if (file) {
            open = true;
            eof = false;
        } else {
            open = false;
            eof = true;
        }
    }

    ~FileReaderWriter() {
        if (file) {
            fclose(file);
        }
    }

    int read_int() override {
        int value;
        fseek(file, read_pos, 0);
        if (fscanf(file, "%d", &value) != 1) {
            eof = true;
            return -1;
        }
        read_pos++;
        return value;
    }

    std::string read_string() override {
        std::string str;
        char c;
        while (!eof) {
            c = read_char();
            if (c == '\n' || c == '\0') {
                break;
            }
            str.push_back(c);
        }
        return str;
    }

    char read_char() override {
        fseek(file, read_pos, 0);
        char c;
        if (fscanf(file, "%c", &c) == EOF) {
            eof = true;
            return '\0';
        }
        read_pos++;
        return c;
    }

    void write_int(int value) override {
        if (file) {
            fprintf(file, "%d", value);
        }
    }

    void write_string(const std::string &str) override {
        if (file) {
            fprintf(file, "%s", str.c_str());
        }
    }

    void write_char(char c) override {
        if (file) {
            fputc(c, file);
        }
    }

    void close() override {
        if (file) {
            fclose(file);
            file = nullptr;
        }
        IO::close();
    }
    void clear_file() {
        FILE *file = fopen(file_name.c_str(), "w");
        if (file == NULL) {
            throw std::runtime_error("Can't open the file!\n");
        }
        fclose(file);
}


};

// Buffered -> BReader ---> BRW
// |                       ^
// v                       |
// BWriter ----------------
class BufferedStringReaderWriter : public ReaderWriter {
private:
    StringReaderWriter rw;
    std::vector<char> buffer;
    size_t bufferSize;
    size_t bufferPos;
    size_t readBufferPos;

    void flush() {
        for (size_t i = 0; i < bufferPos; ++i) {
            rw.write_char(buffer[i]);
        }
        bufferPos = 0;
    }

    void check() {
        if (readBufferPos == bufferPos) {
            std::string s = rw.read_string();
            std::copy(s.begin(), s.end(), buffer.begin());
            bufferPos = s.size();
            readBufferPos = 0;
        }
    }

public:
    BufferedStringReaderWriter(std::string &source, size_t bufSize)
        : rw(source), bufferSize(bufSize), bufferPos(0), readBufferPos(0) {
        buffer.resize(bufferSize);
    }

    int read_int() override {
        std::string value;
        char c;
        while (!eof) {
            c = read_char();
            if (c == '\0' || !isdigit(c)) {
                break;
            }
            value.push_back(c);
        }
        return value.empty() ? -1 : std::stoi(value);
    }

    std::string read_string() override {
        std::string str;
        char c;
        while (!eof) {
            c = read_char();
            if (c == '\n' || c == '\0') {
                break;
            }
            str.push_back(c);
        }
        return str;
    }

    char read_char() override {
        check();
        if (readBufferPos == bufferPos) {
            eof = true;
            return '\0';
        }
        char value = buffer[readBufferPos++];
        return value;
    }

    void write_int(int value) override {
        std::string str = std::to_string(value);
        write_string(str);
    }

    void write_string(const std::string &str) override {
        for (char ch : str) {
            write_char(ch);
        }
    }

    void write_char(char c) override {
        check();
        if (bufferPos == bufferSize) {
            flush();
        }
        buffer[bufferPos++] = c;
    }

    void close() override {
        flush();
        rw.close();
        IO::close();
    }
};

class BufferedFileReaderWriter : public ReaderWriter {
private:
    FileReaderWriter rw;
    std::vector<char> buffer;
    size_t bufferSize;
    size_t bufferPos;
    size_t readBufferPos;

    void flush() {
        for (size_t i = 0; i < bufferPos; ++i) {
            rw.write_char(buffer[i]);
        }
        bufferPos = 0;
    }

    void check() {
        if (readBufferPos == bufferPos) {
            std::string s = rw.read_string();
            std::copy(s.begin(), s.end(), buffer.begin());
            bufferPos = s.size();
            readBufferPos = 0;
        }
    }

public:
    BufferedFileReaderWriter(const std::string &filename, size_t bufSize)
        : rw(filename), bufferSize(bufSize), bufferPos(0), readBufferPos(0) {
        buffer.resize(bufferSize);
    }

        int read_int() override {
        std::string value;
        char c;
        while (!eof) {
            c = read_char();
            if (c == '\0' || !isdigit(c)) {
                break;
            }
            value.push_back(c);
        }
        return value.empty() ? -1 : std::stoi(value);
    }

    std::string read_string() override {
        std::string str;
        char c;
        while (!eof) {
            c = read_char();
            if (c == '\n' || c == '\0') {
                break;
            }
            str.push_back(c);
        }
        return str;
    }

    char read_char() override {
        check();
        if (readBufferPos == bufferPos) {
            eof = true;
            return '\0';
        }
        char value = buffer[readBufferPos++];
        return value;
    }

    void write_int(int value) override {
        std::string str = std::to_string(value);
        write_string(str);
    }

    void write_string(const std::string &str) override {
        for (char ch : str) {
            write_char(ch);
        }
    }

    void write_char(char c) override {
        check();
        if (bufferPos == bufferSize) {
            flush();
        }
        buffer[bufferPos++] = c;
    }

    void close() override {
        flush();
        rw.close();
        IO::close();
    }
};
