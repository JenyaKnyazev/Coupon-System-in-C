#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int id;
    char *name;
    char *email;
    char *password;
    struct Company *next;

}Company;

typedef struct{
    int id;
    char *first_name;
    char *last_name;
    char *email;
    char *password;
    struct Customer *next;
}Customer;

typedef struct{
    int id;
    char *name;
    struct Category *next;
}Category;

typedef struct{
    int day;
    int month;
    int year;
}Date;

typedef struct{
    int id;
    int company_id;
    int category_id;
    char *title;
    char *description;
    Date start_date;
    Date end_date;
    int amount;
    double price;
    char *image;
    struct Coupon *next;
}Coupon;

typedef struct{
    int customer_id;
    int coupon_id;
    struct Customers_vs_coupons *next;
}Customers_vs_coupons;

Company *head_companies=NULL;
Customer *head_costumers=NULL;
Category *head_categories=NULL;
Coupon *head_coupons=NULL;
Customers_vs_coupons *head_customers_vs_coupons=NULL;
void print_date(Date d){
    printf("%d.%d.%d",d.day,d.month,d.year);
}
int equals(char *a,char *b){
    while(*a!='\0'&&*a==*b){
        a++;
        b++;
    }
    if(*a==*b)
        return 1;
    return 0;
}

void scan_string(char **p){
    char ch;
    int length=0;
    *p=NULL;
    do{
        ch=getchar();
        *p=(char *)realloc(*p,++length*sizeof(char));
        *((*p)+length-1)=ch;
    }while(ch!='\n');
    *((*p)+length-1)='\0';
}
void clean_buff(){
    while(getchar()!='\n');
}
Customers_vs_coupons *create_cus_vs_cp(int coupon_id,int customer_id){
    Customers_vs_coupons *p =(Customers_vs_coupons*)malloc(sizeof(Customers_vs_coupons));
    p->coupon_id=coupon_id;
    p->customer_id=customer_id;
    p->next=NULL;
    return p;
}

void add_cus_vs_cp(int coupon_id,int customer_id){
    Customers_vs_coupons *p=create_cus_vs_cp(coupon_id,customer_id);
    Customers_vs_coupons *in=head_customers_vs_coupons;
    if(head_customers_vs_coupons==NULL){
        head_customers_vs_coupons=p;
        return;
    }
    while(in->next!=NULL)
        in=in->next;
    in->next=p;
}
void delete_cus_vs_cp_by_coupon_id(int coupon_id){
    Customers_vs_coupons *in,*prev,*temp=NULL;
    in=prev=head_customers_vs_coupons;
    if(head_customers_vs_coupons==NULL)
        return;
    while(in!=NULL){
        if(in->coupon_id==coupon_id){
            prev->next=in->next;
            temp=in;
        }else
            prev=in;
        in=in->next;
        free(temp);
    }
    if(head_customers_vs_coupons->coupon_id==coupon_id){
        temp=head_customers_vs_coupons;
        head_customers_vs_coupons=head_customers_vs_coupons->next;
        free(temp);
    }
}
void delete_cus_vs_cp_by_customer_id(int customer_id){
    Customers_vs_coupons *in,*prev,*temp=NULL;
    in=prev=head_customers_vs_coupons;
    if(head_customers_vs_coupons==NULL)
        return;
    while(in!=NULL){
        if(in->customer_id==customer_id){
            prev->next=in->next;
            temp=in;
        }else
            prev=in;
        in=in->next;
        free(temp);
    }
    if(head_customers_vs_coupons->customer_id==customer_id){
        temp=head_customers_vs_coupons;
        head_customers_vs_coupons=head_customers_vs_coupons->next;
        free(temp);
    }
}
void add_customer(Customer *p){
    Customer *in=head_costumers;
    int id=1;
    if(head_costumers==NULL){
            p->id=1;
        head_costumers=p;
        return;
    }
    while(in->next!=NULL){
        in=in->next;
        id++;
    }
    p->id=id+1;
    in->next=p;
}
void delete_customer(int customer_id){
    Customer *in,*prev,*temp=NULL;
    in=prev=head_costumers;
    if(head_costumers==NULL)
        return;
    delete_cus_vs_cp_by_customer_id(customer_id);
    while(in!=NULL){
        if(in->id==customer_id){
            prev->next=in->next;
            temp=in;
        }else
            prev=in;
        in=in->next;
        free(temp);
    }
    if(head_costumers->id==customer_id){
        temp=head_costumers;
        head_costumers=head_costumers->next;
        free(temp);
    }
}
int get_customer_id(char *email,char *password){
    Customer *in=head_costumers;
    while(in!=NULL){
        if( equals(in->email,email)&&equals(in->password,password))
            return in->id;
        in=in->next;
    }
    return 0;
}
int check_if_coupon_purchased(int customer_id){
    Customers_vs_coupons *p=head_customers_vs_coupons;
    while(p!=NULL){
        if(p->customer_id==customer_id)
            return 1;
    }
    return 0;
}
void buy_coupon(int coupon_id,int customer_id){
    Coupon *p=head_coupons;
    if(check_if_coupon_purchased(customer_id))
        printf("Coupon limited to one for costumer");
    else{
        while(p!=NULL&&p->id!=coupon_id)
            p=p->next;
        if(p==NULL)
            printf("Coupon not exist\n");
        else{
            p->amount--;
            add_cus_vs_cp(coupon_id,customer_id);
        }
    }
}
Category *create_category(char *name){
    Category *p=(Category*)malloc(sizeof(Category));
    p->name=name;
    p->next=NULL;
    return p;
}
void add_category(char *name){
    Category *p=create_category(name);
    Category *in=head_categories;
    int id=1;
    if(head_categories==NULL){
        p->id=1;
        head_categories=p;
        return;
    }
    while(in->next!=NULL){
        in=in->next;
        id++;
    }
    p->id=id+1;
    in->next=p;
}
void generate_categories(){
    add_category("Food");
    add_category("Electricity");
    add_category("Restaurant");
    add_category("Vacation");
}
void print_categories(){
    Category *p=head_categories;
    while(p!=NULL){
        printf("Category id: %d name: %s\n",p->id,p->name);
        p=p->next;
    }
}
int check_if_company_exist(Company *p){
    Company *in=head_companies;
    while(in!=NULL){
        if(equals(in->name,p->name)||equals(in->email,p->email))
            return 1;
        in=in->next;
    }
    return 0;
}

void add_company(Company *p){
    if(head_companies==NULL){
        p->id=1;
        head_companies=p;
        return;
    }
    if(check_if_company_exist(p)){
        printf("Company with that name or email already exist");
        return;
    }
    Company *current=head_companies;
    while(current->next!=NULL)
        current=current->next;
    p->id=current->id+1;
    current->next=p;
}

int get_company_id(char *email,char *password){
    Company *p=head_companies;
    while(p!=NULL){
        if(equals(p->email,email)&&equals(p->password,password))
            return p->id;
        p=p->next;
    }
    return 0;
}
void add_coupon(Coupon *p){
    if(head_coupons==NULL){
        p->id=1;
        head_coupons=p;
        return;
    }
    Coupon *in=head_coupons;
    while(in->next!=NULL)
        in=in->next;
    p->id=in->id+1;
    in->next=p;
}
void update_coupons_id(){
    int id=1;
    Coupon *p=head_coupons;
    while(p!=NULL){
        p->id=id;
        id++;
        p=p->next;
    }
}
void update_companies_id(){
    int id=1;
    Company *p=head_companies;
    while(p!=NULL){
        p->id=id;
        id++;
        p=p->next;
    }
}
void delete_coupon(int coupon_id){
    Coupon *in=head_coupons;
    Coupon *prev=head_coupons;
    delete_cus_vs_cp_by_coupon_id(coupon_id);
    while(in!=NULL){
        if(in->id==coupon_id){
            prev->next=in->next;
            free(in);
            break;
        }
        prev=in;
        in=in->next;
    }
    if(head_coupons!=NULL)
        if(head_coupons->id==coupon_id){
            Coupon *temp=head_coupons;
            head_coupons=head_coupons->next;
            free(temp);
        }
    update_coupons_id();
}

Coupon *get_coupon_by_id(int coupon_id){
    Coupon *in=head_coupons;
    while(in!=NULL){
        if(in->id==coupon_id)
            return in;
        in=in->next;
    }
    return NULL;
}

int check_if_coupon_belongs_to_company(int coupon_id,int company_id){
    Coupon *c=get_coupon_by_id(coupon_id);
    if(c!=NULL&&c->company_id==company_id)
        return 1;
    return 0;
}
void delete_coupon_and_check(int coupon_id,int company_id){
    if(check_if_coupon_belongs_to_company(coupon_id,company_id))
        delete_coupon(coupon_id);
    else
        printf("That coupon don't belongs to the company or coupon not exist");
}
void delete_all_coupons_of_company(int company_id){
    Coupon *in,*prev,*temp=NULL;
    in=prev=head_coupons;
    if(head_coupons==NULL)
        return;
    while(in!=NULL){
        if(in->company_id==company_id){
            delete_cus_vs_cp_by_coupon_id(in->id);
            prev->next=in->next;
            temp=in;
        }else
            prev=in;
        in=in->next;
        free(temp);
    }
    if(head_coupons->company_id==company_id){
        temp=head_coupons;
        delete_cus_vs_cp_by_coupon_id(head_coupons->id);
        head_coupons=head_coupons->next;
        free(temp);
    }
    update_coupons_id();
}

void delete_company(int company_id){
    delete_all_coupons_of_company(company_id);
    Company *in,*prev;
    in=prev=head_companies;
    if(head_companies==NULL)
        return;
    while(in!=NULL){
        if(in->id==company_id){
            prev->next=in->next;
            break;
        }
        prev=in;
        in=in->next;
    }
    if(head_companies->id==company_id)
        head_companies=head_companies->next;
    free(in);
    update_companies_id;
}
void print_companies(){
    Company *in=head_companies;
    if(head_companies==NULL)
        printf("Companies table empty\n");
    while(in!=NULL){
        printf("Company id: %d\nName: %s\nEmail: %s\nPassword: %s\n"
               ,in->id,in->name,in->email,in->password);
        in=in->next;
    }
}
void print_customers(){
    Customer *in=head_costumers;
    if(head_costumers==NULL)
        printf("Customers table empty\n");
    while(in!=NULL){
        printf("Customer id: %d\nFirst name: %s\nLast name: %s\nEmail: %s\nPassword: %s\n"
               ,in->id,in->first_name,in->last_name,in->email,in->password);
        in=in->next;
    }
}
void print_coupons(){
    Coupon *in=head_coupons;
    if(head_coupons==NULL)
        printf("Coupon table empty\n");
    while(in!=NULL){
        printf("Coupon id: %d\nCompany id: %d\nCategory id: %d\nTitle: %s\nDescription: %s\n"
               ,in->id,in->company_id,in->category_id,in->title,in->description);
        printf("Start date: ");
        print_date(in->start_date);
        printf("\nEnd date: ");
        print_date(in->end_date);
        printf("\nAmount: %d\nPrice: %.2lf\n",in->amount,in->price);
        in=in->next;
    }
}
void print_coupons_of_company(int company_id){
    int flag=0;
    Coupon *in=head_coupons;
    if(head_coupons==NULL)
        printf("Coupon table empty\n");
    while(in!=NULL){
        if(in->company_id==company_id){
            flag=1;
            printf("Coupon id: %d\nCompany id: %d\nCategory id: %d\nTitle: %s\nDescription: %s"
                    ,in->id,in->company_id,in->category_id,in->title,in->description);
            printf("Start date: ");
            print_date(in->start_date);
            printf("\nEnd date: ");
            print_date(in->end_date);
            printf("\nAmount: %d\nPrice: %.2lf\n",in->amount,in->price);
        }
        in=in->next;
    }
    if(!flag)
        printf("Your company don't have coupons\n");
}
Company *create_company(){
    Company *p=(Company*)malloc(sizeof(Company));
    printf("Enter company name\n");
    scan_string(&(p->name));
    printf("Enter company email\n");
    scan_string(&(p->email));
    printf("Enter company password\n");
    scan_string(&(p->password));
    p->next=NULL;
    return p;
}
Customer *create_customer(){
    Customer *p=(Customer*)malloc(sizeof(Customer));
    printf("Enter customer first name\n");
    scan_string(&(p->first_name));
    printf("Enter customer last name\n");
    scan_string(&(p->last_name));
    printf("Enter customer email\n");
    scan_string(&(p->email));
    printf("Enter customer password\n");
    scan_string(&(p->password));
    p->next=NULL;
    return p;
}
Coupon *create_coupon(int company_id){
    Coupon *p=(Coupon*)malloc(sizeof(Coupon));
    p->company_id=company_id;
    printf("Enter category id\n");
    scanf("%d",&(p->category_id) );
    clean_buff();
    printf("Enter title\n");
    scan_string(&(p->title));
    printf("Enter description\n");
    scan_string(&(p->description));
    printf("Enter start date day-month-year\n");
    scanf("%d %d %d",&(p->start_date.day),&(p->start_date.month),&(p->start_date.year));
    printf("Enter end date day-month-year\n");
    scanf("%d %d %d",&(p->end_date.day),&(p->end_date.month),&(p->end_date.year));
    printf("Enter amount\n");
    scanf("%d",&(p->amount) );
    printf("Enter price\n");
    scanf("%lf",&(p->price));
    clean_buff();
    printf("Enter image string\n");
    scan_string(&(p->image));
    p->next=NULL;
    return p;
}
void print_customers_vs_coupons(){
    Customers_vs_coupons *in=head_customers_vs_coupons;
    if(in==NULL)
        printf("Customers vs coupons empty\n");
    while(in!=NULL){
        printf("Customer id: %d Coupon id: %d\n",in->customer_id,in->coupon_id);
        in=in->next;
    }
}
void menu_admin(){
    printf("Enter 1-8\n");
    printf("1 Add company\n2 Add customer\n3 remove company\n4 remove customer\n");
    printf("5 print companies\n6 print customers\n7 print customers vs coupons\n");
    printf("8 back\n");
}
void menu_company(){
    printf("Enter 1-8\n");
    printf("1 Add coupon\n2 remove coupon\n3 print coupons of company\n4 print categories \n8 back\n");
}
void menu_customer(){
    printf("Enter 1-8\n");
    printf("1 buy coupon\n2 print coupons of all companies\n8 back\n");
}
void admin(){
    int select,id;
    do{
        menu_admin();
        scanf("%d",&select);
        clean_buff();
        switch(select){
            case 1:
                add_company(create_company());
                break;
            case 2:
                add_customer(create_customer());
                break;
            case 3:
                printf("Enter company id to remove\n");
                scanf("%d",&id);
                delete_company(id);
                break;
            case 4:
                printf("Enter customer id to remove\n");
                scanf("%d",&id);
                delete_customer(id);
                break;
            case 5:
                print_companies();
                break;
            case 6:
                print_customers();
                break;
            case 7:
                print_customers_vs_coupons();
                break;
        }
    }while(select!=8);
}
void company(){
    char *email;
    char *password;
    int id,select,id2;
    printf("Enter company email\n");
    scan_string(&email);
    printf("Enter company password\n");
    scan_string(&password);
    id=get_company_id(email,password);
    if(id==0)
        printf("invalid email or password or company do not exist\n");
    else{
        do{
            menu_company();
            scanf("%d",&select);
            clean_buff();
            switch(select){
                case 1:
                    add_coupon(create_coupon(id));
                    break;
                case 2:
                    printf("Enter coupon id to remove\n");
                    scanf("%d",&id2);
                    delete_coupon_and_check(id2,id);
                    break;
                case 3:
                    print_coupons_of_company(id);
                    break;
                case 4:
                    print_categories();
            }
        }while(select!=8);
    }
}
void customer(){
    char *email;
    char *password;
    int id,select,id2;
    printf("Enter customer email\n");
    scan_string(&email);
    printf("Enter customer password\n");
    scan_string(&password);
    id=get_customer_id(email,password);
    if(id==0)
        printf("Invalid email or password or customer do not exist\n");
    else{
        do{
            menu_customer();
            scanf("%d",&select);
            clean_buff();
            switch(select){
                case 1:
                    printf("Enter coupon id to buy\n");
                    scanf("%d",&id2);
                    buy_coupon(id2,id);
                    break;
                case 2:
                    print_coupons();
                    break;
            }
        }while(select!=8);
    }
}
void run(){
    int select;
    generate_categories();
    do{
        printf("Enter 1-4\n1 Admin\n2 company\n3 customer\n4 exit\n");
        scanf("%d",&select);
        clean_buff();
        switch(select){
            case 1:
                admin();
                break;
            case 2:
                company();
                break;
            case 3:
                customer();
                break;
        }
    }while(select!=4);
    printf("Good bye\n");
}
int main(){
    run();
    //while(getchar()!='\n');
    getchar();
    return 0;
}

























