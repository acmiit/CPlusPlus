#include <iostream>
#include <set>
#include <unordered_map>
#include <fstream>
#include <sstream>
//测量程序执行时间
#include<chrono>
using namespace std;
class Query
{
public:
    string dealWord(string &word)
    {
        for (size_t idx = 0; idx != word.size(); ++idx)
        {
            if (!isalpha(word[idx]))
            {
                // 返回空字符串
                return string();
            }
            else if (isupper(word[idx]))
            {
                // 大写转小写
                word[idx] = tolower(word[idx]);
            }
        }
        return word;
    }
    void read(const string &filename)
    {
        ifstream ifs(filename);
        if (!ifs)
        {
            cerr << "ifs open file fail!" << endl;
            return;
        }
        string line;
        while (getline(ifs, line))
        {
            istringstream iss(line);
            string word;
            while (iss >> word)
            {
                string newword = dealWord(word);
                if (newword != string())
                {
                    _dict[newword]++;
                }
            }
        }
        ifs.close();
    }
    void store(const string &filename)
    {
        ofstream ofs(filename);
        if (!ofs)
        {
            cerr << "ofs open file fail" << endl;
        }

        for (auto &it : _dict)
        {
            ofs << it.first << " " << it.second << endl;
        }
        ofs.close();
    }

private:
    unordered_map<string, int> _dict;
};
int main()
{
    Query q;
    // 获取程序开始时间点
    auto start = chrono::high_resolution_clock::now();
    q.read("The_Holy_Bible.txt");
    q.store("Dict.txt");
    // 获取程序结束时间点
    auto end = chrono::high_resolution_clock::now();
    // 计算时间差
    auto duration = std::chrono::duration_cast<chrono::milliseconds>(end - start);

    // 输出执行时间
    cout << "程序执行时间：" << duration.count() << " 毫秒" << endl;
    return 0;
}