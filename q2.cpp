//
// Created by kobi on 12/31/22.
//

#include <array>
#include <string>
#include <memory>
#include <cassert>

namespace {

    class trie final {
    public:
        static constexpr auto NUM = 26U;
        struct node final {
            explicit node(const char c) : letter_{c} {}
            char letter_{};
            bool is_word_{false};
            std::array<std::unique_ptr<node>, NUM> n_;
        };
        void insert(const std::string& val) {
            std::array<std::unique_ptr<node>, NUM>* curr = &root_;
            node* last{};
            for(const auto c : val) {
                node* n = (*curr)[c - 'a'].get();
                if (!n) {
                    (*curr)[c - 'a'] = std::make_unique<node>(c - 'a');
                }
                auto t = (*curr)[c - 'a'].get();
                last = (*curr)[c - 'a'].get();
                curr = &t->n_;
            }
            last->is_word_ = true;
        }
        [[nodiscard]]
        bool search(const std::string& val) const {
            const std::array<std::unique_ptr<node>, NUM>* curr = &root_;
            const node* last{};
            for(const char c : val) {
                node* n = (*curr)[c - 'a'].get();
                if (!n) {
                    return false;
                }
                auto t = (*curr)[c - 'a'].get();
                last = (*curr)[c - 'a'].get();
                curr = &t->n_;
            }
            return last->is_word_;
        }
    private:
        std::array<std::unique_ptr<node>, NUM> root_;
    };

}

int main() {
    trie t;
    t.insert("hello");
    assert(t.search("hello"));
    assert(!t.search("world"));
    t.insert("world");
    assert(t.search("hello"));
    assert(t.search("world"));
    return 0;
}
