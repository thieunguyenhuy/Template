int le[N], ri[N], par[N];

stack<int> st;
for (int i = 0; i < n; ++i) {
    int last = -1;
    while (!st.empty() && a[st.top()] > a[i])
        last = st.top(), st.pop();
    if (!st.empty()) ri[st.top()] = i, par[i] = st.top();
    else par[i] = i;
    if (last != -1) le[i] = last, par[last] = i;
    st.emplace(i);
}