#include <link.h>
//생성
s_node  *create_node(int data)
{
    s_node *New_Node = (s_node *)malloc(sizeof(s_node));

    New_Node->data = data;
    New_Node->next = NULL;
    New_Node->prev = NULL;

    return (New_Node);
}

//추가(리스트 끝 추가)
void    append_node(s_node **Head, s_node *newnode)
{
    if ((*Head) == NULL)
    {
        *Head = newnode;
    }
    else
    {
        s_node *Tail = (*Head);
        while (Tail->next != NULL)
        {
            Tail = Tail->next;
        }
        Tail->next = newnode;
        newnode->prev = Tail;
    }
}

s_node    *double_lst_point_last(s_node **head)
{
    s_node *Tail = (*head);
    while (Tail->next != NULL)
    {
        Tail = Tail->next;
    }
    return (head);
}

//노드 중간 삽입
void    insert_node(s_node *current, s_node *newnode)//현재 삽입하려는 곳의 위치, 새로운 노드
{
    newnode->next = current->next;
    newnode->prev = current;

    if (current->next != NULL)//current노드 다음에 노드가 존재
    {
        current->next->prev = newnode;
        //current의 다음 노드에는 원래 currnet가 들었있지만, 새로운 노드를 가리키게 한다.(중간에 삽입시키기 위해)
        
    }
    current->next = newnode;//current는 새로 들어온 노드를 넣으면 된다.
}


//노드 삭제(head or middle or tail 전부 적용되게 만들자)
void    delete_node(s_node **head, s_node *delete)//연결리스트의 head를 가리키는 포인터, 삭제하려는 노드
{
    if (*head == delete)//연결리스트의 첫번째 노드를 삭제 하려는 경우(리스트에 head노드 밖에 없는경우)
    {
        *head = delete->next;//삭제하려는 노드의 다음 노드로 헤드포인터를 옮겨!!!
        if ((*head) != NULL)
        //삭제하려는 노드의 다음 노드가 있으면
            (*head)->prev=NULL;//삭제하려는 노드 다음노가 삭제하려는 노드를 가리키는 prev를 먼저 null처리
        delete->prev = NULL;
        delete->next = NULL;//전부 null처리하면 삭제 완료
                            //헤드만 있다고 해도 결국 head == delete이기 때문에 null로 함으로 삭제
    }
    else//리스트가 존재할 경우
    {
        s_node *empty = delete;//삭제할 노드를 가리킬 노드 포인터
        delete->prev->next = empty->next;
        //삭제 하려는 노드 전 노드를 삭제노드 다음노드를 가리키도록 한다.
        
        if (delete->next != NULL)//중간 노드인 경우
            delete->next->prev = empty->prev;//삭제하려는 노드의 전 노드에 연결
        delete->prev = NULL;
        delete->next = NULL;
    }
}

void    double_list_lstclear(s_node **lst, void (*del)(void*))
{
    s_node  *tmp;
    
    while(*str)
    {
        tmp
    }
}
