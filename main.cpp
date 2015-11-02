/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    const char VALID_NODE = 0;
    const char NULL_NODE = 1;
    
    // Encodes a tree to a single string.
    
    string itoc(int val, int k){
        int tmp = val;
        string str = "";
        int endp = 0;
        bool flag = false;
        if(tmp < 0) {
            tmp = -tmp;
            endp = 1;
            flag = true;
        }
        for(int i = 0; i < k - endp; i ++){
            int foo = tmp % 256 - 128;
            str = string(1, char(foo)) + str;
            tmp /= 256;
        }
        if(flag) str = string(1,127) + str;
        return str;
    }
    
    int ctoi(string str){
        int tmp = 0, ptr = 0;
        int sign = 1;
        if(str[0] == 127){
            sign = -1;
            ptr ++;
        }
        while(ptr < str.length()){
            tmp *= 256;
            tmp += (char)str[ptr++] + 128;
        }//end while
        return tmp * sign;
    }
    
    int serial_push(string *str, TreeNode* root){
        int left_count = 0, right_count = 0;
        if(root == NULL) return 0;
        *str = *str + itoc(root -> val, 4);
        int ptr = (*str).length();
        *str = *str + string(8,0);
        left_count = serial_push(str, root -> left);
        right_count = serial_push(str, root -> right);
        string lft_str = itoc(left_count, 4);
        string rgt_str = itoc(right_count, 4);
        (*str)[ptr] = lft_str[0];
        (*str)[ptr+1] = lft_str[1];
        (*str)[ptr+2] = lft_str[2];
        (*str)[ptr+3] = lft_str[3];
        (*str)[ptr+4] = rgt_str[0];
        (*str)[ptr+5] = rgt_str[1];
        (*str)[ptr+6] = rgt_str[2];
        (*str)[ptr+7] = rgt_str[3];
        return (left_count + right_count + 1);
    }
    
    void deserial_build(string str, TreeNode* root){
        root -> val = ctoi(str.substr(0,4));
        int leftct = ctoi(str.substr(4,4));
        int rightct = ctoi(str.substr(8,4));
       // root -> val += leftct + rightct;
        if(leftct != 0){
            root -> left = new TreeNode(0);
            deserial_build(str.substr(12, 12 * leftct), root -> left);
        }
        if(rightct != 0){
            root -> right = new TreeNode(0);
            deserial_build(str.substr(12 + 12 * leftct, 12 * rightct), root -> right);
        }
    }
    
    string serialize(TreeNode* root) {
        if(root == NULL) return "";
        string mystr = "";
        int tmp = serial_push(&mystr, root);
        return mystr;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        TreeNode *root = new TreeNode(0);
        //if(data.length() != 0) return root;
        if(data.length() == 0) return NULL;
        deserial_build(data, root);
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
