#include <string>
#include "8.hpp"

StringWriter::StringWriter(std::string *string) : string_(string), open(true) {}

bool StringWriter::is_open() const { return open; }

bool StringWriter::is_file_ends() const { return false; }

void StringWriter::close() { open = false; string_ = nullptr; }

void StringWriter::write(char c) { string_->push_back(c); }

void StringWriter::write(const std::string &str) {
  for (char c : str) {
    write(c);
  }
}

void StringWriter::write(int i) {
  std::string number = std::to_string(i);
  write(number);
}

StringReaderWriter::StringReaderWriter(std::string *string)
    : string_(string), open_(true), file_ends_(false), pos(0) {}

bool StringReaderWriter::is_open() const { return open_; }

bool StringReaderWriter::is_file_ends() const { return file_ends_; }

void StringReaderWriter::close() { string_ = nullptr; open_ = false; }

char StringReaderWriter::read_char() {
  if (pos == string_->size() - 1) {
    file_ends_ = true;
  }
  return string_->at(pos++);
}

int StringReaderWriter::read_int() { return read_char() - '0'; }

std::string StringReaderWriter::read_string() {
  std::string line;
  char c;
  while (!file_ends_) {
    c = read_char();
    if (c == '\0' || c == '\n') {
      break;
    }
    line.push_back(c);
  }
  return line;
}

void StringReaderWriter::write(char c) {
  string_->push_back(c);
  file_ends_ = false;
}

void StringReaderWriter::write(const std::string &str) {
  for (char c : str) {
    write(c);
  }
}

void StringReaderWriter::write(int i) {
  std::string number = std::to_string(i);
  write(number);
}

StringReaderWriter::~StringReaderWriter() {
  close();
}

StringReader::StringReader(std::string string)
    : string_iterator(string.begin()), string_ends(string.end()), open(true), file_ends(false) {}

bool StringReader::is_open() const { return open; }

bool StringReader::is_file_ends() const { return file_ends; }

char StringReader::read_char() {
  char c = *string_iterator++;
  if (string_iterator == string_ends) {
    file_ends = true;
  }
  return c;
}

int StringReader::read_int() {
  int i = read_char() - '0';
  return i;
}

void StringReader::close() {
  open = false;
}
FILEWriter::FILEWriter(const std::string file_name)
    : file(nullptr), open(false) {
  file = fopen(file_name.c_str(), "w");
  if (file == nullptr) {
    throw std::runtime_error("Failed to open file");
  }
  open = true;
}

bool FILEWriter::is_open() const { return open; }

bool FILEWriter::is_file_ends() const { return false; }

void FILEWriter::close() {
  fclose(file);

  file = nullptr;
  open = false;
}

void FILEWriter::write(int i) { fprintf(file, "%d", i); }

void FILEWriter::write(char c) { fprintf(file, "%c", c); }

void FILEWriter::write(const std::string &string) {
  for (char c : string) {
    write(c);
  }
}

FILEWriter::~FILEWriter() {
  if (open) {
    close();
  }
}

FILEReaderWriter::FILEReaderWriter(const std::string filename)
    : file(nullptr), open(false), file_ends(false){
  file = fopen(filename.c_str(), "r+");
  if (file == nullptr) {
    throw std::runtime_error("Cannot open file");
  }

  open = true;
}

FILEReaderWriter::~FILEReaderWriter() {
  if (open) {
    close();
  }
}

bool FILEReaderWriter::is_file_ends() const { return file_ends; }

bool FILEReaderWriter::is_open() const { return open; }

void FILEReaderWriter::close() {
  if (file != nullptr) {
    fclose(file);
    file = nullptr;
    open = false;
  }
}

char FILEReaderWriter::read_char() {
  char c;
  fseek(file, file_reading_pos, SEEK_SET);
  int result = fscanf(file, "%c", &c);
  if (result == EOF) {
    file_ends = true;
    return '\0';
  }
  file_reading_pos += result;
  return c;
}

int FILEReaderWriter::read_int() {
  int i;
  fseek(file, file_reading_pos, SEEK_SET);
  int result = fscanf(file, "%d", &i);
  if (result == EOF) {
    file_ends = true;
  }
  file_reading_pos += result;
  return i;
}

std::string FILEReaderWriter::read_string() {
  std::string line;
  char c;
  while (!file_ends) {
    c = read_char();
    if (c == '\0' || c == '\n') {
      break;
    }
    line.push_back(c);
  }
  return line;
}

void FILEReaderWriter::write(int i) { write(std::to_string(i)); }

void FILEReaderWriter::write(char c) {
  file_ends = false;

  fseek(file,file_writing_pos, SEEK_SET);
  int result = fprintf(file, "%c", c);
  file_writing_pos += result;
}

void FILEReaderWriter::write(const std::string &string) {
  for (char c : string) {
    write(c);
  }
}

FILEReader::FILEReader(const std::string &file_name)
    : file(nullptr), open(false), file_ends(false) {
  file = fopen(file_name.c_str(), "r");
  if (file == nullptr) {
    throw std::runtime_error("Failed to open file");
  }
  open = true;
}

FILEReader::~FILEReader() {
  if (open) {
    close();
  }
}

bool FILEReader::is_file_ends() const { return file_ends; }

bool FILEReader::is_open() const { return open; }

void FILEReader::close() {
  if (file != nullptr) {
    fclose(file);
    file = nullptr;
    open = false;
  }
}

char FILEReader::read_char() {
  char c;
  int result = fscanf(file, "%c", &c);
  if (result == EOF) {
    file_ends = true;
    return '\0';
  }
  return c;
}

int FILEReader::read_int() {
  int i;
  int result = fscanf(file, "%d", &i);
  if (result == EOF) {
    file_ends = true;
  }
  return i;
}

std::string FILEReader::read_string() {
  std::string line;
  char c;
  while (!file_ends) {
    c = read_char();
    if (c == '\0' || c == '\n') {
      break;
    }
    line.push_back(c);
  }
  return line;
}

BufferedStringReaderWriter::BufferedStringReaderWriter(std::string &string,
                                                       size_t buffer_size)
    : file_ends(false), buffer_size_(buffer_size), buffer_ends(false),
      string_(string), string_pos(0), open(true) {
  update_buffer();
}

BufferedStringReaderWriter::BufferedStringReaderWriter(std::string &string)
    : BufferedStringReaderWriter(string, 16) {}

void BufferedStringReaderWriter::update_buffer() {
  read_buffer_pos = 0;
  read_buffer.clear();
  if (file_ends) {
    return;
  }
  for (size_t i = 0; i < buffer_size_; i++) {
    if (string_pos == string_.size()) {
      buffer_ends = true;
      return;
    }

    char c = string_.at(string_pos++);

    read_buffer.push_back(c);
  }
  if (read_buffer.empty()) {
    file_ends = true;
  }
}

BufferedStringReaderWriter::~BufferedStringReaderWriter() {}

bool BufferedStringReaderWriter::is_file_ends() const { return file_ends; }

bool BufferedStringReaderWriter::is_open() const { return open; }

void BufferedStringReaderWriter::close() { open = false; }

char BufferedStringReaderWriter::read_char() {
  if (read_buffer_pos == read_buffer.size()) {
    update_write_buffer(true);
    update_buffer();
  }
  char c = read_buffer.at(read_buffer_pos++);
  if (read_buffer_pos == read_buffer.size()) {
    if (buffer_ends) {
      file_ends = true;
    } else {
      update_buffer();
    }
  }
  return c;
}

int BufferedStringReaderWriter::read_int() { return read_char() - '0'; }

std::string BufferedStringReaderWriter::read_string() {
  std::string line;
  char c;
  while (!file_ends) {
    c = read_char();
    if (c == '\0' || c == '\n') {
      break;
    }
    line.push_back(c);
  }
  return line;
}

void BufferedStringReaderWriter::write(int i) { write(std::to_string(i)); }

void BufferedStringReaderWriter::write(char c) {
  write_buffer.push_back(c);
  update_write_buffer(false);
  file_ends = false;
  buffer_ends = false;
}

void BufferedStringReaderWriter::write(const std::string &string) {
  for (char c : string) {
    write(c);
  }
}

void BufferedStringReaderWriter::update_write_buffer(bool now) {
  if (write_buffer.size() < buffer_size_ && !now) {
    return;
  }
  for (char c : write_buffer) {
    string_.push_back(c);
  }
  write_buffer.clear();
}

BufferedFILEReaderWriter::BufferedFILEReaderWriter(const std::string filename,
                                                   size_t buffer_size)
    : file(nullptr), open(false), file_ends(false), buffer_size_(buffer_size),
      buffer_ends(false) {
  file = fopen(filename.c_str(), "r+");
  if (file == nullptr) {
    throw std::runtime_error("Cannot open file");
  }
  open = true;

  update_buffer();
}

BufferedFILEReaderWriter::BufferedFILEReaderWriter(const std::string filename)
    : BufferedFILEReaderWriter(filename, 16) {}

void BufferedFILEReaderWriter::update_buffer() {
  read_buffer_pos = 0;
  read_buffer.clear();
  if (file_ends) {
    return;
  }
  for (size_t i = 0; i < buffer_size_; i++) {
    char c;
    char result = fscanf(file, "%c", &c);
    if (result == EOF) {
      buffer_ends = true;
      break;
    }

    read_buffer.push_back(c);
  }
  if (read_buffer.empty()) {
    file_ends = true;
  }
}

BufferedFILEReaderWriter::~BufferedFILEReaderWriter() {
  if (open) {
    close();
  }
}

bool BufferedFILEReaderWriter::is_file_ends() const { return file_ends; }

bool BufferedFILEReaderWriter::is_open() const { return open; }

void BufferedFILEReaderWriter::close() {
  if (file != nullptr) {
    update_write_buffer(true);

    fclose(file);
    file = nullptr;
    open = false;
  }
}

char BufferedFILEReaderWriter::read_char() {
  if (read_buffer_pos == read_buffer.size()) {
    update_write_buffer(true);
    update_buffer();
  }
  char c = read_buffer.at(read_buffer_pos++);
  if (read_buffer_pos == read_buffer.size()) {
    if (buffer_ends) {
      file_ends = true;
    } else {
        update_buffer();
    }
  }
  return c;
}

int BufferedFILEReaderWriter::read_int() { return read_char() - '0'; }

std::string BufferedFILEReaderWriter::read_string() {
  std::string line;
  char c;
  while (!file_ends) {
    c = read_char();
    if (c == '\0' || c == '\n') {
      break;
    }
    line.push_back(c);
  }
  return line;
}

void BufferedFILEReaderWriter::write(int i) { write(std::to_string(i)); }

void BufferedFILEReaderWriter::write(char c) {
  write_buffer.push_back(c);
  update_write_buffer(false);
  file_ends = false;
  buffer_ends = false;
}

void BufferedFILEReaderWriter::write(const std::string &string) {
  for (char c : string) {
    write(c);
  }
}

void BufferedFILEReaderWriter::update_write_buffer(bool now) {
  if (write_buffer.size() < buffer_size_ && !now) {
    return;
  }
  long current_pos = ftell(file);
  fprintf(file, "%s", write_buffer.c_str());
  fseek(file, current_pos, SEEK_SET);

  write_buffer.clear();
}