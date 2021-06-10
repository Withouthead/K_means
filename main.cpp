#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <cstdlib>
#include <ctime>
#include <map>
#include <algorithm>
class K_Means
{
public:
    K_Means(int _k, const Eigen::MatrixXd&  _x):k(_k),points(_x)
    {
        for(int i = 0; i < _x.rows(); i++)
            point_set_index.push_back(i);
    }

    std::vector<std::vector<int>> run()
    {
        unsigned seed = time(0);
        srand(seed);


        std::vector<int> temp_centerIndex(points.rows());
        for(int i = 0; i < points.rows(); i++) temp_centerIndex[i] = i;
        std::random_shuffle(temp_centerIndex.begin(), temp_centerIndex.end());
        for(int i = 0; i < k; i++) center_points.push_back(points.row(temp_centerIndex[i]));

        std::vector<std::vector<int>> new_point_set(k);

        bool check_center_equal = false;

        int cnt = 0;
        while(!check_center_equal)
        {
            check_center_equal = true;
            point_set = new_point_set;
            new_point_set = std::vector<std::vector<int>>(k);
            std::map<int, Eigen::MatrixXd> cal_center_map;
            for(int i = 0; i < points.rows(); i++)
            {
                double dis_min = std::numeric_limits<double>::max();
                double c_index = 0;
                for(int j = 0;  j < k; j++)
                {
                    double the_dis = cal_distance(center_points[j], points.row(i));
                    if(the_dis < dis_min)
                    {
                        dis_min = the_dis;
                        c_index = j;
                    }
                }
                if(c_index != point_set_index[i])
                    check_center_equal = false;
                point_set_index[i] = c_index;
                if(cal_center_map.find(c_index) != cal_center_map.end()) {
                    cal_center_map[c_index] += points.row(i);
//                    std::cout << cal_center_map[c_index] << std::endl;
                }
                else {
                    cal_center_map[c_index] = points.row(i);
//                    std::cout << cal_center_map[c_index] << std::endl;
                }
                new_point_set[c_index].push_back(i);
            }
            for(int i = 0; i < k; i++) {
//                std::cout << cal_center_map[i];
                center_points[i] = cal_center_map[i] / new_point_set[i].size();
//                std::cout << center_points[i] << std::endl;
            }
            print(cnt, new_point_set);
            cnt ++;
        }

        return point_set;
    }
    void print(int times, const std::vector<std::vector<int>> v) const
    {
        std::cout << "第" << times << "次 "<< std::endl;
        for(int i = 0; i < v.size(); i++) {
            for (int j = 0; j < v[i].size(); j++) {
                if (j != 0)
                    std::cout << ", ";
                else
                    std::cout << "<";
                std::cout << v[i][j];
            }
            std::cout << '>' << std::endl;
        }
        std::cout << std::endl;

    }
private:

    const Eigen::MatrixXd points;
    int k;
    std::vector<Eigen::MatrixXd> center_points;
    std::vector<std::vector<int>> point_set;
    std::vector<int>point_set_index;

    static double cal_distance(const Eigen::MatrixXd& p1, const Eigen::MatrixXd& p2)
    {
        double value = sqrt((p1 - p2).squaredNorm());
        return value;
    }


};

int main() {
    int n, m;
    std::cout << "请分别输入数据的数量和维度" << std::endl;
    std::cin >> n >> m;
    int k;
    std::cout << "请输入分类个数" << std::endl;
    std::cin >> k;
    std::cout << "请输入数据" << std::endl;
    Eigen::MatrixXd data_matrix(n, m);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++) {
            double x;
            std::cin >> x;
            data_matrix(i, j) = x;
        }
    }
    K_Means kmans(k, data_matrix);
    std::vector<std::vector<int>> point_set = kmans.run();
    //kmans.print(point_set);
    return 0;
}
