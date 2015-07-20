#include "al_base.h"

al_base::al_base(size_t r, size_t w, size_t v_num, size_t e_num):round(r),width(w),elements(NULL),al_graph(NULL){
	elements = new std::vector<al_protocol::element>(e_num);
	al_graph = new ALGraph<int>(v_num, ALGraph<int>::DN);
}

al_base::~al_base(){
	delete elements;
	delete al_graph;
}  
/*
void al_base::max_delay_element(al_protocol::element &el, int &de){
	
}
*/


void al_base::init_graph(void(*ptr)(ALGraph<int> &, std::string), std::string al_type){
	(*ptr)(*al_graph, al_type);
}

/*
void al_base::get_element_group(std::vector<std::vector<al_protocol::element>>&){

	
}
*/
void al_base::key_path(std::vector<al_protocol::element> &p, int &d){
	std::vector<int> path = std::vector<int>();
    SaveCriticalPath(*al_graph, path, d);
	p.clear();
	for(int i:path)
		p.push_back((al_protocol::element)i);
	
}










