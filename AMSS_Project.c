/*Assignment Management Software System*/
#include<stdbool.h>
#include <limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 10000
#define ALIKE_SIZE 50
#define NAME_SIZE 50
#define ID_SIZE 25
#define ASSIGNMENT_NUM 10
#define ARR_SIZE 10

// Structure definition for Assignment Node
typedef struct Node_Alist
{
    int student_group_id;
    char status[20];
    int evaluation_marks_of_std1;
    int evaluation_marks_of_std2;
    int viva_marks_of_std1;
    int viva_marks_of_std2;
    struct Node_Alist* next;
}Assignment_Node;


// Structure definition for Student Record
typedef struct Node_list
{
    char student_id_1[ID_SIZE];
    char student_id_2[ID_SIZE]; 
    char student_name[NAME_SIZE];
    char group_partner[NAME_SIZE];
    int group_id;
    int assignment_id;
    char assignment_name[100];
    char deadline[11];
    char status_of_assignment[20];
    int evaluation_marks_1;
    int viva_marks_1;
    int evaluation_marks_2;
    int viva_marks_2;
    bool assignment_submitted;
    bool viva_taken;
    bool assignment_evaluated;
    struct Node_list *next;
   //Assignment_Node* right;
} student_record;




// Structure definition for Assignment Records
typedef struct Node_tag
{
    int assignment_id;
    char topic_name[60];
    char status1[20];
    Assignment_Node *down;
    struct Node_tag *next;
} AssignmentRecords;

typedef struct Hash_table
{
    AssignmentRecords* HASH_TABLE[ASSIGNMENT_NUM ];
    int HASH_SIZE;
}HT_AR;

int hash(int key)
{
    return key-1;
}

//node used in question 7
typedef struct marks_list
{
    int marks;
    int corres_g_id;
    struct marks_list* next;
}marks_node;


//INITIALIZE HASH TABLE
void initialize_HT(HT_AR* HT1)
{
	int i;
    for ( i = 0; i < ASSIGNMENT_NUM; i++)
    {
        HT1->HASH_TABLE[i]=NULL;
        
    }
    HT1->HASH_SIZE=0;
}

    // Initialize Student Record variables
void initialize_SR(student_record *student)
{

    strcpy(student->student_id_1," ");
   strcpy(student->student_id_2," ");
    strcpy(student->student_name, " ");
    strcpy(student->group_partner, " ");
    student->group_id = 0;
    student->assignment_id = 0;
    strcpy(student->assignment_name, " ");
    strcpy(student->deadline, " ");
    strcpy(student->status_of_assignment, " ");
    student->evaluation_marks_1 = 0;
    student->viva_marks_1 = 0;
    student->evaluation_marks_2 = 0;
    student->viva_marks_2 = 0;
    student->next = NULL;
   student->viva_taken=false;
   student->assignment_evaluated=false;
   student->assignment_submitted=false;
    //student->right = NULL;
}
   
    // Initialize Assignment Records variables
    
    void initialize_AR( AssignmentRecords *assignment)
{
    assignment->assignment_id = 0;
    strcpy(assignment->topic_name, " ");
    strcpy(assignment->status1, " ");
    assignment->next = NULL;
    assignment->down = NULL;
}
    // Initialize Assignment Node variables
    void initialize_AssignNode(Assignment_Node *groups)
{
    groups->student_group_id = 0;
    strcpy(groups->status, "notsubmitted");
    groups->evaluation_marks_of_std1 = 0;
    groups->evaluation_marks_of_std2 = 0;
    groups->viva_marks_of_std1 = 0;
    groups->viva_marks_of_std2 = 0;
    groups->next = NULL;
}

student_record* createSRlist(int numNodes)
{
    student_record* nptr;
    student_record* lptr;
    int i;
    lptr=nptr=NULL;
    for ( i = 1; i <=numNodes; i++)
    {
      nptr=(struct Node_list*)malloc(sizeof(struct Node_list));
      initialize_SR(nptr);
      nptr->next=lptr;
      lptr=nptr;
     
    }
    return lptr;
}


AssignmentRecords* createARlist(int numRec,HT_AR* HT1)
{
    AssignmentRecords* nptr;
    AssignmentRecords* lptr=NULL;
    AssignmentRecords* ptr;
    int i;
    lptr=nptr=ptr=NULL;
    for( i=1;i<=numRec;i++)
    {
        nptr=(struct Node_tag*)malloc(sizeof(struct Node_tag));
        initialize_AR(nptr);
        nptr->assignment_id=i;
        HT1->HASH_TABLE[hash(i)]=nptr;
        if(lptr==NULL)
        {
            lptr=nptr;
        }
        else{
            ptr=lptr;
            while(ptr->next!=NULL)
            {
                ptr=ptr->next;
            }
            ptr->next=nptr;
        } 
    }
    return lptr;
}




 //QUESTION 1
void insert_SR(student_record** student, AssignmentRecords** assignment,HT_AR* HT1)
{
      FILE* fp = fopen("evaluation1.csv", "r");
      student_record* S_record=*student;
      AssignmentRecords* ptr;
      Assignment_Node* tail;
      Assignment_Node* traversal;
      Assignment_Node* q;
      Assignment_Node* first;

      int flag=1;
    if (!fp)
        printf("Can't open file\n");
 
    else {
        
        char buffer[MAX_SIZE];
        int key1=0;
        int row = 0;
        int column = 0;
 
        while (fgets(buffer,
                     MAX_SIZE, fp)) {
            column = 0;
            row++;
          if(row==1)
          {
            //skip this iteration
          }
          else
          {
          
            char* value = strtok(buffer, ", ");
 
            while (value) {
                
                if (column == 0) {
                   S_record->group_id=atoi(value);
                   
                }
 
                if (column == 1) {
                    strcpy(S_record->student_id_1,value);
                }
 
               
                if (column == 2) {
                   strcpy(S_record->student_id_2,value);
                }
                 
                 if (column == 3) {
                    strcpy(S_record->student_name,value);
                }

                if (column == 4) {
                   strcpy(S_record->group_partner,value);
                }

                if (column == 5) {
                   S_record->assignment_id=atoi(value);
                   key1= S_record->assignment_id;

                }

                if (column == 6) {
                   strcpy(S_record->assignment_name,value);
                }

                if (column == 7) {
                   strcpy(S_record->deadline,value);
                }

                if (column == 8) {
                   strcpy(S_record->status_of_assignment,value);
                }

                 if (column == 9) {
                   S_record->evaluation_marks_1=atoi(value);
                }
                
                 if (column == 10) {
                  S_record->viva_marks_1=atoi(value);
                }

                 if (column == 11) {
                  S_record->evaluation_marks_1=atoi(value);
                }
                
                if (column == 12) {
                  S_record->viva_marks_2=atoi(value);
                }

                value = strtok(NULL, ", ");
                column++;
            }
             ptr=HT1->HASH_TABLE[hash(key1)];
             if(ptr->down==NULL)
             {
             strcpy(ptr->status1,"declared");
             }
             Assignment_Node* newptr=(struct Node_Alist*)malloc(sizeof(struct Node_Alist));
             initialize_AssignNode(newptr);
             strcpy(newptr->status,"declared");
             first=ptr->down;
             newptr->student_group_id=S_record->group_id;
             if(first==NULL)
             {
                ptr->down=newptr;
                first=newptr;
                tail=newptr;
             }
             else
             {
               // printf("entered into else portion \n ");
           
                //sorted insert

                traversal=ptr->down;
                while(traversal && traversal->student_group_id<S_record->group_id)
                {
                      q=traversal;
                      traversal=traversal->next;
                }
                if(traversal==first)
                {
                  newptr->next=first;
                  first=newptr;
                  ptr->down=first;
                 // printf("entered into the inner if conditon \n");
                }
                 
                 else
                 {
                newptr->next=q->next;
                q->next=newptr;
              
             }
                
             }
           
            S_record=S_record->next;

           }   
        }
 
       
      fclose(fp);
    }
    
}

//question 1-b
void addsNode(student_record** student, AssignmentRecords** assignment,HT_AR* HT1)
{
    int gid;
    char st[20]="notsubmitted";
    int flag=1;
    int flag1=1;
    char name1[NAME_SIZE];
    char name2[NAME_SIZE];
    char id1[ID_SIZE];
    char id2[ID_SIZE];
    char assign_name[100];
    int assign_id;
    char Dline[11];
    Assignment_Node* traversal;
    Assignment_Node* q;
    Assignment_Node* first;
    student_record* nptr;
    student_record* prev;
    student_record* sptr=*student;
    student_record* strav=sptr;
    AssignmentRecords* aptr=*assignment;
    AssignmentRecords* atrav;
    printf("ENTER THE GROUP ID THAT HAS TO BE INSERTED \n");
    scanf("%d",&gid);
    while(strav!=NULL && flag==1)
    {
        if(strav->group_id==gid)
        {
        	flag=0;
		}
		strav=strav->next;
		
    }
    if(flag==1)
    {
        strav=sptr;
        flag1=1;
    	//have to create node and add it
    	nptr=(student_record*)malloc(sizeof(student_record));
        initialize_SR(nptr);
    	printf("ENTER THE NAME OF STUDENT 1:\t");
    	scanf("%s",name1);
        printf("ENTER THE NAME OF STUDENT 2 : \t");
        scanf("%s",name2);
        printf("ENTER THE STUDENT ID 1 \t");
        scanf("%s",id1);
        printf("ENTER THE STUDENT ID 2 \t");
        scanf("%s",id2);
        printf("ENTER THE ASSIGNMENT NAME \t ");
        scanf("%s",assign_name);
        printf("ENTER THE ASSIGNMENT ID \t \t");
        scanf("%d",&assign_id);
        printf("ENTER THE DEADLINE OF THE ASSIGNMENT \t ");
        scanf("%s",Dline);
        strcpy(nptr->student_id_1,id1);
        strcpy(nptr->student_id_2,id2);
        strcpy(nptr->assignment_name,assign_name);
        strcpy(nptr->student_name,name1);
        strcpy(nptr->group_partner,name2);
        strcpy(nptr->deadline,Dline);
        strcpy(nptr->status_of_assignment,st);
        nptr->assignment_id=assign_id;
        nptr->group_id=gid;
        while(strav!=NULL && flag1==1)
        {
            if(strav->group_id > gid)
            {
                flag1=0;
            }
            else
            {
            prev=strav;
            strav=strav->next;
            }
        }
        if(strav==sptr)
        {
          nptr->next=strav;
          sptr=nptr;
        }
        else
        {
            nptr->next=prev->next;
            prev->next=nptr;
        }
        
      atrav=HT1->HASH_TABLE[hash(assign_id)];
      Assignment_Node* newptr=(struct Node_Alist*)malloc(sizeof(struct Node_Alist));
      initialize_AssignNode(newptr);
      first=atrav->down;
      newptr->student_group_id=gid;
        if(first==NULL)
             {
                atrav->down=newptr;
                first=newptr;
                //tail=newptr;
             }
             else
             {
                //sorted insert
                traversal=atrav->down;
                while(traversal && traversal->student_group_id<gid)
                {
                      q=traversal;
                      traversal=traversal->next;
                }
                if(traversal==first)
                {
                  newptr->next=first;
                  first=newptr;
                  atrav->down=first;
                 // printf("entered into the inner if conditon \n");
                }
                 
                 else
                 {
                newptr->next=q->next;
                q->next=newptr;
              
             }
                
             }
    	
	}
	else
	{
		printf("\t GROUP ALREADY EXISTS \t \t");
	}


}





void printSR(student_record** student)
{
    printf("\t \t PRINTING STUDENT RECORDS \n");
    student_record* ptr=*student;
    while (ptr!=NULL)
    {
      
       printf("\n GROUP-ID \t");
       printf("%d",ptr->group_id);
       printf("\n STUDENT-ID-1 \t");
       printf("%s",ptr->student_id_1);
       printf("\n STUDENT-ID-2 \t");
       printf("%s",ptr->student_id_2);
       printf("\n NAME1 \t");
       printf("%s",ptr->student_name);
       printf("\n NAME2 \t");
       printf("%s",ptr->group_partner);
       printf("\n ASSIGNMENT ID \t");
       printf("%d",ptr->assignment_id);
       printf("\n ASSIGNMENT NAME \t");
       printf("%s",ptr->assignment_name);
       printf("\n DEADLINE \t");
       printf("%s",ptr->deadline);
       printf("\n ASSIGNMENT STATUS \t");
       printf("%s",ptr->status_of_assignment);
       printf("\n EVALUATION MARKS1 \t");
       printf("%d",ptr->evaluation_marks_1);
       printf("\n EVALUATION MARKS2 \t");
       printf("%d",ptr->evaluation_marks_2);
       printf("\n VIVA MARKS_1 \t");
       printf("%d",ptr->viva_marks_1);
       printf("\n VIVA MARKS_2 \t");
       printf("%d",ptr->viva_marks_2);
       printf("\n\n");
      

       ptr=ptr->next;
    }
    
}
void printAR(AssignmentRecords** assignment  )
{
    printf("\t \t PRINTING ASSIGNMENT RECORDS \n ");
    AssignmentRecords* ptr=*assignment;
    Assignment_Node* tptr=NULL;
    while(ptr!=NULL)
    {
       printf("\n ASSIGNMENT ID \t");
       printf("%d",ptr->assignment_id);
       printf("\n ASSIGNMENT STATUS \t");
       printf("%s",ptr->status1);
       printf("\n TOPIC NAME \t");
       printf("%s",ptr->topic_name);
       printf("\n \t \t CONNECTED NODE DETAILS \t \t");
       tptr=ptr->down;
       while(tptr!=NULL)
       {
       printf("\n STUDENT GROUP ID \t");
       printf("%d",tptr->student_group_id);
       printf("\n MARKS GIVEN EVAL STD1\t");
       printf("%d",tptr->evaluation_marks_of_std1);
       printf("\n MARKS GIVEN EVAL STD2 \t");
       printf("%d",tptr->evaluation_marks_of_std2);
       printf("\n MARKS GIVEN VIVA STD1 \t");
       printf("%d",tptr->viva_marks_of_std1);
       printf("\n MARKS GIVEN VIVA STD2 \t");
       printf("%d",tptr->viva_marks_of_std2);
       
       printf("\n ASSIGNMENT STATUS \t");
       printf("%s",tptr->status);
      
       tptr=tptr->next;
       }
       printf("\n\n");
       ptr=ptr->next;
    }
}


//QUESTION 2
void insert_AR(student_record** student, AssignmentRecords** assignment,HT_AR* HT1)
{
    printf("\t \t entered into the function inserting assignment records \t \n");
      FILE* fp1 = fopen("assignmentRecord.csv", "r");
      //student_record* S_record=*student;
      int flag=1;
      AssignmentRecords* A_Record=*assignment;
      Assignment_Node* ptr;
      Assignment_Node* nptr; 
      Assignment_Node* tail;
      Assignment_Node* lptr;
      Assignment_Node* p;
      Assignment_Node* first;
      Assignment_Node* traversal;
      Assignment_Node* q;
      Assignment_Node* prev=NULL;
      student_record* sptr=NULL;
      student_record* shead=*student;

      int no_of_groups;
      int group_id;
      int eval_marks_1=0;
      int eval_marks_2=0;
      int viva_marks_1=0;
      int viva_marks_2=0;
      char Status[20]="notsubmitted";
      char cmpstat[20]="declared";
    if (!fp1)
        printf("Can't open file\n");
 
    else {
        
        char buffer[MAX_SIZE];
        int key1=0;
        int row = 0;
        int column = 0;
 
        while (fgets(buffer,
                     MAX_SIZE, fp1)) {
            column = 0;
            row++;
          if(row==1)
          {
            //skip this iteration
          }
          else
          {
          
            char* value = strtok(buffer, ", ");
 
            while (value) {
                
                if (column == 0) {
                   A_Record->assignment_id=atoi(value);
                   
                }
 
                
                if (column == 1) {
                    strcpy(A_Record->topic_name,value);
                }
 
               
                if (column == 2) {
                   strcpy(A_Record->status1,value);
                }
                 
                 

                value = strtok(NULL, ", ");
                column++;
            }
            lptr=A_Record->down;

             while(lptr!=NULL)
            {
           
                p=lptr;
                lptr=lptr->next;
                free(p);
 
            } 
            A_Record->down=NULL;
            first=A_Record->down;
           
            printf("enter the no of groups to which assignment %d was allocated \t",A_Record->assignment_id);
            scanf("%d",&no_of_groups);
            
            for(int i=0;i<no_of_groups;i++)
            {
                sptr=shead;
               //sorted insert according to group-id;
                printf("enter the group id \n ");
                scanf("%d",&group_id);
                 nptr=(Assignment_Node*)malloc(sizeof(Assignment_Node));
                initialize_AssignNode(nptr);
                nptr->student_group_id=group_id;
                // printf("enter the current status \n ");
                // scanf("%s",Status);
                strcpy(nptr->status,Status);
              
                nptr->evaluation_marks_of_std1=eval_marks_1;
              
                nptr->evaluation_marks_of_std2=eval_marks_2;
               
                nptr->viva_marks_of_std1=viva_marks_1;
               
                nptr->viva_marks_of_std2=viva_marks_2;
               
                if(first==NULL)
                {
                    first=nptr;
                    A_Record->down=first;
                }
                else
                {
                   
                traversal=first;
                while(traversal && traversal->student_group_id<group_id)
                {
                      q=traversal;
                      traversal=traversal->next;
                }
                if(traversal==first)
                {
                  nptr->next=first;
                  first=nptr;
                  A_Record->down=first;
                 // printf("entered into the inner if conditon \n");
                }
                 
                 else
                 {
                nptr->next=q->next;
                q->next=nptr;
                // printf("\t%d\n",q->student_group_id);
            
                // printf("\t%d\n",q->next->student_group_id);
                // printf("entered into the outer else condition \n");
             }



                }
                
                //updating the corresponding student record
                //traverse student record according to the corresponding group id and update the existing group id node
                while(sptr->group_id!=group_id)
                {
                    sptr=sptr->next;
                }
                //sptr points to the node which has to  be modified
                sptr->assignment_id=A_Record->assignment_id;
                 if(strcmp(Status,"notsubmitted")==0)
                {
                sptr->evaluation_marks_1=nptr->evaluation_marks_of_std1;
                sptr->evaluation_marks_2=nptr->evaluation_marks_of_std2;
                sptr->viva_marks_1=nptr->viva_marks_of_std1;
                sptr->viva_marks_2=nptr->viva_marks_of_std2;
                strcpy(sptr->status_of_assignment,Status);
                }
                
            }

          
            A_Record=A_Record->next; 

           } 

           
        }
 
       
      fclose(fp1);
    }
    
}

//question 2b
void insertAssignNode(student_record** student, AssignmentRecords** assignment,HT_AR* HT1)
{
    int no_of_groups;
   int Aid;
   char Aname[60];
   char Astatus[20]="declared";
    int group_id;
    int eval_marks_1=0;
    int eval_marks_2=0;
    int viva_marks_1=0;
    int viva_marks_2=0;
    char Status[20]="notsubmitted";
    char cmpstat[20]="declared";
   int flag=1;
   int flag1=1;
   Assignment_Node* newptr;
   student_record* sptr=NULL;
   student_record* shead=*student;
   AssignmentRecords*  aptr=*assignment;
   AssignmentRecords* atrav=aptr;
   AssignmentRecords* prev;
   AssignmentRecords* nptr;
       Assignment_Node* lptr;
      Assignment_Node* p;
      Assignment_Node* first;
      Assignment_Node* traversal;
      Assignment_Node* q;
   printf("ENTER THE ASSIGNMENT ID :\t ");
   scanf("%d",&Aid);
   while(atrav && flag==1)
   {
    if(atrav->assignment_id==Aid)
    {
        flag=0;
    }
    atrav=atrav->next;
   }
   if(flag==1)
   {
    atrav=aptr;
    flag1=1;
      //it means Assignment dosent exist and hence we have to add it
      printf("ENTER THE TOPIC NAME \t");
      scanf("%s",Aname);
      nptr=(AssignmentRecords*)malloc(sizeof(AssignmentRecords));
      initialize_AR(nptr);
      nptr->assignment_id=Aid;
      strcpy(nptr->topic_name,Aname);
      strcpy(nptr->status1,Astatus);
      while(atrav && flag1==1)
      {
         if(atrav->assignment_id>Aid)
         {
            flag1=0;
         }
         else
         {
         prev=atrav;
         atrav=atrav->next;
         }
      }

      if(atrav==aptr)
      {
        nptr->next=atrav;
        aptr=nptr;
       
      }
      else
      {
        
        nptr->next=prev->next;
        prev->next=nptr;
    
      }
       HT1->HASH_TABLE[hash(Aid)]=nptr;
       //allocating this assignment to student groups
         printf("enter the no of groups to which assignment %d was allocated \t",Aid);
        scanf("%d",&no_of_groups);
      first=nptr->down;
        for(int i=0;i<no_of_groups;i++)
            {
                sptr=shead;
               //sorted insert according to group-id;
                printf("enter the group id \n ");
                scanf("%d",&group_id);
                 newptr=(Assignment_Node*)malloc(sizeof(Assignment_Node));
                initialize_AssignNode(newptr);
                newptr->student_group_id=group_id;
                // printf("enter the current status \n ");
                // scanf("%s",Status);
                strcpy(newptr->status,Status);
              
                newptr->evaluation_marks_of_std1=eval_marks_1;
              
                newptr->evaluation_marks_of_std2=eval_marks_2;
               
                newptr->viva_marks_of_std1=viva_marks_1;
               
                newptr->viva_marks_of_std2=viva_marks_2;
               
                if(first==NULL)
                {
                    first=newptr;
                    nptr->down=first;
                }
                else
                {
                   
                traversal=first;
                while(traversal && traversal->student_group_id<group_id)
                {
                      q=traversal;
                      traversal=traversal->next;
                }
                if(traversal==first)
                {
                  newptr->next=first;
                  first=newptr;
                  nptr->down=first;
                 // printf("entered into the inner if conditon \n");
                }
                 
                 else
                 {
                newptr->next=q->next;
                q->next=newptr;
                // printf("\t%d\n",q->student_group_id);
            
                // printf("\t%d\n",q->next->student_group_id);
                // printf("entered into the outer else condition \n");
             }



                }
                
                //updating the corresponding student record
                //traverse student record according to the corresponding group id and update the existing group id node
                while(sptr->group_id!=group_id)
                {
                    sptr=sptr->next;
                }
                //sptr points to the node which has to  be modified
                sptr->assignment_id=Aid;
                 if(strcmp(Status,"notsubmitted")==0)
                {
                sptr->evaluation_marks_1=newptr->evaluation_marks_of_std1;
                sptr->evaluation_marks_2=newptr->evaluation_marks_of_std2;
                sptr->viva_marks_1=newptr->viva_marks_of_std1;
                sptr->viva_marks_2=newptr->viva_marks_of_std2;
                strcpy(sptr->status_of_assignment,Status);
                }
                
            }

          

      



   }
   else
   {
    printf("ASSIGNMENT ALREADY EXISTS IN THE GIVEN LIST \t \t");
   }



}

//question 3a
void submittingAssignments(student_record** student, AssignmentRecords** assignment,HT_AR* HT1)
{
  char submission_date[11];
  student_record* sptr=*student;
  student_record* straversal=sptr;
  AssignmentRecords* aptr=*assignment;
  AssignmentRecords* assign_traverse;
  Assignment_Node* Node_traverse;
  char status_update[20];
  char cmp1_st[20]="submitted";
  int Grp_id;
  int Assign_id=0;
  while(straversal!=NULL)
  {
     printf("\t ENTER THE SUBMISSION DATE IN YEAR-MONTH-DAY FORMAT \n ");
    printf("\t ENTER THE SUBMISSION DATE OF ASSIGNMENT OF THE CORRESPONDING GROUP WITH GROUP ID %d\t",straversal->group_id);
    scanf("%s",submission_date);
    if(strcmp(straversal->status_of_assignment,cmp1_st)==0)
    {
        printf(" Submission for group with GROUP ID %d already recorded.\n", straversal->group_id);
        straversal->assignment_submitted=true;
    }
    else 
    {
        if(strcmp(submission_date,straversal->deadline)<=0)
        {
            strcpy(straversal->status_of_assignment,"submitted");
            straversal->assignment_submitted=true;
        }
        else
        {
            printf(" Submission for group with GROUP ID %d WAS LATE!.\n", straversal->group_id);
        }
    }
    //now correspondingly update the assignment list as well
    Assign_id=straversal->assignment_id;
   Grp_id=straversal->group_id;
   strcpy(status_update,straversal->status_of_assignment);
   assign_traverse=HT1->HASH_TABLE[hash(Assign_id)];
   Node_traverse=assign_traverse->down;
   if(Node_traverse==NULL)
   {
         printf("THERE IS SOME ERROR \n");
   }
   else
   {
        while(Node_traverse->student_group_id != Grp_id)
        {
            Node_traverse=Node_traverse->next;
        }
        //UPDATE THE NODE STATUS NOW
        strcpy(Node_traverse->status,status_update);
   }

   straversal=straversal->next;

  }

}


//question 3b
void change_status_of_assignment(student_record** student, AssignmentRecords** assignment,HT_AR* HT1)
{
    printf("\t entering into the change of status function \t \n ");
    AssignmentRecords* ptr=*assignment;
    AssignmentRecords* traversal=ptr;
    student_record* sptr=*student;
    Assignment_Node* Node_ptr;
    Assignment_Node* tptr;
     int eval_marks_1;
      int eval_marks_2;
      int viva_marks_1;
      int viva_marks_2;
      char Status[20];
      char cmp2_st[20]="submitted";
     int count1=0;
     int count2=0;
     int Gid;
     int numeric=0;
    while(traversal!=NULL)
    {
        Node_ptr=traversal->down;
        tptr=Node_ptr;
        count1=0;
        count2=0;
        while(tptr!=NULL)
        {
            sptr=*student;
             if(strcmp(tptr->status,cmp2_st)==0)
             {
                printf("ENTER THE VALUE OF THE NUMERIC AS 1 IF U WANT TO EVALUATE THE SUBMITTED ASSIGNMENT \t \n");
                scanf("%d",&numeric);
                if(numeric==1)
                {
                printf("enter the details of student record with group id %d who was allocated assignment with assignment id %d \n",tptr->student_group_id,traversal->assignment_id);
                //correspondingly evaluate the record if it was submitted
                printf("enter the evaluation marks of student 1\n");
                scanf("%d",&eval_marks_1);
                tptr->evaluation_marks_of_std1=eval_marks_1;
                printf("enter the evaluation marks of student 2\n");
                scanf("%d",&eval_marks_2);
                tptr->evaluation_marks_of_std2=eval_marks_2;
                printf("enter the viva marks of student 1\n");
                scanf("%d",&viva_marks_1);
                tptr->viva_marks_of_std1=viva_marks_1;
                printf("enter the viva marks of student 2\n");
                scanf("%d",&viva_marks_2);
                tptr->viva_marks_of_std2=viva_marks_2;
                //update the status as evaluated after assigning marks 
                strcpy(tptr->status,"evaluated");
                Gid=tptr->student_group_id;
                while(sptr->group_id!=Gid)
                {
                    sptr=sptr->next;
                }
                sptr->assignment_evaluated=true;
                sptr->viva_taken=true;
                strcpy(sptr->status_of_assignment,tptr->status);
                sptr->evaluation_marks_1=eval_marks_1;
                sptr->evaluation_marks_2=eval_marks_2;
                sptr->viva_marks_1=viva_marks_1;
                sptr->viva_marks_2=viva_marks_2;
                //count1 indicates the no of records that have been evaluated
                count1++;
             }
             else
             {
                sptr=*student;
                Gid=tptr->student_group_id;
                while(sptr->group_id!=Gid)
                {
                    sptr=sptr->next;
                }
                sptr->assignment_evaluated=false;
                sptr->assignment_submitted=true;
                sptr->viva_taken=false;
             }
             }
             else
             {
                printf("the corresponding record with group id %d  who was allocated assignment with assignment id %d was not submitted hence not evaluated \n",tptr->student_group_id,traversal->assignment_id);
                Gid=tptr->student_group_id;
                while(sptr->group_id!=Gid)
                {
                    sptr=sptr->next;
                }
                 strcpy(sptr->status_of_assignment,tptr->status);
             }
             count2++;
             tptr=tptr->next;
        }
        if(count1==count2 && count1!=0 && count2!=0)
        {
              strcpy(traversal->status1,"evaluated");
        }
        else
        {
            strcpy(traversal->status1,"declared");
           
        }
        traversal=traversal->next;
    }
}

//question 4 
void print_LIST_NOT_evaluated(student_record** student, AssignmentRecords** assignment,HT_AR* HT1)
{
      printf("\n \t \t entered into the question 4 function \n");
      AssignmentRecords* aptr=*assignment;
      AssignmentRecords* traversal=aptr;
      char cmp3_st[20]="declared";
      while(traversal!=NULL)
      {
        //printf("entered while loop \n");
       // printf("\t ASSIGNMENT STATUS %s  \n",traversal->status1);
       // printf("\t CMP3_ST %s \n",cmp3_st);
        if(strcmp(traversal->status1,cmp3_st)==0)
        {
            //printf("entered if condition \n");
            printf("\t Assignment record with assignment id %d  ",traversal->assignment_id);
            printf("\n \t STATUS :- %s \t",traversal->status1);
            printf("\n \t TOPIC NAME :- %s \t \n ",traversal->topic_name);
        }
        traversal=traversal->next;
      }
}

//question 5
void groups_not_submitted(student_record** student, AssignmentRecords** assignment,HT_AR* HT1)
{
     printf("\n \t \t entered into the question 5 function \n");
  char submission_date[11];
  student_record* sptr=*student;
  student_record* straversal=sptr;
  AssignmentRecords* aptr=*assignment;
  AssignmentRecords* assign_traverse;
  Assignment_Node* Node_traverse;
  char status_update[20];
  int Grp_id;
  int Assign_id=0;
  while(straversal!=NULL)
  {
     
    if(strcmp(straversal->status_of_assignment,"submitted")==0)
    {
        printf(" Submission for group with GROUP ID %d already recorded.\n", straversal->group_id);
    }
    else if(strcmp(straversal->status_of_assignment,"evaluated")==0)
    {
         printf("\n Evaluation for group with GROUP ID %d already done.\n", straversal->group_id);
    }
    else 
    {

    printf("\t ENTER THE SUBMISSION DATE IN YEAR-MONTH-DAY FORMAT \n ");
    printf("\t ENTER THE SUBMISSION DATE OF ASSIGNMENT OF THE CORRESPONDING GROUP \t");
    scanf("%s",submission_date);

        if(strcmp(submission_date,straversal->deadline)<=0)
        {
            strcpy(straversal->status_of_assignment,"submitted");
        }
        else
        {
            printf(" Submission for group with GROUP ID %d WAS LATE!.\n", straversal->group_id);
            printf(" Details of that student group \n");
            printf("student 1 of this particular group %s \t",straversal->student_id_1);
            printf("\n student 2 of this particular group %s \t",straversal->student_id_2);
        }
    }
    
   straversal=straversal->next;

  }
  //printing list who have not submitted
  straversal=sptr;
  while(straversal!=NULL)
  {
    if(strcmp(straversal->status_of_assignment,"notsubmitted")==0)
    {
        printf("\n GROUP-ID :- %d \t",straversal->group_id);
    }
    straversal=straversal->next;
  }

}
//question 6
void assign_yet_to_be_evaluated(student_record** student, AssignmentRecords** assignment,HT_AR* HT1)
{
    printf("\n \t \t entered into the question 6 function \n");
    student_record* sptr=*student;
    student_record* shead=*student;
    printf("Groups for whom the assignment is yet-to-be-evaluated:\n");
    while(sptr!=NULL)
    { 
        
        if(sptr->assignment_submitted && !sptr->assignment_evaluated)
        {
            if(!sptr->viva_taken)
            {
                printf("group with ID %d whose assignment is not evaluated and viva not taken \n",sptr->group_id);
            }
            else
            {
                printf("group with ID %d whose assignment is not evaluated but viva was taken \n",sptr->group_id);
            }
        }
        sptr=sptr->next;
    }

}


//question 7
// For a given assignment id, print the details of student-groups, in the decreasing order 
// of marks they have received in the assignment
void print_in_decreasing_order(student_record** student, AssignmentRecords** assignment,HT_AR* HT1)
{
    printf("\n \t \t entered into the question 7 function \n");
    student_record* sptr=*student;
    student_record* strav=sptr;
    AssignmentRecords* aptr=*assignment;
    AssignmentRecords* atrav=aptr;
    Assignment_Node* nptr;
    marks_node* mnode;
    marks_node* mlptr;
    marks_node* mtraverse;
    int trav_g_id;
    marks_node* q=NULL;
    marks_node* p;
    int x;
    int total_marks;
    while(atrav!=NULL)
    {
        nptr=atrav->down;
        while(nptr!=NULL)
        {
            total_marks=nptr->evaluation_marks_of_std1 + nptr->evaluation_marks_of_std2 + nptr->viva_marks_of_std1 + nptr->viva_marks_of_std2;
            mnode=(marks_node*)malloc(sizeof(marks_node));
            mnode->marks=total_marks;
            mnode->corres_g_id=nptr->student_group_id;
            mnode->next=NULL;
            x=total_marks;
           //sorted insert
           if(nptr==atrav->down)
           {
            mlptr=mnode;
           p=mlptr;
           
           }
            else
            {
                while(p && p->marks>x)
                {
                    q=p;
                    p=p->next;
                }
                if(p==mlptr)
                {
                    mnode->next=mlptr;
                    mlptr=mnode;
                    p=mlptr;
                }
                else
                {
                    mnode->next=q->next;
                    q->next=mnode;
                }
            }
            nptr=nptr->next;
        }
      mtraverse=mlptr;
      while(mtraverse!=NULL)
      {
         trav_g_id=mtraverse->corres_g_id;
          strav=sptr;
          while(strav->group_id!=trav_g_id)
          {
            strav=strav->next;
          }
          //strav points the corresponding node
          //print the details 
           printf("ASSIGNMENT ID ID- %d\n",strav->assignment_id);
          printf("GROUP ID- %d\n",strav->group_id);
           printf("STUDENT ID 1- %s\n",strav->student_id_1);
           printf("STUDENT ID 2- %s\n",strav->student_id_2);
         printf("MARKS -%d\n",mtraverse->marks);
        mtraverse=mtraverse->next;
      }
      //after usage delete the marks list linked list
      
      while(mlptr!=NULL)
      {
         mtraverse=mlptr;
        mlptr=mlptr->next;
        free(mtraverse);
      }
     atrav=atrav->next;
    }

}

//Print student groups receiving top marks in each of the assignment given.
//question 8
void group_received_top_marks(student_record** student, AssignmentRecords** assignment,HT_AR* HT1)
{

    printf("\n \t \t entered into the question 8 function \n");
    int i=0;
    int j;
    student_record* sptr=*student;
    student_record* strav=sptr;
    AssignmentRecords* aptr=*assignment;
    AssignmentRecords* atrav=aptr;
    Assignment_Node* nptr;
    marks_node* mnode;
    marks_node* mlptr;
    marks_node* mtraverse;
    int max_g_id;
    int arr[ARR_SIZE];
    marks_node* q=NULL;
    marks_node* p;
    int x;
    int count;
    int total_marks;
    int max_marks=INT_MIN;
    while(atrav!=NULL)
    {
        nptr=atrav->down;
        max_marks=INT_MIN;
        i=0;
        while(nptr!=NULL)
        {
            total_marks=nptr->evaluation_marks_of_std1 + nptr->evaluation_marks_of_std2 + nptr->viva_marks_of_std1 + nptr->viva_marks_of_std2;
           if(total_marks>max_marks)
           {
            max_marks=total_marks;
           max_g_id=nptr->student_group_id;
           i=0;
           arr[0]=max_g_id;
           count=0;
           //arr[i]=max_g_id;
           //i++;
           }
          else if(total_marks==max_marks)
          {
             arr[++i]=max_g_id;
             count=i;
          }
            nptr=nptr->next;
        }
    
    j=0;
    printf("ASSIGNMENT ID -%d\n",atrav->assignment_id);
    while(j<=count)
    {
       
       printf("GROUP - %d \n",arr[j]);
       j++;
    }
     for(int k=0;k<ARR_SIZE;k++)
    {
        arr[k]=0;
    }
     atrav=atrav->next;
    }
}



int main()
{
    HT_AR HT1;
    student_record* head = createSRlist(5);
    AssignmentRecords* ARhead = createARlist(5, &HT1);
    int i;
   int flag=1;
   int flag1=1;
 
int loginStatus = 0;
char passwords[129][15];
char ids[129][15];

for(i = 1; i <= 129; i++) {
    sprintf(passwords[i-1], "BT21CSE%03d", i);//BT21CSE001-BT21CSE129
    sprintf(ids[i-1], "DSPD@E%03d", i);  //FORMAT-DSPD@Elast three digits of username
    
}
char Epasswords[15][15];
char Eids[15][15];

for(i = 1; i <=15; i++) {
    sprintf(Epasswords[i-1], "FVNITCSE%03d", i);//FVNITCSE001-FVNITCSE015
    sprintf(Eids[i-1], "E%03d", i); //Elast three digits of EUsername
    
}

char Username[10], password[15],confirm[15];
char EUsername[10], Epassword[15];
printf("\n Welcome To Assignment Management System\n");
printf(" Login as Student or Teacher?\n");
printf(" If teacher enter T, Else S : ");
scanf("%s",confirm);
if(strcmp(confirm,"S")==0)
{
	printf("\n");
printf(" Log in with Username and password!\n");
printf("\n Enter Your Username: ");
scanf("%s", Username);
printf("\nEnter Your Password: ");
scanf("%s", password);

for(i = 0; i < 129; i++) {
    if(strcmp(Username,passwords[i]) == 0 && strcmp(password, ids[i]) == 0  && flag==1) {
        loginStatus = 1;
        flag=0;
    }
}
}
else if(strcmp(confirm,"T")==0)
{
	printf("Log in with Employeeid and password!\n");
	printf("\nEnter Your Employee ID:\n ");
    scanf("%s", EUsername);
    printf("\nEnter Your Password: ");
    scanf("%s", Epassword);

for(i = 0; i < 15; i++) {
    if(strcmp(EUsername, Epasswords[i]) == 0 && strcmp(Epassword, Eids[i]) == 0 && flag==1) {
        loginStatus = 1;
        flag=0;
    }
}
}
 
if(loginStatus) {
    printf("Login successful!\n");
} else {
    printf("Invalid University ID or password! Please try again.\n");
}



    while(loginStatus == 1) {
        printf("\nLogin Successful\n");
        printf("1. Insert a student record\n");
        printf("2. Insert assignment record\n");
        printf("3. Change status of assignment and student lists\n");
        printf("4. Print the list of assignments that are declared but not evaluated\n");
        printf("5. Print the list student groups who have not submitted the assignments even if the due date is over\n");
        printf("6. Print the list of student groups for whom the assignment is yet-to-be-evaluated even though they have been submitted\n");
        printf("7. Print the details of student-groups for a given assignment id\n");
        printf("8. Print student groups receiving top marks in each of the assignment given\n");
        printf("9. Logout\n");

        int option;
        printf("\nEnter your choice: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                insert_SR(&head,&ARhead,&HT1);
                addsNode(&head,&ARhead,&HT1);
                //insert_AR(&head,&ARhead,&HT1);
                printSR(&head);

                printAR(&ARhead);
                break;
            case 2:
                //insert_SR(&head,&ARhead,&HT1);
               // insertAssignNode(&head,&ARhead,&HT1);
                insert_AR(&head,&ARhead,&HT1);
                insertAssignNode(&head,&ARhead,&HT1);
                printSR(&head);
                printAR(&ARhead);
                
               
                break;
            case 3:
                // insert_SR(&head,&ARhead,&HT1);
                // insert_AR(&head,&ARhead,&HT1);
                submittingAssignments(&head, &ARhead, &HT1);
                change_status_of_assignment(&head, &ARhead, &HT1);

                printSR(&head);
                printAR(&ARhead);
                break;
            case 4:
                // insert_SR(&head,&ARhead,&HT1);
                // insert_AR(&head,&ARhead,&HT1);
                // submittingAssignments(&head, &ARhead, &HT1);
                // change_status_of_assignment(&head, &ARhead, &HT1);

               print_LIST_NOT_evaluated(&head,&ARhead,&HT1);
                break;
            case 5:
                groups_not_submitted(&head, &ARhead, &HT1);
                break;
            case 6:
                assign_yet_to_be_evaluated(&head, &ARhead, &HT1);
                break;
            case 7:
                print_in_decreasing_order(&head, &ARhead, &HT1);
                break;
            case 8:
                group_received_top_marks(&head, &ARhead, &HT1);
                break;
            case 9:
                printf("Successfully logged out\n");
                loginStatus = 0;
                flag1=0;
                break;
            default:
                printf("\n  Invalid input. Please enter a number between 1 and 9.\n");
        }
    }
     
     if(flag1==0)
     {
        printf("Thank you for using the assignment manager!\n");
    }

    return 0;
}
