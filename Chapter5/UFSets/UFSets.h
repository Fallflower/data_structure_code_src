#ifndef __UFSETS_H__
#define __UFSETS_H__

#define SIZE 100

class UFSets
{
private:
    int parent[SIZE];
public:
    UFSets() {
        for (int i = 0; i < SIZE; i++)
        {
            parent[i] = -1;
        }
        
    }

    int Find(const int& x) {
        int p = x;
        while (parent[p] >= 0)
        {
            p = parent[p];
        }
        // 压缩路径
        int q = x;
        while (q != p)
        {
            int t = parent[q];
            parent[q] = p;
            q = t; // 继续遍历
        }
        return p;
    }

    bool Union(const int& a, const int& b) {
        if (a<0||b<0||a>=SIZE||b>=SIZE) return false;
        int r1 = Find(a); 
        int r2 = Find(b);
        if (r1 == r2) return true;
        if (parent[r1] < parent[r2]) {
            parent[r1] += parent[r2];
            parent[r2] = r1;
        }
        else {
            parent[r2] += parent[r1];
            parent[r1] = r2;
        }
        return true;
    }
};

#endif