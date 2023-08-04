
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
    int val = l1->val + l2->val;
    int digit = val % 10;
    int carry = static_cast<int>(val > 9);
    ListNode* head = new ListNode(digit);
    ListNode* tail = head;

    l1 = l1->next;
    l2 = l2->next;

    while (l1 && l2)
    {
        val = l1->val + l2->val + carry;
        digit = val % 10;
        carry = static_cast<int>(val > 9);
        tail->next = new ListNode(digit);
        tail = tail->next;
        l1 = l1->next;
        l2 = l2->next;
    }

    while (l1)
    {
        val = l1->val + carry;
        digit = val % 10;
        carry = static_cast<int>(val > 9);
        tail->next = new ListNode(digit);
        tail = tail->next;
        l1 = l1->next;
    }

    while (l2)
    {
        val = l2->val + carry;
        digit = val % 10;
        carry = static_cast<int>(val > 9);
        tail->next = new ListNode(digit);
        tail = tail->next;
        l2 = l2->next;
    }

    if (carry)
    {
        tail->next = new ListNode(1);
    }

    return head;
}

int main()
{
}