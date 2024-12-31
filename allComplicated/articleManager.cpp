#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <stdexcept>
#include <variant>

using OptionValue = std::variant<int, std::map<std::string, int>>;

class ArticleManager {
private:
    std::string articleText;
    std::vector<std::string> pages;
    std::vector<std::string> words;
    int wordsPerLine;
    int linesPerPage;
    std::map<std::string, int> paymentStructure;

public:
    ArticleManager(const std::string& articleText, const std::map<std::string, OptionValue>& options) {
        if (articleText.empty()) {
            throw std::invalid_argument("Article text cannot be null or empty.");
        }
        this->articleText = articleText;

        if (auto wpl = std::get_if<int>(&options.at("wordsPerLine"))) {
            this->wordsPerLine = *wpl;
        } else {
            this->wordsPerLine = 12;
        }

        if (auto lpp = std::get_if<int>(&options.at("linesPerPage"))) {
            this->linesPerPage = *lpp;
        } else {
            this->linesPerPage = 20;
        }

        if (auto ps = std::get_if<std::map<std::string, int>>(&options.at("paymentStructure"))) {
            this->paymentStructure = *ps;
        } else {
            this->paymentStructure = createDefaultPaymentStructure();
        }
    }

private:
    std::map<std::string, int> createDefaultPaymentStructure() {
        return {
            {"1", 30},
            {"2", 30},
            {"3", 60},
            {"4", 60},
            {"default", 100}
        };
    }

public:
    void splitIntoPages() {
        std::istringstream iss(articleText);
        std::string word;
        while (iss >> word) {
            words.push_back(word);
        }
        std::cout << "Total Words: " << words.size() << std::endl;

        std::vector<std::string> lines;
        for (size_t i = 0; i < words.size(); i += wordsPerLine) {
            size_t end = std::min(i + (size_t)wordsPerLine, words.size());
            std::string line;
            for (size_t j = i; j < end; ++j) {
                line += words[j];
                if (j < end - 1) {
                    line += " ";
                }
            }
            lines.push_back(line);
        }

        pages.clear();
        for (size_t i = 0; i < lines.size(); i += linesPerPage) {
            size_t end = std::min(i + (size_t)linesPerPage, lines.size());
            std::string page;
            for (size_t j = i; j < end; ++j) {
                page += lines[j];
                if (j < end - 1) {
                    page += "\n";
                }
            }
            pages.push_back(page);
        }
    }

    int calculatePayment() {
        int totalPages = pages.size();
        if (totalPages < 1) {
            return 0;
        }

        std::string key = std::to_string(std::min(totalPages, 4));
        return paymentStructure.count(key) ? paymentStructure.at(key) : paymentStructure.at("default");
    }

    void displayPages() {
        int payment = calculatePayment();
        std::cout << "Total Pages: " << pages.size() << std::endl;
        std::cout << "Payment Due: $" << payment << std::endl;

        for (size_t i = 0; i < pages.size(); ++i) {
            std::cout << "\nPage " << (i + 1) << ":\n" << pages[i] << std::endl;
        }
    }

    void processArticle() {
        splitIntoPages();
        displayPages();
    }
};

int main() {
    std::stringstream ss;
    ss << "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla "
       << "pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est "
       << "laborum."
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est "
       << "laborum."
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "   
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
       << "et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea ";

    std::string articleText = ss.str();

    std::map<std::string, int> paymentStructure = {
        {"1", 30}, {"2", 30}, {"3", 60}, {"4", 60}, {"default", 100}
    };

    std::map<std::string, OptionValue> options = {
        {"wordsPerLine", 12},
        {"linesPerPage", 20},
        {"paymentStructure", paymentStructure}
    };

    ArticleManager articleManager(articleText, options);
    articleManager.processArticle();

    return 0;
}