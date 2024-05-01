#pragma once
#include <cstddef>
#include <string>

class FILEWriter : public IO {
private:
    FILE *file;
    bool open;

public:
    FILEWriter(const std::string file_name);
    ~FILEWriter() override;

    bool is_open() const override;
    bool is_file_ends() const override;
    void close() override;
    void write(int i);
    void write(char c);
    void write(const std::string &str);
};

struct IO {
  virtual bool is_open() const = 0;
  virtual bool is_file_ends() const = 0;
  virtual void close() = 0;
  virtual ~IO() {}
};

class Reader : public IO {
  virtual char read_char() = 0;
  virtual int read_int() = 0;
  virtual std::string read_string() = 0;
};

class ReaderWriter : public Reader, public Writer {};

class StringReader : public IO {
  std::string::iterator string_iterator;
  std::string::iterator string_ends;
  bool open;
  bool file_ends;

public:
  StringReader(std::string string);
  bool is_open() const;
  bool is_file_ends() const;
  void close();
  char read_char();
  int read_int();
};



class StringReaderWriter : public ReaderWriter{
  std::string* string_;
  bool open_;
  bool file_ends_;
  size_t pos;

public:
  StringReaderWriter(std::string* string);

  bool is_open() const;
  bool is_file_ends() const;
  void close();

  char read_char();
  int read_int();
  std::string read_string();

  void write(char c);
  void write(int i);
  void write(const std::string& string);

  ~StringReaderWriter();
};

class StringWriter : public IO {
  std::string* string_;
  bool open;

public:
  StringWriter(std::string* string);
  bool is_open() const;
  bool is_file_ends() const;
  void close();

  void write(char c);
  void write(int i);
  void write(const std::string& string);
};

class Writer : public IO {
  virtual void write(char c) = 0;
  virtual void write(int i) = 0;
  virtual void write(const std::string& str) = 0;
};

class BufferedFILEReaderWriter: public ReaderWriter {
  FILE* file;
  std::string read_buffer;
  size_t read_buffer_pos;

  std::string write_buffer;

  size_t buffer_size_;

  bool open;
  bool file_ends;
  bool buffer_ends;

  void update_buffer();
  void update_write_buffer(bool now);

public:
  BufferedFILEReaderWriter(const std::string filename);
  BufferedFILEReaderWriter(const std::string filename, size_t buffer_size);
  
  bool is_open() const;
  bool is_file_ends() const;
  void close();

  void write(int i);
  void write(char c);
  void write(const std::string& str);

  char read_char();
  int read_int();
  std::string read_string();
  
  ~BufferedFILEReaderWriter();
};

class BufferedStringReaderWriter: public ReaderWriter {
  std::string& string_;
  size_t string_pos;

  std::string read_buffer;
  size_t read_buffer_pos;

  std::string write_buffer;

  size_t buffer_size_;

  bool open;
  bool file_ends;
  bool buffer_ends;

  void update_buffer();
  void update_write_buffer(bool now);

public:
  BufferedStringReaderWriter(std::string& string);
  BufferedStringReaderWriter(std::string& string, size_t buffer_size);
  
  bool is_open() const;
  bool is_file_ends() const;
  void close();

  void write(int i);
  void write(char c);
  void write(const std::string& str);

  char read_char();
  int read_int();
  std::string read_string();
  
  ~BufferedStringReaderWriter();
};


class FILEReader : public IO {
private:
    FILE *file;
    bool open;
    bool file_ends;

public:
    FILEReader(const std::string &file_name);
    ~FILEReader();

    bool is_file_ends() const;
    bool is_open() const;
    void close();
    char read_char();
    int read_int();
    std::string read_string();
};


class FILEReaderWriter : public ReaderWriter {
  FILE* file;
  bool open;
  bool file_ends;

  int file_writing_pos = 0;
  int file_reading_pos = 0;

public:
  FILEReaderWriter(const std::string filename);
  
  bool is_open() const;
  bool is_file_ends() const;
  void close();

  void write(int i);
  void write(char c);
  void write(const std::string& str);

  char read_char();
  int read_int();
  std::string read_string();
  
  ~FILEReaderWriter();
};