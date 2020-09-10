#include <string>
#include <list>
#include "test_runner.h"
using namespace std;

class Editor {
 public:
  // Реализуйте конструктор по умолчанию и объявленные методы
  Editor() {

  }
  void Left() {
	if (cursor != data.begin()) cursor--;
  }
  void Right() {
	  if (cursor != data.end()) cursor++;
  }
  void Insert(char token) {
	  data.insert(cursor, token);
  }
  void Cut(size_t tokens = 1) {
	  auto dublicate_cursor = cursor;
	  buf.clear();
	  for (size_t i = 0; i < tokens; ++i) {
		  if (cursor == data.end()) break;
	  	  buf.push_back(*cursor);
	  	  buf2.push_back(*cursor);
	  	  cursor++;
	  }
	  data.erase(dublicate_cursor, cursor);
  }
  void Copy(size_t tokens = 1) {
	  buf.clear();
	  for (size_t i = 0; i < tokens; ++i) {
		  if (cursor == data.end()) break;
		  buf.push_back(*cursor);
		  buf2.push_back(*cursor);
		  cursor++;
	  }
	  for (size_t i = 0; i < tokens; ++i) {
		  if (cursor == data.begin()) break;
		  cursor--;
	  }
  }
  void Paste() {
	  data.splice(cursor, buf);
	  buf = buf2;
  }
  string GetText() const {
	  string str = "";
	  for (auto it = data.begin(); it != data.end(); ++it)
		  str+=*it;
	  return str;
  }

 private:

  list<char> data;
  list<char>::iterator cursor = data.begin();
  list<char> buf;
  list<char> buf2;
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);

    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");

  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  Editor editor;
    const string text = "hello, world";
    for (char c : text) {
      editor.Insert(c);
    }
    // Текущее состояние редактора: `hello, world|`
    for (size_t i = 0; i < text.size(); ++i) {
      editor.Left();
    }
    // Текущее состояние редактора: `|hello, world`
    editor.Cut(7);
    // Текущее состояние редактора: `|world`
    // в буфере обмена находится текст `hello, `
    for (size_t i = 0; i < 5; ++i) {
      editor.Right();
    }
    // Текущее состояние редактора: `world|`
    editor.Insert(',');
    editor.Insert(' ');
    // Текущее состояние редактора: `world, |`
    editor.Paste();
    // Текущее состояние редактора: `world, hello, |`
    editor.Left();
    editor.Left();
    //Текущее состояние редактора: `world, hello|, `
    editor.Cut(3); // Будут вырезаны 2 символа
    // Текущее состояние редактора: `world, hello|`
    cout << editor.GetText();
}
