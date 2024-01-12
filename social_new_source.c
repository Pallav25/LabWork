#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

#define OWNED 1
#define CUSTOMER 2

#define MAXNodes 1000
#define MAXContent 100
struct Node;
struct Coordinates;
struct Individual;
struct Group;
struct Organisation;
struct Business;

typedef struct Node{
int id;
char name[100];
char date[11];
char* content[MAXContent];
int numberOfPosts;
}node;

typedef struct Coordinates{
double x;
double y;
}coordinates;


typedef struct Individual{
node basic;
char bday[11];
struct Group* indGroups[MAXNodes];
unsigned int nindgroups;
struct Organisation* indOrganisations[MAXNodes];
unsigned int nindorgs;
struct Business* ownedBusiness[MAXNodes];
unsigned int nownedbuss;
struct Business* customerBusiness[MAXNodes];
unsigned int ncustomerbuss;
}individual;

typedef struct Group{
node basic;
individual* groupIndividuals[MAXNodes];
unsigned int ngroupind;
struct Business* groupBusiness[MAXNodes];
unsigned int ngroupbuss;

}group;


typedef struct Organisation{
node basic;
coordinates cord;
individual* orgIndividuals[MAXNodes];
unsigned int norginds;

}organisation;


typedef struct Business{
node basic;
individual* ownerIndividuals[MAXNodes];
unsigned int nownerinds;
individual* customerIndividuals[MAXNodes];
unsigned int ncustomerinds;
group* memberships[MAXNodes];
unsigned int nmemberships;
}business;

void scanStr(char* , char* );
int scanInt(char* );
int createId(int,int);
int reverseId(int);

int printGroupsAllotId(char*,int*);
void inputLinkedGroups(char* ,group**,unsigned int*);

int printOrgsAllotId(char* ,int*);
void inputLinkedOrganisations(char* , organisation** ,unsigned int*);

int printIndividualsAllotId(char*,int*);
void inputLinkedIndividuals(char*,individual**,unsigned int*);

int printBusinessesAllotId(char*,int*);
void inputLinkedBusinesses(char*,business**,unsigned int*,int);

void createIndividual();
void createOrganisation();
void createBusiness();
void createGroup();

int groups= 0;
int individuals =0;
int organisations=0;
int businesses=0;

individual* allindividuals[MAXNodes];
group* allgroups[MAXNodes];
organisation* allorganisations[MAXNodes];
business* allbusinesses[MAXNodes];

void scanStr(char* str, char* store){
    printf("%s : ",str);
    scanf("%s",store);
}

int scanInt(char* str){
    printf("%s : ", str);
    int a;
    scanf("%d", &a);
    return a;
}

int createId(int n,int type){
    int i;
    int j=type;
    i=log10(n);
    while(i--) j*=10;
    return 10*j+n;
}

int reverseId(int n){
    int i,j=1;
    i=log10(n);
    while(i--) j*=10;
    return n%j;
}

int printGroupsAllotId(char* string,int* id){
    int i;
    int count=0;
    for ( i = 1; i <= groups; i++)
    {
        if(strcmp(allgroups[i]->basic.name,string)==0){
            printf("Group %d: %s\n",i,allgroups[i]->basic.name);
            printf("Content : %s",allgroups[i]->basic.content[0]);
            count++;
            *id=allgroups[i]->basic.id;
        }
    }
    return count;
}

void inputLinkedGroups(char* str1,group* arr[],unsigned int* ngroups){//inputs into the array all the nodes 
    printf("Give the names of all the groups linked to the %s (to exit enter 0) : ",str1);
    char name[100];
    int commonNames;
    int groupId=0;
    group* ptr;
    while(1){
        scanStr("Name",name);
        if(strcmp(name,"0")==0) break;
        commonNames=printGroupsAllotId(name,&groupId);
        if(commonNames==0)  printf("No such matches");
        else if(commonNames>1) {
            printf("Multiple matches found.\n");
            groupId= scanInt("Please specify based on their content. Ids have been provided,choose the appropriate Id");
            ptr=allgroups[reverseId(groupId)];
            arr[++*ngroups]=ptr;
        }
        else {
            ptr=allgroups[reverseId(groupId)];
            arr[++*ngroups]=ptr;
        }
    }
}

int printOrgsAllotId(char* string, int* id) {
    int i;
    int count = 0;
    for (i = 1; i <= organisations; i++) {
        if (strcmp(allorganisations[i]->basic.name, string) == 0) {
            printf("Organisation %d: %s\n", i, allorganisations[i]->basic.name);
            printf("Content : %s", allorganisations[i]->basic.content[0]);
            count++;
            *id = allorganisations[i]->basic.id;
        }
    }
    return count;
}

void inputLinkedOrganisations(char* str, organisation* arr[],unsigned int* norgs) {
    printf("Give the names of all the organisations linked to %s (to exit, enter 0): ", str);
    char name[100];
    int commonNames;
    int orgId = 0;
    organisation* ptr;
    while (1) {
        scanStr("Name", name);
        if (strcmp(name, "0") == 0) break;
        commonNames = printOrgsAllotId(name, &orgId);
        if (commonNames == 0)  printf("No such matches");
        else if (commonNames > 1) {
            printf("Multiple matches found.\n");
            orgId = scanInt("Please specify based on their content. Ids have been provided, choose the appropriate Id");
            ptr = allorganisations[reverseId(orgId)];
            arr[++*norgs] = ptr;
        } else {
            ptr = allorganisations[reverseId(orgId)];
            arr[++*norgs] = ptr;
        }
    }
}

int printBusinessesAllotId(char* string, int* id) {
    int i;
    int count = 0;
    for (i = 1; i <= businesses; i++) {
        if (strcmp(allbusinesses[i]->basic.name, string) == 0) {
            printf("Business %d: %s\n", i, allbusinesses[i]->basic.name);
            printf("Content : %s", allbusinesses[i]->basic.content[0]);
            count++;
            *id = allbusinesses[i]->basic.id;
        }
    }
    return count;
}

void inputLinkedBusinesses(char* str,business* arr[],unsigned int* nbusinesses,int ownedOrCustomer) {
    switch (ownedOrCustomer)
    {
    case OWNED:
        printf("Give the names of all the businesses owned by %s (to exit, enter 0): ", str);
        break;
    
    case CUSTOMER:
        printf("Give the names of all the businesses %s is a customer of (to exit, enter 0): ", str);
        break;
    default:
        printf("Give the names of all the businesses %s is linked to (to exit, enter 0 ): ",str);
        break;
    }
    
    char name[100];
    int commonNames;
    int businessId = 0;
    business* ptr;
    while (1) {
        scanStr("Name", name);
        if (strcmp(name, "0") == 0) break;
        commonNames = printBusinessesAllotId(name, &businessId);
        if (commonNames == 0)  printf("No such matches");
        else if (commonNames > 1) {
            printf("Multiple matches found.\n");
            businessId = scanInt("Please specify based on their content. Ids have been provided, choose the appropriate Id");
            ptr = allbusinesses[reverseId(businessId)];
            arr[++*nbusinesses] = ptr;
        } else {
            ptr = allbusinesses[reverseId(businessId)];
            arr[++*nbusinesses] = ptr;
        }
    }
}

int printIndividualsAllotId(char* string, int* id) {
    int i;
    int count = 0;
    for (i = 1; i <= individuals; i++) {
        if (strcmp(allindividuals[i]->basic.name, string) == 0) {
            printf("Individual %d: %s\n", i, allindividuals[i]->basic.name);
            printf("Content : %s", allindividuals[i]->basic.content[0]);
            count++;
            *id = allindividuals[i]->basic.id;
        }
    }
    return count;
}

void inputLinkedIndividuals(char* str, individual* arr[],unsigned int* nindividuals) {
    printf("Give the names of all the individuals linked to %s (to exit, enter 0): ", str);
    char name[100];
    int commonNames;
    int indId = 0;
    individual* ptr;
    while (1) {
        scanStr("Name", name);
        if (strcmp(name, "0") == 0) break;
        commonNames = printIndividualsAllotId(name, &indId);
        if (commonNames == 0)  printf("No such matches");
        else if (commonNames > 1) {
            printf("Multiple matches found.\n");
            indId = scanInt("Please specify based on their content. Ids have been provided, choose the appropriate Id");
            ptr = allindividuals[reverseId(indId)];
            arr[++*nindividuals] = ptr;
        } else {
            ptr = allindividuals[reverseId(indId)];
            arr[++*nindividuals] = ptr;
        }
    }
}

void createIndividual(){
    individual* new_ind = (individual*) malloc (sizeof(individual));
    allindividuals[++individuals]=new_ind;

    //basic data
    new_ind->basic.id =createId( ++individuals,1);
    scanStr("Name",new_ind->basic.name);
    scanStr("Date",new_ind->basic.date);
    int i;
    for(i=0;i<MAXContent;i++) new_ind->basic.content[i]=NULL;

    //birthday
    scanStr("Birthday(date in the format 01/01/2001)",new_ind->bday);

    //total number of linked groups,businesses and organisations is zero initially
    new_ind->nindgroups=0;
    new_ind->nindorgs=0;
    new_ind->nownedbuss=0;
    new_ind->ncustomerbuss=0;

    //link all the necessary nodes
    inputLinkedGroups("individual",new_ind->indGroups,&new_ind->nindgroups);
    inputLinkedOrganisations("individual",new_ind->indOrganisations,&new_ind->nindorgs);
    inputLinkedBusinesses("individual",new_ind->ownedBusiness,&new_ind->nownedbuss,OWNED);
    inputLinkedBusinesses("individual",new_ind->customerBusiness,&new_ind->ncustomerbuss,CUSTOMER);

}   

void createGroup() {
    group* new_group = (group*)malloc(sizeof(group));
    allgroups[++groups]=new_group;

    // Basic data
    new_group->basic.id = createId(++groups, 2);
    scanStr("Name", new_group->basic.name);
    scanStr("Date", new_group->basic.date);
    int i;
    for (i = 0; i < MAXContent; i++) new_group->basic.content[i] = NULL;

    // Initialize the number of linked individuals and businesses to zero initially
    new_group->ngroupind = 0;
    new_group->ngroupbuss = 0;

    // Input linked individuals and businesses
    inputLinkedIndividuals("group", new_group->groupIndividuals, &new_group->ngroupind);
    inputLinkedBusinesses("group", new_group->groupBusiness, &new_group->ngroupbuss,0);

}

void createOrganisation() {
    organisation* new_org = (organisation*)malloc(sizeof(organisation));
    allorganisations[++organisations]=new_org;

    // Basic data
    new_org->basic.id = createId(++organisations, 3);
    scanStr("Name", new_org->basic.name);
    scanStr("Date", new_org->basic.date);
    int i;
    for (i = 0; i < MAXContent; i++) new_org->basic.content[i] = NULL;

    // Coordinates
    printf("Enter coordinates (x y): ");
    scanf("%lf %lf", &new_org->cord.x, &new_org->cord.y);

    // Initialize the number of linked individuals to zero initially
    new_org->norginds = 0;

    // Input linked individuals
    inputLinkedIndividuals("organisation", new_org->orgIndividuals, &new_org->norginds);

}

void createBusiness() {
    business* new_business = (business*)malloc(sizeof(business));
    allbusinesses[++businesses]=new_business;

    // Basic data
    new_business->basic.id = createId(++businesses, 4);
    scanStr("Name", new_business->basic.name);
    scanStr("Date", new_business->basic.date);
    int i;
    for (i = 0; i < MAXContent; i++) new_business->basic.content[i] = NULL;

    // Initialize the number of linked individuals and groups to zero initially
    new_business->nownerinds = 0;
    new_business->ncustomerinds = 0;
    new_business->nmemberships = 0;

    // Input linked individuals, groups, and customers
    inputLinkedIndividuals("business as owner", new_business->ownerIndividuals, &new_business->nownerinds);
    inputLinkedGroups("business as member", new_business->memberships, &new_business->nmemberships);
    inputLinkedIndividuals("business as customer", new_business->customerIndividuals, &new_business->ncustomerinds);

}

int main(){
    printf("Choose one of the following options:\n");
    printf("1.Create a node\n2.Delete a node\n3.Search for a node\n4.Print all the one-hop nodes\n");
    printf("5.Create and post content\n6.Search for content posted by any node\n");
    printf("7.Display all the content posted by nodes linked to a node\n");
    int option;
    option=scanInt("Give the input as the integer corresponding to the desired option");
    switch (option)
    {
    case 1:

        createIndividual();
        break;
    
    default:
        break;
    }
    return 0;
}