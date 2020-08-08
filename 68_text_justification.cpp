#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
	std::vector<std::string> fullJustify(const std::vector<std::string> & words, int maxWidth) {
		std::vector<std::string> text;
		int i = 0;
		while (i < words.size()) {
			int j = i;
			int length = 0;
			while (j < words.size() && length + words[j].size() + j - i <= maxWidth) {
				length += words[j].size();
				++j;
			}
			--j;

			//此行只有一个单词，左对齐
			if (i == j) {
				text.push_back(words[i] + std::string(size_t(maxWidth - length), ' '));
			}
			//最后一行，左对齐
			else if (j + 1 == words.size()) {
				std::string line;
				for (int k = i; k < j; ++k)
					line += words[k] + " ";
				line += words[j] + std::string(size_t(maxWidth - length - (j - i)), ' ');
				text.push_back(line);
			}
			//此行有多个单词且不为最后一行，两侧对齐
			else {
				int spaces = (maxWidth - length) / (j - i); //平均每个单词间隔有多少个空格
				int rest = (maxWidth - length) % (j - i);	 //靠左的这些单词间隔多一个空格，保证右对齐
				std::string line;
				for (int k = i; k < i + rest; ++k)
					line += words[k] + std::string(size_t(spaces + 1), ' ');
				for (int k = i + rest; k < j; ++k)
					line += words[k] + std::string(size_t(spaces), ' ');
				line += words[j];
				text.push_back(line);
			}

			i = j + 1;
		}

		return text;
	}
};

std::ostream & operator<<(std::ostream & out, const std::vector<std::string> & text) {
	for (const auto & line : text)
		out << line << std::endl;
	return out;
}

int main() {
	//"This    is    an",
    //"example  of text",
    //"justification.  "
	std::vector<std::string> words1 = { "This", "is", "an", "example", "of", "text", "justification." };
	int maxWidth1 = 16;
	std::cout << Solution().fullJustify(words1, maxWidth1) << std::endl;

	//"What   must   be",
    //"acknowledgment  ",
    //"shall be        "
	std::vector<std::string> words2 = { "What", "must", "be", "acknowledgment", "shall", "be" };
	int maxWidth2 = 16;
	std::cout << Solution().fullJustify(words2, maxWidth2) << std::endl;

	//"Science  is  what we",
    //"understand      well",
    //"enough to explain to",
    //"a  computer.  Art is",
    //"everything  else  we",
    //"do                  "
	std::vector<std::string> words3 = { "Science", "is", "what", "we", "understand", "well", "enough",
	    "to", "explain", "to", "a", "computer.", "Art", "is", "everything", "else", "we", "do" };
	int maxWidth3 = 20;
	std::cout << Solution().fullJustify(words3, maxWidth3) << std::endl;

	return 0;
}

