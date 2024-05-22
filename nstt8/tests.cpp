#include "ReadingWriting.hpp"

void testStringReaderWriter() {
    std::string source = "Hello, World!";
    StringReaderWriter rw(source);

    assert(rw.read_char() == 'H');
    assert(rw.read_char() == 'e');
    assert(rw.read_string() == "llo, World!");
    

    rw.write_char(' ');
    rw.write_int(123);
    rw.write_char(' ');
    rw.write_string("Testing");
    rw.write_char(' ');
    rw.write_string("StringWriter");

    std::cout << "Modified source: " << source << "\n";
    assert(source == "Hello, World! 123 Testing StringWriter");

    rw.write_char('!');
    assert(source == "Hello, World! 123 Testing StringWriter!");

    std::string source1 = "523";
    StringReaderWriter rw1(source1);
    assert(rw1.read_int() == 523);

    std::cout << "testStringReaderWriter tests passed!\n";
}



void testFileReaderWriterInt() {
    const std::string filename = "nstt8/test_file.txt";

    FileReaderWriter rw(filename);
    rw.clear_file();
    rw.write_int(1234);

    int intValue = rw.read_int();
    assert(intValue == 1234);

    rw.close();
    
    std::cout << "testFileReaderWriterInt passed!" << std::endl;
}

void testFileReaderWriterChar() {
    const std::string filename = "nstt8/test_file.txt";

    FileReaderWriter rw(filename);
    rw.clear_file();
    rw.write_char('B');

    char charValue = rw.read_char();
    assert(charValue == 'B');

    rw.close();

    std::cout << "testFileReaderWriterChar passed!" << std::endl;
}

void testFileReaderWriterString() {
    const std::string filename = "nstt8/test_file.txt";

    FileReaderWriter rw(filename);
    rw.clear_file();
    rw.write_string("Hello, World!");

    std::string strValue = rw.read_string();
    assert(strValue == "Hello, World!");

    rw.close();

    std::cout << "testFileReaderWriterString passed!" << std::endl;
}

void testBufferedStringReaderWriterString() {
    std::string source = "Hello, World!";
    BufferedStringReaderWriter brw(source, 40);
    brw.write_string(" HI!");

    std::string strValue = brw.read_string();
    assert(strValue == "Hello, World! HI!");
    std::cout << "testBufferedStringReaderWriterString passed!" << std::endl;

}

int main() {
    testStringReaderWriter();
    testFileReaderWriterInt();
    testFileReaderWriterChar();
    testFileReaderWriterString();
    testBufferedStringReaderWriterString();
    return 0;
}