#define MAX_CHAR 256

struct SuffixTreeNode {
    struct SuffixTreeNode *children[MAX_CHAR];
    struct SuffixTreeNode *suffixLink;

    lo start;
    lo *end;
    lo suffixIndex;
};

typedef struct SuffixTreeNode Node;

char text[100];
Node *root = NULL;
Node *lastNewNode = NULL;
Node *activeNode = NULL;
lo activeEdge = -1;
lo activeLength = 0;
lo remainingSuffixCount = 0;
lo leafEnd = -1;
lo *rootEnd = NULL;
lo *splitEnd = NULL;
lo size = -1;

Node *newNode(lo start, lo *end)
{
    Node *node =(Node*) malloc(sizeof(Node));
    REP(0,MAX_CHAR)node->children[i] = NULL;
    node->suffixLink = root;
    node->start = start;
    node->end = end;
    node->suffixIndex = -1;
    return node;
}

lo edgeLength(Node *n) {
    return *(n->end) - (n->start) + 1;
}

lo walkDown(Node *currNode)
{
    if (activeLength >= edgeLength(currNode))
    {
        activeEdge += edgeLength(currNode);
        activeLength -= edgeLength(currNode);
        activeNode = currNode;
        return 1;
    }
    return 0;
}

void extendSuffixTree(lo pos)
{
    leafEnd = pos;
    remainingSuffixCount++;
    lastNewNode = NULL;
    while(remainingSuffixCount > 0) {
        if (activeLength == 0)
            activeEdge = pos;
        if (activeNode->children[text[activeEdge]] == NULL)
        {
            activeNode->children[text[activeEdge]] = newNode(pos, &leafEnd);
            if (lastNewNode != NULL)
            {
                lastNewNode->suffixLink = activeNode;
                lastNewNode = NULL;
            }
        }
        else
        {
            Node *next = activeNode->children[text[activeEdge]];
            if (walkDown(next))continue;
            if (text[next->start + activeLength] == text[pos])
            {
                if(lastNewNode != NULL && activeNode != root)
                {
                    lastNewNode->suffixLink = activeNode;
                    lastNewNode = NULL;
                }
                activeLength++;
                break;
            }
            splitEnd = (int*) malloc(sizeof(int));
            *splitEnd = next->start + activeLength - 1;
            Node *split = newNode(next->start, splitEnd);
            activeNode->children[text[activeEdge]] = split;
            split->children[text[pos]] = newNode(pos, &leafEnd);
            next->start += activeLength;
            split->children[text[next->start]] = next;
            if (lastNewNode != NULL)lastNewNode->suffixLink = split;
            lastNewNode = split;
        }
        remainingSuffixCount--;
        if (activeNode == root && activeLength > 0)
        {
            activeLength--;
            activeEdge = pos - remainingSuffixCount + 1;
        }
        else if (activeNode != root)
        {
            activeNode = activeNode->suffixLink;
        }
    }
}

void print(lo k, lo j)
{
    lo k;
    REP(k,j+1)printf("%c", text[i]);
}

void setSuffixIndexByDFS(Node *n, lo labelHeight)
{
    if (n == NULL)  return;
    if (n->start != -1){
    //label on edge from parent to current node
            print(n->start, *(n->end));
    }
    lo leaf = 1;
    lo i;
    REP(0,MAX_CHAR)
    {
        if (n->children[i] != NULL)
        {
            if (leaf == 1 && n->start != -1)printf(" [%d]\n", n->suffixIndex);
            //current node is not leaf as it has outgoing edges
            leaf = 0;
            setSuffixIndexByDFS(n->children[i], labelHeight + edgeLength(n->children[i]));
        }
    }
    if (leaf == 1)
    {
        n->suffixIndex = size - labelHeight;
        printf(" [%d]\n", n->suffixIndex);
    }
}

void freeSuffixTreeByPostOrder(Node *n)
{
    if (n == NULL) return;
    lo i;
    REP(0,MAX_CHAR)
    {
        if (n->children[i] != NULL)freeSuffixTreeByPostOrder(n->children[i]);
    }
    if (n->suffixIndex == -1)free(n->end);
    free(n);
}

void buildSuffixTree()
{
    size = strlen(text);
    lo i;
    rootEnd = (lo*) malloc(sizeof(lo));
    *rootEnd = - 1;
    root = newNode(-1, rootEnd);
    activeNode = root;
    REP(0,size) extendSuffixTree(i);
    lo labelHeight = 0;
    setSuffixIndexByDFS(root, labelHeight);
    //free dynamically allocated memory
    freeSuffixTreeByPostOrder(root);
}

int main()
{
    cin>>text;
    buildSuffixTree();
    return 0;
}

/* original source code : http://www.geeksforgeeks.org/ukkonens-suffix-tree-construction-part-6/ */
