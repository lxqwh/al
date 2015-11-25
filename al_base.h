#ifndef al_base_h
#define al_base_h


#include <string>
#include <vector>
#include "al_protocol.h"
#include "graph_t.h"

class al_base{
protected:
std::string name;
size_t round;                                  //算法轮数
size_t width;                                  //算子位宽
std::vector<al_protocol::element> *elements;    //元素数组
ALGraph<int> *al_graph;                         //算法AOE图,没有定义除析构以外的其他拷贝控制成员，因此使用时要注意


public:
	al_base(std::string name, size_t r, size_t w, size_t v_num, vector<al_protocol::element>);
void max_delay_element(al_protocol::element &);
void init_graph(void(*ptr)(ALGraph<int> &, std::string), std::string);
virtual void get_element_group(std::vector<std::vector<al_protocol::element>>&){}
virtual void key_path(std::vector<al_protocol::element> &, int &);
virtual ~al_base();
std::string getname(){return name;}
size_t getround(){return round;}
size_t getwidth(){return width;}
ALGraph<int> * getgraph(){return al_graph;}
std::vector<al_protocol::element> * getelements(){return elements;}
};

#endif
