#ifndef algorithm_define_h
#define algorithm_define_h

#include "graph_t.h"
#include <string>

#define IDEA(g)                                                                                           \
	(g).Insertedge(1,2,462);   (g).Insertedge(1,3,356);   (g).Insertedge(1,4,356); (g).Insertedge(1,4,462);       \
	                                                                                                      \
	(g).Insertedge(2,18,0);    (g).Insertedge(2,6,0);     (g).Insertedge(3,22,0);   (g).Insertedge(3,8,0);        \
	(g).Insertedge(4,6,0);     (g).Insertedge(4,16,0);    (g).Insertedge(5,8,0);    (g).Insertedge(5,20,0);       \
	                                                                                                      \
	(g).Insertedge(6,7,30);    (g).Insertedge(8,9,30);                                                        \
	                                                                                                      \
	(g).Insertedge(7,10,462);  (g).Insertedge(9,11,0);                                                        \
	                                                                                                      \
	(g).Insertedge(10,14,0);   (g).Insertedge(10,11,0);                                                       \
	                                                                                                      \
	(g).Insertedge(11,12,356);                                                                              \
	                                                                                                      \
	(g).Insertedge(12,13,462);                                                                              \
	                                                                                                      \
	(g).Insertedge(13,18,0) ;  (g).Insertedge(13,14,0);   (g).Insertedge(13,16,0);                              \
	                                                                                                      \
	(g).Insertedge(18,19,30);	 (g).Insertedge(14,15,356); (g).Insertedge(16,17,30);                             \
	                                                                                                      \
	(g).Insertedge(15,22,0);   (g).Insertedge(15,20,0);                                                       \
	                                                                                                      \
	(g).Insertedge(22,23,30);  (g).Insertedge(20,21,30); 


#define AES(g)                  \
    (g).Insertedge(1,2,163);      \
	(g).Insertedge(2,3,164);      \
	(g).Insertedge(3,4,422);      \
	(g).Insertedge(4,5,30);
	
#define DES(g)                  \
    (g).Insertedge(1,2,60);       \
    (g).Insertedge(1,6,0);	    \
	(g).Insertedge(2,3,30);       \
	(g).Insertedge(3,4,163);      \
	(g).Insertedge(4,5,60);       \
	(g).Insertedge(5,6,0);	    \
	(g).Insertedge(6,7,30);		
	
inline void	init_al_graph(ALGraph<int> &g, std::string al_type){
	if(al_type == "IDEA" ){
		for(int i = 0; i <= 22; i++)
		g.InsertVertex(i+1);
		IDEA(g); 
	}
	else if(al_type == "AES"){
		for(int i = 0; i <= 4; i++){
		g.InsertVertex(i+1);
	    }
		AES(g); 
	}
	else if(al_type == "DES"){  
		for(int i = 0; i <= 6; i++){
		g.InsertVertex(i+1);
	    }
		DES(g);  
	}
}


	#endif

