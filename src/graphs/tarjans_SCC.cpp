vector<vector<int> > SCCs /* The components itself*/;
#define comps SCCs
vector<int> compIndex /* for each node, what is the index of the
component this node inside*/
,ind, lowLink;
stack<int> st;
vector<bool> inst;
vector<vector<int> > adj /*The intial graph*/;  /// Resize it with n+1 in main
int idx = 0; //must be intialized by zero;

void tarjanSCC(int i) {
    lowLink[i] = ind[i] = idx++;
    st.push(i);
    inst[i] = true;
    for (int j = 0; j < adj[i].size(); j++) {
        int k = adj[i][j];
        if (ind[k] == -1) {
            tarjanSCC(k);
            lowLink[i] = min(lowLink[i], lowLink[k]);
        } else if (inst[k]) {
            lowLink[i] = min(lowLink[i], lowLink[k]);
        }
    }
    if (lowLink[i] == ind[i]) {
        vector<int> comp;
        int n = -1;
        while (n != i) {
            n = st.top();
            st.pop();
            comp.push_back(n);
            inst[n] = 0;
            compIndex[n] = comps.size();
        }
        comps.push_back(comp);
    }
}

void SCC() {
    comps.clear();
    compIndex.resize(adj.size());
    ind.clear();
    ind.resize(adj.size(), -1);
    lowLink.resize(adj.size());
    inst.resize(adj.size());
    idx = 0; //must be intialized by zero;
    for (int i = 0; i < adj.size(); i++)
        if (ind[i] == -1)
            tarjanSCC(i);
}

int cntSrc /*the number of source components*/,
cntSnk /*the number of sink components*/;
vector<vector<int> > cmpAdj /*The new graph between components*/;
vector<int> inDeg, outDeg /*the in degree and out degree for each
component*/;
void computeNewGraph() {
    outDeg.clear();
    outDeg.resize(comps.size());
    inDeg.clear();
    inDeg.resize(comps.size());
    cntSrc = cntSnk = comps.size();
    cmpAdj.clear();
    cmpAdj.resize(comps.size());
    for (int i = 0; i < adj.size(); i++) {
    for (int j = 0; j < adj[i].size(); j++) {
            int k = adj[i][j];
            if (compIndex[k] != compIndex[i]) {
                cmpAdj[compIndex[i]].push_back(compIndex[k]);
                if (!(inDeg[compIndex[k]]++))
                    cntSrc--;
                if (!(outDeg[compIndex[i]]++))
                    cntSnk--;
            }
    }
    }
}
