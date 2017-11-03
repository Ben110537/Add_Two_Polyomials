#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
typedef struct Node *PtrToNode;
struct Node {
        int Coefficient;
        int Exponent;
        PtrToNode Next;
};
typedef PtrToNode Polynomial;

Polynomial Read(); /* details omitted */
void Print( Polynomial p ); /* details omitted */
Polynomial Add( Polynomial a, Polynomial b );

int main()
{
        Polynomial a, b, s;
        a = Read();
        b = Read();
        s = Add(a, b);
        Print(s);
        return 0;
}

Polynomial Read()
{
        Polynomial head, tail;
        Polynomial no, ne, tem;
        int co, ex, i=1;
        int size=sizeof(struct Node);

        /*第一项输入*/
        head=0;
        printf("Input the Exponent:\n");
        scanf("%d",&ex);
        printf("Input the Coefficient:\n" );
        scanf("%d",&co );

        no=(struct Node*)malloc(size);
        ne=(struct Node*)malloc(size);
        no->Coefficient=co;
        no->Exponent=ex;
        no->Next=ne;
        head=no;
        tail=no;

        /*第二项输入*/
        while(i) {
                if(ex!=0) {
                        printf("Input the Exponent:\n" );
                        scanf("%d",&ex );
                        printf("Input the Coefficient:\n" );
                        scanf("%d",&co );
                        no=ne;
                        ne=(struct Node*)malloc(size);

                        if(head->Exponent<ex) {
                                i=0;
                                no->Exponent=ex;
                                no->Coefficient=co;
                                no->Next=ne;
                                tail=no;
                        }
                        else if(head->Exponent>ex) {
                                i=0;
                                no->Exponent=ex;
                                no->Coefficient=co;
                                no->Next=head;
                                head->Next=ne;
                                tail=head;
                                head=no;
                        }
                        else{
                                head->Coefficient=head->Coefficient+co;

                        }
                }
                else break;
        }

        /*第n项输入*/
        while (ex!=0) {
                printf("Input the Exponent:\n" );
                scanf("%d",&ex );
                printf("Input the Coefficient:\n" );
                scanf("%d",&co );
                no=ne;
                ne=(struct Node*)malloc(size);

                no->Exponent=ex;
                no->Coefficient=co;

                if(head->Exponent>ex) {
                        no->Next=head;
                        head=no;
                }
                else if(tail->Exponent<ex) {
                        tail->Next=no;
                        tail=no;
                }
                else{
                        tem=head;
                        while (1) {
                                if (tem->Exponent<=ex&&tem->Next->Exponent>ex) {
                                        break;
                                }
                                else if(tem->Next->Exponent<ex) {
                                        tem=tem->Next;
                                }
                        }

                        if(tem->Exponent==ex) {
                                tem->Coefficient=tem->Coefficient+co;
                        }
                        else if(tem->Exponent<ex) {
                                no->Next=tem->Next;
                                tem->Next=no;
                        }
                }

        }
        tail->Next=0;
        return head;
}

void Print( Polynomial p )
{
        while(p->Next!=0) {
                if(p->Exponent==0) {
                        printf("%d + ",p->Coefficient);
                        p=p->Next;
                }
                else {
                        printf(" %dx^%d +",p->Coefficient, p->Exponent);
                        p=p->Next;
                }
        }
        if(p->Exponent==0) {
                printf("%d \n",p->Coefficient);
        }
        else {
                printf(" %dx^%d \n",p->Coefficient, p->Exponent);
        }

}

Polynomial Add( Polynomial a, Polynomial b )
{
        Polynomial head, no, ne, tail;
        int size=sizeof(Polynomial), i=1;
        no=(struct Node*)malloc(size);
        head=no;
        while (1) {
                ne=(struct Node*)malloc(size);
                if(a==0&&b!=0) {
                        no->Exponent=b->Exponent;
                        no->Coefficient=b->Coefficient;
                        no->Next=b->Next;
                        b=0;
                        free(ne);
                        break;
                }
                else if(a!=0&&b==0) {
                        no->Exponent=a->Exponent;
                        no->Coefficient=a->Coefficient;
                        no->Next=a->Next;
                        a=0;
                        free(ne);
                        break;
                }

                else if(a!=0&&b!=0) {
                        no->Next=ne;
                        if(a->Exponent<b->Exponent) {
                                no->Exponent=a->Exponent;
                                no->Coefficient=a->Coefficient;
                                tail=no;
                                no=no->Next;
                                a=a->Next;
                        }
                        else if(a->Exponent>b->Exponent) {
                                no->Exponent=b->Exponent;
                                no->Coefficient=b->Coefficient;
                                tail=no;
                                no=no->Next;
                                b=b->Next;
                        }
                        else if(a->Exponent==b->Exponent) {
                                no->Exponent=a->Exponent;
                                no->Coefficient=a->Coefficient+b->Coefficient;
                                if(no->Coefficient!=0) {
                                        tail=no;
                                        no=no->Next;
                                        a=a->Next;
                                        b=b->Next;
                                }
                                else {
                                        a=a->Next;
                                        b=b->Next;
                                }
                        }
                }
                else {
                        i=0;
                        break;
                }
        }
        if(i==0) tail->Next=0;
        return head;
}
