#ifndef al_base_h
#define al_base_h


#include <string>
#include <vector>
#include "al_protocol.h"
#include "graph_t.h"

class al_base{
protected:
size_t round;                                  //�㷨����
size_t width;                                  //����λ��
std::vector<al_protocol::element> *elements;    //Ԫ������
ALGraph<int> *al_graph;                         //�㷨AOEͼ,û�ж������������������������Ƴ�Ա�����ʹ��ʱҪע��


public:
al_base(size_t r, size_t w, size_t v_num, size_t e_num);
void max_delay_element(al_protocol::element &, int &){}
void init_graph(void(*ptr)(ALGraph<int> &, std::string), std::string);
virtual void get_element_group(std::vector<std::vector<al_protocol::element>>&){}
virtual void key_path(std::vector<al_protocol::element> &, int &);
virtual ~al_base();
};

#endif
