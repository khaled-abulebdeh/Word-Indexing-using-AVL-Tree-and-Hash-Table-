#include <stdio.h>
#include <stdlib.h>
#define wordSize 30
#define tableSize 59
//Khaled Abu Lebdeh
// 1220187
// Section 3
typedef struct node* TNode;
typedef struct NODE* HashNode;//Hash node
struct NODE {
    char word [wordSize];
    int frequency;
    HashNode next;
};
struct node {
    char word [wordSize];
    TNode right;
    TNode left;
    int height;
    int frequency;
};

//AVL Tree Functions
TNode createTNode();
TNode makeEmpty (TNode T);
TNode findTNode (char str [wordSize], TNode T);
TNode findMin (TNode T);
TNode findMax (TNode T);
TNode insertToAVL (char str [wordSize], TNode T);
TNode deleteFromAVL (char str [wordSize], TNode T);
TNode RSR (TNode T); // Right Single Rotation
TNode LSR (TNode T); // left Single Rotation
TNode LRDR (TNode T); // Left Right Double Rotation
TNode RLDR (TNode T); // Right Left Double Rotation
int maxHeight (int rightHeight, int leftHeight);
int getHeight (TNode T);//to avoid trying to access null nodes
TNode createAVL (char loadedText [200*wordSize]);
void printInOrder (TNode T);
void printPreOrder (TNode T);

//Hash Functions
HashNode createHashNode ();
HashNode findHashedWord (char str[wordSize], HashNode HN);
HashNode findPrevWord (char str[wordSize], HashNode HN);
HashNode findLast (HashNode HN);
void insertFirst (char str[wordSize],int freq, HashNode HN);
void deleteFromList (char str[wordSize], HashNode HN);
void deleteTable(HashNode HTable [tableSize]);
int findhashedIndex (char str[wordSize]);
void createHashTable (TNode T,HashNode HTable [tableSize]);
void AVLtoHash (TNode T, HashNode HTable [tableSize]);
void userInsertionToTable (char str [wordSize], HashNode HTable [tableSize]);
void userDeletionFromTable (char str [wordSize], HashNode HTable [tableSize]);
void userSearhFromTable (char str [wordSize], HashNode HTable [tableSize]);
int isLastWord (HashNode myNode, HashNode HN);
void printHashTable (HashNode HTable [tableSize]);
int uniqueWords (HashNode HTable [tableSize]);
int numMostFreq (HashNode HTable [tableSize]);
void printMostFreq (HashNode HTable [tableSize]);
void displayStatistics (HashNode HTable [tableSize]);
void printRepeated (HashNode HTable [tableSize]);
//other functions
void loadFile (char loadedText [200*wordSize]);
void myMenu ();
void printLinkedList (HashNode HN);
void clearSpecialChar (char str []);
int main()
{

    myMenu();

    return 0;
}
void myMenu (){

    char loadedText [200*wordSize]="";
    char newWord [wordSize]="";
    TNode T=NULL;
    HashNode HTable [tableSize] = {NULL};

    int myChoice=-1;
    do {
        printf("\n------------My menu------------\n");
        printf("Enter Your Choice!\n");
        printf("1-Load data from the file.\n");
        printf ("2-Create the AVL tree.\n");
        printf ("3-Insert a word to the AVL tree.\n");
        printf ("4-Delete a word from the AVL tree.\n");
        printf ("5-Print the words as sorted in the AVL tree\n");
        printf ("6-Create the Hash Table\n");
        printf ("7-Insert a word to the Hash table\n");
        printf ("8-Delete a word from the hash table\n");
        printf ("9-Search for a word in the hash table and print its frequency.\n");
        printf ("10-Print words statistics.\n");
        printf ("11-Exit the application\n");
        printf("---------------------------------\n");


        scanf("%d", &myChoice);
        getchar();//the user will have time to write the string
        switch(myChoice){
        case 1:loadFile(loadedText);
        break;

        case 2: T= createAVL(loadedText);
        break;

        case 3:printf("Enter Your Word: ");
            gets(newWord);
            clearSpecialChar(newWord);
            T=insertToAVL(newWord, T);
        break;

        case 4:printf("Enter Your Word: ");
            gets(newWord);
            clearSpecialChar(newWord);
            T=deleteFromAVL(newWord, T);
        break;

        case 5:printf("\nIn Order: \n");
        printInOrder(T);
        break;

        case 6:createHashTable(T,HTable);
        break;

        case 7:printf("Enter Your Word: ");
            gets(newWord);
            clearSpecialChar(newWord);
            userInsertionToTable(newWord, HTable);
        break;

        case 8:printf("Enter Your Word: ");
            gets(newWord);
            clearSpecialChar(newWord);
            userDeletionFromTable(newWord, HTable);
        break;
        case 9:printf("Enter Your Word: ");
            gets(newWord);
            clearSpecialChar(newWord);
            userSearhFromTable(newWord, HTable);
        break;
        case 10:displayStatistics(HTable);
        break;
        case 11:makeEmpty(T);
        printf("Tree was freed..\n");
        deleteTable(HTable);
        break;

        //otherwise
        default: printf("Sorry, you may entered a wrong number, Try again\n");
        break;

        }
    }
    while (myChoice!=11);
    printf("You are Welcome to use our program later\n");
}
TNode createTNode (){
    TNode T= (TNode) malloc (sizeof(struct node));
    if (T==NULL){
        printf("OUT OF MEMORY..!!\n");
        exit (0);
    }
    T->left= T->right= NULL;
    T->word[0]= '\0'; // ensure my string does not have trash value
    T->frequency =1;//
    T->height=0;
    return T;
}
TNode makeEmpty (TNode T){
    if (T!=NULL){
        makeEmpty(T->left);
        makeEmpty(T->right);
        free(T);
    }
    return NULL;
}
TNode createAVL (char loadedText [200*wordSize]){
    TNode T= NULL;
    T= makeEmpty(T);

    char *p= strtok(loadedText, " ");

    while (p!=NULL){

        T= insertToAVL(p, T);

        p=strtok(NULL," ");//NULL is set where " " is found
    }
    return T;
}
TNode findTNode (char str [wordSize], TNode T){
    if (T==NULL){
        return NULL;//not found
    }
    else if (strcmpi(str,T->word)<0){ // str < T->word
        return findTNode (str,T->left);
    }
    else if (strcmpi(str,T->word)>0){ // str > T->word
        return findTNode (str,T->right);
    }
    else
        return T;// word node is found
}
TNode findMin (TNode T){
    if (T==NULL){
        return NULL;
    }
    if (T->left!=NULL){
        return findMin(T->left);
    }
    else
        return T;// word node is found
}
TNode findMax (TNode T){
    if (T==NULL){
        return NULL;
    }
    if (T->right!=NULL){
        return findMin(T->right);
    }
    else
        return T;// word node is found
}
TNode RSR (TNode T){
    TNode newRoot= T->left;
    T->left= newRoot->right;
    newRoot->right= T;

    T->height= maxHeight(getHeight(T->left), getHeight(T->right))+1;
    newRoot->height= maxHeight(getHeight(newRoot->left), getHeight(newRoot->right))+1;
    return newRoot;
}
TNode LSR (TNode T){
    TNode newRoot= T->right;
    T->right= newRoot->left;
    newRoot->left= T;

    T->height= maxHeight(getHeight(T->left), getHeight(T->right))+1;
    newRoot->height= maxHeight(getHeight(newRoot->left), getHeight(newRoot->right))+1;
    return newRoot;
}
TNode LRDR (TNode T){
    T->left= LSR(T->left);
    T= RSR (T);
    return T;
}
TNode RLDR (TNode T){
    T->right= RSR (T->right);
    T= LSR(T);
    return T;
}
TNode deleteFromAVL (char str [wordSize], TNode T){
    if (T==NULL){
        printf("Sorry, word is not existed..!\n");
        return NULL;//element not found
    }
    else if (strcmpi(str,T->word)>0){ // str > T->word

        T->right= deleteFromAVL (str, T->right);
    }
    else if (strcmpi(str,T->word)<0){ // str < T->word

        T->left= deleteFromAVL (str, T->left);
    }
    else {  //element found to delete

        if (T->frequency>1){
            T->frequency--;//delete one repetition of the word
        }
        else {

            if (T->left!=NULL && T->right!=NULL){//has two children
                TNode minInRight= findMin(T->right);
                strcpy(T->word, minInRight->word);
                T->right= deleteFromAVL(minInRight->word, T->right);
            }
            else {// has 0 or 1 child
                TNode temp= T;
                if (T->right==NULL)
                    T= T->left;
                else if (T->left==NULL)
                    T= T->right;

                free(temp);
            }
        }
    }
    //for checking balance, and make needed rotations
    if (T!=NULL){//to avoid errors when deleting node with no children

        //the deletion on right, then # in left is larger if there is an error
        if (getHeight(T->left)-getHeight(T->right)==2){
            //case 1: RSR
            if (T->left->left!=NULL){
                T= RSR(T);//it is easier to do single than double if both are allowed
            }
            else if (T->left->right==NULL){
                T= RSR(T);//it has a left child having no child, also single rotation
            }
                //case 2: LRDR
            else {
                T= LRDR(T);
            }
        }

        //the deletion on left, then # in right is larger if there is an error
        else if (getHeight(T->left)-getHeight(T->right)== -2){

            //case 3: LSR
            if (T->right->right!=NULL){
                T= LSR(T);//it is easier to do single than double if both are allowed
            }
            else if (T->right->left==NULL){
                T= LSR(T);//it has a right child having no child, also single rotation
            }
            //case 4: RLDR
            else {
                T= RLDR(T);
            }
        }
    }

    if (T!=NULL){//element having 0 child, will be freed(NULL) after deletion
        T->height= maxHeight(getHeight(T->left), getHeight(T->right))+1;
    }
    return T;
}
int getHeight (TNode T){//to avoid trying to access null nodes
    if (T==NULL){
        return -1;
        /* we return -1, not 0, in order to use T->height= max(leftHeight, RightHeight)+1;
        if we let it zero, node with 0 child will have height 1
        */
    }
    else
        return T->height;
}
int maxHeight (int rightHeight, int leftHeight){
    if (rightHeight>leftHeight)
        return rightHeight;
    else
        return leftHeight;
}
void printInOrder (TNode T){
    if (T!=NULL){
        printInOrder(T->left);
        printf("%20s --- *%-5d\n", T->word, T->frequency);
        printInOrder(T->right);
    }
}
TNode insertToAVL (char str [wordSize], TNode T){
    if (T==NULL){// correct position is found
        //creating the node to insert it
        T= createTNode();
        strcpy(T->word, str);
    }
    else if (strcmpi(str,T->word)<0){ // str < T->word

        T->left= insertToAVL (str,T->left);
        if (getHeight(T->left)- getHeight(T->right)== +2){
            //case 1: LSR:
            if (strcmpi(str,T->left->word)<0){
                T= RSR (T);
            }
            //case 2: LRDR:
            else {
                T= LRDR(T);
            }
        }
    }
    else if (strcmpi(str,T->word)>0){ // str > T->word

        T->right= insertToAVL (str,T->right);
        if (getHeight(T->left)- getHeight(T->right)== -2){
            //case 3: LSR:
            if (strcmpi(str,T->right->word)>0){
                T= LSR (T);
            }
            //case 4: RLDR
            else {
                T= RLDR(T);
            }
        }

    }
    else {//repeated word
        T->frequency++;
    }

    T->height= maxHeight(getHeight(T->left), getHeight(T->right)) +1 ;// +1 for the Node's edge that connects the right and the left

    return T;
}
void AVLtoHash (TNode T, HashNode HTable [tableSize]){
    if (T!=NULL){
        //left
        AVLtoHash (T->left,HTable);

        //operation
        int index= findhashedIndex(T->word);
        //no need to check if word is already inserted to HTable, since there are no repeated nodes in the AVL (just frequency)
        insertFirst(T->word,T->frequency,HTable[index]);

        //right
        AVLtoHash(T->right, HTable);

    }
}
void deleteTable(HashNode HTable [tableSize]){
    if (HTable==NULL||HTable[0]==NULL){
        return ;
    }

    for (int i=0;i<tableSize; i++){
        //delete linked list in index i
        HashNode temp= HTable[i]->next;
        while (temp!=NULL){
            HTable[i]->next= temp->next;
            free (temp);
            temp= HTable[i]->next;
        }
        free(HTable[i]);
    }
    free (HTable);
    printf("Table wad deleted.\n");
}
HashNode createHashNode (){
    HashNode HN= (HashNode) malloc (sizeof(struct NODE));
    if (HN==NULL){
        printf("OUT OF MEMORY..!!\n");
        exit (0);
    }
    HN->word[0]='\0';
    HN->next=NULL;
    HN->frequency =1;//
    return HN;
}
HashNode findHashedWord (char str[wordSize], HashNode HN){
    if (HN==NULL){
        return NULL;
    }
    HashNode temp= HN->next;
    while(temp!=NULL){
        if (strcmpi(str,temp->word)==0){
            return temp;
        }
        temp= temp->next;
    }
    return NULL;//not found
}
HashNode findPrevWord (char str[wordSize], HashNode HN){
    if (HN==NULL){
        return NULL;
    }
    HashNode p= HN;
    while (p->next!=NULL){
        if (strcmpi(str,p->next->word)==0){
            return p;
        }
        p=p->next;
    }
    return p;//returns the last node if word is not existed
}
int isLastWord (HashNode myNode, HashNode HN){
    return myNode->next==NULL;
}
HashNode findLast (HashNode HN){
    if (HN==NULL){
        return NULL;
    }
    HashNode temp= HN;
    while (temp->next!=NULL){
        temp=temp->next;
    }
    return temp;
}
void insertFirst (char str[wordSize],int freq, HashNode HN){
        if (HN!=NULL){
            HashNode newNode= createHashNode();
            strcpy(newNode->word, str);
            newNode->frequency=freq;
            newNode->next= HN->next;
            HN->next= newNode;
        }
}
void userInsertionToTable (char str [wordSize], HashNode HTable [tableSize]){
    if (HTable[0] == NULL){// we initialize all indexes together, if 0 NULL, there are ale NULL
        printf("Sorry, create Hash Table first..\n");
    }
    else {
        int index= findhashedIndex(str);
        HashNode existed = findHashedWord(str,HTable[index]);
        if (existed!=NULL){//the element is already inserted
            (existed->frequency)++;//increment counter (frequency)
        }
        else {
            insertFirst(str,1,HTable[index]);
        }

    }
}
void deleteFromList (char str[wordSize], HashNode HN){
    HashNode prev= findPrevWord (str, HN);
    if (!isLastWord(prev, HN)){
        HashNode temp= prev->next;
        prev->next= temp->next;
        free(temp);
    }
}
void userDeletionFromTable (char str [wordSize], HashNode HTable [tableSize]){
    if (HTable[0] == NULL){// we initialize all indexes together, if 0 NULL, there are ale NULL
        printf("Sorry, create Hash Table first..\n");
    }
    else {
        int index= findhashedIndex(str);
        HashNode existed= findHashedWord(str,HTable[index]);
        if (existed==NULL){
            printf("Sorry, word is not existed..!\n");
        }
        else if (existed->frequency>1){//repeated
            existed->frequency--;
        }
        else {
            deleteFromList(str,HTable[index]);//ferq=1
        }
    }
}
void userSearhFromTable (char str [wordSize], HashNode HTable [tableSize]){
    if (HTable==NULL || HTable[0]==NULL){
        printf("Sorry, the Hash Table was not created!\n");
        return;
    }
    int index= findhashedIndex(str);
    HashNode myNode= findHashedWord(str, HTable[index]);
    if (myNode==NULL){
        printf("Sorry, word is not existed!\n");
    }
    else {
        printf ("word: %s || frequency: %d\n", myNode->word, myNode->frequency);
    }
}
int findhashedIndex (char str[wordSize]){
    int lettersSum=0;
    int length= strlen(str);
    for (int i=0; i<length; i++){
        lettersSum += (  ((int)tolower(str[i]))* pow (32, i) )  ;
    }
    return lettersSum%tableSize;/// see hard copy notes
}
void createHashTable (TNode T,HashNode HTable [tableSize]){

    //create the Hash Table Array
    for (int i=0; i<tableSize; i++){
        HTable[i]= createHashNode();
        HTable[i]->next=NULL;
        HTable[i]->frequency=0;
    }
    printf("Hash Table was created successfully..\n");

    AVLtoHash (T, HTable);//insert words in AVL to HTable
    if (T!=NULL){
        printf("Data Stored in AVL are in the Hash Table Now\n");
    }

}
void printHashTable (HashNode HTable [tableSize]){
    if (HTable ==NULL || HTable[0]==NULL){
        return;
    }
    for (int i=0; i<tableSize; i++){
        if (HTable[i]->next!=NULL){
            printLinkedList(HTable[i]);

        }
    }
}
void displayStatistics (HashNode HTable [tableSize]){
    if (HTable ==NULL || HTable[0]==NULL){
        printf("Sorry, the Hash Table was not created!\n");
        return;
    }
    printf("-------Hash Table-------\n");
    printHashTable(HTable);
    printf("------------------------\n");
    printf("# of unique words: %d\n", uniqueWords(HTable));
    printf("------------------------\n");
    printf("Most Frequent word/s: ");
    printMostFreq(HTable);
    printf("\n------------------------\n");
    printRepeated(HTable);
    printf("\n------------------------\n");



}
void printRepeated (HashNode HTable [tableSize]){
    int counter=0;
    printf("Enter a frequency , to print all words have a larger frequency: \n");
    scanf("%d", &counter);
    HashNode temp;
    for (int i=0; i<tableSize; i++){
        if (HTable[i]!=NULL && HTable[i]->next!=NULL){
            temp= HTable[i]->next;
            while (temp!=NULL){
                if (temp->frequency>counter){
                    printf(" %s ||", temp->word);
                }
                temp=temp->next;
            }
        }
    }
    temp=NULL;
    free (temp);
}
int uniqueWords (HashNode HTable [tableSize]){
    //we suppose HTable is surely created
    int counter=0;
    HashNode temp;
    for (int i=0; i<tableSize; i++){
        if (HTable[i]!=NULL && HTable[i]->next!=NULL){
            temp= HTable[i]->next;
            while (temp!=NULL){
                if (temp->frequency==1){
                    counter++;
                }
                temp=temp->next;
            }
        }
    }
    temp=NULL;
    free (temp);
    return counter;
}
int numMostFreq (HashNode HTable [tableSize]){
    //we suppose HTable is surely created
    int counter=-1;
    HashNode temp;
    for (int i=0; i<tableSize; i++){
        if (HTable[i]!=NULL && HTable[i]->next!=NULL){
            temp= HTable[i]->next;
            while (temp!=NULL){
                if (temp->frequency>counter){
                    counter= temp->frequency;
                }
                temp=temp->next;
            }
        }
    }
    temp=NULL;
    free (temp);
    return counter;

}
void printMostFreq (HashNode HTable [tableSize]){
    int counter= numMostFreq(HTable);
    HashNode temp;
    for (int i=0; i<tableSize; i++){
        if (HTable[i]!=NULL && HTable[i]->next!=NULL){
            temp= HTable[i]->next;
            while (temp!=NULL){
                if (temp->frequency==counter){
                    printf(" %s ||", temp->word);
                }
                temp=temp->next;
            }
        }
    }
    temp=NULL;
    free (temp);

}
void clearSpecialChar (char str []){
    int length= strlen(str);
    int counter=0;
    char newWord [wordSize]="";
    //to delete special char in the str entered
    for (int i=0; i<length; i++){

        if ((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z')){
            newWord[counter++]= str[i];
        }
    }
    strcpy (str, newWord);

}
void printLinkedList (HashNode HN){
    if (HN==NULL){
        printf("NULL line \n");
    }
    HashNode temp= HN->next;
    while (temp !=NULL){
        printf("...%-s (*%d)...\n", temp->word,temp->frequency);
        temp=temp->next;
    }
}
void loadFile (char loadedText [200*wordSize] ){

    char temp[200*wordSize]= "";
    FILE* input;
    input= fopen("input.txt", "r");
    char scannedLine [30*wordSize]="";


    char *valid= fgets(scannedLine,sizeof(scannedLine),input);//Valid is pointing on the line stored

    if (strlen(scannedLine)==0){
        printf("Sorry, the file has no words..!!\n");
        return;
    }

    while (valid!= NULL) {//as long as lines are not over
        int validsLength= strlen(valid);
        if (valid[validsLength-1]=='\n'){
            valid[validsLength-1]=' ';
        }
        strcat(temp, scannedLine);
        valid= fgets(scannedLine,sizeof(scannedLine),input);//for the next line
    }
    int length=strlen(temp);
    int counter=0;
    for (int i=0; i<length; i++){
        if ((temp[i]>='a'&&temp[i]<='z')||(temp[i]>='A'&&temp[i]<='Z')||(temp[i]==' ')){
            loadedText[counter++]= temp[i];
        }
        else {
            loadedText[counter++]= ' ';
        }

    }
    loadedText[counter+1]='\0';//ensure there is null char after my string

    fclose(input);
    printf("\nData was loaded from input file..\n");
}



