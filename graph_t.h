#ifndef _GRAPH_T_H_
#define _GRAPH_T_H_
#include <iomanip>
#include <queue>
#include <vector>
#include <map>
#include <iostream>
using std::cout;
using std::endl;
using std::pair;
using std::vector;
using std::queue;
using std::setw;
// ���嶥���ڽӱ�Ľڵ�ṹ
class edgeNode
{
public:
    int adjVertex;                    // �ñ��е��ڽӶ����ڶ�����е����
    int weight;                       // �ñߵ�Ȩֵ
    edgeNode *next;

	edgeNode::edgeNode(int a=-1, int w=0) : adjVertex(a), weight(w), next(NULL)
	{
	}
};
// ���캯��
// ����aΪ�ڽӶ������ţ�����wΪ�ߵ�Ȩֵ��Ĭ��ȨֵΪ0

// ���嶥���Ľڵ�
template <class VertexType>
class VertexNode
{
public:
    void ClearedgeList();           // ɾ�����������ڽӱ�
    bool Appendedge(int, int = 0);  // �����������ڽӱ��м���һ����
    bool Removeedge(int);           // �����������ڽӱ���ɾ��һ����
    VertexType data;               // ���������
    edgeNode *edgeList;              // �����ڽӱ���׽ڵ�ָ��
};
// ���һ��������ڽӱ��ͷ��ڽӱ���ڵ�
template<class VertexType>
void VertexNode<VertexType>::ClearedgeList()
{
    edgeNode *p, *q;
    p = edgeList;
    while (p != NULL){
        q = p->next;
        delete p;
        p = q;
    }
    edgeList = NULL;
}
// �����������ڽӱ��м���һ����
// ����vΪ��������ڽӶ�����ţ�wghΪ����ߵ�Ȩֵ
template<class VertexType>
bool VertexNode<VertexType>::Appendedge(int v, int wgh)
{
    edgeNode *p = edgeList;
    edgeNode *q = NULL;
    // �ҵ����ӱ���ĩ�ڵ㣬ĩ�ڵ��ָ�븳ֵ��q�����������һ���ڵ��adjVex��ֵ��v��ͬ���򷵻�false
    while (p != NULL){
        if (p->adjVertex == v)
            return false;
        q = p;
        p = p->next;
    }
    // ���ڽӱ��������һ����
    p = new edgeNode(v, wgh);
    if (q == 0)
        edgeList = p;
    else
        q->next = p;
    return true;
}
// �ڶ�����ڽӱ���ɾ��һ����
// ����vΪҪɾ���ߵ��ڽӶ������
template <class VertexType>
bool VertexNode<VertexType>::Removeedge(int v)
{
    edgeNode *p = edgeList;
    edgeNode *q = NULL;
    // �����ڽӱ�������������ߣ���ɾ��
    while (p != NULL){
        if (p->adjVertex == v){
            if (p == edgeList)
                edgeList = p->next;
            else
                q->next = p->next;
            delete p;
            return true;
        }
        q = p;
        p = p->next;
    }
    return false;
}
// ͼ���ڽӱ���
// VertexType�Ƕ�����������ͣ����VertexType���Ǽ򵥵��������ͣ��ڶ���VertexTypeʱ����������==����������ж��������������Ƿ����
template <class VertexType>
class ALGraph
{
public:
    enum GraphStyle                                                // ͼ������
    {
        DG,                                                        // ����ͼ
        DN,                                                        // ������
        UDG,                                                       // ����ͼ
        UDN                                                        // ������
    };
    ALGraph(int = 0, GraphStyle = UDG);                            // ���캯����Ĭ��ͼ������Ϊ����ͼ
    ~ALGraph();
    int LocateVertex(const VertexType&);                        // ���ݶ�������ݣ��ҵ������ڶ�����е����
    inline int GetNumVertices();                                // ȡ��ͼ�еĶ�����Ŀ
    bool GetVertex(int, VertexType&);                           // ������ţ�ȡ�ö��������
    bool SetVertex(int, const VertexType&);                     // ������ţ����ö��������  
    bool InsertVertex(const VertexType&);                       // ����һ������
    bool DeleteVertex(const VertexType&);                       // ɾ��һ������
    bool Insertedge(const VertexType&, const VertexType&, int = 0); // ����һ����
    bool Deleteedge(const VertexType&, const VertexType&);        // ɾ��һ����
    int GetFirstAdjVex(int);                                    // ������ţ�ȡ�ö���ĵ�һ���ڽӶ�������
    int GetNextAdjVex(int v, int w);                            // ������ţ�ȡ��v(�����w)����һ���ڽӶ������
    bool Getedge(int, int,edgeNode*&);                            // ���ݶ�����ţ�ȡ��������֮��ı�
    inline int GetNumedges();                                    // ȡ��ͼ�еı���
    void DFSTraverse(void (*Visit)(const VertexType&));            // ������ȱ���ͼ
    void BFSTraverse(void (*Visit)(const VertexType&));            // ������ȱ���ͼ
    
private:
    void DFS(void (*Visit)(const VertexType&), int);            // ��һ���������������ȱ���ͼ
    VertexNode<VertexType> *vertices;                           // �����
    int numVertices;                                            // �������
    int numedges;                                               // ����
    int maxVertices;                                            // ���ɴ�ŵĶ������
    GraphStyle style;                                           // ͼ������
    bool *visited;                                              // �ڱ���ʱ����Ƿ���ʹ��ı�־
};
// ���캯��
// ����sΪ��ͼ���ɴ�ŵĶ��������gsΪͼ�����ͣ�Ĭ��Ϊ����ͼUDG
template <class VertexType>
ALGraph<VertexType>::ALGraph(int s, GraphStyle gs) : numVertices(0), numedges(0), maxVertices(s), style(gs)
{
    if (s > 0)
        vertices = new VertexNode<VertexType>[s];
}
// ��������
template <class VertexType>
ALGraph<VertexType>::~ALGraph()
{
    for (int i = 0; i < numVertices; i++)
        vertices[i].ClearedgeList();
    if (maxVertices != 0)
        delete[] vertices;
}
// ���ݶ�������ݣ��ҵ������ڶ�����е����
// ����vexΪ���������
// ����ֵΪ�������š��緵��-1��δ�ҵ���صĶ���
template <class VertexType>
int ALGraph<VertexType>::LocateVertex(const VertexType & vex)
{
    for (int i = 0; i < numVertices; i++)
        if (vertices[i].data == vex)
            return i;
    return -1;
}
// ȡ��ͼ�Ķ�����Ŀ
template <class VertexType>
int ALGraph<VertexType>::GetNumVertices()
{
    return numVertices;
}
// ȡ��ͼ�ı���Ŀ
template <class VertexType>
int ALGraph<VertexType>:: GetNumedges()
{
    return numedges;
}
// ���ݶ������ţ�ȡ�ö��������
// ����vΪ������ţ�����vex���ڷ��ض�������
template <class VertexType>
bool ALGraph<VertexType>::GetVertex(int v, VertexType& vex)
{
    if (v < 0 || v >= numVertices)
        return false;
    
    vex = vertices[v].data;
    return true;
}
// ���ݶ������ţ����ö��������
// ����vΪ������ţ�����vex�������õĶ�������
template <class VertexType>
bool ALGraph<VertexType>::SetVertex(int v, const VertexType &vex)
{
    if (v < 0 || v >= numVertices)
        return false;
    vertices[v].data = vex;
    return true;
}
// ��ͼ�в���һ������
// ����vexΪҪ����Ķ�������
template <class VertexType>
bool ALGraph<VertexType>::InsertVertex(const VertexType &vex)
{
    // ������ڵĶ�������Ѵ����ֵ���򷵻�
    if (numVertices == maxVertices)
        return false;
    // �ж���ͬ�Ķ����Ƿ���ڣ�����ڣ��򷵻�
    for (int i = 0; i < numVertices; i++)
        if (vertices[i].data == vex)
            return false;
    // ����һ��������
    vertices[numVertices].data = vex;
    vertices[numVertices++].edgeList = NULL;
    return true;
}
// ��ͼ��ɾ��һ������
// ����vexΪ��ɾ�������ֵ
template <class VertexType>
bool ALGraph<VertexType>::DeleteVertex(const VertexType &vex)
{
    int i;
    int v;
    // �ڶ�������ҵ�Ҫɾ���������ţ����û�ҵ��򷵻�
    if ((v = LocateVertex(vex)) == -1)
        return false;
    
    // �����������㣬�����Щ������ڽӱ��а�����Ҫɾ���Ķ��㣬���Ƴ�
    for (i = 0; i < numVertices; i++)
        if (i != v)
        {
            if (vertices[i].Removeedge(v))
                numedges--;
        }
    // �ڶ������ɾ�����Ϊv�Ķ���
    vertices[v].ClearedgeList();
    for (i = v; i < numVertices - 1; i++)
        vertices[i] = vertices[i + 1];
    numVertices--;
    // ��������е��ڽӱ߱��еĶ�����Ŵ���Ҫɾ���Ķ�����ţ�����������ż�1
    edgeNode *p;
    for (i = 0; i < numVertices; i++)
    {
        // �����ö�����ڽӱߵ㣬�����ڽӶ������
        p = vertices[i].edgeList;        
        while (p != NULL)
        {
            if (p->adjVertex > v)                // �ж��ڽӶ�����Ƿ����Ҫɾ���Ķ����
                p->adjVertex--;                  // ���>v���򽫶���ż�1
            p = p->next;
        }
    }
    return true;
}
// ��ͼ�в���һ����
// ����vex1��vex2ΪҪ����ߵ����������ֵ������wghΪ������ߵ�Ȩֵ��Ĭ��ֵΪ0
template <class VertexType>
bool ALGraph<VertexType>::Insertedge(const VertexType &vex1, const VertexType &vex2, int wgh)
{
    // �ҵ����������ڶ�����е���ţ��ֱ�ֵ��v1��v2
    // ����������ֻҪ��һ����ͼ�Ķ������δ�ҵ����򷵻�
    int v1 = LocateVertex(vex1);
    int v2 = LocateVertex(vex2);
    if (v1 == -1 || v2 == -1)
        return false;
    // Ϊ��һ��������ڽӱ�������һ����
    vertices[v1].Appendedge(v2,wgh);
    // ���Ϊ����ͼ�����������һ������ڽӱ�������һ����
    if (style == UDG || style == UDN)
        vertices[v2].Appendedge(v1,wgh);
    numedges++;
    return true;
}
// ��ͼ��ɾ��һ����
// ����vex1��vex2ΪҪɾ���ߵ�������������
template <class VertexType>
bool ALGraph<VertexType>::Deleteedge(const VertexType &vex1, const VertexType &vex2)
{
    // �ҵ����������ڶ�����е���ţ��ֱ�ֵ��v1��v2
    // ����������ֻҪ��һ����ͼ�Ķ������δ�ҵ����򷵻�
    int v1 = LocateVertex(vex1);
    int v2 = LocateVertex(vex2);
    if (v1 == -1 || v2 == -1)
        return false;
    // Ϊ��һ��������ڽӱ�������һ����
    vertices[v1].Removeedge(v2);
    // ���Ϊ����ͼ�����������һ������ڽӱ�������һ����
    if (style == UDG || style == UDN)
        vertices[v2].Removeedge(v1);
    numedges--;
    return true;
}
// ȡ��ͼ�е�v������ĵ�һ���ڽӶ������
template <class VertexType>
int ALGraph<VertexType>::GetFirstAdjVex(int v)
{
    if (v < 0 || v >= numVertices)
        return -1;
    if (vertices[v].edgeList == NULL)
        return -1;
    else
        return vertices[v].edgeList->adjVertex;
}
// ������ţ�ȡ��v(�����w)����һ���ڽӶ������
template <class VertexType>
int ALGraph<VertexType>::GetNextAdjVex(int v, int w)
{
    if(v < 0 || v >= numVertices)
        return -1;
    
    edgeNode *p = vertices[v].edgeList;
    while (p != NULL){
        if (p->adjVertex == w)
            break;
        p = p->next;
    }
    if(p == NULL || p->next == NULL)
        return -1;
    return p->next->adjVertex;
}
// ���ݶ�����ţ�ȡ��������֮��ı�
template <class VertexType>
bool ALGraph<VertexType>::Getedge(int v, int w,edgeNode*& edge)
{
    if(v < 0 || v >= numVertices)
        return false;
    if(w < 0 || w >= numVertices)
        return false;
    edge = vertices[v].edgeList;
    while (edge!= NULL){
        if(edge->adjVertex == w)
            break;
        edge = edge->next;
    }
    return edge != NULL;
}
// ��������ȵķ�������ͼ
// ����Visit�Ǳ�����ÿһ����ʱ���õĺ���
template <class VertexType>
void ALGraph<VertexType>::DFSTraverse(void (*Visit)(const VertexType &))
{
    int v;
    
    // ÿһ����ķ��ʱ�־��Ϊfalse
    visited = new bool[numVertices];
    for (v = 0; v < numVertices; v++)
        visited[v] = false;
    // �Զ�����е�ÿһδ���ʹ��Ķ���������б���
    for (v = 0; v < numVertices; v++)
        if (!visited[v])
            DFS(Visit, v);
    
    delete[] visited;
}
// ��ĳһ����������ݹ����������ȵķ�������ͼ
// ����v�ǳ��������ڶ��������
template <class VertexType>
void ALGraph<VertexType>::DFS(void (*Visit)(const VertexType&), int v)
{
    // �������Ϊv�Ķ���ķ��ʱ�־��������Visit����������
    visited[v] = true;
    Visit(vertices[v].data);
    // �������Ϊv�Ķ���������ڽӶ��㣬���ڽӶ�������Ϊw����w�ݹ����DFS
    edgeNode *p = vertices[v].edgeList;
    while (p != NULL){
        int w = p->adjVertex;
        if (!visited[w])
            DFS(Visit, w);
        p = p->next;
    }
}
// �Թ�����ȵķ�������ͼ
// ����Visit�Ǳ�����ÿһ����ʱ���õĺ���
template <class VertexType>
void ALGraph<VertexType>::BFSTraverse(void (*Visit)(const VertexType &))
{
    int v;
    queue<int> vertexQueue;    // ��������
    edgeNode *p;
    
    // ÿһ����ķ��ʱ�־��Ϊfalse
    visited = new bool[numVertices];
    for (v = 0; v < numVertices; v++)
        visited[v] = false;
    
    // �Զ�����е�ÿһδ���ʹ��Ķ���������б���
    for (v = 0; v < numVertices; v++){
        if (visited[v])
            continue;
        visited[v] = true;
        Visit(vertices[v].data);
        vertexQueue.push(v);
        while (!vertexQueue.empty()){
            int u = vertexQueue.front();
            vertexQueue.pop();
            p = vertices[u].edgeList;
            while (p != NULL){
                int w = p->adjVertex;
                if (!visited[w]){
                    visited[w] = true;
                    Visit(vertices[w].data);
                    vertexQueue.push(w);
                }
                p = p->next;
            }
        }
    }
    delete[] visited;
}


////////////////////
////// ����
////////////////////
// ��ͼg�еĸ���������ȣ�����inArr
template<class VertexType>
void FindInDegree( ALGraph<VertexType>& g, int inArr[])
{
    int i,v;
    for (i = 0; i < g.GetNumVertices(); i++)
        inArr[i] = 0;
    for (i = 0; i < g.GetNumVertices(); i++){
        v = g.GetFirstAdjVex(i);
        
        while(v != -1){
            inArr[v]++;
            v = g.GetNextAdjVex(i,v);            
        }
    }
}
// ��������
// ����ͼg�����ڽӱ�洢�ṹ
// ������ͼg���޻�·���˺���ͨ��topoArr����һ��������ŵ��������У�������true������false
// toppArr������˴���
// count�������࣬�Ƿ�Ӧ��ȥ����ֱ����i�᲻����ⲻ�㣿
template<class VertexType>
bool TopologicalSort( ALGraph<VertexType>& g, int* topoArr)//, int* ve)
{
    queue<int> q;            // ��Ŷ�Ϊ0�Ķ�������
    int count = 0;
    int i;
    int w;
    int* inDegree = new int[g.GetNumVertices()];        // ��Ŷ�������
    
    FindInDegree(g, inDegree);                          // �������ж�������
    for( i = 0; i < g.GetNumVertices(); i++)            // ���Ϊ0�Ķ��������
        if (inDegree[i] == 0)
            q.push(i);
    i = 0;
    while ( !q.empty()){
        topoArr[i++] = q.front();
        for (w = g.GetFirstAdjVex(q.front()); w != -1; w = g.GetNextAdjVex(q.front(),w)){
            if (--inDegree[w] == 0)
                q.push(w);
        }
        q.pop();
        count++;
    }
    delete[] inDegree;
    return count == g.GetNumVertices();
}
// ��ӡ������g�Ĺؼ�·��
template<class VertexType>
void PrintCriticalPath( ALGraph<VertexType>& g)
{
    int i, j;
    VertexType vex, start, end;
    int w;
    edgeNode* edge;
    int *ve;
    int *vl;
    int *pArr = new int[g.GetNumVertices()];
    if ( !TopologicalSort(g, pArr)){
        std::cout << "Graph has a circle!" << endl;
        delete[] pArr;
        return;
    }
    ve = new int[g.GetNumVertices()];
    vl = new int[g.GetNumVertices()];
    for (i = 0; i < g.GetNumVertices(); i++)
        ve[i] = 0;
    for (i = 0; i < g.GetNumVertices(); i++){
        for (w = g.GetFirstAdjVex(pArr[i]); w != -1; w = g.GetNextAdjVex(pArr[i], w)){
            g.Getedge(pArr[i], w, edge);
			//����VC6.0����ʹ��max
            ve[w] = (ve[w]>  ve[pArr[i]] + edge->weight) ? ve[w] : ve[pArr[i]] + edge->weight;
        }
    }
    for ( i = 0; i < g.GetNumVertices(); i++)
        vl[i] = ve[g.GetNumVertices() - 1];
    for (i = g.GetNumVertices() - 1; i >= 0; i--){
        for (w = g.GetFirstAdjVex(pArr[i]);w != -1; w = g.GetNextAdjVex(pArr[i], w)){
            g.Getedge(pArr[i], w, edge);
			//����VC6.0����ʹ��min
            vl[pArr[i]] = (vl[pArr[i]]<=vl[w] - edge->weight)?vl[pArr[i]]:vl[w] - edge->weight;
        }
    }
    cout << "|  ���  |  �յ�  |   ���翪ʼʱ��   |   ������ʱ��   |  ��ֵ  |  ��ע  |" << endl;
    for ( i = 0; i < g.GetNumVertices(); i++){
        for (w = g.GetFirstAdjVex(i); w != -1; w = g.GetNextAdjVex(i, w)){
            g.Getedge(i, w, edge);
            g.GetVertex(i, start);
            g.GetVertex(w, end);
            cout << setiosflags(ios::right)
                 << setw(6) << start 
                 << setw(9) << end 
                 << setw(14) << ve[i] 
                 << setw(19) << vl[w] 
                 << setw(14) << edge->weight 
                 << setw(12) << (ve[i] == vl[w] - edge->weight?"�ؼ�·��":"")<< endl;
        }
    }
    delete[] ve;
    delete[] vl;
    delete[] pArr;
}


/*
��ȡһ���ؼ�·�������ݵ����������˳�򣬴��������ʱ������ֵ
��ʼһֱ��0������·�����ܲ�ֹһ������������ֻ��һ����
1.������������·�������еĽ��(��map,�Ժ�һ��Ϊ����ǰһ���ļ�
��Ϊֵ��ֻ��Ϊ�˲���)
2.��ȡ��������
3.�㷨��ͼ��ʾ��
����ͼ����AOV���磬������ͼ��AOV��ת����AOE���索��
*/


template<class VertexType>
void SaveCriticalPath( ALGraph<VertexType>& g, std::vector<int> &save, int &totaldelay)
{
	std::multimap<int, std::pair<int,int>> temp_map;
	int i;
    VertexType  start, end;
    int w;
    edgeNode* edge;
    int *ve;
    int *vl;
	int maxvl = 0, maxv=0, x=0;
    int *pArr = new int[g.GetNumVertices()];
    if ( !TopologicalSort(g, pArr)){
        std::cout << "Graph has a circle!" << endl;
        delete[] pArr;
        return;
    }
    ve = new int[g.GetNumVertices()];
    vl = new int[g.GetNumVertices()];
    for (i = 0; i < g.GetNumVertices(); i++)
        ve[i] = 0;
    for (i = 0; i < g.GetNumVertices(); i++){
        for (w = g.GetFirstAdjVex(pArr[i]); w != -1; w = g.GetNextAdjVex(pArr[i], w)){
            g.Getedge(pArr[i], w, edge);
            ve[w] = (ve[w]>  ve[pArr[i]] + edge->weight) ? ve[w] : ve[pArr[i]] + edge->weight;
        }
    }
    for ( i = 0; i < g.GetNumVertices(); i++)
        vl[i] = ve[g.GetNumVertices() - 1];
    for (i = g.GetNumVertices() - 1; i >= 0; i--){
        for (w = g.GetFirstAdjVex(pArr[i]);w != -1; w = g.GetNextAdjVex(pArr[i], w)){
            g.Getedge(pArr[i], w, edge);
            vl[pArr[i]] = (vl[pArr[i]]<=vl[w] - edge->weight)?vl[pArr[i]]:vl[w] - edge->weight;
        }
    }
    cout << "|  ���  |  �յ�  |   ���翪ʼʱ��   |   ������ʱ��   |  ��ֵ  |  ��ע  |" << endl;
    for ( i = 0; i < g.GetNumVertices(); i++){
        for (w = g.GetFirstAdjVex(i); w != -1; w = g.GetNextAdjVex(i, w)){
            g.Getedge(i, w, edge);
            g.GetVertex(i, start);
            g.GetVertex(w, end);
			if(ve[i] == vl[w] - edge->weight){
				 if(maxvl <= vl[w])
				 {
					 maxvl = vl[w];
					 maxv = w; 
				 }
				temp_map.insert(std::pair<int, std::pair<int,int> >(w, std::pair<int,int>(i, edge->weight)));	  
			}
            cout << setiosflags(std::ios::right)
                 << setw(6) << start 
                 << setw(9) << end 
                 << setw(14) << ve[i] 
                 << setw(19) << vl[w] 
                 << setw(14) << edge->weight 
                 << setw(12) << (ve[i] == vl[w] - edge->weight?"�ؼ�·��":"")<< endl;
        }
    }
	x = maxv;
	while(vl[x]!=0){ //�ҵ���ʼ��λ�ý���
		if((temp_map.lower_bound(x) -> second).second != 0)//key�ĵ�һ��ƥ��Ԫ��
			save.insert(save.begin(),(temp_map.lower_bound(x) -> second).second); //���weigth��Ϊ0����Ϊ��Ч·��������
		//��ͷ�����룬��deque���ã�˫�˶��У�
		x = (temp_map.lower_bound(x) -> second).first; //��ǰ����
	}
	totaldelay = maxvl;
    delete[] ve;
    delete[] vl;
    delete[] pArr;
}



#endif