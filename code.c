#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define INFINITE 1000000000

typedef struct N{
    unsigned int datum;
    int ind;
    struct N*next;
}node;
typedef node* ptr_node;

ptr_node list_creation(void);
ptr_node list_insertion(ptr_node list, unsigned int element, int indice);
void print_list(ptr_node list, int limit);

ptr_node AggiungiGrafo(int num_nodes, ptr_node list, int indice, int dim);
ptr_node TopK(ptr_node matr_list, int k, int length);

int power_10(int exp);

unsigned int Dijkstra(int graph[], int num_nodes);

int main(void){

    int d=0, k;
    int sel=0, i=1000000, j=7, len=0, num=0;
    ptr_node matrix_list;
    
    matrix_list=list_creation();
    
	while(1){
        sel=getchar_unlocked();
        if(sel==32){
            num=num/(power_10(j));
            d=num;
            i=1000000;
            j=7;
            num=0;
        }
        else if(sel==10){
			num=num/(power_10(j));
            k=num;
			break;
        }
        else{
            num=num+((sel-48)*i);
            i=i/10;
            j--;
        }
    }

    // matrix=malloc(d*d*sizeof(int*)); // dynamic matrix allocation
    
    while(1){
        sel=getchar_unlocked(); // chooses which function to call
        if(sel==65){
            for(i=0; i<12; i++){
                getchar_unlocked();
            }
            matrix_list=AggiungiGrafo(d, matrix_list, len, d);
            len++;
        }
        else{
            if(sel==84){
                for(i=0; i<4; i++)
                    getchar_unlocked();
				if(k==0){
					printf("\n");
					continue;
				}
                else
					matrix_list=TopK(matrix_list, k, len);
            }
            else{
				if(sel==-1)
		            return 0;
            }
        }
    }
}

ptr_node list_creation(){
    
    return NULL;
    
}

ptr_node list_insertion(ptr_node list, unsigned int element, int indice){
    
    ptr_node ptr, current;
    current=list;
    
    if(current==NULL || current->datum>=element){
        ptr=(ptr_node)malloc(sizeof(node));
        if(ptr){
            ptr->datum=element;
            ptr->ind=indice;
            ptr->next=current;
            list=ptr;
        }
    }
    else{
        ptr=(ptr_node)malloc(sizeof(node));
        ptr->datum=element;
        ptr->ind=indice;
        ptr->next=NULL;
        while(current->next!=NULL && current->next->datum<ptr->datum)
            current=current->next;
        ptr->next=current->next;
        current->next=ptr;
    }
    return list;
    
}

void print_list(ptr_node list, int limit){
	
	ptr_node ptr;

	for(ptr=list; ptr!=NULL; ptr=ptr->next){
		if(limit==1){
			printf("%d", ptr->ind);
			break;
		}
		else{
			printf("%d ", ptr->ind);
			limit--;
		}
	}
	printf("\n");

}

ptr_node AggiungiGrafo(int num_nodes, ptr_node list, int index, int dim){
    
    int i, j;
    unsigned int sum=0;
    int temp=0, num=0, count=1000000, figures_left=7;
    int matrix[dim*dim];

    /* for(i=0; i<num_nodes; i++){
     for(j=0; j<num_nodes; j++){
     if(j<num_nodes-1)
     fscanf(file_input, "%d,", &matrix[i][j]);
     else
     fscanf(file_input, "%d\n", &matrix[i][j]);
     }
     } */
    
    getchar_unlocked();
    for(i=0; i<num_nodes; i++){
        j=0;
        while(j!=num_nodes){
            temp=getchar_unlocked();
            if(temp==44){
                num=num/(power_10(figures_left));
                matrix[(i*num_nodes)+j]=num;
                j++;
                count=1000000;
                figures_left=7;
                num=0;
            }
            else if(temp!=10){
                num=num+((temp-48)*count);
                count=count/10;
                figures_left--;
            }
            else{
                num=num/(power_10(figures_left));
                matrix[(i*num_nodes)+j]=num;
                j++;
                count=1000000;
                figures_left=7;
                num=0;
            }
        }
    }
    
    sum=Dijkstra(matrix, num_nodes);
    list=list_insertion(list, sum, index);
    return list;
    
}

ptr_node TopK(ptr_node matr_list, int k, int length){
    
    int lim;
    
    if(length==0){
        printf("\n");
        return matr_list;
    }
    
    if(length<k)
        lim=length;
    else
        lim=k;
    print_list(matr_list, lim);

    return matr_list;
    
}

int power_10(int exp){

	int i, res=1;

	for(i=0; i<exp; i++)
		res=res*10;
	return res;

}

unsigned int Dijkstra(int graph[], int num_nodes){
    
    int distance[num_nodes];
    int i, count=0, v, u;
    unsigned int sum=0;
    bool visited[num_nodes]; // visited[i] will be true if vertex i is processed
	int minimum;
    
    for(i=0; i<num_nodes; i++){
        distance[i]=INFINITE;
        visited[i]=false;
    }
    distance[0]=0;
    
    for(i=1; i<num_nodes; i++){
        if(graph[i]!=0)
            break;
        count++;
    }
    if(count==num_nodes-1)
        return 0;
    
    for(count=0; count<num_nodes-1; count++){
		u=0;
		minimum=INFINITE;
		for(v=0; v<num_nodes; v++){
		    if(distance[v]<=minimum && visited[v]==false){
				u=v;
		        minimum=distance[v];
		    }
		}
        visited[u]=true;
        for(v=0; v<num_nodes; v++){
            if(!visited[v] && graph[(u*num_nodes)+v] && distance[u]!=INFINITE && distance[u]+graph[(u*num_nodes)+v]<distance[v])
                distance[v]=distance[u]+graph[(u*num_nodes)+v];
        }
    }
    
    for(i=1;i<num_nodes;i++){
        if(distance[i]==INFINITE)
            continue;
        else 
			sum=sum+distance[i];
    }
    return sum;
    
}
