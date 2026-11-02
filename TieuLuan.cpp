#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct SinhVien
{
    char name[50];
    char lop[50];
    char MaSV[10];
    float GPA;
}sv;
typedef enum ThaoTac
{
    them,
    xoa,
    sua
}ThaoTac;
typedef struct node
{
    sv a;
    struct node *next;
}node;
typedef struct stack
{
    ThaoTac thaotac;
    sv a;
    int vitri;
    struct stack *next;
}stack;
typedef struct nodetree
{
    sv a;
    struct nodetree *left;
    struct nodetree *right;
}nodetree;
node *MakeNode(sv a)
{
    node *NewNode=(node *)malloc(sizeof(node));
    NewNode->a=a;
    NewNode->next = NULL;
    return NewNode;
}
stack *MakeStack(sv a, ThaoTac thaotac)
{
    stack *NewStack=(stack *)malloc(sizeof(stack));
    NewStack->a=a;
    NewStack->thaotac=thaotac;
    NewStack->vitri=0;
    NewStack->next=NULL;
    return NewStack;
}
nodetree *MakeNodeTree(sv a)
{
    nodetree *NewNode=(nodetree*)malloc(sizeof(nodetree));
    NewNode->a=a;
    NewNode->left=NewNode->right=NULL;
    return NewNode;
}
node *TimNode(node *head, char ma[])
{
    while(head!=NULL)
    {
        if(strcmp(head->a.MaSV, ma)==0) return head;
        head=head->next;
    }
    return NULL;
}
nodetree *TimTrongCay(nodetree *root, char ma[])
{
    if(root==NULL) return NULL;
    int c=strcmp(ma, root->a.MaSV);
    if(c==0) return root;
    if(c<0) return TimTrongCay(root->left, ma);
    return TimTrongCay(root->right, ma);
}
void ThemVaoDauStack(stack **head, sv a, ThaoTac thaotac, int vitri)
{
    stack *NewStack=MakeStack(a, thaotac);
    NewStack->vitri=vitri;
    NewStack->next=*head;
    *head=NewStack;
}
void XoaKhoiCay(nodetree **root, char ma[])
{
    if(*root==NULL) return;
    int c=strcmp(ma, (*root)->a.MaSV);
    if(c<0)
    {
        XoaKhoiCay(&(*root)->left, ma);
    }
    else if(c>0)
    {
        XoaKhoiCay(&(*root)->right, ma);
    }
    else
    {
        nodetree *temp=*root;
        if(temp->left==NULL)           
        {
            *root=temp->right;
            free(temp);
        }
        else if(temp->right==NULL)      
        {
            *root=temp->left;
            free(temp);
        }
        else                          
        {
            nodetree *min=temp->right;
            while(min->left!=NULL) min=min->left;
            temp->a=min->a;                          
            XoaKhoiCay(&temp->right, temp->a.MaSV);  
        }
    }
}
void InSinhVien(node *head)
{
    if(head==NULL)
    {
        printf("trong danh sach khong co sinh vien nao ca\n");
        return;
    }
    printf("%-30s%-15s%-20s%-6s\n", "Ho Ten", "MSSV", "Lop", "GPA");
    printf("------------------------------------------------------------------------\n");
    while(head!=NULL)
    {
        printf("%-30s%-15s%-20s%-6.2f\n", head->a.name, head->a.MaSV, head->a.lop, head->a.GPA);
        head=head->next;
    }
}
int SoLuongSinhVien(node *head)
{
    int dem=0;
    while(head!=NULL)
    {
        dem++;
        head=head->next;
    }
    return dem;
}
void ThemVaoDau(node **head, sv a)
{
    node *NewNode=MakeNode(a);
    NewNode->next=*head;
    *head=NewNode;  
}
void ThemVaoSau(node **head, sv a)
{
    node *temp=*head;
    node *NewNode=MakeNode(a);
    if(*head==NULL)
    {
        *head=NewNode;
        return ;
    }
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    temp->next = NewNode;
}
void ThemVaoViTri(node **head, sv a, int k)
{
    int n = SoLuongSinhVien(*head);
    if(k==1)
    {
        ThemVaoDau(head, a);
        return;
    }
    if(k==n+1)
    {
        ThemVaoSau(head, a);
        return;
    }
    node *temp=*head;
    for(int i=1;i<=k-2;i++)
    {
        temp=temp->next;
    }
    node *NewNode=MakeNode(a);
    NewNode->next=temp->next;
    temp->next=NewNode;
}
void ThemVaoCay(nodetree **head, sv b)
{
    if(*head!=NULL)
    {
        if(strcmp(b.MaSV, (*head)->a.MaSV)==0)
        {
            printf("ma sinh vien da ton tai");
            return;
        }
        else
        {
            if(strcmp(b.MaSV, (*head)->a.MaSV)<0)
            {
                ThemVaoCay(&(*head)->left, b);
            }
            else
            {
                ThemVaoCay(&(*head)->right, b);
            }
        }   
    }
    else
    {
        nodetree *NewNode=MakeNodeTree(b);
        *head=NewNode;  
    }
}
void NhapSinhVien(int n,node **head, int LanNhap, nodetree **root, stack **head2)
{
    sv a;
    for(int i=1;i<=n;i++)
    {
        int xoa1;
        do
        {
            printf("nhap ten sinh vien thu %d: ", i);
            fgets(a.name, sizeof(a.name), stdin);
            xoa1=(strchr(a.name, '\n')==NULL);
            if(xoa1)
            {
                int xa1;
                while((xa1=getchar())!='\n'&&xa1!=EOF);
            }
            a.name[strcspn(a.name, "\n")] = '\0';
            if(xoa1||strlen(a.name)==0)
            {
                printf("vui long nhap lai ten\n");
            }
        }while(xoa1||strlen(a.name)==0);
        int xoa2, trung;
        do
        {
            trung=0;
            printf("nhap ma sinh vien: ");
            fgets(a.MaSV, sizeof(a.MaSV), stdin);
            xoa2=(strchr(a.MaSV, '\n')==NULL);
            if(xoa2)
            {
                int xa2;
                while((xa2=getchar())!='\n'&&xa2!=EOF);
            }
            a.MaSV[strcspn(a.MaSV, "\n")] = '\0';
            if(xoa2||strlen(a.MaSV)==0)
            {
                printf("vui long nhap lai ma sinh vien\n");
                continue;
            }
            node *temp=*head;
            while(temp!=NULL)
            {
                if(strcmp(temp->a.MaSV, a.MaSV)==0)
                {
                    trung=1;
                    printf("ma sinh vien da bi trung, vui long nhap lai ma sinh vien\n");
                    break;
                }
                temp=temp->next;
            }
        }while(xoa2||strlen(a.MaSV)==0||trung);
        int xoa3;
        do
        {
            printf("nhap lop: ");
            fgets(a.lop, sizeof(a.lop), stdin);
            xoa3=(strchr(a.lop, '\n')==NULL);
            if(xoa3)
            {
                int xa3;
                while((xa3=getchar())!='\n'&&xa3!=EOF);
            }
            a.lop[strcspn(a.lop, "\n")] = '\0';
            if(xoa3||strlen(a.lop)==0)
            {
                printf("vui long nhap lai lop\n");
            }
        }while(xoa3||strlen(a.lop)==0);
        do
        {
            printf("nhap diem GPA: ");
            scanf("%f", &a.GPA);
            if(a.GPA<0||a.GPA>4)
            {
                printf("vui long nhap lai diem GPA\n");
            }
        }while(a.GPA<0||a.GPA>4);
        getchar();
        int m=SoLuongSinhVien(*head);
        if(!LanNhap)
        {
            ThemVaoSau(head, a);
        }
        else
        {
            int k;
            do
            {
                printf("Nhap vi tri can chen vao danh sach: ");
                scanf("%d", &k);
                getchar();
                if(k<1||k>m+1)
                {
                    printf("vui long nhap lai vi tri can chen\n");
                }
            }while(k<1||k>m+1);
            ThemVaoViTri(head, a, k);
        }
        ThemVaoCay(root, a);
        ThemVaoDauStack(head2, a, them, 0);
    }
}
void XoaNode(node **head, node *i)
{
    node *temp=*head;
    if(*head==NULL||i==NULL)
    {
        return;
    }
    if(temp==i)
    {
        *head=temp->next;
        free(temp);
        return;
    }
    while(temp->next!=i&&temp->next!=NULL)
    {
        temp=temp->next;
    }
    if(temp->next==NULL)
    {
        return;
    }
    node *xoa=temp->next;
    temp->next=temp->next->next;
    free(xoa);
}
void xoatheoma(node **head, nodetree **root, stack **top, char ma[])
{
    node *temp=*head;
    int vt=1;
    while(temp!=NULL&&strcmp(temp->a.MaSV, ma)!=0)
    {
        temp=temp->next;
        vt++;
    }
    if(temp==NULL)
    {
        printf("khong tim thay sinh vien\n");
        return;
    }
    sv a=temp->a;                   
    XoaNode(head, temp);
    XoaKhoiCay(root, a.MaSV);
    ThemVaoDauStack(top, a, xoa, vt);
}
void xoatheoten(node **head, nodetree **root, stack **top, char ten[])
{
    node *temp=*head;
    int vt=1, dem=0;
    while(temp!=NULL)
    {
        node *tiep=temp->next;      
        if(strcmp(temp->a.name, ten)==0)
        {
            sv a=temp->a;
            XoaNode(head, temp);
            XoaKhoiCay(root, a.MaSV);
            ThemVaoDauStack(top, a, xoa, vt);  
            dem++;
        }
        else
        {
            vt++;
        }
        temp=tiep;
    }
    if(dem==0) printf("khong tim thay sinh vien\n");
}
void DongBoCay(nodetree *root, sv a)    
{
    nodetree *q=TimTrongCay(root, a.MaSV);
    if(q!=NULL)
    {
        q->a=a;
    }
}
void sapxeptheodiemtang(node *head)
{
    for(node *i=head;i!=NULL;i=i->next)
    {
        for(node *j=i->next;j!=NULL;j=j->next)
        {
            if(i->a.GPA>j->a.GPA)
            {
                sv temp=i->a;
                i->a=j->a;
                j->a=temp;
            }
        }
    }
}
void sapxeptheodiemgiam(node *head)
{
    for(node *i=head;i!=NULL;i=i->next)
    {
        for(node *j=i->next;j!=NULL;j=j->next)
        {
            if(i->a.GPA<j->a.GPA)
            {
                sv temp=i->a;
                i->a=j->a;
                j->a=temp;
            }
        }
    }
}
void sapxeptheoten(node *head)
{
    for(node *i=head;i!=NULL;i=i->next)
    {
        for(node *j=i->next;j!=NULL;j=j->next)
        {
            if(strcmp(i->a.name, j->a.name) >0)
            {
                sv temp=i->a;
                i->a=j->a;
                j->a=temp;
            }
        }
    }
}
void sapxeptheolop(node *head)
{
    for(node *i=head;i!=NULL;i=i->next)
    {
        for(node *j=i->next;j!=NULL;j=j->next)
        {
            if(strcmp(i->a.lop, j->a.lop) >0)
            {
                sv temp=i->a;
                i->a=j->a;
                j->a=temp;
            }
        }
    }
}
void sapxeptheomatang(node *head)
{
    for(node *i=head;i!=NULL;i=i->next)
    {
        for(node *j=i->next;j!=NULL;j=j->next)
        {
            if(strcmp(i->a.MaSV, j->a.MaSV) >0)
            {
                sv temp=i->a;
                i->a=j->a;
                j->a=temp;
            }
        }
    }
}
void sapxeptheomagiam(node *head)
{
    for(node *i=head;i!=NULL;i=i->next)
    {
        for(node *j=i->next;j!=NULL;j=j->next)
        {
            if(strcmp(i->a.MaSV, j->a.MaSV) <0)
            {
                sv temp=i->a;
                i->a=j->a;
                j->a=temp;
            }
        }
    }
}
void timkiemtheodiem(node *head, float diem)
{
    while(head!=NULL)
    {
        if(head->a.GPA==diem)
        {
            printf("%-30s%-15s%-20s%-6.2f\n", head->a.name, head->a.MaSV, head->a.lop, head->a.GPA);
        }
        head=head->next;
    }
}
void timkiemtheoten(node *head, char ten[])
{
    while(head!=NULL)
    {
        if(strcmp(head->a.name, ten)==0)
        {
            printf("%-30s%-15s%-20s%-6.2f\n", head->a.name, head->a.MaSV, head->a.lop, head->a.GPA);
        }
        head=head->next;
    }
}
void timkiemtheolop(node *head, char lop[])
{
    while(head!=NULL)
    {
        if(strcmp(head->a.lop, lop)==0)
        {
            printf("%-30s%-15s%-20s%-6.2f\n", head->a.name, head->a.MaSV, head->a.lop, head->a.GPA);
        }
        head=head->next;
    }
}
void timkiemtheomasinhvien(node *head, char masv[])
{
    while(head!=NULL)
    {
        if(strcmp(head->a.MaSV, masv)==0)
        {
            printf("%-30s%-15s%-20s%-6.2f\n", head->a.name, head->a.MaSV, head->a.lop, head->a.GPA);
        }
        head=head->next;
    }
}
void GhiRaFile(node *head,  int n)
{
    char ten[50];
    printf("Nhap ten file can ghi ra: ");
    fgets(ten, sizeof(ten), stdin);
    ten[strcspn(ten, "\n")] = '\0';
    FILE *f;
    f=fopen(ten, "w");
    if(f==NULL)
    {
        printf("Loi mo file\n");
        return;
    }
    for(node *i=head;i!=NULL;i=i->next)
    {
        fprintf(f, "Ho Ten: %s\n", i->a.name);
        fprintf(f, "MSSV: %s\n", i->a.MaSV);
        fprintf(f, "Lop: %s\n", i->a.lop);
        fprintf(f, "Diem GPA: %.2f\n\n", i->a.GPA);
    }
    fclose(f);
}
void DocTuFile(node **head, nodetree **root)
{
    char ten[50];
    printf("nhap ten file can doc: ");
    fgets(ten, sizeof(ten), stdin);
    ten[strcspn(ten, "\n")] = '\0';
    FILE *f;
    f=fopen(ten, "r");
    if(f==NULL)
    {
        printf("Loi mo file\n");
        return;
    }
    char dong[1000];
    while (fgets(dong, sizeof(dong), f) != NULL)
    {
        if(dong[0] == '\n') 
        {
            continue;
        }
        node *i=(node*)malloc(sizeof(node));
        sscanf(dong, "Ho Ten: %[^\n]", i->a.name);
        fgets(dong, sizeof(dong), f);
        sscanf(dong, "MSSV: %[^\n]", i->a.MaSV);
        fgets(dong, sizeof(dong), f);
        sscanf(dong, "Lop: %[^\n]", i->a.lop);
        fgets(dong, sizeof(dong), f);
        sscanf(dong, "Diem GPA: %f", &i->a.GPA);
        i->next=NULL;
        if(*head==NULL)
        {
            *head=i;
        }
        else
        {
            node *temp=*head;
            while(temp->next!=NULL)
            {
                temp=temp->next;
            }
            temp->next=i;
        }
        ThemVaoCay(root, i->a);
    }
    fclose(f);
}
void capnhatdiem(node *head, nodetree *root, stack **top, char ma[], float diem)
{
    node *p=TimNode(head, ma);
    if(p==NULL)
    {
        printf("khong tim thay sinh vien\n");
        return;
    }
    ThemVaoDauStack(top, p->a, sua, 0);        
    p->a.GPA=diem;
    DongBoCay(root, p->a);
}
void capnhatten(node *head, nodetree *root, stack **top, char ma[], char ten[])
{
    node *p=TimNode(head, ma);
    if(p==NULL)
    {
        printf("khong tim thay sinh vien\n");
        return;
    }
    ThemVaoDauStack(top, p->a, sua, 0);
    snprintf(p->a.name, sizeof(p->a.name), "%s", ten);
    DongBoCay(root, p->a);
}
void capnhatlop(node *head, nodetree *root, stack **top, char ma[], char lop[])
{
    node *p=TimNode(head, ma);
    if(p==NULL)
    {
        printf("khong tim thay sinh vien\n");
        return;
    }
    ThemVaoDauStack(top, p->a, sua, 0);
    snprintf(p->a.lop, sizeof(p->a.lop), "%s", lop);
    DongBoCay(root, p->a);
}
void XoaStack(stack **head)
{
    if(*head==NULL)
    {
        return;
    }
    stack *temp=*head;
    *head=temp->next;
    free(temp);
}
bool rong(stack *head)
{
    return head==NULL;
}
void undo(node **head, stack **head2, nodetree **root)
{
    if(rong(*head2))
    {
        printf("khong con thao tac de undo");
        return;
    }
    sv a=(*head2)->a;
    ThaoTac thaotac=(*head2)->thaotac;
    int vitri=(*head2)->vitri;
    XoaStack(head2);
    if(thaotac==them)                     
    {
        node *p=TimNode(*head, a.MaSV);
        if(p!=NULL) XoaNode(head, p);
        XoaKhoiCay(root, a.MaSV);
        printf("da xoa sinh vien co ma so %s (hoan tac thao tac them)\n", a.MaSV);
    }
    else if(thaotac==xoa)                 
    {
        int n=SoLuongSinhVien(*head);
        if(vitri<1||vitri>n+1) vitri=n+1;
        ThemVaoViTri(head, a, vitri);
        ThemVaoCay(root, a);
        printf("da them lai sinh vien co ma so %s (hoan tac thao tac xoa)\n", a.MaSV);
    }
    else if(thaotac==sua)                 
    {
        node *p=TimNode(*head, a.MaSV);
        if(p!=NULL) p->a=a;
        DongBoCay(*root, a);
        printf("da khoi phuc sinh vien co ma so %s ve du lieu cu (hoan tac thao tac sua)\n", a.MaSV);
    }
}
void XoaDau(node **head)
{
    if(*head==NULL)
    {
        return;
    }
    node *temp=*head;
    *head=temp->next;
    free(temp);
}
void XoaCuoi(node **head)
{
    node *temp=*head;
    if(*head==NULL)
    {
        return;
    }
    if(temp->next==NULL)
    {
        *head=NULL;
        free(temp);
        return;
    }
    while(temp->next->next!=NULL)
    {
        temp=temp->next;
    }
    node *NodeCuoi=temp->next;
    temp->next=NULL;
    free(NodeCuoi);
}
void XoaGiua(node **head, int m)
{
    int n=SoLuongSinhVien(*head);
    if(m<1||m>n)
    {
        return;
    }
    if(m==1)
    {
        XoaDau(head);
        return;
    }
    if(m==n)
    {
        XoaCuoi(head);
        return;
    }
    node *temp=*head;
    for(int i=1;i<=m-2;i++)
    {
        temp=temp->next;
    }
    node *xoa=temp->next;
    temp->next=temp->next->next;
    free(xoa);
}
void timkiemtheomasinhviennhiphan(nodetree *head, char masv[])
{
    if(head==NULL)
    {
        printf("khong tim thay sinh vien co ma nhu tren\n");
        return;
    }
    if(strcmp(masv, head->a.MaSV)==0)
    {
        printf("%-30s%-15s%-20s%-6.2f\n", head->a.name, head->a.MaSV, head->a.lop, head->a.GPA);
    }
    else if(strcmp(masv, head->a.MaSV)<0)
    {
        timkiemtheomasinhviennhiphan(head->left, masv);
    }
    else
    {
        timkiemtheomasinhviennhiphan(head->right, masv);
    }
}
float diemTrungBinhGPA(node *head)
{
    float dem=0;
    float tong=0;
    while(head!=NULL)
    {
        dem++;
        tong+=head->a.GPA;
        head=head->next;
    }
    return (tong/dem);
}
typedef struct YeuCau
{
    ThaoTac loai;           
    sv a;                   
    struct YeuCau *next;
}YeuCau;
typedef struct Queue
{
    YeuCau *front;          
    YeuCau *rear;           
}Queue;
void KhoiTaoQueue(Queue *q)
{
    q->front=q->rear=NULL;
}
void enqueue(Queue *q, ThaoTac loai, sv a)
{
    YeuCau *y=(YeuCau*)malloc(sizeof(YeuCau));
    y->loai=loai;
    y->a=a;
    y->next=NULL;
    if(q->rear==NULL)
    {
        q->front=q->rear=y;
    }
    else
    {
        q->rear->next=y;
        q->rear=y;
    }
}
void dequeue(Queue *q)      
{
    if(q->front==NULL) return;
    YeuCau *temp=q->front;
    q->front=temp->next;
    if(q->front==NULL)
    {
        q->rear=NULL;       
    }
    free(temp);
}
int XuLyMotYeuCau(Queue *q, node **head, nodetree **root, stack **top)
{
    if(q->front==NULL)
    {
        printf("khong co yeu cau nao dang cho\n");
        return 0;
    }
    ThaoTac loai=q->front->loai;   
    sv a=q->front->a;
    dequeue(q);                     
 
    if(loai==them)
    {
        if(TimNode(*head, a.MaSV)!=NULL)    
        {
            printf("Tu choi yeu cau them sinh vien co ma %s: ma da ton tai\n", a.MaSV);
            return 1;
        }
        ThemVaoSau(head, a);
        ThemVaoCay(root, a);
        ThemVaoDauStack(top, a, them, 0);
        printf("Da xu ly: them sinh vien co ma %s\n", a.MaSV);
    }
    else if(loai==xoa)
    {
        xoatheoma(head, root, top, a.MaSV);   
        printf("Da xu ly: xoa sinh vien co ma %s\n", a.MaSV);
    }
    else if(loai==sua)
    {
        node *p=TimNode(*head, a.MaSV);
        if(p==NULL)
        {
            printf("Tu choi yeu cau cap nhat sinh vien co ma %s: khong tim thay\n", a.MaSV);
            return 1;
        }
        ThemVaoDauStack(top, p->a, sua, 0);                
        snprintf(p->a.name, sizeof(p->a.name), "%s", a.name);
        snprintf(p->a.lop, sizeof(p->a.lop), "%s", a.lop);
        p->a.GPA=a.GPA;
        DongBoCay(*root, p->a);
        printf("Da xu ly: cap nhat sinh vien co ma %s\n", a.MaSV);
    }
    return 1;
}
void XuLyTatCa(Queue *q, node **head, nodetree **root, stack **top)
{
    while(XuLyMotYeuCau(q, head, root, top));
}
void GiaiPhongQueue(Queue *q)
{
    while(q->front!=NULL) dequeue(q);
}
void GiaiPhongDS(node **head)
{
    while(*head!=NULL)
    {
        node *t=*head;
        *head=t->next;
        free(t);
    }
}
void GiaiPhongCay(nodetree **root)
{
    if(*root==NULL) return;
    GiaiPhongCay(&(*root)->left);
    GiaiPhongCay(&(*root)->right);
    free(*root);
    *root=NULL;
}
void GiaiPhongStack(stack **top)
{
    while(*top!=NULL) XoaStack(top);
}
void docChuoi(const char *loinhac, char *out, int size)
{
    printf("%s", loinhac);
    fgets(out, size, stdin);
    if(strchr(out, '\n')==NULL)             
    {
        int c;
        while((c=getchar())!='\n'&&c!=EOF);
    }
    out[strcspn(out, "\n")]='\0';
}
void GuiYeuCau(Queue *q)
{
    int l;
    printf("loai yeu cau (1.them  2.xoa  3.sua): ");
    if(scanf("%d", &l)!=1) l=0;
    while(getchar()!='\n');
    if(l<1||l>3)
    {
        printf("loai yeu cau khong hop le\n");
        return;
    }
    sv a;
    memset(&a, 0, sizeof(a));
    docChuoi("nhap ma sinh vien: ", a.MaSV, sizeof(a.MaSV));
    if(strlen(a.MaSV)==0)
    {
        printf("ma khong duoc rong\n");
        return;
    }
    if(l==1||l==3)
    {
        docChuoi("nhap ten: ", a.name, sizeof(a.name));
        docChuoi("nhap lop: ", a.lop, sizeof(a.lop));
        printf("nhap GPA: ");
        if(scanf("%f", &a.GPA)!=1) a.GPA=-1;
        while(getchar()!='\n');
        if(a.GPA<0||a.GPA>4)
        {
            printf("GPA khong hop le, huy yeu cau\n");
            return;
        }
    }
    enqueue(q, l==1?them:(l==2?xoa:sua), a);
    printf("da xep yeu cau vao hang doi\n");
}
int main()
{
    int n;
    int chon;
    node *head=NULL;
    nodetree *tree=NULL;
    stack *head2=NULL;
    Queue q;
    KhoiTaoQueue(&q);
    do
    {
        printf("-------------------------------");
        printf("\n1/nhap danh sach sinh vien");
        printf("\n2/them sinh vien moi");
        printf("\n3/hien thi danh sach sinh vien");
        printf("\n4/tim kiem sinh vien");
        printf("\n5/xoa sinh vien");
        printf("\n6/cap nhat thong tin");
        printf("\n7/sap xep sinh vien");
        printf("\n8/doc/ghi file text");
        printf("\n9/undo");
        printf("\n10/tim kiem sinh vien nhanh");
        printf("\n11/thong ke du lieu");
        printf("\n12/gui yeu cau vao hang doi");
        printf("\n13/xu ly tat ca yeu cau");
        printf("\n0/thoat chuong trinh");
        printf("\n-------------------------------\n");
        printf("nhap so tu 1->11 de thuc hien chuc nang: ");
        scanf("%d", &chon);
        switch(chon)
        {
            case 1:
                do
                {
                    printf("nhap so sinh vien can them vao danh sach: ");
                    scanf("%d", &n); 
                    if(n==0) return 0;
                    if(n<0)
                    {
                        printf("vui long nhap lai so sinh vien\n");
                    }
                }while(n<=0);
                getchar();
                NhapSinhVien(n, &head, 0, &tree, &head2);
                break;
            case 2:
                int k;    
                do
                {
                    printf("nhap so sinh vien can bo sung vao danh sach: ");
                    scanf("%d", &k);  
                    if(k<0)
                    {
                        printf("vui long nhap lai so sinh vien\n");
                    }
                }while(k<0);
                getchar();
                NhapSinhVien(k, &head, 1, &tree, &head2);
                break;
            case 3:  
                InSinhVien(head);
                break;
            case 4:
                int chon2;
                do
                {
                    printf("-------------------------------");
                    printf("\n1/tim kiem sinh vien theo ten");
                    printf("\n2/tim kiem sinh vien theo ma");
                    printf("\n3/tim kiem sinh vien theo lop");
                    printf("\n4/tim kiem sinh vien theo GPA");
                    printf("\n0/thoat chuc nang");
                    printf("\n-------------------------------");
                    printf("\nnhap lua chon chuc nang tim kiem: ");
                    scanf("%d", &chon2);
                    getchar();
                    switch(chon2)
                    {
                        case 1:
                            char name[50];
                            printf("nhap ten sinh vien can tim kiem: ");
                            fgets(name, sizeof(name), stdin);
                            name[strcspn(name, "\n")] = '\0';
                            timkiemtheoten(head, name);
                            break;
                        case 2:
                            char ma[10];
                            printf("nhap ma so sinh vien cua sinh vien can tim kiem: ");
                            fgets(ma, sizeof(ma), stdin);
                            ma[strcspn(ma, "\n")] = '\0';
                            timkiemtheomasinhvien(head, ma);
                            break;
                        case 3:
                            char lop[50];
                            printf("nhap lop cua sinh vien can tim kiem: ");
                            fgets(lop, sizeof(lop), stdin);
                            lop[strcspn(lop, "\n")] = '\0';
                            timkiemtheolop(head, lop);
                            break;
                        case 4:
                            float gpa;
                            printf("nhap GPA cua sinh vien can tim kiem: ");
                            scanf("%f", &gpa);
                            timkiemtheodiem(head, gpa);
                            break;
                    }
                }while(chon2!=0);
                break;
            case 5:
                int xoa;
                do
                {
                    printf("-------------------------------");
                    printf("\n1/xoa sinh vien theo ten");
                    printf("\n2/xoa sinh vien theo ma");
                    printf("\n0/thoat chuc nang");
                    printf("\n-------------------------------");
                    printf("\nnhap lua chon chuc nang xoa: ");
                    scanf("%d", &xoa);
                    getchar();
                    switch(xoa)
                    {
                        case 1:
                            char name2[50];
                            printf("nhap ten sinh vien can xoa: ");
                            fgets(name2, sizeof(name2), stdin);
                            name2[strcspn(name2, "\n")] = '\0';
                            xoatheoten(&head, &tree, &head2, name2);
                            break;
                        case 2:
                            char ma2[10];
                            printf("nhap ma so sinh vien cua sinh vien can xoa: ");
                            fgets(ma2, sizeof(ma2), stdin);
                            ma2[strcspn(ma2, "\n")] = '\0';
                            xoatheoma(&head, &tree, &head2, ma2);
                            break;
                    }
                }while(xoa!=0);
                break;
            case 6:
                int chon5;
                do
                {
                    printf("-------------------------------");
                    printf("\n1/cap nhat ten sinh vien");
                    printf("\n2/cap nhat lop sinh vien");
                    printf("\n3/cap nhat diem GPA sinh vien");
                    printf("\n0/thoat chuc nang");
                    printf("\n-------------------------------");
                    printf("\nnhap lua chon chuc nang cap nhat: ");
                    scanf("%d", &chon5);
                    getchar();
                    switch(chon5)
                    {
                        case 1:
                            char macn1[10];
                            char tencn[50];
                            printf("nhap ma sinh vien can cap nhat: ");
                            fgets(macn1, sizeof(macn1), stdin);
                            macn1[strcspn(macn1, "\n")] = '\0';
                            printf("nhap ten moi cua sinh vien: ");
                            fgets(tencn, sizeof(tencn), stdin);
                            tencn[strcspn(tencn, "\n")] = '\0';
                            capnhatten(head, tree, &head2, macn1, tencn);
                            break;
                        case 2:
                            char macn2[10];
                            char lopcn[50];
                            printf("nhap ma sinh vien can cap nhat: ");
                            fgets(macn2, sizeof(macn2), stdin);
                            macn2[strcspn(macn2, "\n")] = '\0';
                            printf("nhap lop moi cua sinh vien: ");
                            fgets(lopcn, sizeof(lopcn), stdin);
                            lopcn[strcspn(lopcn, "\n")] = '\0';
                            capnhatlop(head, tree, &head2, macn2, lopcn);
                            break;
                        case 3:
                            char macn3[10];
                            float diemcn;
                            printf("nhap ma sinh vien can cap nhat: ");
                            fgets(macn3, sizeof(macn3), stdin);
                            macn3[strcspn(macn3, "\n")] = '\0';
                            printf("nhap diem GPA moi cua sinh vien: ");
                            scanf("%f", &diemcn);
                            capnhatdiem(head, tree, &head2, macn3, diemcn);
                            break;
                    }
                }while(chon5!=0);
                break;
            case 7:
                int chon3;
                do
                {
                    printf("-------------------------------");
                    printf("\n1/sap xep sinh vien theo ten");
                    printf("\n2/sap xep sinh vien theo ma tang");
                    printf("\n3/sap xep sinh vien theo ma giam");
                    printf("\n4/sap xep sinh vien theo lop");
                    printf("\n5/sap xep sinh vien theo diem tang");
                    printf("\n6/sap xep sinh vien theo diem giam");
                    printf("\n0/thoat chuc nang");
                    printf("\n-------------------------------");
                    printf("\nnhap lua chon chuc nang tim kiem: ");
                    scanf("%d", &chon3);
                    getchar();
                    switch(chon3)
                    {
                        case 1:
                            sapxeptheoten(head);
                            break;
                        case 2:
                            sapxeptheomatang(head);
                            break;
                        case 3:
                            sapxeptheomagiam(head);
                            break;
                        case 4:
                            sapxeptheolop(head);
                            break;
                        case 5:
                            sapxeptheodiemtang(head);
                            break;
                        case 6:
                            sapxeptheodiemgiam(head);
                            break;
                    }
                }while(chon3!=0);
                break;
            case 8:
                int chon4;
                do
                {
                    printf("-------------------------------");
                    printf("\n1/ghi du lieu ra file");
                    printf("\n2/doc du lieu tu file");
                    printf("\n0/thoat chuc nang");
                    printf("\n-------------------------------");
                    printf("\nnhap lua chon chuc nang tu file: ");
                    scanf("%d", &chon4);
                    getchar();
                    switch(chon4)
                    {
                        case 1:
                            GhiRaFile(head, n);
                            break;
                        case 2:
                            DocTuFile(&head, &tree);
                            break;
                    }
                }while(chon4!=0);
                break;
            case 9:
                undo(&head, &head2, &tree);
                break;
            case 10:
                int chon6;
                do
                {
                    printf("-------------------------------");
                    printf("\n1/tim kiem sinh vien theo ma");
                    printf("\n0/thoat chuc nang");
                    printf("\n-------------------------------");
                    printf("\nnhap lua chon chuc nang tim kiem: ");
                    scanf("%d", &chon6);
                    getchar();
                    switch(chon6)
                    {
                        case 1:
                            char ma4[10];
                            printf("nhap ma so sinh vien cua sinh vien can tim kiem: ");
                            fgets(ma4, sizeof(ma4), stdin);
                            ma4[strcspn(ma4, "\n")] = '\0';
                            timkiemtheomasinhviennhiphan(tree, ma4);
                            break;
                    }
                }while(chon6!=0);
                break;
            case 11:
                int chon7;
                do
                {
                    printf("-------------------------------");
                    printf("\n1/tong so sinh vien trong danh sach");
                    printf("\n2/diem trung binh GPA");
                    printf("\n0/thoat chuc nang");
                    printf("\n-------------------------------");
                    printf("\nnhap lua chon chuc nang thong ke: ");
                    scanf("%d", &chon7);
                    getchar();
                    switch(chon7)
                    {
                        case 1:
                            printf("so sinh vien trong danh sach la %d\n", SoLuongSinhVien(head));
                            break;
                        case 2:
                            printf("diem trung binh GPA la %.2f\n", diemTrungBinhGPA(head));
                            break;
                    }
                }while(chon7!=0);
                break;
            case 12:
                GuiYeuCau(&q);
                break;
            case 13:
                XuLyTatCa(&q, &head, &tree, &head2);
                break;
        }
    }while(chon!=0);
    GiaiPhongDS(&head);
    GiaiPhongCay(&tree);
    GiaiPhongStack(&head2);
    GiaiPhongQueue(&q);
    return 0;
}