#include <iostream>
#include <fstream>
#include <limits>
#include <deque>
#include <sstream>

namespace {

    class rate_limit final {
    public:
        rate_limit(const int msg_limit, const int time_limit) : msg_limit_{msg_limit},
        time_limit_{time_limit} {}
        [[nodiscard]] bool push(const uint64_t val) {
            if (q_.empty()) {
                q_.push_back(val);
                return true;
            }
            while(!q_.empty() && (val - q_.front()) >= time_limit_) {
                q_.pop_front();
            }
            if (q_.size() < msg_limit_) {
                q_.push_back(val);
                return true;
            }
            return false;
        }
    private:
        std::deque<uint64_t> q_;
        int msg_limit_{};
        int time_limit_{};
    };

}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "q1 <filename>\n";
        return 1;
    }
    std::ifstream f(argv[1]);
    if (!f.is_open()) {
        std::cerr << "cannot open " << argv[1] << '\n';
        return -1;
    }

    int N = 0, T = 0;
    f >> N  >> T;
    if (f.bad() | f.fail()) {
        std::cerr << "failed to get N and T\n";
        return -1;
    }

    f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::clog << "N and T " << N << ',' << T << '\n';

    std::string line;
    rate_limit rl(N, T);
    while (std::getline(f, line)) {
        //std::clog << "line: " << line << '\n';
        std::istringstream is(line);
        uint64_t val{};
        is >> val;
        const auto ok = rl.push(val);
        if(ok) {
            std::clog << line << ' ' << "pass\n";
        } else {
            std::clog << line << ' ' << "fail\n";
        }
    }

    return 0;
}
