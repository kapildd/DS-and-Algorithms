//
// Created by kapildd on 8/10/17.
//

#include <iostream>
#include <map>
using namespace std;

struct PatriciaTreeNode{
    string text;
    map<char, PatriciaTreeNode*> next;
    PatriciaTreeNode(){ text = "";}
    PatriciaTreeNode(string s) : text(s) {}
};

class PatriciaTree{
    PatriciaTreeNode* root;
public:
    PatriciaTree(){
        root = new PatriciaTreeNode();
    }
    void insert(string s) {
        int start_s = 0;
        char next_char = 0;
        for(PatriciaTreeNode* tmp = root; tmp!=NULL; tmp = tmp->next[next_char]) {
            string curr = s.substr(start_s);
            int k=0;
            while(k<curr.size() && k<tmp->text.size() && curr[k]==tmp->text[k]) k++;
            if(k==curr.size()) {//Alraedy present
                break;
            }else if(k==tmp->text.size()) {//Match occurred, we need to move ahead
                if(tmp->next.size()==0) {//Leaf node, just append the additional data
                    tmp->text = curr;
                    break;
                }
                start_s += k;
                next_char = s[start_s];
            }else{//Mismatch, create two nodes, do the needful by splitting the current text
                string replace_curr = curr.substr(0, k);
                PatriciaTreeNode* node1 = new PatriciaTreeNode(curr.substr(k));
                PatriciaTreeNode* node2 = new PatriciaTreeNode(tmp->text.substr(k));
                node2->next = tmp->next;
                tmp->next.clear();
                tmp->next[curr[k]] = node1;
                tmp->next[tmp->text[k]] = node2;
                tmp->text = replace_curr;
                break;
            }
        }
    }
    bool query(string s) {
        int start_s = 0;
        char next_char = 0;
        for(PatriciaTreeNode* tmp = root; tmp!=NULL; tmp = tmp->next[next_char]) {
            string curr = s.substr(start_s, min(s.size()-start_s, tmp->text.size()));
            if(curr.size() < tmp->text.size())
                curr += tmp->text.substr(curr.size());

            if(curr == tmp->text) {
                start_s += tmp->text.size();
                if(start_s == s.size()) break;
                next_char = s[start_s];
            }else {
                return false;
            }
        }
        return start_s >= s.size();
    }
};

int main() {
    PatriciaTree p;
    p.insert("Hello");
    cout << p.query("Hello") << endl;
    cout << p.query("Hell") << endl;
    cout << p.query("Helloo") << endl;
    cout << p.query("Help") << endl;
    return 0;
}