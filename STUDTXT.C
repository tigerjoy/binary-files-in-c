#include <stdio.h>
#include <conio.h>

typedef struct{
	int roll;
	int p1, p2, p3;
	int avg;
	char g;
}Student;

void input(Student *s){
	printf("Enter your roll(1-100): ");
	scanf("%d", &(s->roll));
	printf("Enter marks in subject 1: ");
	scanf("%d", &(s->p1));
	printf("Enter marks in subject 2: ");
	scanf("%d", &(s->p2));
	printf("Enter marks in subject 3: ");
	scanf("%d", &(s->p3));
}

void calculate(Student *s){
	s->avg = (s->p1 + s->p2 + s->p3) / 3;
	if(s->avg >= 80){
		s->g = 'A';
	}
	else if(s->avg >= 70){
		s->g = 'B';
	}
	else if(s->avg >= 60){
		s->g = 'C';
	}
	else if(s->avg >= 50){
		s->g = 'D';
	}
	else if(s->avg >= 40){
		s->g = 'E';
	}
	else{
		s->g = 'F';
	}
}

void writeRecord(Student *s, char filename[]){
	FILE *fp = fopen(filename, "a");
	fprintf(fp, "%d %d %d %d %d %c", s->roll, 
									 s->p1, 
									 s->p2,
									 s->p3,
									 s->avg,
									 s->g);
	fclose(fp);
}

void displayStudent(Student *s){
	printf("%-5d %-5d %-5d %-5d %-5d %-c\n", s->roll,
									 s->p1,
									 s->p2,
									 s->p3,
									 s->avg,
									 s->g);
}

void displayRecords(char filename[]){
	Student temp;
	long size;
	FILE *fp = fopen(filename, "r");
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);
	printf("\n%-5s %-5s %-5s %-5s %-5s %-5s\n", "ROLL", "SUB1", "SUB2", "SUB3", "AVG", "GRADE");
	while(ftell(fp) < size){
		//printf("Entered loop");
		fscanf(fp, "%d %d %d %d %d %c", &temp.roll, &temp.p1, &temp.p2, &temp.p3, &temp.avg, &temp.g);
		displayStudent(&temp);
	}
	fclose(fp);
}

int main(){
	char dbfile[1024];
	int choice;
	Student temp;
	clrscr();
	printf("Enter the name of the record file: ");
	gets(dbfile);
	do{
		printf("\nPress 1 to insert a record\n");
		printf("Press 2 to display all records\n");
		printf("Press 3 to exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch(choice){
			case 1:	
				input(&temp);
				calculate(&temp);
				writeRecord(&temp, dbfile);
				break;
			case 2:
				displayRecords(dbfile);
				break;
			case 3:
				break;
			default:
				printf("Invalid choice!");
		}
	}while(choice != 3);
	return 0;
}