#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <random>
#include <algorithm>
#include "timer/timer.cpp"

auto time_measure_associate_container(const std::vector<int>& container)
{
    Timer time{ "start filling of set", std::cout };
    std::set<int> ass_container;
    for (const auto elem : container)
        ass_container.emplace(elem);
    time.stop();

    return time.get_time();
}

auto time_measure_by_std_sort(const std::vector<int>& container)
{
    Timer time{ "start sort of vector", std::cout };
    std::vector<int> vector;
    for (const auto elem : container)
        vector.push_back(elem);
    std::sort(std::begin(vector), std::end(vector));
    time.stop();

    return time.get_time();
}

auto test_result(std::vector< std::vector<double> >& seria)
{
    std::vector<double> res;

    for (size_t j = 0; j < seria[0].size(); j++)
    {
        double sum = 0;
        for (size_t i = 0; i < seria.size(); i++)
        {
            sum += seria[i][j];
            std::cout << seria[i][j] << " ";
        }
        std::cout << std::endl << std::endl;
        res.push_back(sum / seria.size());
    }

    return res;
}

int main()
{
    const auto N = 1000;

    std::vector<int> vector(N);
    std::iota(std::begin(vector), std::end(vector), 0);

    std::random_device seed;
    std::mt19937 engine(seed());
    std::shuffle(std::begin(vector), std::end(vector), engine);

    std::vector< std::vector<double> > seria(50);
    for (auto& current : seria)
    {
        current.push_back(time_measure_associate_container(vector)); // #0
        current.push_back(time_measure_by_std_sort(vector));        // #1
    }

    auto result = test_result(seria);
    std::cout << std::endl << std::endl;
    for (auto& elem : result)
        std::cout << elem << " ";

    system("pause");

    return EXIT_SUCCESS;
}

/*
-----------
N == 100000

set:    0.166883 | 0.159023 0.191318 0.195442 0.161243 0.142133 0.143938 0.165477 0.168168 0.160206 0.171513 0.197317 0.186639 0.168287 0.247249 0.160777 0.153536 0.163173 0.158020 0.165386 0.167644 0.177279 0.168067 0.179030 0.174096 0.169679 0.160663 0.194569 0.156775 0.161451 0.171371 0.161157 0.162848 0.172180 0.150889 0.174424 0.147625 0.148936 0.159287 0.227668 0.167157 0.167573 0.160861 0.162705 0.155288 0.156318 0.142837 0.142197 0.144052 0.145075 0.155590

vector: 0.058434 | 0.129819 0.060351 0.063162 0.055014 0.054265 0.055159 0.056669 0.057236 0.067692 0.058488 0.056282 0.055023 0.055611 0.057531 0.054818 0.057255 0.056303 0.057253 0.056647 0.056868 0.060662 0.056998 0.056114 0.054763 0.057681 0.060142 0.055126 0.056084 0.066362 0.054971 0.055076 0.055437 0.056595 0.056675 0.053677 0.053897 0.054628 0.067648 0.057628 0.054121 0.054722 0.057282 0.058354 0.056298 0.055981 0.053740 0.055008 0.053481 0.055302 0.055823
-----------
N = 10000

set:    0.016147 | 0.014348 0.016136 0.017540 0.014508 0.014481 0.017079 0.014250 0.014309 0.015758 0.014756 0.016557 0.017110 0.016670 0.018345 0.014592 0.014224 0.015740 0.014512 0.014564 0.019616 0.017008 0.017232 0.014285 0.017103 0.015679 0.014899 0.014698 0.017219 0.017083 0.017280 0.014383 0.016930 0.017956 0.015351 0.014496 0.018607 0.019758 0.017240 0.014627 0.014409 0.015205 0.014533 0.016049 0.014548 0.018708 0.018929 0.014571 0.015377 0.016231 0.021882

vector: 0.009600 | 0.011279 0.007247 0.009711 0.008522 0.006804 0.011306 0.012237 0.011041 0.014625 0.011559 0.012302 0.007515 0.007205 0.008630 0.012623 0.012654 0.009871 0.008083 0.006639 0.006624 0.006773 0.012349 0.011516 0.012250 0.008603 0.006584 0.006659 0.007052 0.011066 0.012175 0.009654 0.009619 0.013334 0.008656 0.006620 0.006610 0.006736 0.011842 0.012210 0.011997 0.014698 0.008472 0.008312 0.006833 0.006837 0.010282 0.009057 0.009163 0.008213 0.009348
-----------
N == 1000

set:    0.005742 | 0.048806 0.005232 0.005025 0.005969 0.004633 0.005237 0.005977 0.006246 0.005897 0.009329 0.007469 0.007668 0.008438 0.006245 0.003584 0.003796 0.003221 0.005626 0.005250 0.005703 0.003425 0.003213 0.003239 0.005941 0.003314 0.003200 0.003198 0.003785 0.007727 0.005571 0.003328 0.003461 0.003229 0.003676 0.003511 0.005280 0.005250 0.003660 0.003194 0.003183 0.005256 0.003738 0.003190 0.003223 0.003246 0.003247 0.003394 0.008057 0.008077 0.005928

vector: 0.004152 | 0.006456 0.004217 0.006384 0.004508 0.005138 0.005194 0.005423 0.002530 0.004455 0.002616 0.002995 0.004253 0.005668 0.004841 0.007574 0.005428 0.002670 0.003000 0.002507 0.002495 0.004520 0.005350 0.002516 0.002504 0.003884 0.006843 0.002517 0.002512 0.002507 0.002512 0.007373 0.005326 0.004572 0.004671 0.002506 0.002943 0.002496 0.004896 0.004607 0.003163 0.002502 0.004937 0.004925 0.008969 0.005165 0.004235 0.002508 0.002624 0.002645 0.002509
-----------
*/