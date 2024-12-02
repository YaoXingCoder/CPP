
#include <string>
#include <vector>
using std::string;
using std::vector;

#define VEC_DEFALUT_CAPA 64
#define FILENAME_XML "coolshell.xml"
#define FILENAME_OUTPUT "pagelib.txt"

/* 存储结构体 */
struct RssItem {
    string title;
    string link;
    string description;
    string content;
};

/* 读取 */
class RssReader {
public:
    RssReader(const int capacity = VEC_DEFALUT_CAPA);
    void parseRss(); // 解析
    void dump(const string & filename); // 输出
private:
    vector<RssItem> _rss;
};  
