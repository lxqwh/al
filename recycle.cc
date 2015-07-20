
	int idea_maxdelay;
	int aes_maxdelay;
	int des_maxdelay;	
	
	ALGraph<int> idea(23, ALGraph<int>::DN);
	ALGraph<int> aes(5, ALGraph<int>::DN);
	ALGraph<int> des(7, ALGraph<int>::DN);

	
    vector<int> idea_save = vector<int>();
	init_al_graph(idea, "IDEA");
    SaveCriticalPath(idea,idea_save,idea_maxdelay);
	cout<<"the critical path is:"<<endl;
	for(int i:idea_save){
		print_element(i);
		cout<<" -> "<<endl;
	}
	cout<<"the total delay of a round is :"<<idea_maxdelay<<endl;
	cout<<endl;

    vector<int> aes_save = vector<int>();
	init_al_graph(aes, "AES");
    SaveCriticalPath(aes,aes_save,aes_maxdelay);
	cout<<"the critical path is:"<<endl;
	for(int i:aes_save){
		print_element(i);
		cout<<" -> "<<endl;
	}
	cout<<"the total delay of a round is :"<<aes_maxdelay<<endl;
	cout<<endl;
	
    vector<int> des_save = vector<int>();
	init_al_graph(des, "DES");
    SaveCriticalPath(des,des_save,des_maxdelay);
	cout<<"the critical path is:"<<endl;
	for(int i:des_save){
		print_element(i);
		cout<<" -> "<<endl;
	}
	cout<<"the total delay of a round is :"<<des_maxdelay<<endl;
	cout<<endl;	

	
	
	
	
	