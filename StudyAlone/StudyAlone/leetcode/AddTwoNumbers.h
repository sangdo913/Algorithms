#define NULL 0

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0, sum;
        ListNode head(0);
        ListNode *tail = &head;
        while(l1 && l2){
            sum = (l1->val +l2->val + carry);
            carry = (sum)/10;
            sum = sum%10;
            tail->next = new ListNode(sum);
            tail = tail->next;
            
            l1 = l1->next;
            l2 = l2->next;
        }
        while(l1){
            sum = carry + l1->val;
            carry = sum/10;
            sum %=10;
            tail->next = new ListNode(sum);
            tail = tail->next;
            l1 = l1->next;
        }
        while(l2){
            sum = carry + l2->val;
            carry = sum/10;
            sum %=10;
            tail = tail->next = new ListNode(sum);
            
            l2 = l2->next;
        }
        if(carry){
            tail = tail->next = new ListNode(carry);
        }
        
        return head.next;
    }
};