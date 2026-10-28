#include <memory>
#include <algorithm>
#include <iostream>

class SimpleText {
public:
	virtual void render(const std::string& data) const {
		std::cout << data;
	}

};

class DecoratedText : public SimpleText {
public:
	std::unique_ptr<SimpleText> _text_;
	DecoratedText(std::unique_ptr<SimpleText> text) : _text_(std::move(text)) {}

};

class Paragraph : public DecoratedText {
public:
	Paragraph(std::unique_ptr<SimpleText> text) : DecoratedText(std::move(text)) {}

	void render(const std::string& data) const {
		std::cout << "<p>";
		_text_->render(data);
		std::cout << "<p>";
	}

};

class Reversed : public DecoratedText {
public:
	Reversed(std::unique_ptr<SimpleText> text) : DecoratedText(std::move(text)) {}

	void render(std::string& data) {
		std::reverse(data.begin(), data.end());
		_text_->render(data);
	}

};

class Link : public DecoratedText {
public:
	Link(std::unique_ptr<SimpleText> text) : DecoratedText(std::move(text)) {}

	void render(const std::string& data1, const std::string& data2) {
		std::cout << "<a href=";
		_text_->render(data1);
		std::cout << ">";
		_text_->render(data2);
		std::cout << "</a>";
	}
};

int main() {
	auto simple_text = std::make_unique<SimpleText>();
	simple_text->render("Hello world");
	std::cout << std::endl;

	auto paragraph = std::make_unique<Paragraph>(std::make_unique<SimpleText>());
	paragraph->render("Hello world");
	std::cout << std::endl;

	auto reversed = std::make_unique<Reversed>(std::make_unique<SimpleText>());
	std::string s = "Hello world";
	reversed->render(s);
	std::cout << std::endl;

	auto link = std::make_unique<Link>(std::make_unique<SimpleText>());
	link->render("netology.ru", "Hello world");
	std::cout << std::endl;
	return 0;
}