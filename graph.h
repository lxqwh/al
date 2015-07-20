/*
C++ ͼ���ڽӱ�ʵ���࣬�����˶���޸ģ��Ѿ��൱�����ˡ����ߣ��򽡡������޸���¼��2009��8��2�� ��ʼ�汾����LinkList�ඨ���ڽӱ�2009��8��10�� 1. ȡ��LinkList���ʹ�ã�ֱ��ʵ���ڽӱ���ALGraph��������LocateVertex��GetVertex��SetVertex����
2009��12��24�գ��򾲣���
1. ��ALGraph��������BFSTraverse����
2009��12��25��
1. ����MGraph��
2. ����MiniSpanTree��
2009��12��27��
1. ��ALGraph��������GetNumVertices��GetFirstAdjVex��GetNextAdjVex��Getedge����
2010��1��20��
1. Edge��Ϊedge,edge��Ϊedge
2. �����������⣬���������������ļ�
3. ���·��,�ؼ�·��,��С�������Ⱥ�����ֱ�Ӵ�ӡ
4. ����ָ�붼��Ϊp
5. �򵥵�getXXXX������Ϊinline
6. ����DFS��Ϊprivate
*/


#ifndef _GRAPH_T_H_
#define _GRAPH_T_H_
#include <iomanip>
#include <queue>
// ���嶥���ڽӱ�Ľڵ�ṹ
class edgeNode
{
public:
    edgeNode(int = -1, int = 0);       // ���캯��
    int adjVertex;                    // �ñ��е��ڽӶ����ڶ�����е����
    int weight;                       // �ñߵ�Ȩֵ
    edgeNode *next;
};
// ���캯��
// ����aΪ�ڽӶ������ţ�����wΪ�ߵ�Ȩֵ��Ĭ��ȨֵΪ0
edgeNode::edgeNode(int a, int w) : adjVertex(a), weight(w), next(NULL)
{
}
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
    std::queue<int> vertexQueue;    // ��������
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
///////////////////////////
////  ��С������
///////////////////////////
// ���ظ��������У���0��СԪ�ص��±�ֵ
int Minimum(int arr[], int n)
{
    int i;
    int min = 0;
    for(i = 1; i < n; i++){
        if(arr[i] > 0){
            min = i;
            break;
        }
    }
    for(i = min; i < n; i++){
        if( arr[i] > 0 && arr[i] < arr[min])
            min = i;
    }
    return min;
}
// Prim�㷨
// �ӵ�0���������,���㲢��ӡ��g����С������
template <class VertexType>
void Prim( ALGraph<VertexType>& g)
{
    if (g.GetNumVertices() == 0){
        cout << "ͼ���޶���!" << endl;
        return;
    }
    int i, j, k = 0;
    VertexType vex;
    edgeNode *edge = NULL;
    int *lowcost = new int[g.GetNumVertices()];
    VertexType *U = new VertexType[g.GetNumVertices()];
    for (i = 0; i < g.GetNumVertices(); i++){
        lowcost[i] = INT_MAX;
    }
    for (i = 0; i < g.GetNumVertices(); i++){
        if (i != k && g.Getedge(k, i, edge)){
            lowcost[i] = edge->weight;
            g.GetVertex(k, U[i]);
        }
    }
    g.GetVertex(k, U[k]);
    lowcost[k] = 0;
    for ( i = 1; i < g.GetNumVertices(); i++){
        k = Minimum( lowcost, g.GetNumVertices());
        g.GetVertex(k,vex);
        cout << U[k] << " --> " << vex << " : " << lowcost[k] << endl;
        lowcost[k] = 0;
        for (j = 0; j < g.GetNumVertices(); j++){
            if ( g.Getedge(k, j, edge) && edge->weight < lowcost[j]){
                lowcost[j] = edge->weight;
                g.GetVertex(k, U[j]);
            }
        }
    }    
    delete[] lowcost;
    delete[] U;
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
    VertexType vex;
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
        cout << "Graph has a circle!" << endl;
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

///////////////////////////
//// ���·��
///////////////////////////
struct TableEntry
{
    bool    known;
    int     dist;        // ����
    int     preVertex;   // ǰ���ڵ�
};
// ����table��knownΪfalse��dist��С��Ԫ�ص�λ��
// n��table���鳤��
int SmallestUnknownDistIndex(TableEntry table[], int n)
{
    int min = INT_MAX;
    int i;
    int index = -1;
    for(i = 0; i < n; i++){
        if(table[i].known)
            continue;
        if(table[i].dist < min){
            min = table[i].dist;
            index = i;
        }
    }
    return index;
}
// ��Dijkstra�㷨������ͼg�Ķ���vex�����ඥ������·��������TableEntry��������
template <class VertexType>
TableEntry* ShortestPath_DIJ(ALGraph<VertexType>& g, VertexType vex)
{
    int i, v, w;
    int start = g.LocateVertex(vex);
    edgeNode* edge;
    TableEntry* table = new TableEntry[g.GetNumVertices()];
    //init table
    for (i = 0; i < g.GetNumVertices(); i++){
        table[i].known = false;
        table[i].dist = INT_MAX;
        table[i].preVertex = -1;
    }
    table[start].dist = 0;
    while (true){
        v = SmallestUnknownDistIndex(table, g.GetNumVertices());
        if (v == -1)
            break;
        table[v].known = true;
        for(w = g.GetFirstAdjVex(v); w != -1; w = g.GetNextAdjVex(v,w)){
            if(!table[w].known){
                g.Getedge(v, w, edge);
                if(table[v].dist + edge->weight < table[w].dist){
                    table[w].dist = table[v].dist + edge->weight;
                    table[w].preVertex = v;
                }
            }
        }
    }
    return table;
}
// ��ӡtable����㵽����end�����·��
template <class VertexType>
void PrintPath(ALGraph<VertexType>& g, VertexType end, TableEntry table[])
{
    int v = g.LocateVertex(end);
    VertexType vex;
    if(table[v].preVertex != -1)
    {
        g.GetVertex(table[v].preVertex, vex);
        PrintPath(g, vex, table);
        cout << " ---> ";
    }
    cout << end;
}
#endif